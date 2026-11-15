/**
  ******************************************************************************
  * @file    stm32f10x_fsmc.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the FSMC firmware 
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
#ifndef __STM32F10x_FSMC_H
#define __STM32F10x_FSMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup FSMC
  * @{
  */

/** @defgroup FSMC_Exported_Types
  * @{
  */

/** 
  * @brief  Timing parameters For NOR/SRAM Banks  
  */

typedef struct
{
  /* 地址建立时间（HCLK周期数） */
  uint32_t FSMC_AddressSetupTime;       /*!< Defines the number of HCLK cycles to configure
                                             the duration of the address setup time. 
                                             This parameter can be a value between 0 and 0xF.
                                             @note: It is not used with synchronous NOR Flash memories. */

  /* 地址保持时间（HCLK周期数） */
  uint32_t FSMC_AddressHoldTime;        /*!< Defines the number of HCLK cycles to configure
                                             the duration of the address hold time.
                                             This parameter can be a value between 0 and 0xF. 
                                             @note: It is not used with synchronous NOR Flash memories.*/

  /* 数据建立时间（HCLK周期数） */
  uint32_t FSMC_DataSetupTime;          /*!< Defines the number of HCLK cycles to configure
                                             the duration of the data setup time.
                                             This parameter can be a value between 0 and 0xFF.
                                             @note: It is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

  /* 总线周转时间（HCLK周期数） */
  uint32_t FSMC_BusTurnAroundDuration;  /*!< Defines the number of HCLK cycles to configure
                                             the duration of the bus turnaround.
                                             This parameter can be a value between 0 and 0xF.
                                             @note: It is only used for multiplexed NOR Flash memories. */

  /* CLK时钟输出分频系数 */
  uint32_t FSMC_CLKDivision;            /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                             This parameter can be a value between 1 and 0xF.
                                             @note: This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

  /* 数据延迟（存储器时钟周期数） */
  uint32_t FSMC_DataLatency;            /*!< Defines the number of memory clock cycles to issue
                                             to the memory before getting the first data.
                                             The value of this parameter depends on the memory type as shown below:
                                              - It must be set to 0 in case of a CRAM
                                              - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                              - It may assume a value between 0 and 0xF in NOR Flash memories
                                                with synchronous burst mode enable */

  /* 异步访问模式 */
  uint32_t FSMC_AccessMode;             /*!< Specifies the asynchronous access mode. 
                                             This parameter can be a value of @ref FSMC_Access_Mode */
}FSMC_NORSRAMTimingInitTypeDef;

/** 
  * @brief  FSMC NOR/SRAM Init structure definition
  */

