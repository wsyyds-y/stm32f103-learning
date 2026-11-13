/**
  ******************************************************************************
  * @file    stm32f10x_i2c.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the I2C firmware 
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
#ifndef __STM32F10x_I2C_H
#define __STM32F10x_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Types
  * @{
  */

/** 
  * @brief  I2C Init structure definition  
  */

typedef struct
{
  uint32_t I2C_ClockSpeed;          /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 400kHz */
  /* I2C时钟频率 */

  uint16_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */
  /* I2C工作模式 */

  uint16_t I2C_DutyCycle;           /*!< Specifies the I2C fast mode duty cycle.
                                         This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */
  /* 快速模式占空比 */

  uint16_t I2C_OwnAddress1;         /*!< Specifies the first device own address.
                                         This parameter can be a 7-bit or 10-bit address. */
  /* 器件自身地址1 */

  uint16_t I2C_Ack;                 /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement */
  /* 应答使能 */

  uint16_t I2C_AcknowledgedAddress; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */
  /* 应答地址位数 */
}I2C_InitTypeDef;

/**
  * @}
  */ 


/** @defgroup I2C_Exported_Constants
  * @{
  */

#define IS_I2C_ALL_PERIPH(PERIPH) (((PERIPH) == I2C1) || \
                                   ((PERIPH) == I2C2))
/** @defgroup I2C_mode 
  * @{
  */

#define I2C_Mode_I2C                    ((uint16_t)0x0000)  /* I2C模式 */
#define I2C_Mode_SMBusDevice            ((uint16_t)0x0002)  /* SMBus设备模式 */  
#define I2C_Mode_SMBusHost              ((uint16_t)0x000A)  /* SMBus主机模式 */
#define IS_I2C_MODE(MODE) (((MODE) == I2C_Mode_I2C) || \
                           ((MODE) == I2C_Mode_SMBusDevice) || \
                           ((MODE) == I2C_Mode_SMBusHost))
/**
  * @}
  */

/** @defgroup I2C_duty_cycle_in_fast_mode 
  * @{
  */

#define I2C_DutyCycle_16_9              ((uint16_t)0x4000) /*!< I2C fast mode Tlow/Thigh = 16/9 */  /* 快速模式Tlow/Thigh=16/9 */
#define I2C_DutyCycle_2                 ((uint16_t)0xBFFF) /*!< I2C fast mode Tlow/Thigh = 2 */  /* 快速模式Tlow/Thigh=2 */
#define IS_I2C_DUTY_CYCLE(CYCLE) (((CYCLE) == I2C_DutyCycle_16_9) || \
                                  ((CYCLE) == I2C_DutyCycle_2))
/**
  * @}
  */ 

/** @defgroup I2C_acknowledgement
  * @{
  */

#define I2C_Ack_Enable                  ((uint16_t)0x0400)  /* 使能应答 */
#define I2C_Ack_Disable                 ((uint16_t)0x0000)  /* 关闭应答 */
#define IS_I2C_ACK_STATE(STATE) (((STATE) == I2C_Ack_Enable) || \
                                 ((STATE) == I2C_Ack_Disable))
/**
  * @}
  */

/** @defgroup I2C_transfer_direction 
  * @{
  */

#define  I2C_Direction_Transmitter      ((uint8_t)0x00)  /* 发送方向 */
#define  I2C_Direction_Receiver         ((uint8_t)0x01)  /* 接收方向 */
#define IS_I2C_DIRECTION(DIRECTION) (((DIRECTION) == I2C_Direction_Transmitter) || \
                                     ((DIRECTION) == I2C_Direction_Receiver))
/**
  * @}
  */

/** @defgroup I2C_acknowledged_address 
  * @{
  */

#define I2C_AcknowledgedAddress_7bit    ((uint16_t)0x4000)  /* 应答7位地址 */
#define I2C_AcknowledgedAddress_10bit   ((uint16_t)0xC000)  /* 应答10位地址 */
#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) (((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
                                             ((ADDRESS) == I2C_AcknowledgedAddress_10bit))
/**
  * @}
  */ 

/** @defgroup I2C_registers 
  * @{
  */

