/**
  ******************************************************************************
  * @file    stm32f10x_exti.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the EXTI firmware
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
#ifndef __STM32F10x_EXTI_H
#define __STM32F10x_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/** @defgroup EXTI_Exported_Types
  * @{
  */

/** 
  * @brief  EXTI mode enumeration  
  */

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,      /* 中断模式 */
  EXTI_Mode_Event = 0x04           /* 事件模式 */
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/** 
  * @brief  EXTI Trigger enumeration  
  */

typedef enum
{
  EXTI_Trigger_Rising = 0x08,           /* 上升沿触发 */
  EXTI_Trigger_Falling = 0x0C,          /* 下降沿触发 */
  EXTI_Trigger_Rising_Falling = 0x10    /* 上升沿和下降沿均触发 */
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/** 
  * @brief  EXTI Init Structure definition  
  */

typedef struct
{
  uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */
  /* 指定要配置的EXTI线 */
   
  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */
  /* 指定EXTI线的工作模式(中断或事件) */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTITrigger_TypeDef */
  /* 指定EXTI线触发信号的边沿 */

  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */ 
  /* 指定EXTI线的使能状态 */
}EXTI_InitTypeDef;

/**
  * @}
  */

/** @defgroup EXTI_Exported_Constants
  * @{
  */

/** @defgroup EXTI_Lines 
  * @{
  */

#define EXTI_Line0       ((uint32_t)0x00001)  /*!< External interrupt line 0 */  /* 外部中断线0 */
#define EXTI_Line1       ((uint32_t)0x00002)  /*!< External interrupt line 1 */  /* 外部中断线1 */
#define EXTI_Line2       ((uint32_t)0x00004)  /*!< External interrupt line 2 */  /* 外部中断线2 */
#define EXTI_Line3       ((uint32_t)0x00008)  /*!< External interrupt line 3 */  /* 外部中断线3 */
#define EXTI_Line4       ((uint32_t)0x00010)  /*!< External interrupt line 4 */  /* 外部中断线4 */
#define EXTI_Line5       ((uint32_t)0x00020)  /*!< External interrupt line 5 */  /* 外部中断线5 */
#define EXTI_Line6       ((uint32_t)0x00040)  /*!< External interrupt line 6 */  /* 外部中断线6 */
#define EXTI_Line7       ((uint32_t)0x00080)  /*!< External interrupt line 7 */  /* 外部中断线7 */
#define EXTI_Line8       ((uint32_t)0x00100)  /*!< External interrupt line 8 */  /* 外部中断线8 */
#define EXTI_Line9       ((uint32_t)0x00200)  /*!< External interrupt line 9 */  /* 外部中断线9 */
#define EXTI_Line10      ((uint32_t)0x00400)  /*!< External interrupt line 10 */  /* 外部中断线10 */
#define EXTI_Line11      ((uint32_t)0x00800)  /*!< External interrupt line 11 */  /* 外部中断线11 */
#define EXTI_Line12      ((uint32_t)0x01000)  /*!< External interrupt line 12 */  /* 外部中断线12 */
#define EXTI_Line13      ((uint32_t)0x02000)  /*!< External interrupt line 13 */  /* 外部中断线13 */
#define EXTI_Line14      ((uint32_t)0x04000)  /*!< External interrupt line 14 */  /* 外部中断线14 */
#define EXTI_Line15      ((uint32_t)0x08000)  /*!< External interrupt line 15 */  /* 外部中断线15 */
#define EXTI_Line16      ((uint32_t)0x10000)  /*!< External interrupt line 16 Connected to the PVD Output */  /* 连接PVD输出的外部中断线16 */
#define EXTI_Line17      ((uint32_t)0x20000)  /*!< External interrupt line 17 Connected to the RTC Alarm event */  /* 连接RTC闹钟事件的外部中断线17 */
#define EXTI_Line18      ((uint32_t)0x40000)  /*!< External interrupt line 18 Connected to the USB Device/USB OTG FS
                                                   Wakeup from suspend event */  /* 连接USB唤醒事件的外部中断线18 */                                    
#define EXTI_Line19      ((uint32_t)0x80000)  /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */  /* 连接以太网唤醒事件的外部中断线19 */
                                          
#define IS_EXTI_LINE(LINE) ((((LINE) & (uint32_t)0xFFF00000) == 0x00) && ((LINE) != (uint16_t)0x00))
#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || \
                            ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || \
                            ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || \
                            ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || \
                            ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || \
                            ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                            ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                            ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                            ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                            ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19))

                    
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup EXTI_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions
  * @{
  */

void EXTI_DeInit(void);  /* 复位EXTI外设 */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);  /* 根据结构体参数初始化EXTI */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);  /* 将结构体成员初始化为默认值 */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);  /* 产生EXTI软件中断 */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);  /* 获取EXTI标志位状态  主*/
void EXTI_ClearFlag(uint32_t EXTI_Line);  /* 清除EXTI挂起标志              主*/
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);  /* 获取EXTI中断状态        支 */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);  /* 清除EXTI中断挂起位    支*/

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_EXTI_H */
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
