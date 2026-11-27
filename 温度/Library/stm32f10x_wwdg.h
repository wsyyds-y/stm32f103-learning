/**
  ******************************************************************************
  * @file    stm32f10x_wwdg.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the WWDG firmware
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
#ifndef __STM32F10x_WWDG_H
#define __STM32F10x_WWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */ 

/** @defgroup WWDG_Exported_Types
  * @{
  */ 
  
/**
  * @}
  */ 

/** @defgroup WWDG_Exported_Constants
  * @{
  */ 
  
/** @defgroup WWDG_Prescaler 
  * @{
  */ 
  
#define WWDG_Prescaler_1    ((uint32_t)0x00000000)  /* 预分频1 */
#define WWDG_Prescaler_2    ((uint32_t)0x00000080)  /* 预分频2 */
#define WWDG_Prescaler_4    ((uint32_t)0x00000100)  /* 预分频4 */
#define WWDG_Prescaler_8    ((uint32_t)0x00000180)  /* 预分频8 */
#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
                                      ((PRESCALER) == WWDG_Prescaler_2) || \
                                      ((PRESCALER) == WWDG_Prescaler_4) || \
                                      ((PRESCALER) == WWDG_Prescaler_8))  /* 校验WWDG预分频参数是否合法 */
#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)  /* 校验WWDG窗口取值范围 */
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))  /* 校验WWDG计数器取值范围 */

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup WWDG_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup WWDG_Exported_Functions
  * @{
  */ 
  
void WWDG_DeInit(void);  /* 将WWDG寄存器复位为默认值 */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);  /* 设置WWDG预分频值 */
void WWDG_SetWindowValue(uint8_t WindowValue);  /* 设置WWDG窗口值 */
void WWDG_EnableIT(void);  /* 使能WWDG提前唤醒中断EWI */
void WWDG_SetCounter(uint8_t Counter);  /* 设置WWDG计数器值（喂狗） */
void WWDG_Enable(uint8_t Counter);  /* 启动WWDG并装载计数器初值 */
FlagStatus WWDG_GetFlagStatus(void);  /* 读取提前唤醒中断标志状态 */
void WWDG_ClearFlag(void);  /* 清除提前唤醒中断标志 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_WWDG_H */

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
