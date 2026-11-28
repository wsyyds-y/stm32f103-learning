#ifndef __NTC_H
#define __NTC_H

#include "stm32f10x.h"

/**
  ******************************************************************************
  * @file    NTC.h
  * @brief   NTC 热敏电阻分压测温 —— 对外接口
  *
  * 接线（默认 NTC 在下臂，与常见 4 脚 AO/DO 模块一致）：
  *   3.3V ── Rs(10k) ──┬── AO ──> PA0 (ADC1_IN0)
  *                      └── NTC ── GND
  *
  * 若 NTC 接在上臂（3.3V ── NTC ── AO ── Rs ── GND），把 NTC.c 里的
  * NTC_LOW_SIDE 改成 0 即可，其余代码不用动。
  ******************************************************************************
  */

/* 初始化：PA0 模拟输入 + ADC1 单次转换 + 自校准。 */
void NTC_Init(void);

/* 单次转换：软件触发，等 EOC 后读 DR，带超时保护（不会死等）。 */
uint16_t NTC_ReadAdc(void);

/* 连读 times 次取平均，压低噪声；times 传 0 按 1 处理。 */
uint16_t NTC_ReadAdcAve(uint8_t times);

/* ADC 码值 -> AO 电压（mV），按 VREF=3.3V、12 位满量程换算。 */
uint16_t NTC_AdcToMv(uint16_t adc);

/* ADC 码值 -> 反推出的热敏电阻阻值（Ω），用于对着万用表核对模型。 */
uint32_t NTC_AdcToOhm(uint16_t adc);

/* ADC 码值 -> 温度，单位 0.1℃。B 值公式 + 单点修正。 */
int16_t NTC_AdcToTempX10(uint16_t adc);

/* 返回当前编译进固件的修正量（0.1℃），供屏幕显示、方便对着改。 */
int16_t NTC_GetOffsetX10(void);

#endif
