/**
  ******************************************************************************
  * @file    stm32f10x_sdio.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the SDIO firmware
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
#ifndef __STM32F10x_SDIO_H
#define __STM32F10x_SDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */

/** @defgroup SDIO_Exported_Types
  * @{
  */

typedef struct
{
  /* 采样时钟边沿选择 */
  uint32_t SDIO_ClockEdge;            /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref SDIO_Clock_Edge */

  /* 时钟分频旁路使能 */
  uint32_t SDIO_ClockBypass;          /*!< Specifies whether the SDIO Clock divider bypass is
                                           enabled or disabled.
                                           This parameter can be a value of @ref SDIO_Clock_Bypass */

  /* 空闲时时钟输出节能 */
  uint32_t SDIO_ClockPowerSave;       /*!< Specifies whether SDIO Clock output is enabled or
                                           disabled when the bus is idle.
                                           This parameter can be a value of @ref SDIO_Clock_Power_Save */

  /* SDIO总线宽度 */
  uint32_t SDIO_BusWide;              /*!< Specifies the SDIO bus width.
                                           This parameter can be a value of @ref SDIO_Bus_Wide */

  /* 硬件流控制使能 */
  uint32_t SDIO_HardwareFlowControl;  /*!< Specifies whether the SDIO hardware flow control is enabled or disabled.
                                           This parameter can be a value of @ref SDIO_Hardware_Flow_Control */

  /* 时钟分频系数 */
  uint8_t SDIO_ClockDiv;              /*!< Specifies the clock frequency of the SDIO controller.
                                           This parameter can be a value between 0x00 and 0xFF. */
                                           
} SDIO_InitTypeDef;

typedef struct
{
  /* 命令参数 */
  uint32_t SDIO_Argument;  /*!< Specifies the SDIO command argument which is sent
                                to a card as part of a command message. If a command
                                contains an argument, it must be loaded into this register
                                before writing the command to the command register */

  uint32_t SDIO_CmdIndex; /* 命令索引 */ /*!< Specifies the SDIO command index. It must be lower than 0x40. */

  /* 响应类型 */
  uint32_t SDIO_Response;  /*!< Specifies the SDIO response type.
                                This parameter can be a value of @ref SDIO_Response_Type */

  /* 等待中断或结束请求 */
  uint32_t SDIO_Wait;      /*!< Specifies whether SDIO wait-for-interrupt request is enabled or disabled.
                                This parameter can be a value of @ref SDIO_Wait_Interrupt_State */

  /* 命令路径状态机使能 */
  uint32_t SDIO_CPSM;      /*!< Specifies whether SDIO Command path state machine (CPSM)
                                is enabled or disabled.
                                This parameter can be a value of @ref SDIO_CPSM_State */
} SDIO_CmdInitTypeDef;

typedef struct
{
  uint32_t SDIO_DataTimeOut; /* 数据超时时间 */ /*!< Specifies the data timeout period in card bus clock periods. */

  uint32_t SDIO_DataLength; /* 传输数据字节数 */ /*!< Specifies the number of data bytes to be transferred. */
 
  /* 数据块大小 */
  uint32_t SDIO_DataBlockSize;  /*!< Specifies the data block size for block transfer.
                                     This parameter can be a value of @ref SDIO_Data_Block_Size */
 
  /* 数据传输方向 */
  uint32_t SDIO_TransferDir;    /*!< Specifies the data transfer direction, whether the transfer
                                     is a read or write.
                                     This parameter can be a value of @ref SDIO_Transfer_Direction */
 
  /* 流或块传输模式 */
  uint32_t SDIO_TransferMode;   /*!< Specifies whether data transfer is in stream or block mode.
                                     This parameter can be a value of @ref SDIO_Transfer_Type */
 
  /* 数据路径状态机使能 */
  uint32_t SDIO_DPSM;           /*!< Specifies whether SDIO Data path state machine (DPSM)
                                     is enabled or disabled.
                                     This parameter can be a value of @ref SDIO_DPSM_State */
} SDIO_DataInitTypeDef;

