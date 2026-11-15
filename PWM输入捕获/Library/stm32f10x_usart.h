/**
  ******************************************************************************
  * @file    stm32f10x_usart.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the USART 
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
#ifndef __STM32F10x_USART_H
#define __STM32F10x_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */ 

/** @defgroup USART_Exported_Types
  * @{
  */ 

/** 
  * @brief  USART Init Structure definition  
  */ 
  
typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */
  /* 配置USART通信波特率 */

  uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */
  /* 一帧中的数据位长度(8位或9位) */

  uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */
  /* 停止位个数 */

  uint16_t USART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                  word length is set to 8 data bits). */
  /* 校验模式(无/奇/偶校验) */
 
  uint16_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */
  /* 接收或发送模式 */

  uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
  /* 硬件流控制模式 */
} USART_InitTypeDef;

/** 
  * @brief  USART Clock Init Structure definition  
  */ 
  
typedef struct
{

  uint16_t USART_Clock;   /*!< Specifies whether the USART clock is enabled or disabled.
                               This parameter can be a value of @ref USART_Clock */
  /* 同步时钟使能或关闭 */

  uint16_t USART_CPOL;    /*!< Specifies the steady state value of the serial clock.
                               This parameter can be a value of @ref USART_Clock_Polarity */
  /* 串行时钟极性 */

  uint16_t USART_CPHA;    /*!< Specifies the clock transition on which the bit capture is made.
                               This parameter can be a value of @ref USART_Clock_Phase */
  /* 数据采样对应的时钟边沿 */

  uint16_t USART_LastBit; /*!< Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                               This parameter can be a value of @ref USART_Last_Bit */
  /* 末位是否在SCLK上输出时钟脉冲 */
} USART_ClockInitTypeDef;

/**
  * @}
  */ 

/** @defgroup USART_Exported_Constants
  * @{
  */ 
  
#define IS_USART_ALL_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3) || \
                                     ((PERIPH) == UART4) || \
                                     ((PERIPH) == UART5))

#define IS_USART_123_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3))

#define IS_USART_1234_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                      ((PERIPH) == USART2) || \
                                      ((PERIPH) == USART3) || \
                                      ((PERIPH) == UART4))
/** @defgroup USART_Word_Length 
  * @{
  */ 
  
#define USART_WordLength_8b                  ((uint16_t)0x0000)  /* 8位数据字长 */
#define USART_WordLength_9b                  ((uint16_t)0x1000)  /* 9位数据字长 */
                                    
#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WordLength_8b) || \
                                      ((LENGTH) == USART_WordLength_9b))
/**
  * @}
  */ 

/** @defgroup USART_Stop_Bits 
  * @{
  */ 
  
#define USART_StopBits_1                     ((uint16_t)0x0000)  /* 1个停止位 */
#define USART_StopBits_0_5                   ((uint16_t)0x1000)  /* 0.5个停止位 */
#define USART_StopBits_2                     ((uint16_t)0x2000)  /* 2个停止位 */
#define USART_StopBits_1_5                   ((uint16_t)0x3000)  /* 1.5个停止位 */
#define IS_USART_STOPBITS(STOPBITS) (((STOPBITS) == USART_StopBits_1) || \
                                     ((STOPBITS) == USART_StopBits_0_5) || \
                                     ((STOPBITS) == USART_StopBits_2) || \
                                     ((STOPBITS) == USART_StopBits_1_5))
/**
  * @}
  */ 

/** @defgroup USART_Parity 
  * @{
  */ 
  
#define USART_Parity_No                      ((uint16_t)0x0000)  /* 无校验 */
#define USART_Parity_Even                    ((uint16_t)0x0400)  /* 偶校验 */
#define USART_Parity_Odd                     ((uint16_t)0x0600)  /* 奇校验 */ 
#define IS_USART_PARITY(PARITY) (((PARITY) == USART_Parity_No) || \
                                 ((PARITY) == USART_Parity_Even) || \
                                 ((PARITY) == USART_Parity_Odd))
/**
  * @}
  */ 

/** @defgroup USART_Mode 
  * @{
  */ 
  
#define USART_Mode_Rx                        ((uint16_t)0x0004)  /* 接收模式 */
#define USART_Mode_Tx                        ((uint16_t)0x0008)  /* 发送模式 */
#define IS_USART_MODE(MODE) ((((MODE) & (uint16_t)0xFFF3) == 0x00) && ((MODE) != (uint16_t)0x00))
/**
  * @}
  */ 

