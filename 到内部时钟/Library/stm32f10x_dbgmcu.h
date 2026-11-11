/**
  ******************************************************************************
  * @file    stm32f10x_dbgmcu.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the DBGMCU 
  *          firmware library.
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
#ifndef __STM32F10x_DBGMCU_H
#define __STM32F10x_DBGMCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup DBGMCU
  * @{
  */

/** @defgroup DBGMCU_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Constants
  * @{
  */

#define DBGMCU_SLEEP                 ((uint32_t)0x00000001)  /* 睡眠模式下保持调试连接 */
#define DBGMCU_STOP                  ((uint32_t)0x00000002)  /* 停止模式下保持调试连接 */
#define DBGMCU_STANDBY               ((uint32_t)0x00000004)  /* 待机模式下保持调试连接 */
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00000100)  /* 内核停止时暂停IWDG */
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000200)  /* 内核停止时暂停WWDG */
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000400)  /* 内核停止时暂停TIM1 */
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000800)  /* 内核停止时暂停TIM2 */
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00001000)  /* 内核停止时暂停TIM3 */
#define DBGMCU_TIM4_STOP             ((uint32_t)0x00002000)  /* 内核停止时暂停TIM4 */
#define DBGMCU_CAN1_STOP             ((uint32_t)0x00004000)  /* 内核停止时暂停CAN1 */
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00008000)  /* 内核停止时暂停I2C1 SMBUS超时 */
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00010000)  /* 内核停止时暂停I2C2 SMBUS超时 */
#define DBGMCU_TIM8_STOP             ((uint32_t)0x00020000)  /* 内核停止时暂停TIM8 */
#define DBGMCU_TIM5_STOP             ((uint32_t)0x00040000)  /* 内核停止时暂停TIM5 */
#define DBGMCU_TIM6_STOP             ((uint32_t)0x00080000)  /* 内核停止时暂停TIM6 */
#define DBGMCU_TIM7_STOP             ((uint32_t)0x00100000)  /* 内核停止时暂停TIM7 */
#define DBGMCU_CAN2_STOP             ((uint32_t)0x00200000)  /* 内核停止时暂停CAN2 */
#define DBGMCU_TIM15_STOP            ((uint32_t)0x00400000)  /* 内核停止时暂停TIM15 */
#define DBGMCU_TIM16_STOP            ((uint32_t)0x00800000)  /* 内核停止时暂停TIM16 */
#define DBGMCU_TIM17_STOP            ((uint32_t)0x01000000)  /* 内核停止时暂停TIM17 */
#define DBGMCU_TIM12_STOP            ((uint32_t)0x02000000)  /* 内核停止时暂停TIM12 */
#define DBGMCU_TIM13_STOP            ((uint32_t)0x04000000)  /* 内核停止时暂停TIM13 */
#define DBGMCU_TIM14_STOP            ((uint32_t)0x08000000)  /* 内核停止时暂停TIM14 */
#define DBGMCU_TIM9_STOP             ((uint32_t)0x10000000)  /* 内核停止时暂停TIM9 */
#define DBGMCU_TIM10_STOP            ((uint32_t)0x20000000)  /* 内核停止时暂停TIM10 */
#define DBGMCU_TIM11_STOP            ((uint32_t)0x40000000)  /* 内核停止时暂停TIM11 */
                                              
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0x800000F8) == 0x00) && ((PERIPH) != 0x00))  /* 校验调试外设参数是否合法 */
/**
  * @}
  */ 

/** @defgroup DBGMCU_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Exported_Functions
  * @{
  */

uint32_t DBGMCU_GetREVID(void);  /* 获取设备版本标识REVID */
uint32_t DBGMCU_GetDEVID(void);  /* 获取设备标识DEVID */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);  /* 配置调试模式下外设与低功耗模式的行为 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_DBGMCU_H */
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