/**
  * @}
  */ 

/** @defgroup SDIO_Exported_Constants
  * @{
  */

/** @defgroup SDIO_Clock_Edge 
  * @{
  */

#define SDIO_ClockEdge_Rising               ((uint32_t)0x00000000)  /* 上升沿采样 */
#define SDIO_ClockEdge_Falling              ((uint32_t)0x00002000)  /* 下降沿采样 */
#define IS_SDIO_CLOCK_EDGE(EDGE) (((EDGE) == SDIO_ClockEdge_Rising) || \
                                  ((EDGE) == SDIO_ClockEdge_Falling))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Bypass 
  * @{
  */

#define SDIO_ClockBypass_Disable             ((uint32_t)0x00000000)  /* 关闭时钟旁路 */
#define SDIO_ClockBypass_Enable              ((uint32_t)0x00000400)  /* 使能时钟旁路 */    
#define IS_SDIO_CLOCK_BYPASS(BYPASS) (((BYPASS) == SDIO_ClockBypass_Disable) || \
                                     ((BYPASS) == SDIO_ClockBypass_Enable))
/**
  * @}
  */ 

/** @defgroup SDIO_Clock_Power_Save 
  * @{
  */

#define SDIO_ClockPowerSave_Disable         ((uint32_t)0x00000000)  /* 关闭节能模式 */
#define SDIO_ClockPowerSave_Enable          ((uint32_t)0x00000200)  /* 使能节能模式 */ 
#define IS_SDIO_CLOCK_POWER_SAVE(SAVE) (((SAVE) == SDIO_ClockPowerSave_Disable) || \
                                        ((SAVE) == SDIO_ClockPowerSave_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Bus_Wide 
  * @{
  */

#define SDIO_BusWide_1b                     ((uint32_t)0x00000000)  /* 1位总线宽度 */
#define SDIO_BusWide_4b                     ((uint32_t)0x00000800)  /* 4位总线宽度 */
#define SDIO_BusWide_8b                     ((uint32_t)0x00001000)  /* 8位总线宽度 */
#define IS_SDIO_BUS_WIDE(WIDE) (((WIDE) == SDIO_BusWide_1b) || ((WIDE) == SDIO_BusWide_4b) || \
                                ((WIDE) == SDIO_BusWide_8b))

/**
  * @}
  */

/** @defgroup SDIO_Hardware_Flow_Control 
  * @{
  */

#define SDIO_HardwareFlowControl_Disable    ((uint32_t)0x00000000)  /* 关闭硬件流控制 */
#define SDIO_HardwareFlowControl_Enable     ((uint32_t)0x00004000)  /* 使能硬件流控制 */
#define IS_SDIO_HARDWARE_FLOW_CONTROL(CONTROL) (((CONTROL) == SDIO_HardwareFlowControl_Disable) || \
                                                ((CONTROL) == SDIO_HardwareFlowControl_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Power_State 
  * @{
  */

#define SDIO_PowerState_OFF                 ((uint32_t)0x00000000)  /* 关闭SDIO电源 */
#define SDIO_PowerState_ON                  ((uint32_t)0x00000003)  /* 开启SDIO电源 */
#define IS_SDIO_POWER_STATE(STATE) (((STATE) == SDIO_PowerState_OFF) || ((STATE) == SDIO_PowerState_ON)) 
/**
  * @}
  */ 


/** @defgroup SDIO_Interrupt_sources 
  * @{
  */

#define SDIO_IT_CCRCFAIL                    ((uint32_t)0x00000001)  /* 命令响应CRC失败 */
#define SDIO_IT_DCRCFAIL                    ((uint32_t)0x00000002)  /* 数据CRC失败 */
#define SDIO_IT_CTIMEOUT                    ((uint32_t)0x00000004)  /* 命令响应超时 */
#define SDIO_IT_DTIMEOUT                    ((uint32_t)0x00000008)  /* 数据超时 */
#define SDIO_IT_TXUNDERR                    ((uint32_t)0x00000010)  /* 发送FIFO下溢 */
#define SDIO_IT_RXOVERR                     ((uint32_t)0x00000020)  /* 接收FIFO上溢 */
#define SDIO_IT_CMDREND                     ((uint32_t)0x00000040)  /* 命令响应接收完成 */
#define SDIO_IT_CMDSENT                     ((uint32_t)0x00000080)  /* 命令发送完成 */
#define SDIO_IT_DATAEND                     ((uint32_t)0x00000100)  /* 数据传输结束 */
#define SDIO_IT_STBITERR                    ((uint32_t)0x00000200)  /* 起始位错误 */
#define SDIO_IT_DBCKEND                     ((uint32_t)0x00000400)  /* 数据块CRC状态回传完成 */
#define SDIO_IT_CMDACT                      ((uint32_t)0x00000800)  /* 命令传输中 */
#define SDIO_IT_TXACT                       ((uint32_t)0x00001000)  /* 数据发送中 */
#define SDIO_IT_RXACT                       ((uint32_t)0x00002000)  /* 数据接收中 */
#define SDIO_IT_TXFIFOHE                    ((uint32_t)0x00004000)  /* 发送FIFO半空 */
#define SDIO_IT_RXFIFOHF                    ((uint32_t)0x00008000)  /* 接收FIFO半满 */
#define SDIO_IT_TXFIFOF                     ((uint32_t)0x00010000)  /* 发送FIFO满 */
#define SDIO_IT_RXFIFOF                     ((uint32_t)0x00020000)  /* 接收FIFO满 */
#define SDIO_IT_TXFIFOE                     ((uint32_t)0x00040000)  /* 发送FIFO空 */
#define SDIO_IT_RXFIFOE                     ((uint32_t)0x00080000)  /* 接收FIFO空 */
#define SDIO_IT_TXDAVL                      ((uint32_t)0x00100000)  /* 发送FIFO有数据 */
#define SDIO_IT_RXDAVL                      ((uint32_t)0x00200000)  /* 接收FIFO有数据 */
#define SDIO_IT_SDIOIT                      ((uint32_t)0x00400000)  /* SDIO卡中断 */
#define SDIO_IT_CEATAEND                    ((uint32_t)0x00800000)  /* CE-ATA命令完成 */
#define IS_SDIO_IT(IT) ((((IT) & (uint32_t)0xFF000000) == 0x00) && ((IT) != (uint32_t)0x00))
/**
  * @}
  */ 

/** @defgroup SDIO_Command_Index
  * @{
  */

#define IS_SDIO_CMD_INDEX(INDEX)            ((INDEX) < 0x40)
/**
  * @}
  */

/** @defgroup SDIO_Response_Type 
  * @{
  */

#define SDIO_Response_No                    ((uint32_t)0x00000000)  /* 无响应 */
#define SDIO_Response_Short                 ((uint32_t)0x00000040)  /* 短响应 */
#define SDIO_Response_Long                  ((uint32_t)0x000000C0)  /* 长响应 */
#define IS_SDIO_RESPONSE(RESPONSE) (((RESPONSE) == SDIO_Response_No) || \
                                    ((RESPONSE) == SDIO_Response_Short) || \
                                    ((RESPONSE) == SDIO_Response_Long))
/**
  * @}
  */

/** @defgroup SDIO_Wait_Interrupt_State 
  * @{
  */

#define SDIO_Wait_No                        ((uint32_t)0x00000000) /* 无等待 */ /*!< SDIO No Wait, TimeOut is enabled */
#define SDIO_Wait_IT                        ((uint32_t)0x00000100) /* 等待中断请求 */ /*!< SDIO Wait Interrupt Request */
#define SDIO_Wait_Pend                      ((uint32_t)0x00000200) /* 等待传输结束 */ /*!< SDIO Wait End of transfer */
#define IS_SDIO_WAIT(WAIT) (((WAIT) == SDIO_Wait_No) || ((WAIT) == SDIO_Wait_IT) || \
                            ((WAIT) == SDIO_Wait_Pend))
/**
  * @}
  */

/** @defgroup SDIO_CPSM_State 
  * @{
  */

#define SDIO_CPSM_Disable                    ((uint32_t)0x00000000)  /* 关闭命令路径状态机 */
#define SDIO_CPSM_Enable                     ((uint32_t)0x00000400)  /* 使能命令路径状态机 */
#define IS_SDIO_CPSM(CPSM) (((CPSM) == SDIO_CPSM_Enable) || ((CPSM) == SDIO_CPSM_Disable))
/**
  * @}
  */ 

/** @defgroup SDIO_Response_Registers 
  * @{
  */

#define SDIO_RESP1                          ((uint32_t)0x00000000)  /* 响应寄存器1 */
#define SDIO_RESP2                          ((uint32_t)0x00000004)  /* 响应寄存器2 */
#define SDIO_RESP3                          ((uint32_t)0x00000008)  /* 响应寄存器3 */
#define SDIO_RESP4                          ((uint32_t)0x0000000C)  /* 响应寄存器4 */
#define IS_SDIO_RESP(RESP) (((RESP) == SDIO_RESP1) || ((RESP) == SDIO_RESP2) || \
                            ((RESP) == SDIO_RESP3) || ((RESP) == SDIO_RESP4))
