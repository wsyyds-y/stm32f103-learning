/**
  ******************************************************************************
  * @file    stm32f10x_bkp.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the BKP firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_BKP_H
#define __STM32F10x_BKP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup BKP
  * @{
  */

/** @defgroup BKP_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Exported_Constants
  * @{
  */

/** @defgroup Tamper_Pin_active_level 
  * @{
  */

#define BKP_TamperPinLevel_High           ((uint16_t)0x0000)  /* 侵入引脚高电平有效 */
#define BKP_TamperPinLevel_Low            ((uint16_t)0x0001)  /* 侵入引脚低电平有效 */
#define IS_BKP_TAMPER_PIN_LEVEL(LEVEL) (((LEVEL) == BKP_TamperPinLevel_High) || \
                                        ((LEVEL) == BKP_TamperPinLevel_Low))
/**
  * @}
  */

/** @defgroup RTC_output_source_to_output_on_the_Tamper_pin 
  * @{
  */

#define BKP_RTCOutputSource_None          ((uint16_t)0x0000)  /* 侵入引脚无RTC输出 */
#define BKP_RTCOutputSource_CalibClock    ((uint16_t)0x0080)  /* 输出64分频的RTC时钟 */
#define BKP_RTCOutputSource_Alarm         ((uint16_t)0x0100)  /* 输出RTC闹钟脉冲 */
#define BKP_RTCOutputSource_Second        ((uint16_t)0x0300)  /* 输出RTC秒脉冲 */
#define IS_BKP_RTC_OUTPUT_SOURCE(SOURCE) (((SOURCE) == BKP_RTCOutputSource_None) || \
                                          ((SOURCE) == BKP_RTCOutputSource_CalibClock) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Alarm) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Second))
/**
  * @}
  */

/** @defgroup Data_Backup_Register 
  * @{
  */

#define BKP_DR1                           ((uint16_t)0x0004)  /* 数据备份寄存器1 */
#define BKP_DR2                           ((uint16_t)0x0008)  /* 数据备份寄存器2 */
#define BKP_DR3                           ((uint16_t)0x000C)  /* 数据备份寄存器3 */
#define BKP_DR4                           ((uint16_t)0x0010)  /* 数据备份寄存器4 */
#define BKP_DR5                           ((uint16_t)0x0014)  /* 数据备份寄存器5 */
#define BKP_DR6                           ((uint16_t)0x0018)  /* 数据备份寄存器6 */
#define BKP_DR7                           ((uint16_t)0x001C)  /* 数据备份寄存器7 */
#define BKP_DR8                           ((uint16_t)0x0020)  /* 数据备份寄存器8 */
#define BKP_DR9                           ((uint16_t)0x0024)  /* 数据备份寄存器9 */
#define BKP_DR10                          ((uint16_t)0x0028)  /* 数据备份寄存器10 */
#define BKP_DR11                          ((uint16_t)0x0040)  /* 数据备份寄存器11 */
#define BKP_DR12                          ((uint16_t)0x0044)  /* 数据备份寄存器12 */
#define BKP_DR13                          ((uint16_t)0x0048)  /* 数据备份寄存器13 */
#define BKP_DR14                          ((uint16_t)0x004C)  /* 数据备份寄存器14 */
#define BKP_DR15                          ((uint16_t)0x0050)  /* 数据备份寄存器15 */
#define BKP_DR16                          ((uint16_t)0x0054)  /* 数据备份寄存器16 */
#define BKP_DR17                          ((uint16_t)0x0058)  /* 数据备份寄存器17 */
#define BKP_DR18                          ((uint16_t)0x005C)  /* 数据备份寄存器18 */
#define BKP_DR19                          ((uint16_t)0x0060)  /* 数据备份寄存器19 */
#define BKP_DR20                          ((uint16_t)0x0064)  /* 数据备份寄存器20 */
#define BKP_DR21                          ((uint16_t)0x0068)  /* 数据备份寄存器21 */
#define BKP_DR22                          ((uint16_t)0x006C)  /* 数据备份寄存器22 */
#define BKP_DR23                          ((uint16_t)0x0070)  /* 数据备份寄存器23 */
#define BKP_DR24                          ((uint16_t)0x0074)  /* 数据备份寄存器24 */
#define BKP_DR25                          ((uint16_t)0x0078)  /* 数据备份寄存器25 */
#define BKP_DR26                          ((uint16_t)0x007C)  /* 数据备份寄存器26 */
#define BKP_DR27                          ((uint16_t)0x0080)  /* 数据备份寄存器27 */
#define BKP_DR28                          ((uint16_t)0x0084)  /* 数据备份寄存器28 */
#define BKP_DR29                          ((uint16_t)0x0088)  /* 数据备份寄存器29 */
#define BKP_DR30                          ((uint16_t)0x008C)  /* 数据备份寄存器30 */
#define BKP_DR31                          ((uint16_t)0x0090)  /* 数据备份寄存器31 */
#define BKP_DR32                          ((uint16_t)0x0094)  /* 数据备份寄存器32 */
#define BKP_DR33                          ((uint16_t)0x0098)  /* 数据备份寄存器33 */
#define BKP_DR34                          ((uint16_t)0x009C)  /* 数据备份寄存器34 */
#define BKP_DR35                          ((uint16_t)0x00A0)  /* 数据备份寄存器35 */
#define BKP_DR36                          ((uint16_t)0x00A4)  /* 数据备份寄存器36 */
#define BKP_DR37                          ((uint16_t)0x00A8)  /* 数据备份寄存器37 */
#define BKP_DR38                          ((uint16_t)0x00AC)  /* 数据备份寄存器38 */
#define BKP_DR39                          ((uint16_t)0x00B0)  /* 数据备份寄存器39 */
#define BKP_DR40                          ((uint16_t)0x00B4)  /* 数据备份寄存器40 */
#define BKP_DR41                          ((uint16_t)0x00B8)  /* 数据备份寄存器41 */
#define BKP_DR42                          ((uint16_t)0x00BC)  /* 数据备份寄存器42 */

