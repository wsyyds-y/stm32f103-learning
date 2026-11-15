/**
  ******************************************************************************
  * @file    stm32f10x_can.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the CAN firmware 
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
#ifndef __STM32F10x_CAN_H
#define __STM32F10x_CAN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/** @defgroup CAN_Exported_Types
  * @{
  */

#define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN1) || \
                                   ((PERIPH) == CAN2))

/** 
  * @brief  CAN init structure definition
  */

typedef struct
{
  uint16_t CAN_Prescaler;   /*!< Specifies the length of a time quantum. 
                                 It ranges from 1 to 1024. */
  /* 一个时间单元的长度(1~1024) */
  
  uint8_t CAN_Mode;         /*!< Specifies the CAN operating mode.
                                 This parameter can be a value of 
                                @ref CAN_operating_mode */
  /* CAN工作模式 */

  uint8_t CAN_SJW;          /*!< Specifies the maximum number of time quanta 
                                 the CAN hardware is allowed to lengthen or 
                                 shorten a bit to perform resynchronization.
                                 This parameter can be a value of 
                                 @ref CAN_synchronisation_jump_width */
  /* 重新同步跳变宽度 */

  uint8_t CAN_BS1;          /*!< Specifies the number of time quanta in Bit 
                                 Segment 1. This parameter can be a value of 
                                 @ref CAN_time_quantum_in_bit_segment_1 */
  /* 位段1的时间单元数 */

  uint8_t CAN_BS2;          /*!< Specifies the number of time quanta in Bit 
                                 Segment 2.
                                 This parameter can be a value of 
                                 @ref CAN_time_quantum_in_bit_segment_2 */
  /* 位段2的时间单元数 */
  
  FunctionalState CAN_TTCM; /*!< Enable or disable the time triggered 
                                 communication mode. This parameter can be set 
                                 either to ENABLE or DISABLE. */
  /* 时间触发通信模式 */
  
  FunctionalState CAN_ABOM;  /*!< Enable or disable the automatic bus-off 
                                  management. This parameter can be set either 
                                  to ENABLE or DISABLE. */
  /* 自动离线管理 */

  FunctionalState CAN_AWUM;  /*!< Enable or disable the automatic wake-up mode. 
                                  This parameter can be set either to ENABLE or 
                                  DISABLE. */
  /* 自动唤醒模式 */

  FunctionalState CAN_NART;  /*!< Enable or disable the no-automatic 
                                  retransmission mode. This parameter can be 
                                  set either to ENABLE or DISABLE. */
  /* 禁止自动重传 */

  FunctionalState CAN_RFLM;  /*!< Enable or disable the Receive FIFO Locked mode.
                                  This parameter can be set either to ENABLE 
                                  or DISABLE. */
  /* 接收FIFO锁定模式 */

  FunctionalState CAN_TXFP;  /*!< Enable or disable the transmit FIFO priority.
                                  This parameter can be set either to ENABLE 
                                  or DISABLE. */
  /* 发送FIFO优先级 */
} CAN_InitTypeDef;

/** 
  * @brief  CAN filter init structure definition
  */