/**
  * @}
  */

/** @defgroup SDIO_Data_Length 
  * @{
  */

#define IS_SDIO_DATA_LENGTH(LENGTH) ((LENGTH) <= 0x01FFFFFF)
/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Size 
  * @{
  */

#define SDIO_DataBlockSize_1b               ((uint32_t)0x00000000)  /* 数据块大小1字节 */
#define SDIO_DataBlockSize_2b               ((uint32_t)0x00000010)  /* 数据块大小2字节 */
#define SDIO_DataBlockSize_4b               ((uint32_t)0x00000020)  /* 数据块大小4字节 */
#define SDIO_DataBlockSize_8b               ((uint32_t)0x00000030)  /* 数据块大小8字节 */
#define SDIO_DataBlockSize_16b              ((uint32_t)0x00000040)  /* 数据块大小16字节 */
#define SDIO_DataBlockSize_32b              ((uint32_t)0x00000050)  /* 数据块大小32字节 */
#define SDIO_DataBlockSize_64b              ((uint32_t)0x00000060)  /* 数据块大小64字节 */
#define SDIO_DataBlockSize_128b             ((uint32_t)0x00000070)  /* 数据块大小128字节 */
#define SDIO_DataBlockSize_256b             ((uint32_t)0x00000080)  /* 数据块大小256字节 */
#define SDIO_DataBlockSize_512b             ((uint32_t)0x00000090)  /* 数据块大小512字节 */
#define SDIO_DataBlockSize_1024b            ((uint32_t)0x000000A0)  /* 数据块大小1024字节 */
#define SDIO_DataBlockSize_2048b            ((uint32_t)0x000000B0)  /* 数据块大小2048字节 */
#define SDIO_DataBlockSize_4096b            ((uint32_t)0x000000C0)  /* 数据块大小4096字节 */
#define SDIO_DataBlockSize_8192b            ((uint32_t)0x000000D0)  /* 数据块大小8192字节 */
#define SDIO_DataBlockSize_16384b           ((uint32_t)0x000000E0)  /* 数据块大小16384字节 */
#define IS_SDIO_BLOCK_SIZE(SIZE) (((SIZE) == SDIO_DataBlockSize_1b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16b) || \
                                  ((SIZE) == SDIO_DataBlockSize_32b) || \
                                  ((SIZE) == SDIO_DataBlockSize_64b) || \
                                  ((SIZE) == SDIO_DataBlockSize_128b) || \
                                  ((SIZE) == SDIO_DataBlockSize_256b) || \
                                  ((SIZE) == SDIO_DataBlockSize_512b) || \
                                  ((SIZE) == SDIO_DataBlockSize_1024b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2048b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4096b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8192b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16384b)) 
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Direction 
  * @{
  */

#define SDIO_TransferDir_ToCard             ((uint32_t)0x00000000)  /* 数据方向:写往SD卡 */
#define SDIO_TransferDir_ToSDIO             ((uint32_t)0x00000002)  /* 数据方向:从SD卡读出 */
#define IS_SDIO_TRANSFER_DIR(DIR) (((DIR) == SDIO_TransferDir_ToCard) || \
                                   ((DIR) == SDIO_TransferDir_ToSDIO))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Type 
  * @{
  */

#define SDIO_TransferMode_Block             ((uint32_t)0x00000000)  /* 块传输模式 */
#define SDIO_TransferMode_Stream            ((uint32_t)0x00000004)  /* 流传输模式 */
#define IS_SDIO_TRANSFER_MODE(MODE) (((MODE) == SDIO_TransferMode_Stream) || \
                                     ((MODE) == SDIO_TransferMode_Block))
