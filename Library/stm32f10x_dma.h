/**
  ******************************************************************************
  * @file    stm32f10x_dma.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the DMA firmware 
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
#ifndef __STM32F10x_DMA_H
#define __STM32F10x_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/** @defgroup DMA_Exported_Types
  * @{
  */

/** 
  * @brief  DMA Init structure definition
  */

typedef struct
{
  uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx. */  /* 外设基地址 */

  uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx. */  /* 存储器基地址 */

  uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction */
  /* 数据传输方向 */

  uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction. */
  /* 缓冲区数据量（单位为数据单元） */

  uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */
  /* 外设地址是否自增 */

  uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode */
  /* 存储器地址是否自增 */

  uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size */
  /* 外设数据宽度 */

  uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size */
  /* 存储器数据宽度 */

  uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode.
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */
  /* 工作模式：循环或普通 */

  uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level */
  /* 软件优先级 */

  uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory */
  /* 存储器到存储器模式 */
}DMA_InitTypeDef;

/**
  * @}
  */

/** @defgroup DMA_Exported_Constants
  * @{
  */

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5) || \
                                   ((PERIPH) == DMA1_Channel6) || \
                                   ((PERIPH) == DMA1_Channel7) || \
                                   ((PERIPH) == DMA2_Channel1) || \
                                   ((PERIPH) == DMA2_Channel2) || \
                                   ((PERIPH) == DMA2_Channel3) || \
                                   ((PERIPH) == DMA2_Channel4) || \
                                   ((PERIPH) == DMA2_Channel5))

/** @defgroup DMA_data_transfer_direction 
  * @{
  */

#define DMA_DIR_PeripheralDST              ((uint32_t)0x00000010)  /* 数据由存储器传输到外设 */
#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)  /* 数据由外设传输到存储器 */
#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralDST) || \
                         ((DIR) == DMA_DIR_PeripheralSRC))
/**
  * @}
  */

/** @defgroup DMA_peripheral_incremented_mode 
  * @{
  */

#define DMA_PeripheralInc_Enable           ((uint32_t)0x00000040)  /* 外设地址自动递增 */
#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)  /* 外设地址不递增 */
#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Enable) || \
                                            ((STATE) == DMA_PeripheralInc_Disable))
/**
  * @}
  */

/** @defgroup DMA_memory_incremented_mode 
  * @{
  */

#define DMA_MemoryInc_Enable               ((uint32_t)0x00000080)  /* 存储器地址自动递增 */
#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)  /* 存储器地址不递增 */
#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Enable) || \
                                        ((STATE) == DMA_MemoryInc_Disable))
/**
  * @}
  */