typedef struct
{
  uint16_t CAN_FilterIdHigh;         /*!< Specifies the filter identification number (MSBs for a 32-bit
                                              configuration, first one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */
  /* 过滤器标识符高16位 */

  uint16_t CAN_FilterIdLow;          /*!< Specifies the filter identification number (LSBs for a 32-bit
                                              configuration, second one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */
  /* 过滤器标识符低16位 */

  uint16_t CAN_FilterMaskIdHigh;     /*!< Specifies the filter mask number or identification number,
                                              according to the mode (MSBs for a 32-bit configuration,
                                              first one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */
  /* 过滤器掩码高16位 */

  uint16_t CAN_FilterMaskIdLow;      /*!< Specifies the filter mask number or identification number,
                                              according to the mode (LSBs for a 32-bit configuration,
                                              second one for a 16-bit configuration).
                                              This parameter can be a value between 0x0000 and 0xFFFF */
  /* 过滤器掩码低16位 */

  uint16_t CAN_FilterFIFOAssignment; /*!< Specifies the FIFO (0 or 1) which will be assigned to the filter.
                                              This parameter can be a value of @ref CAN_filter_FIFO */
  /* 过滤器关联的FIFO(0或1) */
  
  uint8_t CAN_FilterNumber;          /*!< Specifies the filter which will be initialized. It ranges from 0 to 13. */  /* 滤波器编号(0~13) */

  uint8_t CAN_FilterMode;            /*!< Specifies the filter mode to be initialized.
                                              This parameter can be a value of @ref CAN_filter_mode */
  /* 过滤器模式 */

  uint8_t CAN_FilterScale;           /*!< Specifies the filter scale.
                                              This parameter can be a value of @ref CAN_filter_scale */
  /* 过滤器位宽(16位或32位) */

  FunctionalState CAN_FilterActivation; /*!< Enable or disable the filter.
                                              This parameter can be set either to ENABLE or DISABLE. */
  /* 使能或关闭过滤器 */
} CAN_FilterInitTypeDef;

/** 
  * @brief  CAN Tx message structure definition  
  */

typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */
  /* 标准标识符 */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */
  /* 扩展标识符 */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be transmitted. This parameter can be a value 
                        of @ref CAN_identifier_type */
  /* 标识符类型 */

  uint8_t RTR;     /*!< Specifies the type of frame for the message that will 
                        be transmitted. This parameter can be a value of 
                        @ref CAN_remote_transmission_request */
  /* 帧类型(数据帧或远程帧) */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be 
                        transmitted. This parameter can be a value between 
                        0 to 8 */
  /* 数据长度(0~8字节) */

  uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0 
                        to 0xFF. */
  /* 待发送的数据 */
} CanTxMsg;

/** 
  * @brief  CAN Rx message structure definition  
  */

typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */
  /* 标准标识符 */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */
  /* 扩展标识符 */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be received. This parameter can be a value of 
                        @ref CAN_identifier_type */
  /* 标识符类型 */

  uint8_t RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of 
                        @ref CAN_remote_transmission_request */
  /* 帧类型(数据帧或远程帧) */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */
  /* 数据长度(0~8字节) */

  uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to 
                        0xFF. */
  /* 接收到的数据 */

  uint8_t FMI;     /*!< Specifies the index of the filter the message stored in 
                        the mailbox passes through. This parameter can be a 
                        value between 0 to 0xFF */
  /* 消息通过的过滤器索引 */
} CanRxMsg;

/**
  * @}
  */

/** @defgroup CAN_Exported_Constants
  * @{
  */

/** @defgroup CAN_sleep_constants 
  * @{
  */

#define CAN_InitStatus_Failed              ((uint8_t)0x00) /*!< CAN initialization failed */  /* CAN初始化失败 */
#define CAN_InitStatus_Success             ((uint8_t)0x01) /*!< CAN initialization OK */  /* CAN初始化成功 */

/**
  * @}
  */

/** @defgroup CAN_Mode 
  * @{
  */

#define CAN_Mode_Normal             ((uint8_t)0x00)  /*!< normal mode */  /* 正常模式 */
#define CAN_Mode_LoopBack           ((uint8_t)0x01)  /*!< loopback mode */  /* 回环模式 */
#define CAN_Mode_Silent             ((uint8_t)0x02)  /*!< silent mode */  /* 静默模式 */
#define CAN_Mode_Silent_LoopBack    ((uint8_t)0x03)  /*!< loopback combined with silent mode */  /* 回环与静默组合模式 */

#define IS_CAN_MODE(MODE) (((MODE) == CAN_Mode_Normal) || \
                           ((MODE) == CAN_Mode_LoopBack)|| \
                           ((MODE) == CAN_Mode_Silent) || \
                           ((MODE) == CAN_Mode_Silent_LoopBack))
/**
  * @}
  */


/**
  * @defgroup CAN_Operating_Mode 
  * @{
  */  
