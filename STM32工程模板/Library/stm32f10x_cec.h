/**
  ******************************************************************************
  * @file    stm32f10x_cec.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the CEC firmware 
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
#ifndef __STM32F10x_CEC_H
#define __STM32F10x_CEC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup CEC
  * @{
  */
  

/** @defgroup CEC_Exported_Types
  * @{
  */
   
/** 
  * @brief  CEC Init structure definition  
  */ 
typedef struct
{
  /* CEC位时序错误模式 */
  uint16_t CEC_BitTimingMode; /*!< Configures the CEC Bit Timing Error Mode. 
                               This parameter can be a value of @ref CEC_BitTiming_Mode */
  /* CEC位周期错误模式 */
  uint16_t CEC_BitPeriodMode; /*!< Configures the CEC Bit Period Error Mode. 
                               This parameter can be a value of @ref CEC_BitPeriod_Mode */
}CEC_InitTypeDef;

/**
  * @}
  */

/** @defgroup CEC_Exported_Constants
  * @{
  */ 
  
/** @defgroup CEC_BitTiming_Mode 
  * @{
  */ 
#define CEC_BitTimingStdMode                    ((uint16_t)0x00) /* 位时序错误标准模式 */ /*!< Bit timing error Standard Mode */
#define CEC_BitTimingErrFreeMode                CEC_CFGR_BTEM /* 位时序错误自由模式 */ /*!< Bit timing error Free Mode */

#define IS_CEC_BIT_TIMING_ERROR_MODE(MODE) (((MODE) == CEC_BitTimingStdMode) || \
                                            ((MODE) == CEC_BitTimingErrFreeMode))
/**
  * @}
  */

/** @defgroup CEC_BitPeriod_Mode 
  * @{
  */ 
#define CEC_BitPeriodStdMode                    ((uint16_t)0x00) /* 位周期错误标准模式 */ /*!< Bit period error Standard Mode */
#define CEC_BitPeriodFlexibleMode                CEC_CFGR_BPEM /* 位周期错误灵活模式 */ /*!< Bit period error Flexible Mode */

#define IS_CEC_BIT_PERIOD_ERROR_MODE(MODE) (((MODE) == CEC_BitPeriodStdMode) || \
                                            ((MODE) == CEC_BitPeriodFlexibleMode))
/**
  * @}
  */ 


/** @defgroup CEC_interrupts_definition 
  * @{
  */ 
#define CEC_IT_TERR                              CEC_CSR_TERR  /* 发送错误中断 */
#define CEC_IT_TBTRF                             CEC_CSR_TBTRF  /* 发送块传输完成中断 */
#define CEC_IT_RERR                              CEC_CSR_RERR  /* 接收错误中断 */
#define CEC_IT_RBTF                              CEC_CSR_RBTF  /* 接收块传输完成中断 */
#define IS_CEC_GET_IT(IT) (((IT) == CEC_IT_TERR) || ((IT) == CEC_IT_TBTRF) || \
                           ((IT) == CEC_IT_RERR) || ((IT) == CEC_IT_RBTF))
/**
  * @}
  */ 


/** @defgroup CEC_Own_Address 
  * @{
  */ 
#define IS_CEC_ADDRESS(ADDRESS) ((ADDRESS) < 0x10)
/**
  * @}
  */ 

/** @defgroup CEC_Prescaler 
  * @{
  */ 
#define IS_CEC_PRESCALER(PRESCALER) ((PRESCALER) <= 0x3FFF)

/**
  * @}
  */

/** @defgroup CEC_flags_definition 
  * @{
  */
   
/** 
  * @brief  ESR register flags  
  */ 
