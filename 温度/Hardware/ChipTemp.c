#include "stm32f10x.h"
#include "ChipTemp.h"

/**
  ******************************************************************************
  * @file    ChipTemp.c
  * @brief   STM32F103 片内温度传感器（ADC1_IN16）测温
  *
  * 原理：芯片内部有一个温度敏感的二极管，输出电压随温度线性下降，
  *       接到 ADC1 的通道 16。数据手册给的标称值：
  *         25℃ 时  VSENSE ≈ 1.43V
  *         斜率     ≈ 4.3mV/℃（负温度系数，温度升高电压降低）
  *       所以：T(℃) = 25 + (1430mV - VSENSE) / 4.3
  *
  * 用之前必须做两件事（本文件已做）：
  *   1) ADC_TempSensorVrefintCmd(ENABLE) 打开 TSVREFE 位，否则通道 16 读不到；
  *   2) 采样时间给足 —— 手册要求 ≥ 17.1µs，这里用 239.5 周期（12MHz 下约 21µs）。
  *
  * 精度说明：标称 ±1.5℃，且测的是芯片自身温度，满载会比环境高 1~3℃。
  * 想更准：与一支标准温度计放在同一环境里读一次，把差值写进 CHIPTEMP_OFFSET_X10。
  ******************************************************************************
  */

/* 采样与标定参数：换板子/换芯片只改这一段 */
#define CHIPTEMP_ADC            ADC1
#define CHIPTEMP_VREF           3.3f    /* ADC 参考电压 = VDDA = 3.3V */
#define CHIPTEMP_ADC_MAX        4095.0f /* 12 位 ADC 满量程 */
#define CHIPTEMP_V25_MV         1430.0f /* 数据手册：25℃ 时 VSENSE 典型 1.43V */
#define CHIPTEMP_SLOPE_MV       4.3f    /* 数据手册：4.3mV/℃（负斜率） */
#define CHIPTEMP_OFFSET_X10     0       /* 与标准温度计对比后的修正量，单位 0.1℃ */

/* 初始化：ADC1 单次转换 + 校准，通道 16 由 ADC_TempSensorVrefintCmd 打开。
 * 内部通道不用配 GPIO，所以这里没有引脚的初始化。 */
void ChipTemp_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    uint32_t wait;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);           /* 72MHz/6 = 12MHz，不超过 14MHz */

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       /* 单通道，不扫描 */
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; /* 单次转换，软件触发 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(CHIPTEMP_ADC, &ADC_InitStructure);

    /* 通道 16 = 内部温度传感器；采样时间必须 ≥17.1µs，239.5 周期约 21µs */
    ADC_RegularChannelConfig(CHIPTEMP_ADC, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);

    /* 打开内部温度传感器与 Vrefint 的使能位（TSVREFE），否则读到的是 0 */
    ADC_TempSensorVrefintCmd(ENABLE);
    ADC_Cmd(CHIPTEMP_ADC, ENABLE);

    /* 上电自校准，否则码值有固定偏差；等待都带超时，避免时钟配错时卡死 */
    ADC_ResetCalibration(CHIPTEMP_ADC);
    wait = 0;
    while (ADC_GetResetCalibrationStatus(CHIPTEMP_ADC) && (++wait < 200000));

    ADC_StartCalibration(CHIPTEMP_ADC);
    wait = 0;
    while (ADC_GetCalibrationStatus(CHIPTEMP_ADC) && (++wait < 200000));

    /* 内部传感器刚上电有 17µs 唤醒时间，第一次转换丢弃不用 */
    (void)ChipTemp_ReadAdc();
}

/* 单次转换：软件启动 -> 等 EOC -> 读 DR。
 * 转换一直不结束就返回寄存器当前值，宁可读数偏一点也不卡死主循环。 */
uint16_t ChipTemp_ReadAdc(void)
{
    uint32_t wait = 0;

    ADC_SoftwareStartConvCmd(CHIPTEMP_ADC, ENABLE);
    while ((ADC_GetFlagStatus(CHIPTEMP_ADC, ADC_FLAG_EOC) == RESET) && (++wait < 200000));
    return ADC_GetConversionValue(CHIPTEMP_ADC);
}

/* 连续转换取平均：内部传感器噪声约 ±1 码，平均后显示不跳。
 * 用 uint32_t 累加，8 次也不会溢出。 */
uint16_t ChipTemp_ReadAdcAve(uint8_t times)
{
    uint32_t sum = 0;
    uint8_t i;

    if (times == 0)
    {
        times = 1;
    }
    for (i = 0; i < times; i++)
    {
        sum += ChipTemp_ReadAdc();
    }
    return (uint16_t)(sum / times);
}

/* ADC 码值换算成 mV：adc/4095*3.3V。用整数算，避免显示时引入浮点。 */
uint16_t ChipTemp_AdcToMv(uint16_t adc)
{
    return (uint16_t)((uint32_t)adc * 3300 / 4095);
}

/* mV -> 温度（0.1℃ 定点）。温度越高 VSENSE 越低，所以是 (V25 - Vsense)/Slope。
 * 结果钳在 -40~125℃，超出范围按边界显示，不输出乱值。 */
int16_t ChipTemp_AdcToTempX10(uint16_t adc)
{
    float mv;
    float temp_c;
    int32_t temp_x10;

    mv = (float)adc * CHIPTEMP_VREF * 1000.0f / CHIPTEMP_ADC_MAX;

    temp_c = 25.0f + (CHIPTEMP_V25_MV - mv) / CHIPTEMP_SLOPE_MV
             + (float)CHIPTEMP_OFFSET_X10 / 10.0f;

    temp_x10 = (int32_t)(temp_c * 10.0f + (temp_c >= 0 ? 0.5f : -0.5f));

    if (temp_x10 > 1250) temp_x10 = 1250;
    if (temp_x10 < -400) temp_x10 = -400;

    return (int16_t)temp_x10;
}

/* 把本文件的标定修正量报给上层显示，省得 main.c 再抄一遍常量。 */
int16_t ChipTemp_GetOffsetX10(void)
{
    return (int16_t)CHIPTEMP_OFFSET_X10;
}