#define CAN_OperatingMode_Initialization  ((uint8_t)0x00) /*!< Initialization mode */  /* 初始化模式 */
#define CAN_OperatingMode_Normal          ((uint8_t)0x01) /*!< Normal mode */  /* 正常模式 */
#define CAN_OperatingMode_Sleep           ((uint8_t)0x02) /*!< sleep mode */  /* 睡眠模式 */


#define IS_CAN_OPERATING_MODE(MODE) (((MODE) == CAN_OperatingMode_Initialization) ||\
                                    ((MODE) == CAN_OperatingMode_Normal)|| \
																		((MODE) == CAN_OperatingMode_Sleep))
/**
  * @}
  */
  
/**
  * @defgroup CAN_Mode_Status
  * @{
  */  

#define CAN_ModeStatus_Failed    ((uint8_t)0x00)                /*!< CAN entering the specific mode failed */  /* 进入指定模式失败 */
#define CAN_ModeStatus_Success   ((uint8_t)!CAN_ModeStatus_Failed)   /*!< CAN entering the specific mode Succeed */  /* 进入指定模式成功 */


/**
  * @}
  */

/** @defgroup CAN_synchronisation_jump_width 
  * @{
  */

#define CAN_SJW_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */  /* 1个时间单元 */
#define CAN_SJW_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */  /* 2个时间单元 */
#define CAN_SJW_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */  /* 3个时间单元 */
#define CAN_SJW_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */  /* 4个时间单元 */

#define IS_CAN_SJW(SJW) (((SJW) == CAN_SJW_1tq) || ((SJW) == CAN_SJW_2tq)|| \
                         ((SJW) == CAN_SJW_3tq) || ((SJW) == CAN_SJW_4tq))
/**
  * @}
  */

/** @defgroup CAN_time_quantum_in_bit_segment_1 
  * @{
  */

#define CAN_BS1_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */  /* 1个时间单元 */
#define CAN_BS1_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */  /* 2个时间单元 */
#define CAN_BS1_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */  /* 3个时间单元 */
#define CAN_BS1_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */  /* 4个时间单元 */
#define CAN_BS1_5tq                 ((uint8_t)0x04)  /*!< 5 time quantum */  /* 5个时间单元 */
#define CAN_BS1_6tq                 ((uint8_t)0x05)  /*!< 6 time quantum */  /* 6个时间单元 */
#define CAN_BS1_7tq                 ((uint8_t)0x06)  /*!< 7 time quantum */  /* 7个时间单元 */
#define CAN_BS1_8tq                 ((uint8_t)0x07)  /*!< 8 time quantum */  /* 8个时间单元 */
#define CAN_BS1_9tq                 ((uint8_t)0x08)  /*!< 9 time quantum */  /* 9个时间单元 */
#define CAN_BS1_10tq                ((uint8_t)0x09)  /*!< 10 time quantum */  /* 10个时间单元 */
#define CAN_BS1_11tq                ((uint8_t)0x0A)  /*!< 11 time quantum */  /* 11个时间单元 */
#define CAN_BS1_12tq                ((uint8_t)0x0B)  /*!< 12 time quantum */  /* 12个时间单元 */
#define CAN_BS1_13tq                ((uint8_t)0x0C)  /*!< 13 time quantum */  /* 13个时间单元 */
#define CAN_BS1_14tq                ((uint8_t)0x0D)  /*!< 14 time quantum */  /* 14个时间单元 */
#define CAN_BS1_15tq                ((uint8_t)0x0E)  /*!< 15 time quantum */  /* 15个时间单元 */
#define CAN_BS1_16tq                ((uint8_t)0x0F)  /*!< 16 time quantum */  /* 16个时间单元 */

#define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16tq)
/**
  * @}
  */

/** @defgroup CAN_time_quantum_in_bit_segment_2 
  * @{
  */