#define CEC_FLAG_BTE                            ((uint32_t)0x10010000)  /* 位时序错误标志 */
#define CEC_FLAG_BPE                            ((uint32_t)0x10020000)  /* 位周期错误标志 */
#define CEC_FLAG_RBTFE                          ((uint32_t)0x10040000)  /* 接收块传输完成错误标志 */
#define CEC_FLAG_SBE                            ((uint32_t)0x10080000)  /* 起始位错误标志 */
#define CEC_FLAG_ACKE                           ((uint32_t)0x10100000)  /* 块应答错误标志 */
#define CEC_FLAG_LINE                           ((uint32_t)0x10200000)  /* 总线线路错误标志 */
#define CEC_FLAG_TBTFE                          ((uint32_t)0x10400000)  /* 发送块传输完成错误标志 */

/** 
  * @brief  CSR register flags  
  */ 
#define CEC_FLAG_TEOM                           ((uint32_t)0x00000002)  /* 发送结束标志 */  
#define CEC_FLAG_TERR                           ((uint32_t)0x00000004)  /* 发送错误标志 */
#define CEC_FLAG_TBTRF                          ((uint32_t)0x00000008)  /* 发送字节传输请求或块传输完成标志 */
#define CEC_FLAG_RSOM                           ((uint32_t)0x00000010)  /* 接收消息起始标志 */
#define CEC_FLAG_REOM                           ((uint32_t)0x00000020)  /* 接收消息结束标志 */
#define CEC_FLAG_RERR                           ((uint32_t)0x00000040)  /* 接收错误标志 */
#define CEC_FLAG_RBTF                           ((uint32_t)0x00000080)  /* 接收字节或块传输完成标志 */

#define IS_CEC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFF03) == 0x00) && ((FLAG) != 0x00))
                               
#define IS_CEC_GET_FLAG(FLAG) (((FLAG) == CEC_FLAG_BTE) || ((FLAG) == CEC_FLAG_BPE) || \
                               ((FLAG) == CEC_FLAG_RBTFE) || ((FLAG)== CEC_FLAG_SBE) || \
                               ((FLAG) == CEC_FLAG_ACKE) || ((FLAG) == CEC_FLAG_LINE) || \
                               ((FLAG) == CEC_FLAG_TBTFE) || ((FLAG) == CEC_FLAG_TEOM) || \
                               ((FLAG) == CEC_FLAG_TERR) || ((FLAG) == CEC_FLAG_TBTRF) || \
                               ((FLAG) == CEC_FLAG_RSOM) || ((FLAG) == CEC_FLAG_REOM) || \
                               ((FLAG) == CEC_FLAG_RERR) || ((FLAG) == CEC_FLAG_RBTF))

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup CEC_Exported_Macros
  * @{
  */
 
/**
  * @}
  */

/** @defgroup CEC_Exported_Functions
  * @{
  */ 
void CEC_DeInit(void);  /* 复位CEC外设 */
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct);  /* 根据结构体参数初始化CEC */
void CEC_Cmd(FunctionalState NewState);  /* 使能或禁止CEC外设 */
void CEC_ITConfig(FunctionalState NewState);  /* 使能或禁止CEC中断 */
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress);  /* 配置CEC自身地址 */
void CEC_SetPrescaler(uint16_t CEC_Prescaler);  /* 设置CEC预分频值 */
void CEC_SendDataByte(uint8_t Data);  /* 发送一个数据字节 */
uint8_t CEC_ReceiveDataByte(void);  /* 读取最近接收的数据字节 */
void CEC_StartOfMessage(void);  /* 开始发送新消息 */
void CEC_EndOfMessageCmd(FunctionalState NewState);  /* 设置发送数据是否带EOM结束标志 */
FlagStatus CEC_GetFlagStatus(uint32_t CEC_FLAG);  /* 获取CEC标志位状态 */
void CEC_ClearFlag(uint32_t CEC_FLAG);  /* 清除CEC标志 */
ITStatus CEC_GetITStatus(uint8_t CEC_IT);  /* 获取CEC中断状态 */
void CEC_ClearITPendingBit(uint16_t CEC_IT);  /* 清除CEC中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_CEC_H */

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