typedef struct
{
  /* 要使用的NOR/SRAM存储块 */
  uint32_t FSMC_Bank;                /*!< Specifies the NOR/SRAM memory bank that will be used.
                                          This parameter can be a value of @ref FSMC_NORSRAM_Bank */

  /* 地址/数据总线复用使能 */
  uint32_t FSMC_DataAddressMux;      /*!< Specifies whether the address and data values are
                                          multiplexed on the databus or not. 
                                          This parameter can be a value of @ref FSMC_Data_Address_Bus_Multiplexing */

  /* 外部存储器类型 */
  uint32_t FSMC_MemoryType;          /*!< Specifies the type of external memory attached to
                                          the corresponding memory bank.
                                          This parameter can be a value of @ref FSMC_Memory_Type */

  /* 外部存储器数据宽度 */
  uint32_t FSMC_MemoryDataWidth;     /*!< Specifies the external memory device width.
                                          This parameter can be a value of @ref FSMC_Data_Width */

  /* 突发访问模式使能 */
  uint32_t FSMC_BurstAccessMode;     /*!< Enables or disables the burst access mode for Flash memory,
                                          valid only with synchronous burst Flash memories.
                                          This parameter can be a value of @ref FSMC_Burst_Access_Mode */
                                       
  /* 异步传输等待信号使能 */
  uint32_t FSMC_AsynchronousWait;     /*!< Enables or disables wait signal during asynchronous transfers,
                                          valid only with asynchronous Flash memories.
                                          This parameter can be a value of @ref FSMC_AsynchronousWait */

  /* 等待信号极性 */
  uint32_t FSMC_WaitSignalPolarity;  /*!< Specifies the wait signal polarity, valid only when accessing
                                          the Flash memory in burst mode.
                                          This parameter can be a value of @ref FSMC_Wait_Signal_Polarity */

  /* 回卷突发模式使能 */
  uint32_t FSMC_WrapMode;            /*!< Enables or disables the Wrapped burst access mode for Flash
                                          memory, valid only when accessing Flash memories in burst mode.
                                          This parameter can be a value of @ref FSMC_Wrap_Mode */

  /* 等待信号有效时机 */
  uint32_t FSMC_WaitSignalActive;    /*!< Specifies if the wait signal is asserted by the memory one
                                          clock cycle before the wait state or during the wait state,
                                          valid only when accessing memories in burst mode. 
                                          This parameter can be a value of @ref FSMC_Wait_Timing */

  /* 写操作使能 */
  uint32_t FSMC_WriteOperation;      /*!< Enables or disables the write operation in the selected bank by the FSMC. 
                                          This parameter can be a value of @ref FSMC_Write_Operation */

  /* 等待信号使能 */
  uint32_t FSMC_WaitSignal;          /*!< Enables or disables the wait-state insertion via wait
                                          signal, valid for Flash memory access in burst mode. 
                                          This parameter can be a value of @ref FSMC_Wait_Signal */

  /* 扩展模式使能 */
  uint32_t FSMC_ExtendedMode;        /*!< Enables or disables the extended mode.
                                          This parameter can be a value of @ref FSMC_Extended_Mode */

  /* 写突发使能 */
  uint32_t FSMC_WriteBurst;          /*!< Enables or disables the write burst operation.
                                          This parameter can be a value of @ref FSMC_Write_Burst */

  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct; /* 读写共用的时序参数指针 */ /*!< Timing Parameters for write and read access if the  ExtendedMode is not used*/

  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct; /* 扩展模式下的写时序参数指针 */ /*!< Timing Parameters for write access if the  ExtendedMode is used*/
}FSMC_NORSRAMInitTypeDef;

/** 
  * @brief  Timing parameters For FSMC NAND and PCCARD Banks
  */

typedef struct
{
  /* 命令前的地址建立时间 */
  uint32_t FSMC_SetupTime;      /*!< Defines the number of HCLK cycles to setup address before
                                     the command assertion for NAND-Flash read or write access
                                     to common/Attribute or I/O memory space (depending on
                                     the memory space timing to be configured).
                                     This parameter can be a value between 0 and 0xFF.*/

  /* 命令保持时间 */
  uint32_t FSMC_WaitSetupTime;  /*!< Defines the minimum number of HCLK cycles to assert the
                                     command for NAND-Flash read or write access to
                                     common/Attribute or I/O memory space (depending on the
                                     memory space timing to be configured). 
                                     This parameter can be a number between 0x00 and 0xFF */

  /* 命令撤销后地址/数据保持时间 */
  uint32_t FSMC_HoldSetupTime;  /*!< Defines the number of HCLK clock cycles to hold address
                                     (and data for write access) after the command deassertion
                                     for NAND-Flash read or write access to common/Attribute
                                     or I/O memory space (depending on the memory space timing
                                     to be configured).
                                     This parameter can be a number between 0x00 and 0xFF */

  /* 写操作开始后数据总线高阻时间 */
  uint32_t FSMC_HiZSetupTime;   /*!< Defines the number of HCLK clock cycles during which the
                                     databus is kept in HiZ after the start of a NAND-Flash
                                     write access to common/Attribute or I/O memory space (depending
                                     on the memory space timing to be configured).
                                     This parameter can be a number between 0x00 and 0xFF */
}FSMC_NAND_PCCARDTimingInitTypeDef;

/** 
  * @brief  FSMC NAND Init structure definition
  */

