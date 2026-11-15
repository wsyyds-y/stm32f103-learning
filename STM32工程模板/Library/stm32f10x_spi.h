/**
  ******************************************************************************
  * @file    stm32f10x_spi.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the SPI firmware 
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
#ifndef __STM32F10x_SPI_H
#define __STM32F10x_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */ 

/** @defgroup SPI_Exported_Types
  * @{
  */

/** 
  * @brief  SPI Init structure definition  
  */

typedef struct
{
  /* SPI数据方向 */
  uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

  /* SPI主从模式 */
  uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

  /* SPI数据帧长度 */
  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  /* 时钟极性 */
  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  /* 时钟相位 */
  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  /* NSS管理方式（硬件或软件） */
  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
  /* 波特率预分频系数 */
  uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  /* 数据传输先发MSB或LSB */
  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint16_t SPI_CRCPolynomial; /* CRC计算多项式 */ /*!< Specifies the polynomial used for the CRC calculation. */
}SPI_InitTypeDef;

/** 
  * @brief  I2S Init structure definition  
  */

typedef struct
{

  /* I2S工作模式 */
  uint16_t I2S_Mode;         /*!< Specifies the I2S operating mode.
                                  This parameter can be a value of @ref I2S_Mode */

  /* I2S通信标准 */
  uint16_t I2S_Standard;     /*!< Specifies the standard used for the I2S communication.
                                  This parameter can be a value of @ref I2S_Standard */

  /* I2S数据格式 */
  uint16_t I2S_DataFormat;   /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of @ref I2S_Data_Format */

  /* I2S主时钟（MCLK）输出使能 */
  uint16_t I2S_MCLKOutput;   /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of @ref I2S_MCLK_Output */

  /* I2S音频采样频率 */
  uint32_t I2S_AudioFreq;    /*!< Specifies the frequency selected for the I2S communication.
                                  This parameter can be a value of @ref I2S_Audio_Frequency */

  /* I2S时钟空闲电平 */
  uint16_t I2S_CPOL;         /*!< Specifies the idle state of the I2S clock.
                                  This parameter can be a value of @ref I2S_Clock_Polarity */
}I2S_InitTypeDef;

/**
  * @}
  */

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3))

#define IS_SPI_23_PERIPH(PERIPH) (((PERIPH) == SPI2) || \
                                  ((PERIPH) == SPI3))

/** @defgroup SPI_data_direction 
  * @{
  */
  
#define SPI_Direction_2Lines_FullDuplex ((uint16_t)0x0000)  /* 双线全双工模式 */
#define SPI_Direction_2Lines_RxOnly     ((uint16_t)0x0400)  /* 双线只接收模式 */
#define SPI_Direction_1Line_Rx          ((uint16_t)0x8000)  /* 单线只接收模式 */
#define SPI_Direction_1Line_Tx          ((uint16_t)0xC000)  /* 单线只发送模式 */
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))
/**
  * @}
  */

/** @defgroup SPI_mode 
  * @{
  */

#define SPI_Mode_Master                 ((uint16_t)0x0104)  /* SPI主模式 */
#define SPI_Mode_Slave                  ((uint16_t)0x0000)  /* SPI从模式 */
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */

/** @defgroup SPI_data_size 
  * @{
  */

#define SPI_DataSize_16b                ((uint16_t)0x0800)  /* 数据帧长度16位 */
#define SPI_DataSize_8b                 ((uint16_t)0x0000)  /* 数据帧长度8位 */
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSize_16b) || \
                                   ((DATASIZE) == SPI_DataSize_8b))
/**
  * @}
  */ 

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                    ((uint16_t)0x0000)  /* 时钟空闲为低电平 */
#define SPI_CPOL_High                   ((uint16_t)0x0002)  /* 时钟空闲为高电平 */
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)  /* 第一个时钟边沿采样 */
#define SPI_CPHA_2Edge                  ((uint16_t)0x0001)  /* 第二个时钟边沿采样 */
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management 
  * @{
  */

#define SPI_NSS_Soft                    ((uint16_t)0x0200)  /* NSS由软件管理 */
#define SPI_NSS_Hard                    ((uint16_t)0x0000)  /* NSS由硬件管理 */
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))
/**
  * @}
  */ 

/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */

#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)  /* 波特率2分频 */
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008)  /* 波特率4分频 */
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010)  /* 波特率8分频 */
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018)  /* 波特率16分频 */
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)  /* 波特率32分频 */
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028)  /* 波特率64分频 */
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030)  /* 波特率128分频 */
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038)  /* 波特率256分频 */
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))
/**
  * @}
  */ 

/** @defgroup SPI_MSB_LSB_transmission 
  * @{
  */

