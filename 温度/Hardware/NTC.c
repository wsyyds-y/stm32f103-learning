#include "stm32f10x.h"
#include "NTC.h"
#include <math.h>

/**
  ******************************************************************************
  * @file    NTC.c
  * @brief   NTC 热敏电阻 + LM393 模块驱动：ADC 读 AO 算温度，GPIO 读 DO 报警
  *
  * 模块电路（常见廉价温度模块）：
  *   3.3V ── R1(10k) ──┬── AO
  *                     └── NTC(10k, B=3950) ── GND
  *   AO 同时接到 LM393 的一端，另一端由蓝色电位器给出阈值，比较结果从 DO 输出。
  * 所以温度升高 -> NTC 阻值变小 -> AO 电压变低；DO 在超过阈值时翻转（通常为低）。
  *
  * 下面的宏是本文件唯一的“标定入口”，换模块/换分压只改这里。
  ******************************************************************************
  */

/* AO 接的 ADC 通道与引脚 */
#define NTC_ADC                 ADC1
#define NTC_ADC_CHANNEL         ADC_Channel_0
#define NTC_GPIO_PORT           GPIOA
#define NTC_GPIO_PIN            GPIO_Pin_0
#define NTC_GPIO_CLK            RCC_APB2Periph_GPIOA

/* DO 接的普通 GPIO（比较器输出） */
#define NTC_DO_PORT             GPIOB
#define NTC_DO_PIN              GPIO_Pin_13
#define NTC_DO_CLK              RCC_APB2Periph_GPIOB
#define NTC_DO_ACTIVE_LOW       1       /* 1=DO 为低时表示超温（LM393 常见），0=反相 */

/* 分压与 NTC 参数：NTC(10k, B=3950) 在下臂，上臂串联电阻按实物标定。
 * 标定依据：本板实测 AO = 2.1V，室温约 20℃ 时 NTC ≈ 12.1kΩ，
 *           反推 Rs = Rt×(3.3-V)/V ≈ 6.9kΩ（不是常见的 10k，所以默认模型会读成 13℃）。
 * 如果你的室温实测不是 20℃，按 Rs = Rt×(3.3-V)/V 重算：
 *   25℃ → Rt=10kΩ → Rs≈5.7kΩ；18℃ → Rt=12.9kΩ → Rs≈7.4kΩ。 */
#define NTC_VREF                3.3f    /* ADC 参考电压 = 板子 3.3V */
#define NTC_ADC_MAX             4095.0f /* 12 位 ADC 满量程 */
#define NTC_R_SERIES            6900.0f /* 与 NTC 串联的固定电阻（本板实测标定，见下方说明） */
#define NTC_R0                  10000.0f/* NTC 在 25℃ 时的阻值 */
#define NTC_T0_K                298.15f /* 25℃ 对应的开尔文温度 */
#define NTC_B                   3950.0f /* NTC 的 B 值（常见 3435 / 3950） */
#define NTC_LOW_SIDE            1       /* 1=NTC 接 GND（温度升高 AO 电压降低） */

/* 初始化：PA0 模拟输入 + ADC1 单次转换 + 校准；PB13 上拉输入读 DO。 */
void NTC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    uint32_t wait;

    RCC_APB2PeriphClockCmd(NTC_GPIO_CLK | NTC_DO_CLK | RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);       /* ADC 时钟 72/6 = 12MHz，不超过 14MHz */

    GPIO_InitStructure.GPIO_Pin = NTC_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   /* 模拟输入，ADC 专用 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NTC_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = NTC_DO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   /* 上拉输入，兼容开漏输出 */
    GPIO_Init(NTC_DO_PORT, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   /* 单通道，不扫描 */
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; /* 单次转换，由软件启动 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(NTC_ADC, &ADC_InitStructure);

    ADC_RegularChannelConfig(NTC_ADC, NTC_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

    ADC_Cmd(NTC_ADC, ENABLE);

    /* 上电先校准，否则码值有固定偏差。
     * 等待循环都加了超时计数：万一 ADC 时钟没配对，也不会把整个程序卡死在这里。 */
    ADC_ResetCalibration(NTC_ADC);
    wait = 0;
    while (ADC_GetResetCalibrationStatus(NTC_ADC) && (++wait < 200000));

    ADC_StartCalibration(NTC_ADC);
    wait = 0;
    while (ADC_GetCalibrationStatus(NTC_ADC) && (++wait < 200000));
}

/* 单次转换：软件触发 -> 等 EOC -> 读 DR。
 * 同样带超时，转换一直不结束就返回当前寄存器值（宁可显示偏一点，也不卡死主循环）。 */
uint16_t NTC_ReadAdc(void)
{
    uint32_t wait = 0;

    ADC_SoftwareStartConvCmd(NTC_ADC, ENABLE);
    while ((ADC_GetFlagStatus(NTC_ADC, ADC_FLAG_EOC) == RESET) && (++wait < 200000));
    return ADC_GetConversionValue(NTC_ADC);
}

/* ADC 码值 -> 电压 -> NTC 阻值 -> B 值公式 -> ℃ -> 0.1℃。
 * 数学上：Rt = Rs * V/(Vref-V)（NTC 在下臂），T = 1/(1/T0 + ln(Rt/R0)/B) - 273.15 */
int16_t NTC_AdcToTempX10(uint16_t adc)
{
    float vout;
    float rt;
    float temp_c;
    int32_t temp_x10;

    vout = (float)adc / NTC_ADC_MAX * NTC_VREF;

    /* 电压贴边时阻值会算成 0 或无穷，直接钳住，避免 logf() 出 NaN */
    if (vout < 0.02f) vout = 0.02f;
    if (vout > NTC_VREF - 0.02f) vout = NTC_VREF - 0.02f;

#if NTC_LOW_SIDE
    rt = NTC_R_SERIES * vout / (NTC_VREF - vout);
#else
    rt = NTC_R_SERIES * (NTC_VREF - vout) / vout;
#endif

    if (rt < 50.0f) rt = 50.0f;             /* 对应约 150℃，超出量程 */
    if (rt > 2000000.0f) rt = 2000000.0f;   /* 对应约 -40℃，防止 ln 溢出 */

    temp_c = 1.0f / (1.0f / NTC_T0_K + logf(rt / NTC_R0) / NTC_B) - 273.15f;
    temp_x10 = (int32_t)(temp_c * 10.0f + (temp_c >= 0 ? 0.5f : -0.5f));

    if (temp_x10 > 1250) temp_x10 = 1250;
    if (temp_x10 < -550) temp_x10 = -550;

    return (int16_t)temp_x10;
}

/* 读 DO：按 NTC_DO_ACTIVE_LOW 的设定把电平翻译成“是否超温”。 */
uint8_t NTC_IsAlarm(void)
{
    uint8_t level = GPIO_ReadInputDataBit(NTC_DO_PORT, NTC_DO_PIN);

#if NTC_DO_ACTIVE_LOW
    return (level == 0) ? 1 : 0;
#else
    return (level == 0) ? 0 : 1;
#endif
}