#define CAN_BS2_1tq                 ((uint8_t)0x00)  /*!< 1 time quantum */  /* 1个时间单元 */
#define CAN_BS2_2tq                 ((uint8_t)0x01)  /*!< 2 time quantum */  /* 2个时间单元 */
#define CAN_BS2_3tq                 ((uint8_t)0x02)  /*!< 3 time quantum */  /* 3个时间单元 */
#define CAN_BS2_4tq                 ((uint8_t)0x03)  /*!< 4 time quantum */  /* 4个时间单元 */
#define CAN_BS2_5tq                 ((uint8_t)0x04)  /*!< 5 time quantum */  /* 5个时间单元 */
#define CAN_BS2_6tq                 ((uint8_t)0x05)  /*!< 6 time quantum */  /* 6个时间单元 */
#define CAN_BS2_7tq                 ((uint8_t)0x06)  /*!< 7 time quantum */  /* 7个时间单元 */
#define CAN_BS2_8tq                 ((uint8_t)0x07)  /*!< 8 time quantum */  /* 8个时间单元 */

#define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8tq)

/**
  * @}
  */

/** @defgroup CAN_clock_prescaler 
  * @{
  */

#define IS_CAN_PRESCALER(PRESCALER) (((PRESCALER) >= 1) && ((PRESCALER) <= 1024))

/**
  * @}
  */

/** @defgroup CAN_filter_number 
  * @{
  */
#ifndef STM32F10X_CL
  #define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 13)
#else
  #define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 27)
#endif /* STM32F10X_CL */ 
/**
  * @}
  */

/** @defgroup CAN_filter_mode 
  * @{
  */

#define CAN_FilterMode_IdMask       ((uint8_t)0x00)  /*!< identifier/mask mode */  /* 标识符/掩码模式 */
#define CAN_FilterMode_IdList       ((uint8_t)0x01)  /*!< identifier list mode */  /* 标识符列表模式 */

#define IS_CAN_FILTER_MODE(MODE) (((MODE) == CAN_FilterMode_IdMask) || \
                                  ((MODE) == CAN_FilterMode_IdList))
/**
  * @}
  */

/** @defgroup CAN_filter_scale 
  * @{
  */

#define CAN_FilterScale_16bit       ((uint8_t)0x00) /*!< Two 16-bit filters */  /* 两个16位过滤器 */
#define CAN_FilterScale_32bit       ((uint8_t)0x01) /*!< One 32-bit filter */  /* 一个32位过滤器 */

#define IS_CAN_FILTER_SCALE(SCALE) (((SCALE) == CAN_FilterScale_16bit) || \
                                    ((SCALE) == CAN_FilterScale_32bit))

/**
  * @}
  */

/** @defgroup CAN_filter_FIFO
  * @{
  */

#define CAN_Filter_FIFO0             ((uint8_t)0x00)  /*!< Filter FIFO 0 assignment for filter x */  /* 滤波器关联FIFO0 */
#define CAN_Filter_FIFO1             ((uint8_t)0x01)  /*!< Filter FIFO 1 assignment for filter x */  /* 滤波器关联FIFO1 */
#define IS_CAN_FILTER_FIFO(FIFO) (((FIFO) == CAN_FilterFIFO0) || \
                                  ((FIFO) == CAN_FilterFIFO1))
/**
  * @}
  */

/** @defgroup Start_bank_filter_for_slave_CAN 
  * @{
  */
#define IS_CAN_BANKNUMBER(BANKNUMBER) (((BANKNUMBER) >= 1) && ((BANKNUMBER) <= 27))
/**
  * @}
  */

/** @defgroup CAN_Tx 
  * @{
  */

#define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ((TRANSMITMAILBOX) <= ((uint8_t)0x02))
#define IS_CAN_STDID(STDID)   ((STDID) <= ((uint32_t)0x7FF))
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= ((uint32_t)0x1FFFFFFF))
#define IS_CAN_DLC(DLC)       ((DLC) <= ((uint8_t)0x08))

/**
  * @}
  */

/** @defgroup CAN_identifier_type 
  * @{
  */

