#include "stm32f10x.h"
#include "NTC.h"
#include <math.h>

/**
  * NTC 测温，四步走：
  *   码值 → 电压 → 热敏阻值 → 温度
  *
  * 电路：3.3V ── 10k ──┬── PA0
  *                     └── NTC ── GND
  *   温度升高 → NTC 阻值变小 → PA0 电压变低
  *
  * 换电阻/换 NTC 只改下面这几个数：
  */
#define NTC_VREF        3.3f      /* ADC 参考电压 = 板子 3.3V */
#define ADC_MAX         4095.0f   /* 12 位 ADC 满量程 */
#define NTC_R_SERIES    10000.0f  /* 与 NTC 串联的 10k */
#define NTC_R0          10000.0f  /* NTC 在 25℃ 时是 10k */
#define NTC_T0_K        298.15f   /* 25℃ 的绝对温度 = 273.15 + 25 */
#define NTC_B           3950.0f   /* NTC 的 B 值 */

/* ① 码值 → 电压：adc/4095 × 3.3V */
static float AdcToVolt(uint16_t adc)
{
    return (float)adc / ADC_MAX * NTC_VREF;
}

/* ② 电压 → NTC 阻值。分压公式 Rt = Rs·V/(3.3−V)
 * 先钳住贴边电压：算出 0Ω 或无穷大再取对数会得到 NaN */
static float VoltToOhm(float v)
{
    if (v < 0.02f)                v = 0.02f;
    if (v > NTC_VREF - 0.02f)     v = NTC_VREF - 0.02f;
    return NTC_R_SERIES * v / (NTC_VREF - v);
}

/* ③ 阻值 → 温度（B 值公式）：1/T = 1/T0 + ln(Rt/R0)/B，再减 273.15 转摄氏度 */
static float OhmToTempC(float rt)
{
    return 1.0f / (1.0f / NTC_T0_K + logf(rt / NTC_R0) / NTC_B) - 273.15f;
}

/* 初始化 ADC1：PA0 模拟输入、单次转换、12MHz ADC 时钟。调一次即可。 */
void NTC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);            /* 72MHz/6=12MHz，不能超 14MHz */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; /* 模拟输入 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;        /* 只扫一个通道 */
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  /* 单次转换 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);                          /* 上电校准一次 */
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

/* 读一次码值：软件启动转换 → 等结束标志 → 取数据寄存器 */
uint16_t NTC_ReadAdc(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

/* 对外主函数：平均 8 次 → 三步换算 → 0.1℃ 定点整数。
 * 用 0.1℃ 的整数是为了不让浮点跑到显示代码里，也省 flash。 */
int16_t NTC_GetTempX10(void)
{
    uint32_t sum = 0;
    uint8_t  i;
    float    v;
    float    rt;
    float    t;
    int32_t  t10;

    for (i = 0; i < 8; i++)          /* 单次采样末位会跳 ±2，8 次平均才稳 */
    {
        sum += NTC_ReadAdc();
    }

    v  = AdcToVolt((uint16_t)(sum / 8));
    rt = VoltToOhm(v);
    t  = OhmToTempC(rt);

    t10 = (int32_t)(t * 10.0f + (t >= 0 ? 0.5f : -0.5f));  /* 四舍五入到 0.1℃ */
    if (t10 > 1250)  t10 = 1250;                           /* 钳在 -40~125℃ */
    if (t10 < -400)  t10 = -400;

    return (int16_t)t10;
}