/** @defgroup DMA_peripheral_data_size 
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)  /* 外设数据宽度为8位 */
#define DMA_PeripheralDataSize_HalfWord    ((uint32_t)0x00000100)  /* 外设数据宽度为16位 */
#define DMA_PeripheralDataSize_Word        ((uint32_t)0x00000200)  /* 外设数据宽度为32位 */
#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_memory_data_size 
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)  /* 存储器数据宽度为8位 */
#define DMA_MemoryDataSize_HalfWord        ((uint32_t)0x00000400)  /* 存储器数据宽度为16位 */
#define DMA_MemoryDataSize_Word            ((uint32_t)0x00000800)  /* 存储器数据宽度为32位 */
#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_circular_normal_mode 
  * @{
  */

#define DMA_Mode_Circular                  ((uint32_t)0x00000020)  /* 循环模式 */
#define DMA_Mode_Normal                    ((uint32_t)0x00000000)  /* 普通模式（单次传输） */
#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Circular) || ((MODE) == DMA_Mode_Normal))
/**
  * @}
  */

/** @defgroup DMA_priority_level 
  * @{
  */

#define DMA_Priority_VeryHigh              ((uint32_t)0x00003000)  /* 优先级：非常高 */
#define DMA_Priority_High                  ((uint32_t)0x00002000)  /* 优先级：高 */
#define DMA_Priority_Medium                ((uint32_t)0x00001000)  /* 优先级：中 */
#define DMA_Priority_Low                   ((uint32_t)0x00000000)  /* 优先级：低 */
#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))
/**
  * @}
  */

/** @defgroup DMA_memory_to_memory 
  * @{
  */

#define DMA_M2M_Enable                     ((uint32_t)0x00004000)  /* 使能存储器到存储器模式 */
#define DMA_M2M_Disable                    ((uint32_t)0x00000000)  /* 关闭存储器到存储器模式 */
#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Enable) || ((STATE) == DMA_M2M_Disable))

/**
  * @}
  */

/** @defgroup DMA_interrupts_definition 
  * @{
  */

#define DMA_IT_TC                          ((uint32_t)0x00000002)  /* 传输完成中断 */
#define DMA_IT_HT                          ((uint32_t)0x00000004)  /* 半传输中断 */
#define DMA_IT_TE                          ((uint32_t)0x00000008)  /* 传输错误中断 */
#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA1_IT_GL1                        ((uint32_t)0x00000001)  /* DMA1通道1全局中断 */
#define DMA1_IT_TC1                        ((uint32_t)0x00000002)  /* DMA1通道1传输完成中断 */
#define DMA1_IT_HT1                        ((uint32_t)0x00000004)  /* DMA1通道1半传输中断 */
#define DMA1_IT_TE1                        ((uint32_t)0x00000008)  /* DMA1通道1传输错误中断 */
#define DMA1_IT_GL2                        ((uint32_t)0x00000010)  /* DMA1通道2全局中断 */
#define DMA1_IT_TC2                        ((uint32_t)0x00000020)  /* DMA1通道2传输完成中断 */
#define DMA1_IT_HT2                        ((uint32_t)0x00000040)  /* DMA1通道2半传输中断 */
#define DMA1_IT_TE2                        ((uint32_t)0x00000080)  /* DMA1通道2传输错误中断 */
#define DMA1_IT_GL3                        ((uint32_t)0x00000100)  /* DMA1通道3全局中断 */
#define DMA1_IT_TC3                        ((uint32_t)0x00000200)  /* DMA1通道3传输完成中断 */
#define DMA1_IT_HT3                        ((uint32_t)0x00000400)  /* DMA1通道3半传输中断 */
#define DMA1_IT_TE3                        ((uint32_t)0x00000800)  /* DMA1通道3传输错误中断 */
#define DMA1_IT_GL4                        ((uint32_t)0x00001000)  /* DMA1通道4全局中断 */
#define DMA1_IT_TC4                        ((uint32_t)0x00002000)  /* DMA1通道4传输完成中断 */
#define DMA1_IT_HT4                        ((uint32_t)0x00004000)  /* DMA1通道4半传输中断 */
#define DMA1_IT_TE4                        ((uint32_t)0x00008000)  /* DMA1通道4传输错误中断 */
#define DMA1_IT_GL5                        ((uint32_t)0x00010000)  /* DMA1通道5全局中断 */
#define DMA1_IT_TC5                        ((uint32_t)0x00020000)  /* DMA1通道5传输完成中断 */
#define DMA1_IT_HT5                        ((uint32_t)0x00040000)  /* DMA1通道5半传输中断 */
#define DMA1_IT_TE5                        ((uint32_t)0x00080000)  /* DMA1通道5传输错误中断 */
#define DMA1_IT_GL6                        ((uint32_t)0x00100000)  /* DMA1通道6全局中断 */
#define DMA1_IT_TC6                        ((uint32_t)0x00200000)  /* DMA1通道6传输完成中断 */
#define DMA1_IT_HT6                        ((uint32_t)0x00400000)  /* DMA1通道6半传输中断 */
#define DMA1_IT_TE6                        ((uint32_t)0x00800000)  /* DMA1通道6传输错误中断 */
#define DMA1_IT_GL7                        ((uint32_t)0x01000000)  /* DMA1通道7全局中断 */
#define DMA1_IT_TC7                        ((uint32_t)0x02000000)  /* DMA1通道7传输完成中断 */
#define DMA1_IT_HT7                        ((uint32_t)0x04000000)  /* DMA1通道7半传输中断 */
#define DMA1_IT_TE7                        ((uint32_t)0x08000000)  /* DMA1通道7传输错误中断 */

#define DMA2_IT_GL1                        ((uint32_t)0x10000001)  /* DMA2通道1全局中断 */
#define DMA2_IT_TC1                        ((uint32_t)0x10000002)  /* DMA2通道1传输完成中断 */
#define DMA2_IT_HT1                        ((uint32_t)0x10000004)  /* DMA2通道1半传输中断 */
#define DMA2_IT_TE1                        ((uint32_t)0x10000008)  /* DMA2通道1传输错误中断 */
#define DMA2_IT_GL2                        ((uint32_t)0x10000010)  /* DMA2通道2全局中断 */
#define DMA2_IT_TC2                        ((uint32_t)0x10000020)  /* DMA2通道2传输完成中断 */
#define DMA2_IT_HT2                        ((uint32_t)0x10000040)  /* DMA2通道2半传输中断 */
#define DMA2_IT_TE2                        ((uint32_t)0x10000080)  /* DMA2通道2传输错误中断 */
#define DMA2_IT_GL3                        ((uint32_t)0x10000100)  /* DMA2通道3全局中断 */
#define DMA2_IT_TC3                        ((uint32_t)0x10000200)  /* DMA2通道3传输完成中断 */
#define DMA2_IT_HT3                        ((uint32_t)0x10000400)  /* DMA2通道3半传输中断 */
#define DMA2_IT_TE3                        ((uint32_t)0x10000800)  /* DMA2通道3传输错误中断 */
#define DMA2_IT_GL4                        ((uint32_t)0x10001000)  /* DMA2通道4全局中断 */
#define DMA2_IT_TC4                        ((uint32_t)0x10002000)  /* DMA2通道4传输完成中断 */
#define DMA2_IT_HT4                        ((uint32_t)0x10004000)  /* DMA2通道4半传输中断 */
#define DMA2_IT_TE4                        ((uint32_t)0x10008000)  /* DMA2通道4传输错误中断 */
#define DMA2_IT_GL5                        ((uint32_t)0x10010000)  /* DMA2通道5全局中断 */
#define DMA2_IT_TC5                        ((uint32_t)0x10020000)  /* DMA2通道5传输完成中断 */
#define DMA2_IT_HT5                        ((uint32_t)0x10040000)  /* DMA2通道5半传输中断 */
#define DMA2_IT_TE5                        ((uint32_t)0x10080000)  /* DMA2通道5传输错误中断 */

#define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00))

#define IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || \
                           ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || \
                           ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || \
                           ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || \
                           ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || \
                           ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || \
                           ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || \
                           ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || \
                           ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || \
                           ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || \
                           ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || \
                           ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || \
                           ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || \
                           ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7) || \
                           ((IT) == DMA2_IT_GL1) || ((IT) == DMA2_IT_TC1) || \
                           ((IT) == DMA2_IT_HT1) || ((IT) == DMA2_IT_TE1) || \
                           ((IT) == DMA2_IT_GL2) || ((IT) == DMA2_IT_TC2) || \
                           ((IT) == DMA2_IT_HT2) || ((IT) == DMA2_IT_TE2) || \
                           ((IT) == DMA2_IT_GL3) || ((IT) == DMA2_IT_TC3) || \
                           ((IT) == DMA2_IT_HT3) || ((IT) == DMA2_IT_TE3) || \
                           ((IT) == DMA2_IT_GL4) || ((IT) == DMA2_IT_TC4) || \
                           ((IT) == DMA2_IT_HT4) || ((IT) == DMA2_IT_TE4) || \
                           ((IT) == DMA2_IT_GL5) || ((IT) == DMA2_IT_TC5) || \
                           ((IT) == DMA2_IT_HT5) || ((IT) == DMA2_IT_TE5))