#define CAN_Id_Standard             ((uint32_t)0x00000000)  /*!< Standard Id */  /* 标准标识符 */
#define CAN_Id_Extended             ((uint32_t)0x00000004)  /*!< Extended Id */  /* 扩展标识符 */
#define IS_CAN_IDTYPE(IDTYPE) (((IDTYPE) == CAN_Id_Standard) || \
                               ((IDTYPE) == CAN_Id_Extended))
/**
  * @}
  */

/** @defgroup CAN_remote_transmission_request 
  * @{
  */

#define CAN_RTR_Data                ((uint32_t)0x00000000)  /*!< Data frame */  /* 数据帧 */
#define CAN_RTR_Remote              ((uint32_t)0x00000002)  /*!< Remote frame */  /* 远程帧 */
#define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_Data) || ((RTR) == CAN_RTR_Remote))

/**
  * @}
  */

/** @defgroup CAN_transmit_constants 
  * @{
  */

#define CAN_TxStatus_Failed         ((uint8_t)0x00)/*!< CAN transmission failed */  /* 发送失败 */
#define CAN_TxStatus_Ok             ((uint8_t)0x01) /*!< CAN transmission succeeded */  /* 发送成功 */
#define CAN_TxStatus_Pending        ((uint8_t)0x02) /*!< CAN transmission pending */  /* 发送挂起 */
#define CAN_TxStatus_NoMailBox      ((uint8_t)0x04) /*!< CAN cell did not provide an empty mailbox */  /* 无空邮箱 */

/**
  * @}
  */

/** @defgroup CAN_receive_FIFO_number_constants 
  * @{
  */

#define CAN_FIFO0                 ((uint8_t)0x00) /*!< CAN FIFO 0 used to receive */  /* 接收FIFO0 */
#define CAN_FIFO1                 ((uint8_t)0x01) /*!< CAN FIFO 1 used to receive */  /* 接收FIFO1 */

#define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))

/**
  * @}
  */

/** @defgroup CAN_sleep_constants 
  * @{
  */

#define CAN_Sleep_Failed     ((uint8_t)0x00) /*!< CAN did not enter the sleep mode */  /* 未进入睡眠模式 */
#define CAN_Sleep_Ok         ((uint8_t)0x01) /*!< CAN entered the sleep mode */  /* 已进入睡眠模式 */

/**
  * @}
  */

/** @defgroup CAN_wake_up_constants 
  * @{
  */

#define CAN_WakeUp_Failed        ((uint8_t)0x00) /*!< CAN did not leave the sleep mode */  /* 未退出睡眠模式 */
#define CAN_WakeUp_Ok            ((uint8_t)0x01) /*!< CAN leaved the sleep mode */  /* 已退出睡眠模式 */

/**
  * @}
  */

/**
  * @defgroup   CAN_Error_Code_constants
  * @{
  */  
                                                                
#define CAN_ErrorCode_NoErr           ((uint8_t)0x00) /*!< No Error */  /* 无错误 */ 
#define	CAN_ErrorCode_StuffErr        ((uint8_t)0x10) /*!< Stuff Error */  /* 填充错误 */ 
#define	CAN_ErrorCode_FormErr         ((uint8_t)0x20) /*!< Form Error */  /* 格式错误 */ 
#define	CAN_ErrorCode_ACKErr          ((uint8_t)0x30) /*!< Acknowledgment Error */  /* 应答错误 */ 
#define	CAN_ErrorCode_BitRecessiveErr ((uint8_t)0x40) /*!< Bit Recessive Error */  /* 位隐性错误 */ 
#define	CAN_ErrorCode_BitDominantErr  ((uint8_t)0x50) /*!< Bit Dominant Error */  /* 位显性错误 */ 
#define	CAN_ErrorCode_CRCErr          ((uint8_t)0x60) /*!< CRC Error  */  /* CRC错误 */ 
#define	CAN_ErrorCode_SoftwareSetErr  ((uint8_t)0x70) /*!< Software Set Error */  /* 软件设置错误 */ 


/**
  * @}
  */

/** @defgroup CAN_flags 
  * @{
  */
/* If the flag is 0x3XXXXXXX, it means that it can be used with CAN_GetFlagStatus()
   and CAN_ClearFlag() functions. */