/**
  * @}
  */

/** @defgroup SDIO_DPSM_State 
  * @{
  */

#define SDIO_DPSM_Disable                    ((uint32_t)0x00000000)  /* 关闭数据路径状态机 */
#define SDIO_DPSM_Enable                     ((uint32_t)0x00000001)  /* 使能数据路径状态机 */
#define IS_SDIO_DPSM(DPSM) (((DPSM) == SDIO_DPSM_Enable) || ((DPSM) == SDIO_DPSM_Disable))
/**
  * @}
  */

/** @defgroup SDIO_Flags 
  * @{
  */

#define SDIO_FLAG_CCRCFAIL                  ((uint32_t)0x00000001)  /* 命令响应CRC失败标志 */
#define SDIO_FLAG_DCRCFAIL                  ((uint32_t)0x00000002)  /* 数据CRC失败标志 */
#define SDIO_FLAG_CTIMEOUT                  ((uint32_t)0x00000004)  /* 命令响应超时标志 */
#define SDIO_FLAG_DTIMEOUT                  ((uint32_t)0x00000008)  /* 数据超时标志 */
#define SDIO_FLAG_TXUNDERR                  ((uint32_t)0x00000010)  /* 发送FIFO下溢标志 */
#define SDIO_FLAG_RXOVERR                   ((uint32_t)0x00000020)  /* 接收FIFO上溢标志 */
#define SDIO_FLAG_CMDREND                   ((uint32_t)0x00000040)  /* 命令响应接收完成标志 */
#define SDIO_FLAG_CMDSENT                   ((uint32_t)0x00000080)  /* 命令发送完成标志 */
#define SDIO_FLAG_DATAEND                   ((uint32_t)0x00000100)  /* 数据传输结束标志 */
#define SDIO_FLAG_STBITERR                  ((uint32_t)0x00000200)  /* 起始位错误标志 */
#define SDIO_FLAG_DBCKEND                   ((uint32_t)0x00000400)  /* 数据块CRC状态回传完成标志 */
#define SDIO_FLAG_CMDACT                    ((uint32_t)0x00000800)  /* 命令传输中标志 */
#define SDIO_FLAG_TXACT                     ((uint32_t)0x00001000)  /* 数据发送中标志 */
#define SDIO_FLAG_RXACT                     ((uint32_t)0x00002000)  /* 数据接收中标志 */
#define SDIO_FLAG_TXFIFOHE                  ((uint32_t)0x00004000)  /* 发送FIFO半空标志 */
#define SDIO_FLAG_RXFIFOHF                  ((uint32_t)0x00008000)  /* 接收FIFO半满标志 */
#define SDIO_FLAG_TXFIFOF                   ((uint32_t)0x00010000)  /* 发送FIFO满标志 */
#define SDIO_FLAG_RXFIFOF                   ((uint32_t)0x00020000)  /* 接收FIFO满标志 */
#define SDIO_FLAG_TXFIFOE                   ((uint32_t)0x00040000)  /* 发送FIFO空标志 */
#define SDIO_FLAG_RXFIFOE                   ((uint32_t)0x00080000)  /* 接收FIFO空标志 */
#define SDIO_FLAG_TXDAVL                    ((uint32_t)0x00100000)  /* 发送FIFO有数据标志 */
#define SDIO_FLAG_RXDAVL                    ((uint32_t)0x00200000)  /* 接收FIFO有数据标志 */
#define SDIO_FLAG_SDIOIT                    ((uint32_t)0x00400000)  /* SDIO卡中断标志 */
#define SDIO_FLAG_CEATAEND                  ((uint32_t)0x00800000)  /* CE-ATA命令完成标志 */
#define IS_SDIO_FLAG(FLAG) (((FLAG)  == SDIO_FLAG_CCRCFAIL) || \
                            ((FLAG)  == SDIO_FLAG_DCRCFAIL) || \
                            ((FLAG)  == SDIO_FLAG_CTIMEOUT) || \
                            ((FLAG)  == SDIO_FLAG_DTIMEOUT) || \
                            ((FLAG)  == SDIO_FLAG_TXUNDERR) || \
                            ((FLAG)  == SDIO_FLAG_RXOVERR) || \
                            ((FLAG)  == SDIO_FLAG_CMDREND) || \
                            ((FLAG)  == SDIO_FLAG_CMDSENT) || \
                            ((FLAG)  == SDIO_FLAG_DATAEND) || \
                            ((FLAG)  == SDIO_FLAG_STBITERR) || \
                            ((FLAG)  == SDIO_FLAG_DBCKEND) || \
                            ((FLAG)  == SDIO_FLAG_CMDACT) || \
                            ((FLAG)  == SDIO_FLAG_TXACT) || \
                            ((FLAG)  == SDIO_FLAG_RXACT) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOHE) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOHF) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOF) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOF) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOE) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOE) || \
                            ((FLAG)  == SDIO_FLAG_TXDAVL) || \
                            ((FLAG)  == SDIO_FLAG_RXDAVL) || \
                            ((FLAG)  == SDIO_FLAG_SDIOIT) || \
                            ((FLAG)  == SDIO_FLAG_CEATAEND))