#define I2C_Register_CR1                ((uint8_t)0x00)  /* CR1寄存器地址 */
#define I2C_Register_CR2                ((uint8_t)0x04)  /* CR2寄存器地址 */
#define I2C_Register_OAR1               ((uint8_t)0x08)  /* OAR1寄存器地址 */
#define I2C_Register_OAR2               ((uint8_t)0x0C)  /* OAR2寄存器地址 */
#define I2C_Register_DR                 ((uint8_t)0x10)  /* DR寄存器地址 */
#define I2C_Register_SR1                ((uint8_t)0x14)  /* SR1寄存器地址 */
#define I2C_Register_SR2                ((uint8_t)0x18)  /* SR2寄存器地址 */
#define I2C_Register_CCR                ((uint8_t)0x1C)  /* CCR寄存器地址 */
#define I2C_Register_TRISE              ((uint8_t)0x20)  /* TRISE寄存器地址 */
#define IS_I2C_REGISTER(REGISTER) (((REGISTER) == I2C_Register_CR1) || \
                                   ((REGISTER) == I2C_Register_CR2) || \
                                   ((REGISTER) == I2C_Register_OAR1) || \
                                   ((REGISTER) == I2C_Register_OAR2) || \
                                   ((REGISTER) == I2C_Register_DR) || \
                                   ((REGISTER) == I2C_Register_SR1) || \
                                   ((REGISTER) == I2C_Register_SR2) || \
                                   ((REGISTER) == I2C_Register_CCR) || \
                                   ((REGISTER) == I2C_Register_TRISE))
/**
  * @}
  */

/** @defgroup I2C_SMBus_alert_pin_level 
  * @{
  */

#define I2C_SMBusAlert_Low              ((uint16_t)0x2000)  /* SMBusAlert引脚低电平 */
#define I2C_SMBusAlert_High             ((uint16_t)0xDFFF)  /* SMBusAlert引脚高电平 */
#define IS_I2C_SMBUS_ALERT(ALERT) (((ALERT) == I2C_SMBusAlert_Low) || \
                                   ((ALERT) == I2C_SMBusAlert_High))
/**
  * @}
  */

/** @defgroup I2C_PEC_position 
  * @{
  */

#define I2C_PECPosition_Next            ((uint16_t)0x0800)  /* PEC位于下一字节 */
#define I2C_PECPosition_Current         ((uint16_t)0xF7FF)  /* PEC位于当前字节 */
#define IS_I2C_PEC_POSITION(POSITION) (((POSITION) == I2C_PECPosition_Next) || \
                                       ((POSITION) == I2C_PECPosition_Current))
/**
  * @}
  */ 

/** @defgroup I2C_NCAK_position 
  * @{
  */

#define I2C_NACKPosition_Next           ((uint16_t)0x0800)  /* NACK位于下一字节 */
#define I2C_NACKPosition_Current        ((uint16_t)0xF7FF)  /* NACK位于当前字节 */
#define IS_I2C_NACK_POSITION(POSITION)  (((POSITION) == I2C_NACKPosition_Next) || \
                                         ((POSITION) == I2C_NACKPosition_Current))
/**
  * @}
  */ 

/** @defgroup I2C_interrupts_definition 
  * @{
  */

#define I2C_IT_BUF                      ((uint16_t)0x0400)  /* 缓冲中断 */
#define I2C_IT_EVT                      ((uint16_t)0x0200)  /* 事件中断 */
#define I2C_IT_ERR                      ((uint16_t)0x0100)  /* 错误中断 */
#define IS_I2C_CONFIG_IT(IT) ((((IT) & (uint16_t)0xF8FF) == 0x00) && ((IT) != 0x00))
/**
  * @}
  */ 

/** @defgroup I2C_interrupts_definition 
  * @{
  */