/* If the flag is 0x1XXXXXXX, it means that it can only be used with CAN_GetFlagStatus() function.  */

/* Transmit Flags */
#define CAN_FLAG_RQCP0             ((uint32_t)0x38000001) /*!< Request MailBox0 Flag */  /* 邮箱0请求完成标志 */
#define CAN_FLAG_RQCP1             ((uint32_t)0x38000100) /*!< Request MailBox1 Flag */  /* 邮箱1请求完成标志 */
#define CAN_FLAG_RQCP2             ((uint32_t)0x38010000) /*!< Request MailBox2 Flag */  /* 邮箱2请求完成标志 */

/* Receive Flags */
#define CAN_FLAG_FMP0              ((uint32_t)0x12000003) /*!< FIFO 0 Message Pending Flag */  /* FIFO0报文挂起标志 */
#define CAN_FLAG_FF0               ((uint32_t)0x32000008) /*!< FIFO 0 Full Flag            */  /* FIFO0满标志 */
#define CAN_FLAG_FOV0              ((uint32_t)0x32000010) /*!< FIFO 0 Overrun Flag         */  /* FIFO0溢出标志 */
#define CAN_FLAG_FMP1              ((uint32_t)0x14000003) /*!< FIFO 1 Message Pending Flag */  /* FIFO1报文挂起标志 */
#define CAN_FLAG_FF1               ((uint32_t)0x34000008) /*!< FIFO 1 Full Flag            */  /* FIFO1满标志 */
#define CAN_FLAG_FOV1              ((uint32_t)0x34000010) /*!< FIFO 1 Overrun Flag         */  /* FIFO1溢出标志 */

/* Operating Mode Flags */
#define CAN_FLAG_WKU               ((uint32_t)0x31000008) /*!< Wake up Flag */  /* 唤醒标志 */
#define CAN_FLAG_SLAK              ((uint32_t)0x31000012) /*!< Sleep acknowledge Flag */  /* 睡眠应答标志 */
/* Note: When SLAK intterupt is disabled (SLKIE=0), no polling on SLAKI is possible. 
         In this case the SLAK bit can be polled.*/

/* Error Flags */
#define CAN_FLAG_EWG               ((uint32_t)0x10F00001) /*!< Error Warning Flag   */  /* 错误警告标志 */
#define CAN_FLAG_EPV               ((uint32_t)0x10F00002) /*!< Error Passive Flag   */  /* 错误被动标志 */
#define CAN_FLAG_BOF               ((uint32_t)0x10F00004) /*!< Bus-Off Flag         */  /* 总线关闭标志 */
#define CAN_FLAG_LEC               ((uint32_t)0x30F00070) /*!< Last error code Flag */  /* 最后错误代码标志 */

#define IS_CAN_GET_FLAG(FLAG) (((FLAG) == CAN_FLAG_LEC)  || ((FLAG) == CAN_FLAG_BOF)   || \
                               ((FLAG) == CAN_FLAG_EPV)  || ((FLAG) == CAN_FLAG_EWG)   || \
                               ((FLAG) == CAN_FLAG_WKU)  || ((FLAG) == CAN_FLAG_FOV0)  || \
                               ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FMP0)  || \
                               ((FLAG) == CAN_FLAG_FOV1) || ((FLAG) == CAN_FLAG_FF1)   || \
                               ((FLAG) == CAN_FLAG_FMP1) || ((FLAG) == CAN_FLAG_RQCP2) || \
                               ((FLAG) == CAN_FLAG_RQCP1)|| ((FLAG) == CAN_FLAG_RQCP0) || \
                               ((FLAG) == CAN_FLAG_SLAK ))

#define IS_CAN_CLEAR_FLAG(FLAG)(((FLAG) == CAN_FLAG_LEC) || ((FLAG) == CAN_FLAG_RQCP2) || \
                                ((FLAG) == CAN_FLAG_RQCP1)  || ((FLAG) == CAN_FLAG_RQCP0) || \
                                ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FOV0) ||\
                                ((FLAG) == CAN_FLAG_FF1) || ((FLAG) == CAN_FLAG_FOV1) || \
                                ((FLAG) == CAN_FLAG_WKU) || ((FLAG) == CAN_FLAG_SLAK))
