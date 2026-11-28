#ifndef __CHIPTEMP_H
#define __CHIPTEMP_H

#include "stm32f10x.h"

/**
  ******************************************************************************
  * @file    ChipTemp.h
  * @brief   STM32F103 片内温度传感器驱动（ADC1_IN16）—— 对外接口
  *
  * 为什么用它：手头那块 4 脚蓝板（MH + AO/DO + LM393 + 蓝电位器）背面是
  * TCRT5000 一类的红外反射式光电开关，测的是反射光，不是温度。
  * 而 F103 内部自带一个温度传感器（接 ADC1 的通道 16），不需要任何外接元件，
  * 精度 ±1.5℃ 左右，测室温 ±1~2℃ 够用。
  *
  * 注意：它测的是芯片自身的温度，比室温略高 1~3℃（芯片自己发热），
  * 用 CHIPTEMP_OFFSET_X10 与标准温度计对比一次即可修正。
  ******************************************************************************
  */

/* 初始化：开 ADC1 时钟与 TSVREFE、通道 16、239.5 周期采样、自校准。 */
void ChipTemp_Init(void);

/* 单次转换：软件触发，等 EOC 后读 DR，带超时保护（不会死等）。 */
uint16_t ChipTemp_ReadAdc(void);

/* 连读 times 次取平均，压低噪声；times 传 0 按 1 处理。 */
uint16_t ChipTemp_ReadAdcAve(uint8_t times);

/* ADC 码值 -> 传感器电压（mV），按 VREF=3.3V、12 位满量程换算。 */
uint16_t ChipTemp_AdcToMv(uint16_t adc);

/* ADC 码值 -> 温度，单位 0.1℃。公式：T = 25 + (V25-Vsense)/Slope + 修正。 */
int16_t ChipTemp_AdcToTempX10(uint16_t adc);

/* 返回当前编译进固件的修正量（0.1℃），供屏幕上显示、方便对着改。 */
int16_t ChipTemp_GetOffsetX10(void);

#endif