#define I2C_IT_SMBALERT                 ((uint32_t)0x01008000)  /* SMBus警报中断 */
#define I2C_IT_TIMEOUT                  ((uint32_t)0x01004000)  /* 超时错误中断 */
#define I2C_IT_PECERR                   ((uint32_t)0x01001000)  /* PEC错误中断 */
#define I2C_IT_OVR                      ((uint32_t)0x01000800)  /* 溢出/下溢中断 */
#define I2C_IT_AF                       ((uint32_t)0x01000400)  /* 应答失败中断 */
#define I2C_IT_ARLO                     ((uint32_t)0x01000200)  /* 仲裁丢失中断 */
#define I2C_IT_BERR                     ((uint32_t)0x01000100)  /* 总线错误中断 */
#define I2C_IT_TXE                      ((uint32_t)0x06000080)  /* 发送数据寄存器空中断 */
#define I2C_IT_RXNE                     ((uint32_t)0x06000040)  /* 接收数据寄存器非空中断 */
#define I2C_IT_STOPF                    ((uint32_t)0x02000010)  /* 停止条件检测中断 */
#define I2C_IT_ADD10                    ((uint32_t)0x02000008)  /* 10位地址头发送中断 */
#define I2C_IT_BTF                      ((uint32_t)0x02000004)  /* 字节传输完成中断 */
#define I2C_IT_ADDR                     ((uint32_t)0x02000002)  /* 地址发送/匹配中断 */
#define I2C_IT_SB                       ((uint32_t)0x02000001)  /* 起始位中断 */

#define IS_I2C_CLEAR_IT(IT) ((((IT) & (uint16_t)0x20FF) == 0x00) && ((IT) != (uint16_t)0x00))

#define IS_I2C_GET_IT(IT) (((IT) == I2C_IT_SMBALERT) || ((IT) == I2C_IT_TIMEOUT) || \
                           ((IT) == I2C_IT_PECERR) || ((IT) == I2C_IT_OVR) || \
                           ((IT) == I2C_IT_AF) || ((IT) == I2C_IT_ARLO) || \
                           ((IT) == I2C_IT_BERR) || ((IT) == I2C_IT_TXE) || \
                           ((IT) == I2C_IT_RXNE) || ((IT) == I2C_IT_STOPF) || \
                           ((IT) == I2C_IT_ADD10) || ((IT) == I2C_IT_BTF) || \
                           ((IT) == I2C_IT_ADDR) || ((IT) == I2C_IT_SB))
/**
  * @}
  */

/** @defgroup I2C_flags_definition 
  * @{
  */

/** 
  * @brief  SR2 register flags  
  */

#define I2C_FLAG_DUALF                  ((uint32_t)0x00800000)  /* 双地址标志（从机） */
#define I2C_FLAG_SMBHOST                ((uint32_t)0x00400000)  /* SMBus主机头标志 */
#define I2C_FLAG_SMBDEFAULT             ((uint32_t)0x00200000)  /* SMBus默认头标志 */
#define I2C_FLAG_GENCALL                ((uint32_t)0x00100000)  /* 广播呼叫头标志 */
#define I2C_FLAG_TRA                    ((uint32_t)0x00040000)  /* 发送/接收标志 */
#define I2C_FLAG_BUSY                   ((uint32_t)0x00020000)  /* 总线忙标志 */
#define I2C_FLAG_MSL                    ((uint32_t)0x00010000)  /* 主/从模式标志 */

/** 
  * @brief  SR1 register flags  
  */

#define I2C_FLAG_SMBALERT               ((uint32_t)0x10008000)  /* SMBus警报标志 */
#define I2C_FLAG_TIMEOUT                ((uint32_t)0x10004000)  /* 超时或Tlow错误标志 */
#define I2C_FLAG_PECERR                 ((uint32_t)0x10001000)  /* 接收PEC错误标志 */
#define I2C_FLAG_OVR                    ((uint32_t)0x10000800)  /* 溢出/下溢标志 */
#define I2C_FLAG_AF                     ((uint32_t)0x10000400)  /* 应答失败标志 */
#define I2C_FLAG_ARLO                   ((uint32_t)0x10000200)  /* 仲裁丢失标志 */
#define I2C_FLAG_BERR                   ((uint32_t)0x10000100)  /* 总线错误标志 */
#define I2C_FLAG_TXE                    ((uint32_t)0x10000080)  /* 发送数据寄存器空标志 */
#define I2C_FLAG_RXNE                   ((uint32_t)0x10000040)  /* 接收数据寄存器非空标志 */
#define I2C_FLAG_STOPF                  ((uint32_t)0x10000010)  /* 停止条件检测标志 */
#define I2C_FLAG_ADD10                  ((uint32_t)0x10000008)  /* 10位地址头发送标志 */
#define I2C_FLAG_BTF                    ((uint32_t)0x10000004)  /* 字节传输完成标志 */
#define I2C_FLAG_ADDR                   ((uint32_t)0x10000002)  /* 地址发送/匹配标志 */
#define I2C_FLAG_SB                     ((uint32_t)0x10000001)  /* 起始位标志 */