/**
  * @}
  */

/** @defgroup DMA_flags_definition 
  * @{
  */
#define DMA1_FLAG_GL1                      ((uint32_t)0x00000001)  /* DMA1通道1全局标志 */
#define DMA1_FLAG_TC1                      ((uint32_t)0x00000002)  /* DMA1通道1传输完成标志 */
#define DMA1_FLAG_HT1                      ((uint32_t)0x00000004)  /* DMA1通道1半传输标志 */
#define DMA1_FLAG_TE1                      ((uint32_t)0x00000008)  /* DMA1通道1传输错误标志 */
#define DMA1_FLAG_GL2                      ((uint32_t)0x00000010)  /* DMA1通道2全局标志 */
#define DMA1_FLAG_TC2                      ((uint32_t)0x00000020)  /* DMA1通道2传输完成标志 */
#define DMA1_FLAG_HT2                      ((uint32_t)0x00000040)  /* DMA1通道2半传输标志 */
#define DMA1_FLAG_TE2                      ((uint32_t)0x00000080)  /* DMA1通道2传输错误标志 */
#define DMA1_FLAG_GL3                      ((uint32_t)0x00000100)  /* DMA1通道3全局标志 */
#define DMA1_FLAG_TC3                      ((uint32_t)0x00000200)  /* DMA1通道3传输完成标志 */
#define DMA1_FLAG_HT3                      ((uint32_t)0x00000400)  /* DMA1通道3半传输标志 */
#define DMA1_FLAG_TE3                      ((uint32_t)0x00000800)  /* DMA1通道3传输错误标志 */
#define DMA1_FLAG_GL4                      ((uint32_t)0x00001000)  /* DMA1通道4全局标志 */
#define DMA1_FLAG_TC4                      ((uint32_t)0x00002000)  /* DMA1通道4传输完成标志 */
#define DMA1_FLAG_HT4                      ((uint32_t)0x00004000)  /* DMA1通道4半传输标志 */
#define DMA1_FLAG_TE4                      ((uint32_t)0x00008000)  /* DMA1通道4传输错误标志 */
#define DMA1_FLAG_GL5                      ((uint32_t)0x00010000)  /* DMA1通道5全局标志 */
#define DMA1_FLAG_TC5                      ((uint32_t)0x00020000)  /* DMA1通道5传输完成标志 */
#define DMA1_FLAG_HT5                      ((uint32_t)0x00040000)  /* DMA1通道5半传输标志 */
#define DMA1_FLAG_TE5                      ((uint32_t)0x00080000)  /* DMA1通道5传输错误标志 */
#define DMA1_FLAG_GL6                      ((uint32_t)0x00100000)  /* DMA1通道6全局标志 */
#define DMA1_FLAG_TC6                      ((uint32_t)0x00200000)  /* DMA1通道6传输完成标志 */
#define DMA1_FLAG_HT6                      ((uint32_t)0x00400000)  /* DMA1通道6半传输标志 */
#define DMA1_FLAG_TE6                      ((uint32_t)0x00800000)  /* DMA1通道6传输错误标志 */
#define DMA1_FLAG_GL7                      ((uint32_t)0x01000000)  /* DMA1通道7全局标志 */
#define DMA1_FLAG_TC7                      ((uint32_t)0x02000000)  /* DMA1通道7传输完成标志 */
#define DMA1_FLAG_HT7                      ((uint32_t)0x04000000)  /* DMA1通道7半传输标志 */
#define DMA1_FLAG_TE7                      ((uint32_t)0x08000000)  /* DMA1通道7传输错误标志 */