#define SPI_FirstBit_MSB                ((uint16_t)0x0000)  /* 先发送最高位（MSB） */
#define SPI_FirstBit_LSB                ((uint16_t)0x0080)  /* 先发送最低位（LSB） */
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))
/**
  * @}
  */

/** @defgroup I2S_Mode 
  * @{
  */

#define I2S_Mode_SlaveTx                ((uint16_t)0x0000)  /* I2S从机发送 */
#define I2S_Mode_SlaveRx                ((uint16_t)0x0100)  /* I2S从机接收 */
#define I2S_Mode_MasterTx               ((uint16_t)0x0200)  /* I2S主机发送 */
#define I2S_Mode_MasterRx               ((uint16_t)0x0300)  /* I2S主机接收 */
#define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
                           ((MODE) == I2S_Mode_SlaveRx) || \
                           ((MODE) == I2S_Mode_MasterTx) || \
                           ((MODE) == I2S_Mode_MasterRx) )
/**
  * @}
  */

/** @defgroup I2S_Standard 
  * @{
  */

#define I2S_Standard_Phillips           ((uint16_t)0x0000)  /* Philips标准 */
#define I2S_Standard_MSB                ((uint16_t)0x0010)  /* MSB对齐标准 */
#define I2S_Standard_LSB                ((uint16_t)0x0020)  /* LSB对齐标准 */
#define I2S_Standard_PCMShort           ((uint16_t)0x0030)  /* PCM短帧标准 */
#define I2S_Standard_PCMLong            ((uint16_t)0x00B0)  /* PCM长帧标准 */
#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
                                   ((STANDARD) == I2S_Standard_MSB) || \
                                   ((STANDARD) == I2S_Standard_LSB) || \
                                   ((STANDARD) == I2S_Standard_PCMShort) || \
                                   ((STANDARD) == I2S_Standard_PCMLong))
/**
  * @}
  */

/** @defgroup I2S_Data_Format 
  * @{
  */

#define I2S_DataFormat_16b              ((uint16_t)0x0000)  /* 16位数据格式 */
#define I2S_DataFormat_16bextended      ((uint16_t)0x0001)  /* 16位扩展数据格式 */
#define I2S_DataFormat_24b              ((uint16_t)0x0003)  /* 24位数据格式 */
#define I2S_DataFormat_32b              ((uint16_t)0x0005)  /* 32位数据格式 */
#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
                                    ((FORMAT) == I2S_DataFormat_24b) || \
                                    ((FORMAT) == I2S_DataFormat_32b))
/**
  * @}
  */ 

/** @defgroup I2S_MCLK_Output 
  * @{
  */

#define I2S_MCLKOutput_Enable           ((uint16_t)0x0200)  /* 使能MCLK输出 */
#define I2S_MCLKOutput_Disable          ((uint16_t)0x0000)  /* 关闭MCLK输出 */
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))
/**
  * @}
  */

/** @defgroup I2S_Audio_Frequency 
  * @{
  */

#define I2S_AudioFreq_192k               ((uint32_t)192000)  /* 音频采样率192kHz */
#define I2S_AudioFreq_96k                ((uint32_t)96000)  /* 音频采样率96kHz */
#define I2S_AudioFreq_48k                ((uint32_t)48000)  /* 音频采样率48kHz */
#define I2S_AudioFreq_44k                ((uint32_t)44100)  /* 音频采样率44.1kHz */
#define I2S_AudioFreq_32k                ((uint32_t)32000)  /* 音频采样率32kHz */
#define I2S_AudioFreq_22k                ((uint32_t)22050)  /* 音频采样率22.05kHz */
#define I2S_AudioFreq_16k                ((uint32_t)16000)  /* 音频采样率16kHz */
#define I2S_AudioFreq_11k                ((uint32_t)11025)  /* 音频采样率11.025kHz */
#define I2S_AudioFreq_8k                 ((uint32_t)8000)  /* 音频采样率8kHz */
#define I2S_AudioFreq_Default            ((uint32_t)2)  /* 默认音频采样率 */

#define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= I2S_AudioFreq_8k) && \
                                  ((FREQ) <= I2S_AudioFreq_192k)) || \
                                 ((FREQ) == I2S_AudioFreq_Default))
/**
  * @}
  */ 

/** @defgroup I2S_Clock_Polarity 
  * @{
  */

