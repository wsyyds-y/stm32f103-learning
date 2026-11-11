/**
  ******************************************************************************
  * @file    stm32f10x_iwdg.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the IWDG 
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
#ifndef __STM32F10x_IWDG_H
#define __STM32F10x_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/** @defgroup IWDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/** @defgroup IWDG_WriteAccess
  * @{
  */

#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)  /* 允许写IWDG_PR与IWDG_RLR */
#define IWDG_WriteAccess_Disable    ((uint16_t)0x0000)  /* 禁止写IWDG_PR与IWDG_RLR */
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
                                      ((ACCESS) == IWDG_WriteAccess_Disable))  /* 校验IWDG写访问参数是否合法 */
/**
  * @}
  */

/** @defgroup IWDG_prescaler 
  * @{
  */

#define IWDG_Prescaler_4            ((uint8_t)0x00)  /* 预分频4 */
#define IWDG_Prescaler_8            ((uint8_t)0x01)  /* 预分频8 */
#define IWDG_Prescaler_16           ((uint8_t)0x02)  /* 预分频16 */
#define IWDG_Prescaler_32           ((uint8_t)0x03)  /* 预分频32 */
#define IWDG_Prescaler_64           ((uint8_t)0x04)  /* 预分频64 */
#define IWDG_Prescaler_128          ((uint8_t)0x05)  /* 预分频128 */
#define IWDG_Prescaler_256          ((uint8_t)0x06)  /* 预分频256 */
#define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == IWDG_Prescaler_4)  || \
                                      ((PRESCALER) == IWDG_Prescaler_8)  || \
                                      ((PRESCALER) == IWDG_Prescaler_16) || \
                                      ((PRESCALER) == IWDG_Prescaler_32) || \
                                      ((PRESCALER) == IWDG_Prescaler_64) || \
                                      ((PRESCALER) == IWDG_Prescaler_128)|| \
                                      ((PRESCALER) == IWDG_Prescaler_256))  /* 校验IWDG预分频参数是否合法 */
/**
  * @}
  */

/** @defgroup IWDG_Flag 
  * @{
  */

#define IWDG_FLAG_PVU               ((uint16_t)0x0001)  /* 预分频值更新进行中标志 */
#define IWDG_FLAG_RVU               ((uint16_t)0x0002)  /* 重装载值更新进行中标志 */
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU))  /* 校验IWDG标志参数是否合法 */
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)  /* 校验IWDG重装载取值范围 */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Functions
  * @{
  */

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);  /* 使能或关闭IWDG_PR与IWDG_RLR寄存器的写访问 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);  /* 设置IWDG预分频值 */
void IWDG_SetReload(uint16_t Reload);  /* 设置IWDG重装载值 */
void IWDG_ReloadCounter(void);  /* 重装载IWDG计数器（喂狗） */
void IWDG_Enable(void);  /* 启动IWDG独立看门狗 */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);  /* 检查指定的IWDG标志位是否置位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IWDG_H */
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