typedef struct
{
  /* 要使用的NAND存储块 */
  uint32_t FSMC_Bank;              /*!< Specifies the NAND memory bank that will be used.
                                      This parameter can be a value of @ref FSMC_NAND_Bank */

  /* 等待特性使能 */
  uint32_t FSMC_Waitfeature;      /*!< Enables or disables the Wait feature for the NAND Memory Bank.
                                       This parameter can be any value of @ref FSMC_Wait_feature */

  /* 外部存储器数据宽度 */
  uint32_t FSMC_MemoryDataWidth;  /*!< Specifies the external memory device width.
                                       This parameter can be any value of @ref FSMC_Data_Width */

  /* ECC计算使能 */
  uint32_t FSMC_ECC;              /*!< Enables or disables the ECC computation.
                                       This parameter can be any value of @ref FSMC_ECC */

  /* 扩展ECC页大小 */
  uint32_t FSMC_ECCPageSize;      /*!< Defines the page size for the extended ECC.
                                       This parameter can be any value of @ref FSMC_ECC_Page_Size */

  /* CLE低到RE低延时（HCLK周期数） */
  uint32_t FSMC_TCLRSetupTime;    /*!< Defines the number of HCLK cycles to configure the
                                       delay between CLE low and RE low.
                                       This parameter can be a value between 0 and 0xFF. */

  /* ALE低到RE低延时（HCLK周期数） */
  uint32_t FSMC_TARSetupTime;     /*!< Defines the number of HCLK cycles to configure the
                                       delay between ALE low and RE low.
                                       This parameter can be a number between 0x0 and 0xFF */

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct; /* 公共空间时序参数指针 */ /*!< FSMC Common Space Timing */

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct; /* 属性空间时序参数指针 */ /*!< FSMC Attribute Space Timing */
}FSMC_NANDInitTypeDef;

/** 
  * @brief  FSMC PCCARD Init structure definition
  */

typedef struct
{
  /* 等待特性使能 */
  uint32_t FSMC_Waitfeature;    /*!< Enables or disables the Wait feature for the Memory Bank.
                                    This parameter can be any value of @ref FSMC_Wait_feature */

  /* CLE低到RE低延时（HCLK周期数） */
  uint32_t FSMC_TCLRSetupTime;  /*!< Defines the number of HCLK cycles to configure the
                                     delay between CLE low and RE low.
                                     This parameter can be a value between 0 and 0xFF. */

  /* ALE低到RE低延时（HCLK周期数） */
  uint32_t FSMC_TARSetupTime;   /*!< Defines the number of HCLK cycles to configure the
                                     delay between ALE low and RE low.
                                     This parameter can be a number between 0x0 and 0xFF */

  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct; /* 公共空间时序参数指针 */ /*!< FSMC Common Space Timing */

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct; /* 属性空间时序参数指针 */ /*!< FSMC Attribute Space Timing */
  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct; /* IO空间时序参数指针 */ /*!< FSMC IO Space Timing */
}FSMC_PCCARDInitTypeDef;

/**
  * @}
  */

/** @defgroup FSMC_Exported_Constants
  * @{
  */

/** @defgroup FSMC_NORSRAM_Bank 
  * @{
  */
#define FSMC_Bank1_NORSRAM1                             ((uint32_t)0x00000000)  /* NOR/SRAM存储块1 */
#define FSMC_Bank1_NORSRAM2                             ((uint32_t)0x00000002)  /* NOR/SRAM存储块2 */
#define FSMC_Bank1_NORSRAM3                             ((uint32_t)0x00000004)  /* NOR/SRAM存储块3 */
#define FSMC_Bank1_NORSRAM4                             ((uint32_t)0x00000006)  /* NOR/SRAM存储块4 */
/**
  * @}
  */

/** @defgroup FSMC_NAND_Bank 
  * @{
  */  
#define FSMC_Bank2_NAND                                 ((uint32_t)0x00000010)  /* NAND存储块2 */
#define FSMC_Bank3_NAND                                 ((uint32_t)0x00000100)  /* NAND存储块3 */
/**
  * @}
  */

/** @defgroup FSMC_PCCARD_Bank 
  * @{
  */    
#define FSMC_Bank4_PCCARD                               ((uint32_t)0x00001000)  /* PCCARD存储块4 */
/**
  * @}
  */

#define IS_FSMC_NORSRAM_BANK(BANK) (((BANK) == FSMC_Bank1_NORSRAM1) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM2) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM3) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM4))  /* 校验NOR/SRAM存储块参数 */