#define IS_SDIO_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFF3FF800) == 0x00) && ((FLAG) != (uint32_t)0x00))

#define IS_SDIO_GET_IT(IT) (((IT)  == SDIO_IT_CCRCFAIL) || \
                            ((IT)  == SDIO_IT_DCRCFAIL) || \
                            ((IT)  == SDIO_IT_CTIMEOUT) || \
                            ((IT)  == SDIO_IT_DTIMEOUT) || \
                            ((IT)  == SDIO_IT_TXUNDERR) || \
                            ((IT)  == SDIO_IT_RXOVERR) || \
                            ((IT)  == SDIO_IT_CMDREND) || \
                            ((IT)  == SDIO_IT_CMDSENT) || \
                            ((IT)  == SDIO_IT_DATAEND) || \
                            ((IT)  == SDIO_IT_STBITERR) || \
                            ((IT)  == SDIO_IT_DBCKEND) || \
                            ((IT)  == SDIO_IT_CMDACT) || \
                            ((IT)  == SDIO_IT_TXACT) || \
                            ((IT)  == SDIO_IT_RXACT) || \
                            ((IT)  == SDIO_IT_TXFIFOHE) || \
                            ((IT)  == SDIO_IT_RXFIFOHF) || \
                            ((IT)  == SDIO_IT_TXFIFOF) || \
                            ((IT)  == SDIO_IT_RXFIFOF) || \
                            ((IT)  == SDIO_IT_TXFIFOE) || \
                            ((IT)  == SDIO_IT_RXFIFOE) || \
                            ((IT)  == SDIO_IT_TXDAVL) || \
                            ((IT)  == SDIO_IT_RXDAVL) || \
                            ((IT)  == SDIO_IT_SDIOIT) || \
                            ((IT)  == SDIO_IT_CEATAEND))