#define IS_BKP_DR(DR) (((DR) == BKP_DR1)  || ((DR) == BKP_DR2)  || ((DR) == BKP_DR3)  || \
                       ((DR) == BKP_DR4)  || ((DR) == BKP_DR5)  || ((DR) == BKP_DR6)  || \
                       ((DR) == BKP_DR7)  || ((DR) == BKP_DR8)  || ((DR) == BKP_DR9)  || \
                       ((DR) == BKP_DR10) || ((DR) == BKP_DR11) || ((DR) == BKP_DR12) || \
                       ((DR) == BKP_DR13) || ((DR) == BKP_DR14) || ((DR) == BKP_DR15) || \
                       ((DR) == BKP_DR16) || ((DR) == BKP_DR17) || ((DR) == BKP_DR18) || \
                       ((DR) == BKP_DR19) || ((DR) == BKP_DR20) || ((DR) == BKP_DR21) || \
                       ((DR) == BKP_DR22) || ((DR) == BKP_DR23) || ((DR) == BKP_DR24) || \
                       ((DR) == BKP_DR25) || ((DR) == BKP_DR26) || ((DR) == BKP_DR27) || \
                       ((DR) == BKP_DR28) || ((DR) == BKP_DR29) || ((DR) == BKP_DR30) || \
                       ((DR) == BKP_DR31) || ((DR) == BKP_DR32) || ((DR) == BKP_DR33) || \
                       ((DR) == BKP_DR34) || ((DR) == BKP_DR35) || ((DR) == BKP_DR36) || \
                       ((DR) == BKP_DR37) || ((DR) == BKP_DR38) || ((DR) == BKP_DR39) || \
                       ((DR) == BKP_DR40) || ((DR) == BKP_DR41) || ((DR) == BKP_DR42))

#define IS_BKP_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x7F)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup BKP_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Exported_Functions
  * @{
  */

void BKP_DeInit(void);  /* 复位BKP外设 */
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel);  /* 配置侵入引脚有效电平 */
void BKP_TamperPinCmd(FunctionalState NewState);  /* 使能或禁止侵入引脚 */
void BKP_ITConfig(FunctionalState NewState);  /* 使能或禁止侵入中断 */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource);  /* 配置RTC输出到侵入引脚 */
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);  /* 设置RTC时钟校准值 */
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);  /* 写数据到备份寄存器 */
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);  /* 从备份寄存器读数据 */
FlagStatus BKP_GetFlagStatus(void);  /* 获取侵入引脚事件标志 */
void BKP_ClearFlag(void);  /* 清除侵入引脚事件标志 */
ITStatus BKP_GetITStatus(void);  /* 获取侵入引脚中断状态 */
void BKP_ClearITPendingBit(void);  /* 清除侵入引脚中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_BKP_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