#define IS_FSMC_NAND_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                 ((BANK) == FSMC_Bank3_NAND))  /* 校验NAND存储块参数 */

#define IS_FSMC_GETFLAG_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                    ((BANK) == FSMC_Bank3_NAND) || \
                                    ((BANK) == FSMC_Bank4_PCCARD))  /* 校验标志读取存储块参数 */

#define IS_FSMC_IT_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                               ((BANK) == FSMC_Bank3_NAND) || \
                               ((BANK) == FSMC_Bank4_PCCARD))  /* 校验中断存储块参数 */

/** @defgroup NOR_SRAM_Controller 
  * @{
  */

/** @defgroup FSMC_Data_Address_Bus_Multiplexing 
  * @{
  */

#define FSMC_DataAddressMux_Disable                       ((uint32_t)0x00000000)  /* 禁止地址/数据总线复用 */
#define FSMC_DataAddressMux_Enable                        ((uint32_t)0x00000002)  /* 使能地址/数据总线复用 */
#define IS_FSMC_MUX(MUX) (((MUX) == FSMC_DataAddressMux_Disable) || \
                          ((MUX) == FSMC_DataAddressMux_Enable))  /* 校验总线复用参数 */

/**
  * @}
  */

/** @defgroup FSMC_Memory_Type 
  * @{
  */

#define FSMC_MemoryType_SRAM                            ((uint32_t)0x00000000)  /* SRAM存储器 */
#define FSMC_MemoryType_PSRAM                           ((uint32_t)0x00000004)  /* PSRAM存储器 */
#define FSMC_MemoryType_NOR                             ((uint32_t)0x00000008)  /* NOR Flash存储器 */
#define IS_FSMC_MEMORY(MEMORY) (((MEMORY) == FSMC_MemoryType_SRAM) || \
                                ((MEMORY) == FSMC_MemoryType_PSRAM)|| \
                                ((MEMORY) == FSMC_MemoryType_NOR))  /* 校验存储器类型参数 */

/**
  * @}
  */

/** @defgroup FSMC_Data_Width 
  * @{
  */

#define FSMC_MemoryDataWidth_8b                         ((uint32_t)0x00000000)  /* 8位数据宽度 */
#define FSMC_MemoryDataWidth_16b                        ((uint32_t)0x00000010)  /* 16位数据宽度 */
#define IS_FSMC_MEMORY_WIDTH(WIDTH) (((WIDTH) == FSMC_MemoryDataWidth_8b) || \
                                     ((WIDTH) == FSMC_MemoryDataWidth_16b))  /* 校验数据宽度参数 */

/**
  * @}
  */

/** @defgroup FSMC_Burst_Access_Mode 
  * @{
  */

#define FSMC_BurstAccessMode_Disable                    ((uint32_t)0x00000000)   /* 禁止突发访问模式 */
#define FSMC_BurstAccessMode_Enable                     ((uint32_t)0x00000100)  /* 使能突发访问模式 */
#define IS_FSMC_BURSTMODE(STATE) (((STATE) == FSMC_BurstAccessMode_Disable) || \
                                  ((STATE) == FSMC_BurstAccessMode_Enable))  /* 校验突发访问模式参数 */
/**
  * @}
  */
  
/** @defgroup FSMC_AsynchronousWait 
  * @{
  */
#define FSMC_AsynchronousWait_Disable                   ((uint32_t)0x00000000)  /* 禁止异步等待信号 */
#define FSMC_AsynchronousWait_Enable                    ((uint32_t)0x00008000)  /* 使能异步等待信号 */
#define IS_FSMC_ASYNWAIT(STATE) (((STATE) == FSMC_AsynchronousWait_Disable) || \
                                 ((STATE) == FSMC_AsynchronousWait_Enable))  /* 校验异步等待参数 */

/**
  * @}
  */
  
/** @defgroup FSMC_Wait_Signal_Polarity 
  * @{
  */

#define FSMC_WaitSignalPolarity_Low                     ((uint32_t)0x00000000)  /* 等待信号低电平有效 */
#define FSMC_WaitSignalPolarity_High                    ((uint32_t)0x00000200)  /* 等待信号高电平有效 */
#define IS_FSMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FSMC_WaitSignalPolarity_Low) || \
                                         ((POLARITY) == FSMC_WaitSignalPolarity_High))  /* 校验等待信号极性参数 */ 