/** @defgroup USART_Hardware_Flow_Control 
  * @{
  */ 
#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)  /* 无硬件流控制 */
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)  /* RTS硬件流控制 */
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)  /* CTS硬件流控制 */
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)  /* RTS和CTS硬件流控制 */
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
                              (((CONTROL) == USART_HardwareFlowControl_None) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS) || \
                               ((CONTROL) == USART_HardwareFlowControl_CTS) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))
/**
  * @}
  */ 

/** @defgroup USART_Clock 
  * @{
  */ 
#define USART_Clock_Disable                  ((uint16_t)0x0000)  /* 关闭同步时钟 */
#define USART_Clock_Enable                   ((uint16_t)0x0800)  /* 使能同步时钟 */
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) || \
                               ((CLOCK) == USART_Clock_Enable))
/**
  * @}
  */ 

/** @defgroup USART_Clock_Polarity 
  * @{
  */
  
#define USART_CPOL_Low                       ((uint16_t)0x0000)  /* 时钟空闲为低电平 */
#define USART_CPOL_High                      ((uint16_t)0x0400)  /* 时钟空闲为高电平 */
#define IS_USART_CPOL(CPOL) (((CPOL) == USART_CPOL_Low) || ((CPOL) == USART_CPOL_High))

/**
  * @}
  */ 

/** @defgroup USART_Clock_Phase
  * @{
  */

#define USART_CPHA_1Edge                     ((uint16_t)0x0000)  /* 第1个时钟边沿采样 */
#define USART_CPHA_2Edge                     ((uint16_t)0x0200)  /* 第2个时钟边沿采样 */
#define IS_USART_CPHA(CPHA) (((CPHA) == USART_CPHA_1Edge) || ((CPHA) == USART_CPHA_2Edge))

/**
  * @}
  */

/** @defgroup USART_Last_Bit
  * @{
  */

#define USART_LastBit_Disable                ((uint16_t)0x0000)  /* 末位不在SCLK输出时钟 */
#define USART_LastBit_Enable                 ((uint16_t)0x0100)  /* 末位在SCLK输出时钟 */
#define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_LastBit_Disable) || \
                                   ((LASTBIT) == USART_LastBit_Enable))
/**
  * @}
  */ 

/** @defgroup USART_Interrupt_definition 
  * @{
  */
  
#define USART_IT_PE                          ((uint16_t)0x0028)  /* 校验错误中断 */
#define USART_IT_TXE                         ((uint16_t)0x0727)  /* 发送数据寄存器空中断 */
#define USART_IT_TC                          ((uint16_t)0x0626)  /* 发送完成中断 */
#define USART_IT_RXNE                        ((uint16_t)0x0525)  /* 接收数据寄存器非空中断 */
#define USART_IT_IDLE                        ((uint16_t)0x0424)  /* 空闲线路检测中断 */
#define USART_IT_LBD                         ((uint16_t)0x0846)  /* LIN断开检测中断 */
#define USART_IT_CTS                         ((uint16_t)0x096A)  /* CTS变化中断 */
#define USART_IT_ERR                         ((uint16_t)0x0060)  /* 错误中断 */
#define USART_IT_ORE                         ((uint16_t)0x0360)  /* 溢出错误中断 */
#define USART_IT_NE                          ((uint16_t)0x0260)  /* 噪声错误中断 */
#define USART_IT_FE                          ((uint16_t)0x0160)  /* 帧错误中断 */
#define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                               ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                               ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                               ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ERR))
#define IS_USART_GET_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                            ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                            ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                            ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ORE) || \
                            ((IT) == USART_IT_NE) || ((IT) == USART_IT_FE))
#define IS_USART_CLEAR_IT(IT) (((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                               ((IT) == USART_IT_LBD) || ((IT) == USART_IT_CTS))
/**
  * @}
  */

/** @defgroup USART_DMA_Requests 
  * @{
  */

#define USART_DMAReq_Tx                      ((uint16_t)0x0080)  /* 发送DMA请求 */
#define USART_DMAReq_Rx                      ((uint16_t)0x0040)  /* 接收DMA请求 */
#define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFF3F) == 0x00) && ((DMAREQ) != (uint16_t)0x00))

/**
  * @}
  */ 

/** @defgroup USART_WakeUp_methods
  * @{
  */