#define DMA2_FLAG_GL1                      ((uint32_t)0x10000001)  /* DMA2通道1全局标志 */
#define DMA2_FLAG_TC1                      ((uint32_t)0x10000002)  /* DMA2通道1传输完成标志 */
#define DMA2_FLAG_HT1                      ((uint32_t)0x10000004)  /* DMA2通道1半传输标志 */
#define DMA2_FLAG_TE1                      ((uint32_t)0x10000008)  /* DMA2通道1传输错误标志 */
#define DMA2_FLAG_GL2                      ((uint32_t)0x10000010)  /* DMA2通道2全局标志 */
#define DMA2_FLAG_TC2                      ((uint32_t)0x10000020)  /* DMA2通道2传输完成标志 */
#define DMA2_FLAG_HT2                      ((uint32_t)0x10000040)  /* DMA2通道2半传输标志 */
#define DMA2_FLAG_TE2                      ((uint32_t)0x10000080)  /* DMA2通道2传输错误标志 */
#define DMA2_FLAG_GL3                      ((uint32_t)0x10000100)  /* DMA2通道3全局标志 */
#define DMA2_FLAG_TC3                      ((uint32_t)0x10000200)  /* DMA2通道3传输完成标志 */
#define DMA2_FLAG_HT3                      ((uint32_t)0x10000400)  /* DMA2通道3半传输标志 */
#define DMA2_FLAG_TE3                      ((uint32_t)0x10000800)  /* DMA2通道3传输错误标志 */
#define DMA2_FLAG_GL4                      ((uint32_t)0x10001000)  /* DMA2通道4全局标志 */
#define DMA2_FLAG_TC4                      ((uint32_t)0x10002000)  /* DMA2通道4传输完成标志 */
#define DMA2_FLAG_HT4                      ((uint32_t)0x10004000)  /* DMA2通道4半传输标志 */
#define DMA2_FLAG_TE4                      ((uint32_t)0x10008000)  /* DMA2通道4传输错误标志 */
#define DMA2_FLAG_GL5                      ((uint32_t)0x10010000)  /* DMA2通道5全局标志 */
#define DMA2_FLAG_TC5                      ((uint32_t)0x10020000)  /* DMA2通道5传输完成标志 */
#define DMA2_FLAG_HT5                      ((uint32_t)0x10040000)  /* DMA2通道5半传输标志 */
#define DMA2_FLAG_TE5                      ((uint32_t)0x10080000)  /* DMA2通道5传输错误标志 */

