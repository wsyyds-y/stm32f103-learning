#include "stm32f10x.h"
#include "NTC.h"
#include <math.h>

/**
  ******************************************************************************
  * @file    NTC.c
  * @brief   NTC 热敏电阻分压测温（AO -> PA0 -> ADC1_IN0）
  *
  * 电路（NTC_LOW_SIDE = 1，默认）：
  *   3.3V ── Rs ──┬── AO
  *                └── NTC ── GND
  *   温度升高 -> NTC 阻值变小 -> AO 电压变低
  *
  * 计算链：ADC 码值 -> AO 电压 -> NTC 阻值 Rt -> B 值公式 -> ℃
  *   下臂：Rt = Rs * V / (Vref - V)
  *   上臂：Rt = Rs * (Vref - V) / V
  *   温度：T = 1 / (1/T0 + ln(Rt/R0)/B) - 273.15
  *
  * 标定入口只有下面这些宏。默认值取最常见的「10k NTC + 10k 上拉」，
  * 如果你量到的 Rt 和万用表对得上、温度却差几度，先改 NTC_OFFSET_X10；
  * 若整条曲线的斜率都不对，再调 NTC_B（3950 / 3435 最常见）。
  ******************************************************************************
  */

/* AO 接的 ADC 通道与引脚 */
#define NTC_ADC                 ADC1
#define NTC_ADC_CHANNEL         ADC_Channel_0
#define NTC_GPIO_PORT           GPIOA
#define NTC_GPIO_PIN            GPIO_Pin_0
#define NTC_GPIO_CLK            RCC_APB2Periph_GPIOA

/* 分压与 NTC 参数：换模块/换电阻只改这一段 */
#define NTC_VREF                3.3f     /* ADC 参考电压 = 板子 3.3V */
#define NTC_ADC_MAX             4095.0f  /* 12 位 ADC 满量程 */
#define NTC_R_SERIES            10000.0f /* 与 NTC 串联的固定电阻，常见 10k */
#define NTC_R0                  10000.0f /* NTC 在 25℃ 时的阻值 */
#define NTC_T0_K                298.15f  /* 25℃ 对应的开尔文温度 */
#define NTC_B                   3950.0f  /* NTC 的 B 值（常见 3435 / 3950） */
#define NTC_LOW_SIDE            1        /* 1=NTC 接 GND（温度升高 AO 降低） */
#define NTC_OFFSET_X10          0        /* 单点修正，单位 0.1℃；读数高了 2.3℃ 就写 -23 */

/* 初始化：PA0 模拟输入 + ADC1 单次转换 + 校准。
 * 等待循环都带超时计数：万一 ADC 时钟没配对，也不会把整个程序卡死在这里。 */
void NTC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    uint32_t wait;

    RCC_APB2PeriphClockCmd(NTC_GPIO_CLK | RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);       /* ADC 时钟 72/6 = 12MHz，不超过 14MHz */

    GPIO_InitStructure.GPIO_Pin = NTC_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   /* 模拟输入，ADC 专用 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NTC_GPIO_PORT, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       /* 单通道，不扫描 */
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; /* 单次转换，软件触发 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(NTC_ADC, &ADC_InitStructure);

    ADC_RegularChannelConfig(NTC_ADC, NTC_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
    ADC_Cmd(NTC_ADC, ENABLE);

    /* 上电先校准，否则码值有固定偏差 */
    ADC_ResetCalibration(NTC_ADC);
    wait = 0;
    while (ADC_GetResetCalibrationStatus(NTC_ADC) && (++wait < 200000));

    ADC_StartCalibration(NTC_ADC);
    wait = 0;
    while (ADC_GetCalibrationStatus(NTC_ADC) && (++wait < 200000));
}

/* 单次转换：软件启动 -> 等 EOC -> 读 DR。
 * 转换一直不结束就返回寄存器当前值，宁可读数偏一点也不卡死主循环。 */
uint16_t NTC_ReadAdc(void)
{
    uint32_t wait = 0;

    ADC_SoftwareStartConvCmd(NTC_ADC, ENABLE);
    while ((ADC_GetFlagStatus(NTC_ADC, ADC_FLAG_EOC) == RESET) && (++wait < 200000));
    return ADC_GetConversionValue(NTC_ADC);
}

/* 连续转换取平均：单次采样末位常有 ±2 的跳动，8 次平均后显示稳。
 * 用 uint32_t 累加，255 次也不会溢出。 */
uint16_t NTC_ReadAdcAve(uint8_t times)
{
    uint32_t sum = 0;
    uint8_t i;

    if (times == 0)
    {
        times = 1;
    }
    for (i = 0; i < times; i++)
    {
        sum += NTC_ReadAdc();
    }
    return (uint16_t)(sum / times);
}

/* ADC 码值换算成 mV：adc/4095*3.3V。用整数算，避免显示时引入浮点。 */
uint16_t NTC_AdcToMv(uint16_t adc)
{
    return (uint16_t)((uint32_t)adc * 3300 / 4095);
}

/* ADC 码值 -> NTC 阻值（Ω，取整）。
 * 先钳住贴边的电压：算出 0Ω 或无穷大后再往下传，logf() 会出 NaN。 */
uint32_t NTC_AdcToOhm(uint16_t adc)
{
    float vout;
    float rt;

    vout = (float)adc / NTC_ADC_MAX * NTC_VREF;

    if (vout < 0.02f) vout = 0.02f;
    if (vout > NTC_VREF - 0.02f) vout = NTC_VREF - 0.02f;

#if NTC_LOW_SIDE
    rt = NTC_R_SERIES * vout / (NTC_VREF - vout);
#else
    rt = NTC_R_SERIES * (NTC_VREF - vout) / vout;
#endif

    if (rt < 10.0f) rt = 10.0f;
    if (rt > 2000000.0f) rt = 2000000.0f;

    return (uint32_t)(rt + 0.5f);
}

/* 阻值 -> 温度（0.1℃ 定点）。B 值公式：
 *   1/T = 1/T0 + ln(Rt/R0)/B
 * 结果钳在 -40~125℃，超出范围按边界显示，不输出乱值。 */
int16_t NTC_AdcToTempX10(uint16_t adc)
{
    float rt;
    float temp_c;
    int32_t temp_x10;

    rt = (float)NTC_AdcToOhm(adc);

    temp_c = 1.0f / (1.0f / NTC_T0_K + logf(rt / NTC_R0) / NTC_B) - 273.15f
             + (float)NTC_OFFSET_X10 / 10.0f;

    temp_x10 = (int32_t)(temp_c * 10.0f + (temp_c >= 0 ? 0.5f : -0.5f));

    if (temp_x10 > 1250) temp_x10 = 1250;
    if (temp_x10 < -400) temp_x10 = -400;

    return (int16_t)temp_x10;
}

/* 把本文件的标定修正量报给上层显示，省得 main.c 再抄一遍常量。 */
int16_t NTC_GetOffsetX10(void)
{
    return (int16_t)NTC_OFFSET_X10;
}