#define USART_WakeUp_IdleLine                ((uint16_t)0x0000)  /* 空闲线路唤醒 */
#define USART_WakeUp_AddressMark             ((uint16_t)0x0800)  /* 地址标记唤醒 */
#define IS_USART_WAKEUP(WAKEUP) (((WAKEUP) == USART_WakeUp_IdleLine) || \
                                 ((WAKEUP) == USART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup USART_LIN_Break_Detection_Length 
  * @{
  */
  
#define USART_LINBreakDetectLength_10b      ((uint16_t)0x0000)  /* 10位断开检测 */
#define USART_LINBreakDetectLength_11b      ((uint16_t)0x0020)  /* 11位断开检测 */
#define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
                               (((LENGTH) == USART_LINBreakDetectLength_10b) || \
                                ((LENGTH) == USART_LINBreakDetectLength_11b))
/**
  * @}
  */

/** @defgroup USART_IrDA_Low_Power 
  * @{
  */

#define USART_IrDAMode_LowPower              ((uint16_t)0x0004)  /* IrDA低功耗模式 */
#define USART_IrDAMode_Normal                ((uint16_t)0x0000)  /* IrDA正常模式 */
#define IS_USART_IRDA_MODE(MODE) (((MODE) == USART_IrDAMode_LowPower) || \
                                  ((MODE) == USART_IrDAMode_Normal))
/**
  * @}
  */ 

/** @defgroup USART_Flags 
  * @{
  */

#define USART_FLAG_CTS                       ((uint16_t)0x0200)  /* CTS变化标志 */
#define USART_FLAG_LBD                       ((uint16_t)0x0100)  /* LIN断开检测标志 */
#define USART_FLAG_TXE                       ((uint16_t)0x0080)  /* 发送数据寄存器空标志 */
#define USART_FLAG_TC                        ((uint16_t)0x0040)  /* 发送完成标志 */
#define USART_FLAG_RXNE                      ((uint16_t)0x0020)  /* 接收数据寄存器非空标志 */
#define USART_FLAG_IDLE                      ((uint16_t)0x0010)  /* 空闲线路检测标志 */
#define USART_FLAG_ORE                       ((uint16_t)0x0008)  /* 溢出错误标志 */
#define USART_FLAG_NE                        ((uint16_t)0x0004)  /* 噪声错误标志 */
#define USART_FLAG_FE                        ((uint16_t)0x0002)  /* 帧错误标志 */
#define USART_FLAG_PE                        ((uint16_t)0x0001)  /* 校验错误标志 */
#define IS_USART_FLAG(FLAG) (((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
                             ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
                             ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
                             ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
                             ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE))
                              
#define IS_USART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFC9F) == 0x00) && ((FLAG) != (uint16_t)0x00))
#define IS_USART_PERIPH_FLAG(PERIPH, USART_FLAG) ((((*(uint32_t*)&(PERIPH)) != UART4_BASE) &&\
                                                  ((*(uint32_t*)&(PERIPH)) != UART5_BASE)) \
                                                  || ((USART_FLAG) != USART_FLAG_CTS)) 
#define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))
#define IS_USART_ADDRESS(ADDRESS) ((ADDRESS) <= 0xF)
#define IS_USART_DATA(DATA) ((DATA) <= 0x1FF)

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup USART_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USART_Exported_Functions
  * @{
  */

void USART_DeInit(USART_TypeDef* USARTx);  /* 将指定USART外设寄存器复位为默认值 */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);  /* 根据结构体参数初始化指定USART */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);  /* 用默认值填充USART初始化结构体 */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);  /* 初始化指定USART的同步时钟 */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);  /* 用默认值填充USART时钟初始化结构体 */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭指定USART */
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);  /* 使能或关闭指定USART中断 */
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);  /* 使能或关闭USART的DMA请求 */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);  /* 设置USART节点地址 */
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);  /* 选择USART唤醒方式 */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 进入或退出USART静默模式 */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength);  /* 设置USART的LIN断开检测长度 */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭USART的LIN模式 */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);  /* 通过USART发送一个数据 */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);  /* 读取USART最近接收的数据 */
void USART_SendBreak(USART_TypeDef* USARTx);  /* 发送断开帧 */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);  /* 设置USART保护时间 */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);  /* 设置USART红外预分频 */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭SmartCard模式 */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭SmartCard的NACK发送 */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭半双工模式 */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭8倍过采样 */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭单比特采样方式 */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);  /* 配置IrDA模式 */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);  /* 使能或关闭IrDA模式 */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);  /* 检查指定USART标志位状态 */
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);  /* 清除USART标志位 */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);  /* 检查指定USART中断状态 */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);  /* 清除USART中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_USART_H */
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