#define IS_I2C_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0x20FF) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_I2C_GET_FLAG(FLAG) (((FLAG) == I2C_FLAG_DUALF) || ((FLAG) == I2C_FLAG_SMBHOST) || \
                               ((FLAG) == I2C_FLAG_SMBDEFAULT) || ((FLAG) == I2C_FLAG_GENCALL) || \
                               ((FLAG) == I2C_FLAG_TRA) || ((FLAG) == I2C_FLAG_BUSY) || \
                               ((FLAG) == I2C_FLAG_MSL) || ((FLAG) == I2C_FLAG_SMBALERT) || \
                               ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_PECERR) || \
                               ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_AF) || \
                               ((FLAG) == I2C_FLAG_ARLO) || ((FLAG) == I2C_FLAG_BERR) || \
                               ((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_RXNE) || \
                               ((FLAG) == I2C_FLAG_STOPF) || ((FLAG) == I2C_FLAG_ADD10) || \
                               ((FLAG) == I2C_FLAG_BTF) || ((FLAG) == I2C_FLAG_ADDR) || \
                               ((FLAG) == I2C_FLAG_SB))
/**
  * @}
  */

/** @defgroup I2C_Events 
  * @{
  */

/*========================================
     
                     I2C Master Events (Events grouped in order of communication)
                                                        ==========================================*/
/** 
  * @brief  Communication start
  * 
  * After sending the START condition (I2C_GenerateSTART() function) the master 
  * has to wait for this event. It means that the Start condition has been correctly 
  * released on the I2C bus (the bus is free, no other devices is communicating).
  * 
  */
/* --EV5 */
#define  I2C_EVENT_MASTER_MODE_SELECT                      ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */  /* 主机起始条件已发出（EV5） */

/** 
  * @brief  Address Acknowledge
  * 
  * After checking on EV5 (start condition correctly released on the bus), the 
  * master sends the address of the slave(s) with which it will communicate 
  * (I2C_Send7bitAddress() function, it also determines the direction of the communication: 
  * Master transmitter or Receiver). Then the master has to wait that a slave acknowledges 
  * his address. If an acknowledge is sent on the bus, one of the following events will 
  * be set:
  * 
  *  1) In case of Master Receiver (7-bit addressing): the I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED 
  *     event is set.
  *  
  *  2) In case of Master Transmitter (7-bit addressing): the I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED 
  *     is set
  *  
  *  3) In case of 10-Bit addressing mode, the master (just after generating the START 
  *  and checking on EV5) has to send the header of 10-bit addressing mode (I2C_SendData() 
  *  function). Then master should wait on EV9. It means that the 10-bit addressing 
  *  header has been correctly sent on the bus. Then master should send the second part of 
  *  the 10-bit address (LSB) using the function I2C_Send7bitAddress(). Then master 
  *  should wait for event EV6. 
  *     
  */

/* --EV6 */
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */  /* 主机发送模式已选中（EV6） */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */  /* 主机接收模式已选中（EV6） */
/* --EV9 */
#define  I2C_EVENT_MASTER_MODE_ADDRESS10                   ((uint32_t)0x00030008)  /* BUSY, MSL and ADD10 flags */  /* 主机10位地址头已发送（EV9） */

