#ifndef __NTC_H
#define __NTC_H

#include "stm32f10x.h"

/**
  * NTC 热敏电阻测温（AO -> PA0 -> ADC1_IN0）对外接口，只给 3 个函数。
  */

void NTC_Init(void);          /* 配好 ADC1，调一次 */
uint16_t NTC_ReadAdc(void);   /* 读一次 12 位码值（0~4095） */
int16_t NTC_GetTempX10(void); /* 采 8 次平均后换算，返回 0.1℃，如 253 表示 25.3℃ */

#endif