/**
  * @}
  */

  
/** @defgroup CAN_interrupts 
  * @{
  */


  
#define CAN_IT_TME                  ((uint32_t)0x00000001) /*!< Transmit mailbox empty Interrupt*/  /* 发送邮箱空中断 */

/* Receive Interrupts */
#define CAN_IT_FMP0                 ((uint32_t)0x00000002) /*!< FIFO 0 message pending Interrupt*/  /* FIFO0报文挂起中断 */
#define CAN_IT_FF0                  ((uint32_t)0x00000004) /*!< FIFO 0 full Interrupt*/  /* FIFO0满中断 */
#define CAN_IT_FOV0                 ((uint32_t)0x00000008) /*!< FIFO 0 overrun Interrupt*/  /* FIFO0溢出中断 */
#define CAN_IT_FMP1                 ((uint32_t)0x00000010) /*!< FIFO 1 message pending Interrupt*/  /* FIFO1报文挂起中断 */
#define CAN_IT_FF1                  ((uint32_t)0x00000020) /*!< FIFO 1 full Interrupt*/  /* FIFO1满中断 */
#define CAN_IT_FOV1                 ((uint32_t)0x00000040) /*!< FIFO 1 overrun Interrupt*/  /* FIFO1溢出中断 */

/* Operating Mode Interrupts */
#define CAN_IT_WKU                  ((uint32_t)0x00010000) /*!< Wake-up Interrupt*/  /* 唤醒中断 */
#define CAN_IT_SLK                  ((uint32_t)0x00020000) /*!< Sleep acknowledge Interrupt*/  /* 睡眠应答中断 */

/* Error Interrupts */
#define CAN_IT_EWG                  ((uint32_t)0x00000100) /*!< Error warning Interrupt*/  /* 错误警告中断 */
#define CAN_IT_EPV                  ((uint32_t)0x00000200) /*!< Error passive Interrupt*/  /* 错误被动中断 */
#define CAN_IT_BOF                  ((uint32_t)0x00000400) /*!< Bus-off Interrupt*/  /* 总线关闭中断 */
#define CAN_IT_LEC                  ((uint32_t)0x00000800) /*!< Last error code Interrupt*/  /* 最后错误代码中断 */
#define CAN_IT_ERR                  ((uint32_t)0x00008000) /*!< Error Interrupt*/  /* 错误中断 */

/* Flags named as Interrupts : kept only for FW compatibility */
#define CAN_IT_RQCP0   CAN_IT_TME  /* 兼容旧名,同CAN_IT_TME */
#define CAN_IT_RQCP1   CAN_IT_TME  /* 兼容旧名,同CAN_IT_TME */
#define CAN_IT_RQCP2   CAN_IT_TME  /* 兼容旧名,同CAN_IT_TME */


#define IS_CAN_IT(IT)        (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FMP0)  ||\
                             ((IT) == CAN_IT_FF0)  || ((IT) == CAN_IT_FOV0)  ||\
                             ((IT) == CAN_IT_FMP1) || ((IT) == CAN_IT_FF1)   ||\
                             ((IT) == CAN_IT_FOV1) || ((IT) == CAN_IT_EWG)   ||\
                             ((IT) == CAN_IT_EPV)  || ((IT) == CAN_IT_BOF)   ||\
                             ((IT) == CAN_IT_LEC)  || ((IT) == CAN_IT_ERR)   ||\
                             ((IT) == CAN_IT_WKU)  || ((IT) == CAN_IT_SLK))

#define IS_CAN_CLEAR_IT(IT) (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FF0)    ||\
                             ((IT) == CAN_IT_FOV0)|| ((IT) == CAN_IT_FF1)    ||\
                             ((IT) == CAN_IT_FOV1)|| ((IT) == CAN_IT_EWG)    ||\
                             ((IT) == CAN_IT_EPV) || ((IT) == CAN_IT_BOF)    ||\
                             ((IT) == CAN_IT_LEC) || ((IT) == CAN_IT_ERR)    ||\
                             ((IT) == CAN_IT_WKU) || ((IT) == CAN_IT_SLK))