#define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00))

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || \
                               ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || \
                               ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || \
                               ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || \
                               ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || \
                               ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || \
                               ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || \
                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || \
                               ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC5) || \
                               ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE5) || \
                               ((FLAG) == DMA1_FLAG_GL6) || ((FLAG) == DMA1_FLAG_TC6) || \
                               ((FLAG) == DMA1_FLAG_HT6) || ((FLAG) == DMA1_FLAG_TE6) || \
                               ((FLAG) == DMA1_FLAG_GL7) || ((FLAG) == DMA1_FLAG_TC7) || \
                               ((FLAG) == DMA1_FLAG_HT7) || ((FLAG) == DMA1_FLAG_TE7) || \
                               ((FLAG) == DMA2_FLAG_GL1) || ((FLAG) == DMA2_FLAG_TC1) || \
                               ((FLAG) == DMA2_FLAG_HT1) || ((FLAG) == DMA2_FLAG_TE1) || \
                               ((FLAG) == DMA2_FLAG_GL2) || ((FLAG) == DMA2_FLAG_TC2) || \
                               ((FLAG) == DMA2_FLAG_HT2) || ((FLAG) == DMA2_FLAG_TE2) || \
                               ((FLAG) == DMA2_FLAG_GL3) || ((FLAG) == DMA2_FLAG_TC3) || \
                               ((FLAG) == DMA2_FLAG_HT3) || ((FLAG) == DMA2_FLAG_TE3) || \
                               ((FLAG) == DMA2_FLAG_GL4) || ((FLAG) == DMA2_FLAG_TC4) || \
                               ((FLAG) == DMA2_FLAG_HT4) || ((FLAG) == DMA2_FLAG_TE4) || \
                               ((FLAG) == DMA2_FLAG_GL5) || ((FLAG) == DMA2_FLAG_TC5) || \
                               ((FLAG) == DMA2_FLAG_HT5) || ((FLAG) == DMA2_FLAG_TE5))
/**
  * @}
  */

/** @defgroup DMA_Buffer_Size 
  * @{
  */

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DMA_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions
  * @{
  */

void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);  /* 将指定DMA通道寄存器复位为默认值 */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);  /* 根据结构体参数初始化指定DMA通道 */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);  /* 将DMA初始化结构体各成员设为默认值 */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);  /* 使能或关闭指定DMA通道 */
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);  /* 使能或关闭指定DMA通道中断 */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber);  /* 设置当前DMA传输的数据量 */ 
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);  /* 返回当前DMA传输剩余的数据量 */
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);  /* 检查指定DMA标志位是否置位 */
void DMA_ClearFlag(uint32_t DMAy_FLAG);  /* 清除指定DMA通道的待处理标志 */
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);  /* 检查指定DMA中断是否发生 */
void DMA_ClearITPendingBit(uint32_t DMAy_IT);  /* 清除指定DMA中断的待处理位 */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F10x_DMA_H */
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
