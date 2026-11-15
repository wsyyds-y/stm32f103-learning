/**
  ******************************************************************************
  * @file    stm32f10x_pwr.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the PWR firmware 
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
#ifndef __STM32F10x_PWR_H
#define __STM32F10x_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */ 

/** @defgroup PWR_Exported_Types
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup PWR_Exported_Constants
  * @{
  */ 

/** @defgroup PVD_detection_level 
  * @{
  */ 

#define PWR_PVDLevel_2V2          ((uint32_t)0x00000000)  /* PVD检测阈值2.2V */
#define PWR_PVDLevel_2V3          ((uint32_t)0x00000020)  /* PVD检测阈值2.3V */
#define PWR_PVDLevel_2V4          ((uint32_t)0x00000040)  /* PVD检测阈值2.4V */
#define PWR_PVDLevel_2V5          ((uint32_t)0x00000060)  /* PVD检测阈值2.5V */
#define PWR_PVDLevel_2V6          ((uint32_t)0x00000080)  /* PVD检测阈值2.6V */
#define PWR_PVDLevel_2V7          ((uint32_t)0x000000A0)  /* PVD检测阈值2.7V */
#define PWR_PVDLevel_2V8          ((uint32_t)0x000000C0)  /* PVD检测阈值2.8V */
#define PWR_PVDLevel_2V9          ((uint32_t)0x000000E0)  /* PVD检测阈值2.9V */
#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_2V2) || ((LEVEL) == PWR_PVDLevel_2V3)|| \
                                 ((LEVEL) == PWR_PVDLevel_2V4) || ((LEVEL) == PWR_PVDLevel_2V5)|| \
                                 ((LEVEL) == PWR_PVDLevel_2V6) || ((LEVEL) == PWR_PVDLevel_2V7)|| \
                                 ((LEVEL) == PWR_PVDLevel_2V8) || ((LEVEL) == PWR_PVDLevel_2V9))
/**
  * @}
  */

/** @defgroup Regulator_state_is_STOP_mode 
  * @{
  */

#define PWR_Regulator_ON          ((uint32_t)0x00000000)  /* STOP模式下调节器开启 */
#define PWR_Regulator_LowPower    ((uint32_t)0x00000001)  /* STOP模式下调节器低功耗 */
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))
/**
  * @}
  */

/** @defgroup STOP_mode_entry 
  * @{
  */

#define PWR_STOPEntry_WFI         ((uint8_t)0x01)  /* 用WFI指令进入STOP模式 */
#define PWR_STOPEntry_WFE         ((uint8_t)0x02)  /* 用WFE指令进入STOP模式 */
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))
 
/**
  * @}
  */

/** @defgroup PWR_Flag 
  * @{
  */

#define PWR_FLAG_WU               ((uint32_t)0x00000001)  /* 唤醒标志 */
#define PWR_FLAG_SB               ((uint32_t)0x00000002)  /* 待机标志 */
#define PWR_FLAG_PVDO             ((uint32_t)0x00000004)  /* PVD输出标志 */
#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PWR_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup PWR_Exported_Functions
  * @{
  */

void PWR_DeInit(void);  /* 复位PWR外设 */
void PWR_BackupAccessCmd(FunctionalState NewState);  /* 使能或禁止访问RTC和备份寄存器 */
void PWR_PVDCmd(FunctionalState NewState);  /* 使能或禁止PVD电源电压检测器 */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);  /* 配置PVD检测电压阈值 */
void PWR_WakeUpPinCmd(FunctionalState NewState);  /* 使能或禁止WKUP唤醒引脚 */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);  /* 进入STOP停止模式 */
void PWR_EnterSTANDBYMode(void);  /* 进入STANDBY待机模式 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);  /* 获取PWR标志位状态 */
void PWR_ClearFlag(uint32_t PWR_FLAG);  /* 清除PWR挂起标志 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_PWR_H */
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