#define I2S_CPOL_Low                    ((uint16_t)0x0000)  /* I2S时钟空闲为低电平 */
#define I2S_CPOL_High                   ((uint16_t)0x0008)  /* I2S时钟空闲为高电平 */
#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_I2S_DMA_transfer_requests 
  * @{
  */

#define SPI_I2S_DMAReq_Tx               ((uint16_t)0x0002)  /* 发送缓冲区DMA请求 */
#define SPI_I2S_DMAReq_Rx               ((uint16_t)0x0001)  /* 接收缓冲区DMA请求 */
#define IS_SPI_I2S_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFFFC) == 0x00) && ((DMAREQ) != 0x00))
/**
  * @}
  */

/** @defgroup SPI_NSS_internal_software_management 
  * @{
  */

#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0100)  /* 内部NSS置位 */
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)  /* 内部NSS复位 */
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))
/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive 
  * @{
  */

#define SPI_CRC_Tx                      ((uint8_t)0x00)  /* 选择发送CRC寄存器 */
#define SPI_CRC_Rx                      ((uint8_t)0x01)  /* 选择接收CRC寄存器 */
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))
/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive 
  * @{
  */

#define SPI_Direction_Rx                ((uint16_t)0xBFFF)  /* 双向模式选择接收方向 */
#define SPI_Direction_Tx                ((uint16_t)0x4000)  /* 双向模式选择发送方向 */
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))
/**
  * @}
  */

/** @defgroup SPI_I2S_interrupts_definition 
  * @{
  */

#define SPI_I2S_IT_TXE                  ((uint8_t)0x71)  /* 发送缓冲区空中断 */
#define SPI_I2S_IT_RXNE                 ((uint8_t)0x60)  /* 接收缓冲区非空中断 */
#define SPI_I2S_IT_ERR                  ((uint8_t)0x50)  /* 错误中断 */
#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                 ((IT) == SPI_I2S_IT_RXNE) || \
                                 ((IT) == SPI_I2S_IT_ERR))
#define SPI_I2S_IT_OVR                  ((uint8_t)0x56)  /* 溢出错误中断 */
#define SPI_IT_MODF                     ((uint8_t)0x55)  /* 模式错误中断 */
#define SPI_IT_CRCERR                   ((uint8_t)0x54)  /* CRC错误中断 */
#define I2S_IT_UDR                      ((uint8_t)0x53)  /* 下溢错误中断 */
#define IS_SPI_I2S_CLEAR_IT(IT) (((IT) == SPI_IT_CRCERR))
#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE) || ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == I2S_IT_UDR) || ((IT) == SPI_IT_CRCERR) || \
                               ((IT) == SPI_IT_MODF) || ((IT) == SPI_I2S_IT_OVR))
/**
  * @}
  */

/** @defgroup SPI_I2S_flags_definition 
  * @{
  */

#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)  /* 接收缓冲区非空标志 */
#define SPI_I2S_FLAG_TXE                ((uint16_t)0x0002)  /* 发送缓冲区空标志 */
#define I2S_FLAG_CHSIDE                 ((uint16_t)0x0004)  /* 声道选择标志 */
#define I2S_FLAG_UDR                    ((uint16_t)0x0008)  /* 下溢错误标志 */
#define SPI_FLAG_CRCERR                 ((uint16_t)0x0010)  /* CRC错误标志 */
#define SPI_FLAG_MODF                   ((uint16_t)0x0020)  /* 模式错误标志 */
#define SPI_I2S_FLAG_OVR                ((uint16_t)0x0040)  /* 溢出错误标志 */
#define SPI_I2S_FLAG_BSY                ((uint16_t)0x0080)  /* 忙标志 */
#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE))
/**
  * @}
  */

/** @defgroup SPI_CRC_polynomial 
  * @{
  */

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SPI_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions
  * @{
  */

void SPI_I2S_DeInit(SPI_TypeDef* SPIx);  /* 将SPI/I2S外设寄存器复位为默认值 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);  /* 根据结构体参数初始化SPI外设 */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);  /* 根据结构体参数初始化I2S外设并计算分频 */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);  /* 将SPI初始化结构体各成员设为默认值 */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);  /* 将I2S初始化结构体各成员设为默认值 */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);  /* 使能或关闭指定SPI外设 */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);  /* 使能或关闭指定I2S外设 */
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);  /* 使能或关闭SPI/I2S中断 */
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);  /* 使能或关闭SPI/I2S的DMA请求 */
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);  /* 通过SPI/I2S发送一个数据 */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);  /* 读取SPI/I2S最近接收的数据 */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);  /* 软件配置SPI的NSS引脚内部电平 */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);  /* 使能或关闭SPI的SS输出 */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);  /* 配置SPI数据帧长度 */
void SPI_TransmitCRC(SPI_TypeDef* SPIx);  /* 发送SPI的CRC值 */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);  /* 使能或关闭SPI的CRC计算 */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);  /* 返回SPI发送或接收CRC寄存器的值 */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);  /* 返回SPI的CRC多项式寄存器值 */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);  /* 配置双向模式下SPI的数据传输方向 */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);  /* 检查指定SPI/I2S标志位是否置位 */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);  /* 清除SPI的CRC错误标志 */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);  /* 检查指定SPI/I2S中断是否发生 */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);  /* 清除SPI的CRC错误中断待处理位 */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F10x_SPI_H */
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