/** 
  * @brief Communication events
  * 
  * If a communication is established (START condition generated and slave address 
  * acknowledged) then the master has to check on one of the following events for 
  * communication procedures:
  *  
  * 1) Master Receiver mode: The master has to wait on the event EV7 then to read 
  *    the data received from the slave (I2C_ReceiveData() function).
  * 
  * 2) Master Transmitter mode: The master has to send data (I2C_SendData() 
  *    function) then to wait on event EV8 or EV8_2.
  *    These two events are similar: 
  *     - EV8 means that the data has been written in the data register and is 
  *       being shifted out.
  *     - EV8_2 means that the data has been physically shifted out and output 
  *       on the bus.
  *     In most cases, using EV8 is sufficient for the application.
  *     Using EV8_2 leads to a slower communication but ensure more reliable test.
  *     EV8_2 is also more suitable than EV8 for testing on the last data transmission 
  *     (before Stop condition generation).
  *     
  *  @note In case the  user software does not guarantee that this event EV7 is 
  *  managed before the current byte end of transfer, then user may check on EV7 
  *  and BTF flag at the same time (ie. (I2C_EVENT_MASTER_BYTE_RECEIVED | I2C_FLAG_BTF)).
  *  In this case the communication may be slower.
  * 
  */

/* Master RECEIVER mode -----------------------------*/ 
/* --EV7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */  /* 主机已收到一个字节（EV7） */

/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */  /* 主机数据发送中（EV8） */
/* --EV8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED                 ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */  /* 主机数据发送完成（EV8_2） */


/*========================================
     
                     I2C Slave Events (Events grouped in order of communication)
                                                        ==========================================*/

/** 
  * @brief  Communication start events
  * 
  * Wait on one of these events at the start of the communication. It means that 
  * the I2C peripheral detected a Start condition on the bus (generated by master 
  * device) followed by the peripheral address. The peripheral generates an ACK 
  * condition on the bus (if the acknowledge feature is enabled through function 
  * I2C_AcknowledgeConfig()) and the events listed above are set :
  *  
  * 1) In normal case (only one address managed by the slave), when the address 
  *   sent by the master matches the own address of the peripheral (configured by 
  *   I2C_OwnAddress1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set 
  *   (where XXX could be TRANSMITTER or RECEIVER).
  *    
  * 2) In case the address sent by the master matches the second address of the 
  *   peripheral (configured by the function I2C_OwnAddress2Config() and enabled 
  *   by the function I2C_DualAddressCmd()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED 
  *   (where XXX could be TRANSMITTER or RECEIVER) are set.
  *   
  * 3) In case the address sent by the master is General Call (address 0x00) and 
  *   if the General Call is enabled for the peripheral (using function I2C_GeneralCallCmd()) 
  *   the following event is set I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED.   
  * 
  */

/* --EV1  (all the events below are variants of EV1) */   
/* 1) Case of One Single Address managed by the slave */
#define  I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED          ((uint32_t)0x00020002) /* BUSY and ADDR flags */  /* 从机接收地址匹配（EV1） */
#define  I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED       ((uint32_t)0x00060082) /* TRA, BUSY, TXE and ADDR flags */  /* 从机发送地址匹配（EV1） */

/* 2) Case of Dual address managed by the slave */
#define  I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED    ((uint32_t)0x00820000)  /* DUALF and BUSY flags */  /* 从机接收第二地址匹配（EV1） */
#define  I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ((uint32_t)0x00860080)  /* DUALF, TRA, BUSY and TXE flags */  /* 从机发送第二地址匹配（EV1） */

/* 3) Case of General Call enabled for the slave */
#define  I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED        ((uint32_t)0x00120000)  /* GENCALL and BUSY flags */  /* 从机广播呼叫地址匹配（EV1） */