/**
  * @}
  */

/** @defgroup FSMC_Wrap_Mode 
  * @{
  */

#define FSMC_WrapMode_Disable                           ((uint32_t)0x00000000)  /* 禁止回卷突发模式 */
#define FSMC_WrapMode_Enable                            ((uint32_t)0x00000400)   /* 使能回卷突发模式 */
#define IS_FSMC_WRAP_MODE(MODE) (((MODE) == FSMC_WrapMode_Disable) || \
                                 ((MODE) == FSMC_WrapMode_Enable))  /* 校验回卷模式参数 */

/**
  * @}
  */

/** @defgroup FSMC_Wait_Timing 
  * @{
  */

#define FSMC_WaitSignalActive_BeforeWaitState           ((uint32_t)0x00000000)  /* 等待信号在等待周期前有效 */
#define FSMC_WaitSignalActive_DuringWaitState           ((uint32_t)0x00000800)   /* 等待信号在等待周期内有效 */
#define IS_FSMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FSMC_WaitSignalActive_BeforeWaitState) || \
                                            ((ACTIVE) == FSMC_WaitSignalActive_DuringWaitState))  /* 校验等待信号有效时机参数 */

/**
  * @}
  */

/** @defgroup FSMC_Write_Operation 
  * @{
  */

#define FSMC_WriteOperation_Disable                     ((uint32_t)0x00000000)  /* 禁止写操作 */
#define FSMC_WriteOperation_Enable                      ((uint32_t)0x00001000)  /* 使能写操作 */
#define IS_FSMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FSMC_WriteOperation_Disable) || \
                                            ((OPERATION) == FSMC_WriteOperation_Enable))  /* 校验写操作参数 */
                              
/**
  * @}
  */

/** @defgroup FSMC_Wait_Signal 
  * @{
  */

#define FSMC_WaitSignal_Disable                         ((uint32_t)0x00000000)  /* 禁止等待信号 */
#define FSMC_WaitSignal_Enable                          ((uint32_t)0x00002000)   /* 使能等待信号 */
#define IS_FSMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FSMC_WaitSignal_Disable) || \
                                      ((SIGNAL) == FSMC_WaitSignal_Enable))  /* 校验等待信号参数 */
/**
  * @}
  */

/** @defgroup FSMC_Extended_Mode 
  * @{
  */

#define FSMC_ExtendedMode_Disable                       ((uint32_t)0x00000000)  /* 禁止扩展模式 */
#define FSMC_ExtendedMode_Enable                        ((uint32_t)0x00004000)  /* 使能扩展模式 */

#define IS_FSMC_EXTENDED_MODE(MODE) (((MODE) == FSMC_ExtendedMode_Disable) || \
                                     ((MODE) == FSMC_ExtendedMode_Enable))  /* 校验扩展模式参数 */ 

/**
  * @}
  */

/** @defgroup FSMC_Write_Burst 
  * @{
  */

#define FSMC_WriteBurst_Disable                         ((uint32_t)0x00000000)  /* 禁止写突发 */
#define FSMC_WriteBurst_Enable                          ((uint32_t)0x00080000)   /* 使能写突发 */
#define IS_FSMC_WRITE_BURST(BURST) (((BURST) == FSMC_WriteBurst_Disable) || \
                                    ((BURST) == FSMC_WriteBurst_Enable))  /* 校验写突发参数 */
/**
  * @}
  */

/** @defgroup FSMC_Address_Setup_Time 
  * @{
  */

#define IS_FSMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 0xF)  /* 校验地址建立时间（≤0xF） */

/**
  * @}
  */

/** @defgroup FSMC_Address_Hold_Time 
  * @{
  */

#define IS_FSMC_ADDRESS_HOLD_TIME(TIME) ((TIME) <= 0xF)  /* 校验地址保持时间（≤0xF） */

/**
  * @}
  */

/** @defgroup FSMC_Data_Setup_Time 
  * @{
  */