/**
  * @}
  */

/** @defgroup CAN_Legacy 
  * @{
  */
#define CANINITFAILED               CAN_InitStatus_Failed  /* 兼容旧名:CAN初始化失败 */
#define CANINITOK                   CAN_InitStatus_Success  /* 兼容旧名:CAN初始化成功 */
#define CAN_FilterFIFO0             CAN_Filter_FIFO0  /* 兼容旧名:滤波器FIFO0 */
#define CAN_FilterFIFO1             CAN_Filter_FIFO1  /* 兼容旧名:滤波器FIFO1 */
#define CAN_ID_STD                  CAN_Id_Standard  /* 兼容旧名:标准标识符 */           
#define CAN_ID_EXT                  CAN_Id_Extended  /* 兼容旧名:扩展标识符 */
#define CAN_RTR_DATA                CAN_RTR_Data  /* 兼容旧名:数据帧 */         
#define CAN_RTR_REMOTE              CAN_RTR_Remote  /* 兼容旧名:远程帧 */
#define CANTXFAILE                  CAN_TxStatus_Failed  /* 兼容旧名:发送失败 */
#define CANTXOK                     CAN_TxStatus_Ok  /* 兼容旧名:发送成功 */
#define CANTXPENDING                CAN_TxStatus_Pending  /* 兼容旧名:发送挂起 */
#define CAN_NO_MB                   CAN_TxStatus_NoMailBox  /* 兼容旧名:无空邮箱 */
#define CANSLEEPFAILED              CAN_Sleep_Failed  /* 兼容旧名:未进入睡眠 */
#define CANSLEEPOK                  CAN_Sleep_Ok  /* 兼容旧名:已进入睡眠 */
#define CANWAKEUPFAILED             CAN_WakeUp_Failed  /* 兼容旧名:未退出睡眠 */        
#define CANWAKEUPOK                 CAN_WakeUp_Ok  /* 兼容旧名:已退出睡眠 */        

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CAN_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup CAN_Exported_Functions
  * @{
  */
/*  Function used to set the CAN configuration to the default reset state *****/ 
void CAN_DeInit(CAN_TypeDef* CANx);  /* 将CAN外设寄存器复位为默认值 */

/* Initialization and Configuration functions *********************************/ 
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);  /* 根据结构体初始化CAN */
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);  /* 初始化CAN过滤器 */
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);  /* 用默认值填充CAN初始化结构体 */
void CAN_SlaveStartBank(uint8_t CAN_BankNumber);  /* 设置从CAN的起始过滤器组 */ 
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState);  /* 使能或关闭CAN调试冻结 */
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState);  /* 使能或关闭时间触发通信模式 */

/* Transmit functions *********************************************************/
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage);  /* 选择空邮箱并发送报文 */
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);  /* 查询报文发送状态 */
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);  /* 取消指定邮箱的发送 */

/* Receive functions **********************************************************/
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);  /* 从FIFO读取接收报文 */
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);  /* 释放指定接收FIFO */
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);  /* 返回FIFO中待处理报文数 */


/* Operation modes functions **************************************************/
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode);  /* 请求进入指定工作模式 */
uint8_t CAN_Sleep(CAN_TypeDef* CANx);  /* 请求进入睡眠模式 */
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);  /* 退出睡眠模式 */

/* Error management functions *************************************************/
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx);  /* 获取最后错误代码 */
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx);  /* 获取接收错误计数器 */
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx);  /* 获取发送错误计数器低字节 */

/* Interrupts and flags management functions **********************************/
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState);  /* 使能或关闭CAN中断 */
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);  /* 检查CAN标志位状态 */
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG);  /* 清除CAN标志位 */
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);  /* 检查CAN中断状态 */
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT);  /* 清除CAN中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_CAN_H */
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