/** 
  * @brief  Communication events
  * 
  * Wait on one of these events when EV1 has already been checked and: 
  * 
  * - Slave RECEIVER mode:
  *     - EV2: When the application is expecting a data byte to be received. 
  *     - EV4: When the application is expecting the end of the communication: master 
  *       sends a stop condition and data transmission is stopped.
  *    
  * - Slave Transmitter mode:
  *    - EV3: When a byte has been transmitted by the slave and the application is expecting 
  *      the end of the byte transmission. The two events I2C_EVENT_SLAVE_BYTE_TRANSMITTED and
  *      I2C_EVENT_SLAVE_BYTE_TRANSMITTING are similar. The second one can optionally be 
  *      used when the user software doesn't guarantee the EV3 is managed before the
  *      current byte end of transfer.
  *    - EV3_2: When the master sends a NACK in order to tell slave that data transmission 
  *      shall end (before sending the STOP condition). In this case slave has to stop sending 
  *      data bytes and expect a Stop condition on the bus.
  *      
  *  @note In case the  user software does not guarantee that the event EV2 is 
  *  managed before the current byte end of transfer, then user may check on EV2 
  *  and BTF flag at the same time (ie. (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_BTF)).
  * In this case the communication may be slower.
  *
  */

/* Slave RECEIVER mode --------------------------*/ 
/* --EV2 */
#define  I2C_EVENT_SLAVE_BYTE_RECEIVED                     ((uint32_t)0x00020040)  /* BUSY and RXNE flags */  /* 从机已收到一个字节（EV2） */
/* --EV4  */
#define  I2C_EVENT_SLAVE_STOP_DETECTED                     ((uint32_t)0x00000010)  /* STOPF flag */  /* 从机检测到停止条件（EV4） */

/* Slave TRANSMITTER mode -----------------------*/
/* --EV3 */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTED                  ((uint32_t)0x00060084)  /* TRA, BUSY, TXE and BTF flags */  /* 从机数据发送完成（EV3） */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTING                 ((uint32_t)0x00060080)  /* TRA, BUSY and TXE flags */  /* 从机数据发送中（EV3） */
/* --EV3_2 */
#define  I2C_EVENT_SLAVE_ACK_FAILURE                       ((uint32_t)0x00000400)  /* AF flag */  /* 从机应答失败（EV3_2） */

/*===========================      End of Events Description           ==========================================*/

#define IS_I2C_EVENT(EVENT) (((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_BYTE_RECEIVED) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)) || \
                             ((EVENT) == I2C_EVENT_SLAVE_BYTE_TRANSMITTED) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL)) || \
                             ((EVENT) == I2C_EVENT_SLAVE_STOP_DETECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_MODE_SELECT) || \
                             ((EVENT) == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_RECEIVED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTING) || \
                             ((EVENT) == I2C_EVENT_MASTER_MODE_ADDRESS10) || \
                             ((EVENT) == I2C_EVENT_SLAVE_ACK_FAILURE))
/**
  * @}
  */

/** @defgroup I2C_own_address1 
  * @{
  */

#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x3FF)
/**
  * @}
  */

/** @defgroup I2C_clock_speed 
  * @{
  */

#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 400000))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup I2C_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Exported_Functions
  * @{
  */

void I2C_DeInit(I2C_TypeDef* I2Cx);  /* 将指定I2C外设寄存器复位为默认值 */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);  /* 根据结构体参数初始化指定I2C外设 */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);  /* 将I2C初始化结构体各成员设为默认值 */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭指定I2C外设 */
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C的DMA请求 */
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 设置下一次DMA传输是否为最后一次 */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 生成I2C起始条件 */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 生成I2C停止条件 */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C应答功能 */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);  /* 配置I2C自身的第二从机地址 */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C双地址模式 */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C广播呼叫功能 */
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);  /* 使能或关闭指定的I2C中断 */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);  /* 通过I2C发送一个数据字节 */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);  /* 返回I2C最近接收到的数据 */
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);  /* 发送7位从机地址并指定传输方向 */
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);  /* 读取指定I2C寄存器的值 */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C软件复位 */
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition);  /* 配置主机接收模式下的NACK位置 */
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert);  /* 控制SMBusAlert引脚的高/低电平 */
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C的PEC传输 */
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition);  /* 配置I2C的PEC位置 */
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭传输字节的PEC计算 */
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);  /* 返回I2C的PEC值 */
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C的ARP功能 */
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);  /* 使能或关闭I2C时钟延展 */
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle);  /* 配置I2C快速模式占空比 */