#define IS_FSMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 0xFF))  /* 校验数据建立时间（1~0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_Bus_Turn_around_Duration 
  * @{
  */

#define IS_FSMC_TURNAROUND_TIME(TIME) ((TIME) <= 0xF)  /* 校验总线周转时间（≤0xF） */

/**
  * @}
  */

/** @defgroup FSMC_CLK_Division 
  * @{
  */

#define IS_FSMC_CLK_DIV(DIV) ((DIV) <= 0xF)  /* 校验时钟分频（≤0xF） */

/**
  * @}
  */

/** @defgroup FSMC_Data_Latency 
  * @{
  */

#define IS_FSMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 0xF)  /* 校验数据延迟（≤0xF） */

/**
  * @}
  */

/** @defgroup FSMC_Access_Mode 
  * @{
  */

#define FSMC_AccessMode_A                               ((uint32_t)0x00000000)  /* 访问模式A */
#define FSMC_AccessMode_B                               ((uint32_t)0x10000000)   /* 访问模式B */
#define FSMC_AccessMode_C                               ((uint32_t)0x20000000)  /* 访问模式C */
#define FSMC_AccessMode_D                               ((uint32_t)0x30000000)  /* 访问模式D */
#define IS_FSMC_ACCESS_MODE(MODE) (((MODE) == FSMC_AccessMode_A) || \
                                   ((MODE) == FSMC_AccessMode_B) || \
                                   ((MODE) == FSMC_AccessMode_C) || \
                                   ((MODE) == FSMC_AccessMode_D))  /* 校验访问模式参数 */ 

/**
  * @}
  */

/**
  * @}
  */
  
/** @defgroup NAND_PCCARD_Controller 
  * @{
  */

/** @defgroup FSMC_Wait_feature 
  * @{
  */

#define FSMC_Waitfeature_Disable                        ((uint32_t)0x00000000)  /* 禁止等待特性 */
#define FSMC_Waitfeature_Enable                         ((uint32_t)0x00000002)  /* 使能等待特性 */
#define IS_FSMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FSMC_Waitfeature_Disable) || \
                                       ((FEATURE) == FSMC_Waitfeature_Enable))  /* 校验等待特性参数 */

/**
  * @}
  */


/** @defgroup FSMC_ECC 
  * @{
  */

#define FSMC_ECC_Disable                                ((uint32_t)0x00000000)  /* 禁止ECC校验 */
#define FSMC_ECC_Enable                                 ((uint32_t)0x00000040)  /* 使能ECC校验 */
#define IS_FSMC_ECC_STATE(STATE) (((STATE) == FSMC_ECC_Disable) || \
                                  ((STATE) == FSMC_ECC_Enable))  /* 校验ECC状态参数 */

/**
  * @}
  */

/** @defgroup FSMC_ECC_Page_Size 
  * @{
  */

#define FSMC_ECCPageSize_256Bytes                       ((uint32_t)0x00000000)  /* ECC页大小256字节 */
#define FSMC_ECCPageSize_512Bytes                       ((uint32_t)0x00020000)  /* ECC页大小512字节 */
#define FSMC_ECCPageSize_1024Bytes                      ((uint32_t)0x00040000)  /* ECC页大小1024字节 */
#define FSMC_ECCPageSize_2048Bytes                      ((uint32_t)0x00060000)  /* ECC页大小2048字节 */
#define FSMC_ECCPageSize_4096Bytes                      ((uint32_t)0x00080000)  /* ECC页大小4096字节 */
#define FSMC_ECCPageSize_8192Bytes                      ((uint32_t)0x000A0000)  /* ECC页大小8192字节 */
#define IS_FSMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FSMC_ECCPageSize_256Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_512Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_1024Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_2048Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_4096Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_8192Bytes))  /* 校验ECC页大小参数 */

/**
  * @}
  */

/** @defgroup FSMC_TCLR_Setup_Time 
  * @{
  */