#define IS_SDIO_CLEAR_IT(IT) ((((IT) & (uint32_t)0xFF3FF800) == 0x00) && ((IT) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup SDIO_Read_Wait_Mode 
  * @{
  */

#define SDIO_ReadWaitMode_CLK               ((uint32_t)0x00000001)  /* 读等待由时钟控制 */
#define SDIO_ReadWaitMode_DATA2             ((uint32_t)0x00000000)  /* 读等待由DATA2线控制 */
#define IS_SDIO_READWAIT_MODE(MODE) (((MODE) == SDIO_ReadWaitMode_CLK) || \
                                     ((MODE) == SDIO_ReadWaitMode_DATA2))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SDIO_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions
  * @{
  */

void SDIO_DeInit(void);  /* 将SDIO寄存器复位为默认值 */
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);  /* 按结构体初始化SDIO */
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);  /* 用默认值填充初始化结构体 */
void SDIO_ClockCmd(FunctionalState NewState);  /* 使能或关闭SDIO时钟 */
void SDIO_SetPowerState(uint32_t SDIO_PowerState);  /* 设置SDIO电源状态 */
uint32_t SDIO_GetPowerState(void);  /* 获取SDIO电源状态 */
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);  /* 使能或关闭SDIO中断 */
void SDIO_DMACmd(FunctionalState NewState);  /* 使能或关闭SDIO DMA请求 */
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);  /* 发送SDIO命令 */
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);  /* 用默认值填充命令结构体 */
uint8_t SDIO_GetCommandResponse(void);  /* 获取命令响应值 */
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);  /* 获取响应寄存器内容 */
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);  /* 配置SDIO数据传输 */
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);  /* 用默认值填充数据结构体 */
uint32_t SDIO_GetDataCounter(void);  /* 获取剩余数据计数器值 */
uint32_t SDIO_ReadData(void);  /* 从FIFO读取数据 */
void SDIO_WriteData(uint32_t Data);  /* 向FIFO写入数据 */
uint32_t SDIO_GetFIFOCount(void);  /* 获取FIFO中数据个数 */
void SDIO_StartSDIOReadWait(FunctionalState NewState);  /* 启动SDIO读等待 */
void SDIO_StopSDIOReadWait(FunctionalState NewState);  /* 停止SDIO读等待 */
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode);  /* 设置SDIO读等待模式 */
void SDIO_SetSDIOOperation(FunctionalState NewState);  /* 使能SDIO操作模式 */
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);  /* 发送SDIO挂起命令 */
void SDIO_CommandCompletionCmd(FunctionalState NewState);  /* 使能或关闭命令完成信号 */
void SDIO_CEATAITCmd(FunctionalState NewState);  /* 使能或关闭CE-ATA中断 */
void SDIO_SendCEATACmd(FunctionalState NewState);  /* 发送CE-ATA命令 */
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG);  /* 获取SDIO标志状态 */
void SDIO_ClearFlag(uint32_t SDIO_FLAG);  /* 清除SDIO标志 */
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT);  /* 获取SDIO中断状态 */
void SDIO_ClearITPendingBit(uint32_t SDIO_IT);  /* 清除SDIO中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_SDIO_H */
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