/**
 * @brief
 ****************************************************************************************
 *
 *                         I2C State Monitoring Functions
 *                       
 ****************************************************************************************   
 * This I2C driver provides three different ways for I2C state monitoring
 *  depending on the application requirements and constraints:
 *        
 *  
 * 1) Basic state monitoring:
 *    Using I2C_CheckEvent() function:
 *    It compares the status registers (SR1 and SR2) content to a given event
 *    (can be the combination of one or more flags).
 *    It returns SUCCESS if the current status includes the given flags 
 *    and returns ERROR if one or more flags are missing in the current status.
 *    - When to use:
 *      - This function is suitable for most applications as well as for startup 
 *      activity since the events are fully described in the product reference manual 
 *      (RM0008).
 *      - It is also suitable for users who need to define their own events.
 *    - Limitations:
 *      - If an error occurs (ie. error flags are set besides to the monitored flags),
 *        the I2C_CheckEvent() function may return SUCCESS despite the communication
 *        hold or corrupted real state. 
 *        In this case, it is advised to use error interrupts to monitor the error
 *        events and handle them in the interrupt IRQ handler.
 *        
 *        @note 
 *        For error management, it is advised to use the following functions:
 *          - I2C_ITConfig() to configure and enable the error interrupts (I2C_IT_ERR).
 *          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
 *            Where x is the peripheral instance (I2C1, I2C2 ...)
 *          - I2C_GetFlagStatus() or I2C_GetITStatus() to be called into I2Cx_ER_IRQHandler()
 *            in order to determine which error occurred.
 *          - I2C_ClearFlag() or I2C_ClearITPendingBit() and/or I2C_SoftwareResetCmd()
 *            and/or I2C_GenerateStop() in order to clear the error flag and source,
 *            and return to correct communication status.
 *            
 *
 *  2) Advanced state monitoring:
 *     Using the function I2C_GetLastEvent() which returns the image of both status 
 *     registers in a single word (uint32_t) (Status Register 2 value is shifted left 
 *     by 16 bits and concatenated to Status Register 1).
 *     - When to use:
 *       - This function is suitable for the same applications above but it allows to
 *         overcome the limitations of I2C_GetFlagStatus() function (see below).
 *         The returned value could be compared to events already defined in the 
 *         library (stm32f10x_i2c.h) or to custom values defined by user.
 *       - This function is suitable when multiple flags are monitored at the same time.
 *       - At the opposite of I2C_CheckEvent() function, this function allows user to
 *         choose when an event is accepted (when all events flags are set and no 
 *         other flags are set or just when the needed flags are set like 
 *         I2C_CheckEvent() function).
 *     - Limitations:
 *       - User may need to define his own events.
 *       - Same remark concerning the error management is applicable for this 
 *         function if user decides to check only regular communication flags (and 
 *         ignores error flags).
 *     
 *
 *  3) Flag-based state monitoring:
 *     Using the function I2C_GetFlagStatus() which simply returns the status of 
 *     one single flag (ie. I2C_FLAG_RXNE ...). 
 *     - When to use:
 *        - This function could be used for specific applications or in debug phase.
 *        - It is suitable when only one flag checking is needed (most I2C events 
 *          are monitored through multiple flags).
 *     - Limitations: 
 *        - When calling this function, the Status register is accessed. Some flags are
 *          cleared when the status register is accessed. So checking the status
 *          of one Flag, may clear other ones.
 *        - Function may need to be called twice or more in order to monitor one 
 *          single event.
 *            
 */

/**
 * 
 *  1) Basic state monitoring
 *******************************************************************************
 */
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);  /* 检查最近的I2C事件是否等于指定事件 */
/**
 * 
 *  2) Advanced state monitoring
 *******************************************************************************
 */
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);  /* 返回I2C最近一次事件 */
/**
 * 
 *  3) Flag-based state monitoring
 *******************************************************************************
 */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);  /* 检查指定I2C标志是否置位 */
/**
 *
 *******************************************************************************
 */

void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);  /* 清除I2C的指定挂起标志 */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);  /* 检查指定I2C中断是否发生 */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);  /* 清除I2C指定的中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F10x_I2C_H */
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