#define IS_FSMC_TCLR_TIME(TIME) ((TIME) <= 0xFF)  /* 校验CLE低到RE低延时（≤0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_TAR_Setup_Time 
  * @{
  */

#define IS_FSMC_TAR_TIME(TIME) ((TIME) <= 0xFF)  /* 校验ALE低到RE低延时（≤0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_Setup_Time 
  * @{
  */

#define IS_FSMC_SETUP_TIME(TIME) ((TIME) <= 0xFF)  /* 校验建立时间（≤0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_Wait_Setup_Time 
  * @{
  */

#define IS_FSMC_WAIT_TIME(TIME) ((TIME) <= 0xFF)  /* 校验等待建立时间（≤0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_Hold_Setup_Time 
  * @{
  */

#define IS_FSMC_HOLD_TIME(TIME) ((TIME) <= 0xFF)  /* 校验保持建立时间（≤0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_HiZ_Setup_Time 
  * @{
  */

#define IS_FSMC_HIZ_TIME(TIME) ((TIME) <= 0xFF)  /* 校验高阻建立时间（≤0xFF） */

/**
  * @}
  */

/** @defgroup FSMC_Interrupt_sources 
  * @{
  */

#define FSMC_IT_RisingEdge                              ((uint32_t)0x00000008)  /* 上升沿检测中断 */
#define FSMC_IT_Level                                   ((uint32_t)0x00000010)  /* 电平检测中断 */
#define FSMC_IT_FallingEdge                             ((uint32_t)0x00000020)  /* 下降沿检测中断 */
#define IS_FSMC_IT(IT) ((((IT) & (uint32_t)0xFFFFFFC7) == 0x00000000) && ((IT) != 0x00000000))  /* 校验中断源参数 */
#define IS_FSMC_GET_IT(IT) (((IT) == FSMC_IT_RisingEdge) || \
                            ((IT) == FSMC_IT_Level) || \
                            ((IT) == FSMC_IT_FallingEdge))  /* 校验中断源参数 */ 
/**
  * @}
  */

/** @defgroup FSMC_Flags 
  * @{
  */

#define FSMC_FLAG_RisingEdge                            ((uint32_t)0x00000001)  /* 上升沿检测标志 */
#define FSMC_FLAG_Level                                 ((uint32_t)0x00000002)  /* 电平检测标志 */
#define FSMC_FLAG_FallingEdge                           ((uint32_t)0x00000004)  /* 下降沿检测标志 */
#define FSMC_FLAG_FEMPT                                 ((uint32_t)0x00000040)  /* FIFO空标志 */
#define IS_FSMC_GET_FLAG(FLAG) (((FLAG) == FSMC_FLAG_RisingEdge) || \
                                ((FLAG) == FSMC_FLAG_Level) || \
                                ((FLAG) == FSMC_FLAG_FallingEdge) || \
                                ((FLAG) == FSMC_FLAG_FEMPT))  /* 校验标志参数 */

#define IS_FSMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))  /* 校验待清除标志参数 */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FSMC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup FSMC_Exported_Functions
  * @{
  */

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);  /* 复位NOR/SRAM存储块寄存器为默认值 */
void FSMC_NANDDeInit(uint32_t FSMC_Bank);  /* 复位NAND存储块寄存器为默认值 */
void FSMC_PCCARDDeInit(void);  /* 复位PCCARD存储块寄存器为默认值 */
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);  /* 根据结构体参数初始化NOR/SRAM控制器 */
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);  /* 根据结构体参数初始化NAND控制器 */
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);  /* 根据结构体参数初始化PCCARD控制器 */
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);  /* 将NOR/SRAM初始化结构体各成员置为默认值 */
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);  /* 将NAND初始化结构体各成员置为默认值 */
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);  /* 将PCCARD初始化结构体各成员置为默认值 */
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);  /* 使能或禁用指定的NOR/SRAM存储块 */
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState);  /* 使能或禁用指定的NAND存储块 */
void FSMC_PCCARDCmd(FunctionalState NewState);  /* 使能或禁用PCCARD存储块 */
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState);  /* 使能或禁用NAND存储块的ECC校验 */
uint32_t FSMC_GetECC(uint32_t FSMC_Bank);  /* 读取ECC错误纠正码寄存器的值 */
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState);  /* 使能或禁用指定的FSMC中断 */
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);  /* 获取指定的FSMC标志状态 */
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);  /* 清除指定的FSMC标志 */
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT);  /* 获取指定的FSMC中断状态 */
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT);  /* 清除指定的FSMC中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F10x_FSMC_H */
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
