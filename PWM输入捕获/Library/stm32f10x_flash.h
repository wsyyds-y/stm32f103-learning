/**
  ******************************************************************************
  * @file    stm32f10x_flash.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the FLASH 
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
#ifndef __STM32F10x_FLASH_H
#define __STM32F10x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/** @defgroup FLASH_Exported_Types
  * @{
  */

/** 
  * @brief  FLASH Status  
  */

typedef enum
{ 
  FLASH_BUSY = 1,  /* FLASH忙 */
  FLASH_ERROR_PG,  /* FLASH编程错误 */
  FLASH_ERROR_WRP,  /* FLASH写保护错误 */
  FLASH_COMPLETE,  /* FLASH操作完成 */
  FLASH_TIMEOUT  /* FLASH操作超时 */
}FLASH_Status;

/**
  * @}
  */

/** @defgroup FLASH_Exported_Constants
  * @{
  */

/** @defgroup Flash_Latency 
  * @{
  */

#define FLASH_Latency_0                ((uint32_t)0x00000000)  /*!< FLASH Zero Latency cycle */  /* FLASH零等待周期 */
#define FLASH_Latency_1                ((uint32_t)0x00000001)  /*!< FLASH One Latency cycle */  /* FLASH一个等待周期 */
#define FLASH_Latency_2                ((uint32_t)0x00000002)  /*!< FLASH Two Latency cycles */  /* FLASH两个等待周期 */
#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2))
/**
  * @}
  */

/** @defgroup Half_Cycle_Enable_Disable 
  * @{
  */

#define FLASH_HalfCycleAccess_Enable   ((uint32_t)0x00000008)  /*!< FLASH Half Cycle Enable */  /* 使能FLASH半周期访问 */
#define FLASH_HalfCycleAccess_Disable  ((uint32_t)0x00000000)  /*!< FLASH Half Cycle Disable */  /* 禁止FLASH半周期访问 */
#define IS_FLASH_HALFCYCLEACCESS_STATE(STATE) (((STATE) == FLASH_HalfCycleAccess_Enable) || \
                                               ((STATE) == FLASH_HalfCycleAccess_Disable)) 
/**
  * @}
  */

/** @defgroup Prefetch_Buffer_Enable_Disable 
  * @{
  */

#define FLASH_PrefetchBuffer_Enable    ((uint32_t)0x00000010)  /*!< FLASH Prefetch Buffer Enable */  /* 使能FLASH预取缓冲区 */
#define FLASH_PrefetchBuffer_Disable   ((uint32_t)0x00000000)  /*!< FLASH Prefetch Buffer Disable */  /* 禁止FLASH预取缓冲区 */
#define IS_FLASH_PREFETCHBUFFER_STATE(STATE) (((STATE) == FLASH_PrefetchBuffer_Enable) || \
                                              ((STATE) == FLASH_PrefetchBuffer_Disable)) 
/**
  * @}
  */

/** @defgroup Option_Bytes_Write_Protection 
  * @{
  */

/* Values to be used with STM32 Low and Medium density devices */
#define FLASH_WRProt_Pages0to3         ((uint32_t)0x00000001) /*!< STM32 Low and Medium density devices: Write protection of page 0 to 3 */  /* 写保护第0~3页 */
#define FLASH_WRProt_Pages4to7         ((uint32_t)0x00000002) /*!< STM32 Low and Medium density devices: Write protection of page 4 to 7 */  /* 写保护第4~7页 */
#define FLASH_WRProt_Pages8to11        ((uint32_t)0x00000004) /*!< STM32 Low and Medium density devices: Write protection of page 8 to 11 */  /* 写保护第8~11页 */
#define FLASH_WRProt_Pages12to15       ((uint32_t)0x00000008) /*!< STM32 Low and Medium density devices: Write protection of page 12 to 15 */  /* 写保护第12~15页 */
#define FLASH_WRProt_Pages16to19       ((uint32_t)0x00000010) /*!< STM32 Low and Medium density devices: Write protection of page 16 to 19 */  /* 写保护第16~19页 */
#define FLASH_WRProt_Pages20to23       ((uint32_t)0x00000020) /*!< STM32 Low and Medium density devices: Write protection of page 20 to 23 */  /* 写保护第20~23页 */
#define FLASH_WRProt_Pages24to27       ((uint32_t)0x00000040) /*!< STM32 Low and Medium density devices: Write protection of page 24 to 27 */  /* 写保护第24~27页 */
#define FLASH_WRProt_Pages28to31       ((uint32_t)0x00000080) /*!< STM32 Low and Medium density devices: Write protection of page 28 to 31 */  /* 写保护第28~31页 */

/* Values to be used with STM32 Medium-density devices */
#define FLASH_WRProt_Pages32to35       ((uint32_t)0x00000100) /*!< STM32 Medium-density devices: Write protection of page 32 to 35 */  /* 写保护第32~35页 */
#define FLASH_WRProt_Pages36to39       ((uint32_t)0x00000200) /*!< STM32 Medium-density devices: Write protection of page 36 to 39 */  /* 写保护第36~39页 */
#define FLASH_WRProt_Pages40to43       ((uint32_t)0x00000400) /*!< STM32 Medium-density devices: Write protection of page 40 to 43 */  /* 写保护第40~43页 */
#define FLASH_WRProt_Pages44to47       ((uint32_t)0x00000800) /*!< STM32 Medium-density devices: Write protection of page 44 to 47 */  /* 写保护第44~47页 */
#define FLASH_WRProt_Pages48to51       ((uint32_t)0x00001000) /*!< STM32 Medium-density devices: Write protection of page 48 to 51 */  /* 写保护第48~51页 */
#define FLASH_WRProt_Pages52to55       ((uint32_t)0x00002000) /*!< STM32 Medium-density devices: Write protection of page 52 to 55 */  /* 写保护第52~55页 */
#define FLASH_WRProt_Pages56to59       ((uint32_t)0x00004000) /*!< STM32 Medium-density devices: Write protection of page 56 to 59 */  /* 写保护第56~59页 */
#define FLASH_WRProt_Pages60to63       ((uint32_t)0x00008000) /*!< STM32 Medium-density devices: Write protection of page 60 to 63 */  /* 写保护第60~63页 */
#define FLASH_WRProt_Pages64to67       ((uint32_t)0x00010000) /*!< STM32 Medium-density devices: Write protection of page 64 to 67 */  /* 写保护第64~67页 */
#define FLASH_WRProt_Pages68to71       ((uint32_t)0x00020000) /*!< STM32 Medium-density devices: Write protection of page 68 to 71 */  /* 写保护第68~71页 */
#define FLASH_WRProt_Pages72to75       ((uint32_t)0x00040000) /*!< STM32 Medium-density devices: Write protection of page 72 to 75 */  /* 写保护第72~75页 */
#define FLASH_WRProt_Pages76to79       ((uint32_t)0x00080000) /*!< STM32 Medium-density devices: Write protection of page 76 to 79 */  /* 写保护第76~79页 */
#define FLASH_WRProt_Pages80to83       ((uint32_t)0x00100000) /*!< STM32 Medium-density devices: Write protection of page 80 to 83 */  /* 写保护第80~83页 */
#define FLASH_WRProt_Pages84to87       ((uint32_t)0x00200000) /*!< STM32 Medium-density devices: Write protection of page 84 to 87 */  /* 写保护第84~87页 */
#define FLASH_WRProt_Pages88to91       ((uint32_t)0x00400000) /*!< STM32 Medium-density devices: Write protection of page 88 to 91 */  /* 写保护第88~91页 */
#define FLASH_WRProt_Pages92to95       ((uint32_t)0x00800000) /*!< STM32 Medium-density devices: Write protection of page 92 to 95 */  /* 写保护第92~95页 */
#define FLASH_WRProt_Pages96to99       ((uint32_t)0x01000000) /*!< STM32 Medium-density devices: Write protection of page 96 to 99 */  /* 写保护第96~99页 */
#define FLASH_WRProt_Pages100to103     ((uint32_t)0x02000000) /*!< STM32 Medium-density devices: Write protection of page 100 to 103 */  /* 写保护第100~103页 */
#define FLASH_WRProt_Pages104to107     ((uint32_t)0x04000000) /*!< STM32 Medium-density devices: Write protection of page 104 to 107 */  /* 写保护第104~107页 */
#define FLASH_WRProt_Pages108to111     ((uint32_t)0x08000000) /*!< STM32 Medium-density devices: Write protection of page 108 to 111 */  /* 写保护第108~111页 */
#define FLASH_WRProt_Pages112to115     ((uint32_t)0x10000000) /*!< STM32 Medium-density devices: Write protection of page 112 to 115 */  /* 写保护第112~115页 */
#define FLASH_WRProt_Pages116to119     ((uint32_t)0x20000000) /*!< STM32 Medium-density devices: Write protection of page 115 to 119 */  /* 写保护第116~119页 */
#define FLASH_WRProt_Pages120to123     ((uint32_t)0x40000000) /*!< STM32 Medium-density devices: Write protection of page 120 to 123 */  /* 写保护第120~123页 */
#define FLASH_WRProt_Pages124to127     ((uint32_t)0x80000000) /*!< STM32 Medium-density devices: Write protection of page 124 to 127 */  /* 写保护第124~127页 */

/* Values to be used with STM32 High-density and STM32F10X Connectivity line devices */
#define FLASH_WRProt_Pages0to1         ((uint32_t)0x00000001) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 0 to 1 */  /* 写保护第0~1页 */
#define FLASH_WRProt_Pages2to3         ((uint32_t)0x00000002) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 2 to 3 */  /* 写保护第2~3页 */
#define FLASH_WRProt_Pages4to5         ((uint32_t)0x00000004) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 4 to 5 */  /* 写保护第4~5页 */
#define FLASH_WRProt_Pages6to7         ((uint32_t)0x00000008) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 6 to 7 */  /* 写保护第6~7页 */
#define FLASH_WRProt_Pages8to9         ((uint32_t)0x00000010) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 8 to 9 */  /* 写保护第8~9页 */
#define FLASH_WRProt_Pages10to11       ((uint32_t)0x00000020) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 10 to 11 */  /* 写保护第10~11页 */
#define FLASH_WRProt_Pages12to13       ((uint32_t)0x00000040) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 12 to 13 */  /* 写保护第12~13页 */
#define FLASH_WRProt_Pages14to15       ((uint32_t)0x00000080) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 14 to 15 */  /* 写保护第14~15页 */
#define FLASH_WRProt_Pages16to17       ((uint32_t)0x00000100) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 16 to 17 */  /* 写保护第16~17页 */
#define FLASH_WRProt_Pages18to19       ((uint32_t)0x00000200) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 18 to 19 */  /* 写保护第18~19页 */
#define FLASH_WRProt_Pages20to21       ((uint32_t)0x00000400) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 20 to 21 */  /* 写保护第20~21页 */
#define FLASH_WRProt_Pages22to23       ((uint32_t)0x00000800) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 22 to 23 */  /* 写保护第22~23页 */
#define FLASH_WRProt_Pages24to25       ((uint32_t)0x00001000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 24 to 25 */  /* 写保护第24~25页 */
#define FLASH_WRProt_Pages26to27       ((uint32_t)0x00002000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 26 to 27 */  /* 写保护第26~27页 */
#define FLASH_WRProt_Pages28to29       ((uint32_t)0x00004000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 28 to 29 */  /* 写保护第28~29页 */
#define FLASH_WRProt_Pages30to31       ((uint32_t)0x00008000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 30 to 31 */  /* 写保护第30~31页 */
#define FLASH_WRProt_Pages32to33       ((uint32_t)0x00010000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 32 to 33 */  /* 写保护第32~33页 */
#define FLASH_WRProt_Pages34to35       ((uint32_t)0x00020000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 34 to 35 */  /* 写保护第34~35页 */
#define FLASH_WRProt_Pages36to37       ((uint32_t)0x00040000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 36 to 37 */  /* 写保护第36~37页 */
#define FLASH_WRProt_Pages38to39       ((uint32_t)0x00080000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 38 to 39 */  /* 写保护第38~39页 */
#define FLASH_WRProt_Pages40to41       ((uint32_t)0x00100000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 40 to 41 */  /* 写保护第40~41页 */
#define FLASH_WRProt_Pages42to43       ((uint32_t)0x00200000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 42 to 43 */  /* 写保护第42~43页 */
#define FLASH_WRProt_Pages44to45       ((uint32_t)0x00400000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 44 to 45 */  /* 写保护第44~45页 */
#define FLASH_WRProt_Pages46to47       ((uint32_t)0x00800000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 46 to 47 */  /* 写保护第46~47页 */
#define FLASH_WRProt_Pages48to49       ((uint32_t)0x01000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 48 to 49 */  /* 写保护第48~49页 */
#define FLASH_WRProt_Pages50to51       ((uint32_t)0x02000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 50 to 51 */  /* 写保护第50~51页 */
#define FLASH_WRProt_Pages52to53       ((uint32_t)0x04000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 52 to 53 */  /* 写保护第52~53页 */
#define FLASH_WRProt_Pages54to55       ((uint32_t)0x08000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 54 to 55 */  /* 写保护第54~55页 */
#define FLASH_WRProt_Pages56to57       ((uint32_t)0x10000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 56 to 57 */  /* 写保护第56~57页 */
#define FLASH_WRProt_Pages58to59       ((uint32_t)0x20000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 58 to 59 */  /* 写保护第58~59页 */
#define FLASH_WRProt_Pages60to61       ((uint32_t)0x40000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 60 to 61 */  /* 写保护第60~61页 */
#define FLASH_WRProt_Pages62to127      ((uint32_t)0x80000000) /*!< STM32 Connectivity line devices: Write protection of page 62 to 127 */  /* 写保护第62~127页 */
#define FLASH_WRProt_Pages62to255      ((uint32_t)0x80000000) /*!< STM32 Medium-density devices: Write protection of page 62 to 255 */  /* 写保护第62~255页 */
#define FLASH_WRProt_Pages62to511      ((uint32_t)0x80000000) /*!< STM32 XL-density devices: Write protection of page 62 to 511 */  /* 写保护第62~511页 */

#define FLASH_WRProt_AllPages          ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Pages */  /* 写保护所有页 */

#define IS_FLASH_WRPROT_PAGE(PAGE) (((PAGE) != 0x00000000))

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x080FFFFF))

#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806))

/**
  * @}
  */

/** @defgroup Option_Bytes_IWatchdog 
  * @{
  */

#define OB_IWDG_SW                     ((uint16_t)0x0001)  /*!< Software IWDG selected */  /* 选择软件IWDG */
#define OB_IWDG_HW                     ((uint16_t)0x0000)  /*!< Hardware IWDG selected */  /* 选择硬件IWDG */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STOP 
  * @{
  */

#define OB_STOP_NoRST                  ((uint16_t)0x0002) /*!< No reset generated when entering in STOP */  /* 进入STOP不产生复位 */
#define OB_STOP_RST                    ((uint16_t)0x0000) /*!< Reset generated when entering in STOP */  /* 进入STOP产生复位 */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STDBY 
  * @{
  */

#define OB_STDBY_NoRST                 ((uint16_t)0x0004) /*!< No reset generated when entering in STANDBY */  /* 进入STANDBY不产生复位 */
#define OB_STDBY_RST                   ((uint16_t)0x0000) /*!< Reset generated when entering in STANDBY */  /* 进入STANDBY产生复位 */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

#ifdef STM32F10X_XL
/**
  * @}
  */
/** @defgroup FLASH_Boot
  * @{
  */
#define FLASH_BOOT_Bank1  ((uint16_t)0x0000) /*!< At startup, if boot pins are set in boot from user Flash position
                                                  and this parameter is selected the device will boot from Bank1(Default) */  /* 从存储块1启动(默认) */
#define FLASH_BOOT_Bank2  ((uint16_t)0x0001) /*!< At startup, if boot pins are set in boot from user Flash position
                                                  and this parameter is selected the device will boot from Bank 2 or Bank 1,
                                                  depending on the activation of the bank */  /* 从存储块2启动 */
#define IS_FLASH_BOOT(BOOT) (((BOOT) == FLASH_BOOT_Bank1) || ((BOOT) == FLASH_BOOT_Bank2))
#endif
/**
  * @}
  */
/** @defgroup FLASH_Interrupts 
  * @{
  */
#ifdef STM32F10X_XL
#define FLASH_IT_BANK2_ERROR                 ((uint32_t)0x80000400)  /*!< FPEC BANK2 error interrupt source */  /* 存储块2错误中断源 */
#define FLASH_IT_BANK2_EOP                   ((uint32_t)0x80001000)  /*!< End of FLASH BANK2 Operation Interrupt source */  /* 存储块2操作结束中断源 */

#define FLASH_IT_BANK1_ERROR                 FLASH_IT_ERROR          /*!< FPEC BANK1 error interrupt source */  /* 存储块1错误中断源 */
#define FLASH_IT_BANK1_EOP                   FLASH_IT_EOP            /*!< End of FLASH BANK1 Operation Interrupt source */  /* 存储块1操作结束中断源 */

#define FLASH_IT_ERROR                 ((uint32_t)0x00000400)  /*!< FPEC BANK1 error interrupt source */  /* 存储块1错误中断源 */
#define FLASH_IT_EOP                   ((uint32_t)0x00001000)  /*!< End of FLASH BANK1 Operation Interrupt source */  /* 存储块1操作结束中断源 */
#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0x7FFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))
#else
#define FLASH_IT_ERROR                 ((uint32_t)0x00000400)  /*!< FPEC error interrupt source */  /* FPEC错误中断源 */
#define FLASH_IT_EOP                   ((uint32_t)0x00001000)  /*!< End of FLASH Operation Interrupt source */  /* FLASH操作结束中断源 */
#define FLASH_IT_BANK1_ERROR           FLASH_IT_ERROR          /*!< FPEC BANK1 error interrupt source */  /* 存储块1错误中断源 */
#define FLASH_IT_BANK1_EOP             FLASH_IT_EOP            /*!< End of FLASH BANK1 Operation Interrupt source */  /* 存储块1操作结束中断源 */

#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))
#endif

/**
  * @}
  */

/** @defgroup FLASH_Flags 
  * @{
  */
#ifdef STM32F10X_XL
#define FLASH_FLAG_BANK2_BSY                 ((uint32_t)0x80000001)  /*!< FLASH BANK2 Busy flag */  /* 存储块2忙标志 */
#define FLASH_FLAG_BANK2_EOP                 ((uint32_t)0x80000020)  /*!< FLASH BANK2 End of Operation flag */  /* 存储块2操作结束标志 */
#define FLASH_FLAG_BANK2_PGERR               ((uint32_t)0x80000004)  /*!< FLASH BANK2 Program error flag */  /* 存储块2编程错误标志 */
#define FLASH_FLAG_BANK2_WRPRTERR            ((uint32_t)0x80000010)  /*!< FLASH BANK2 Write protected error flag */  /* 存储块2写保护错误标志 */

#define FLASH_FLAG_BANK1_BSY                 FLASH_FLAG_BSY       /*!< FLASH BANK1 Busy flag*/  /* 存储块1忙标志 */
#define FLASH_FLAG_BANK1_EOP                 FLASH_FLAG_EOP       /*!< FLASH BANK1 End of Operation flag */  /* 存储块1操作结束标志 */
#define FLASH_FLAG_BANK1_PGERR               FLASH_FLAG_PGERR     /*!< FLASH BANK1 Program error flag */  /* 存储块1编程错误标志 */
#define FLASH_FLAG_BANK1_WRPRTERR            FLASH_FLAG_WRPRTERR  /*!< FLASH BANK1 Write protected error flag */  /* 存储块1写保护错误标志 */

#define FLASH_FLAG_BSY                 ((uint32_t)0x00000001)  /*!< FLASH Busy flag */  /* FLASH忙标志 */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */  /* FLASH操作结束标志 */
#define FLASH_FLAG_PGERR               ((uint32_t)0x00000004)  /*!< FLASH Program error flag */  /* FLASH编程错误标志 */
#define FLASH_FLAG_WRPRTERR            ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */  /* FLASH写保护错误标志 */
#define FLASH_FLAG_OPTERR              ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */  /* FLASH选项字节错误标志 */
 
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0x7FFFFFCA) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_EOP) || \
                                  ((FLAG) == FLASH_FLAG_PGERR) || ((FLAG) == FLASH_FLAG_WRPRTERR) || \
                                  ((FLAG) == FLASH_FLAG_OPTERR)|| \
                                  ((FLAG) == FLASH_FLAG_BANK1_BSY) || ((FLAG) == FLASH_FLAG_BANK1_EOP) || \
                                  ((FLAG) == FLASH_FLAG_BANK1_PGERR) || ((FLAG) == FLASH_FLAG_BANK1_WRPRTERR) || \
                                  ((FLAG) == FLASH_FLAG_BANK2_BSY) || ((FLAG) == FLASH_FLAG_BANK2_EOP) || \
                                  ((FLAG) == FLASH_FLAG_BANK2_PGERR) || ((FLAG) == FLASH_FLAG_BANK2_WRPRTERR))
#else
#define FLASH_FLAG_BSY                 ((uint32_t)0x00000001)  /*!< FLASH Busy flag */  /* FLASH忙标志 */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */  /* FLASH操作结束标志 */
#define FLASH_FLAG_PGERR               ((uint32_t)0x00000004)  /*!< FLASH Program error flag */  /* FLASH编程错误标志 */
#define FLASH_FLAG_WRPRTERR            ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */  /* FLASH写保护错误标志 */
#define FLASH_FLAG_OPTERR              ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */  /* FLASH选项字节错误标志 */

#define FLASH_FLAG_BANK1_BSY                 FLASH_FLAG_BSY       /*!< FLASH BANK1 Busy flag*/  /* 存储块1忙标志 */
#define FLASH_FLAG_BANK1_EOP                 FLASH_FLAG_EOP       /*!< FLASH BANK1 End of Operation flag */  /* 存储块1操作结束标志 */
#define FLASH_FLAG_BANK1_PGERR               FLASH_FLAG_PGERR     /*!< FLASH BANK1 Program error flag */  /* 存储块1编程错误标志 */
#define FLASH_FLAG_BANK1_WRPRTERR            FLASH_FLAG_WRPRTERR  /*!< FLASH BANK1 Write protected error flag */  /* 存储块1写保护错误标志 */
 
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFCA) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_EOP) || \
                                  ((FLAG) == FLASH_FLAG_PGERR) || ((FLAG) == FLASH_FLAG_WRPRTERR) || \
								  ((FLAG) == FLASH_FLAG_BANK1_BSY) || ((FLAG) == FLASH_FLAG_BANK1_EOP) || \
                                  ((FLAG) == FLASH_FLAG_BANK1_PGERR) || ((FLAG) == FLASH_FLAG_BANK1_WRPRTERR) || \
                                  ((FLAG) == FLASH_FLAG_OPTERR))
#endif

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASH_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions
  * @{
  */

/*------------ Functions used for all STM32F10x devices -----*/
void FLASH_SetLatency(uint32_t FLASH_Latency);  /* 设置FLASH等待周期数 */
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);  /* 使能或禁止FLASH半周期访问 */
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);  /* 使能或禁止FLASH预取缓冲区 */
void FLASH_Unlock(void);  /* 解锁FLASH编程擦除控制器 */
void FLASH_Lock(void);  /* 锁定FLASH编程擦除控制器 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);  /* 擦除指定的FLASH页 */
FLASH_Status FLASH_EraseAllPages(void);  /* 擦除所有FLASH页 */
FLASH_Status FLASH_EraseOptionBytes(void);  /* 擦除FLASH选项字节 */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);  /* 在指定地址编程一个32位字 */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);  /* 在指定地址编程一个16位半字 */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);  /* 在选项字节数据地址编程半字 */
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);  /* 对指定页使能写保护 */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);  /* 使能或禁止读出保护 */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);  /* 配置用户选项字节(IWDG/STOP/STDBY) */
uint32_t FLASH_GetUserOptionByte(void);  /* 获取FLASH用户选项字节值 */
uint32_t FLASH_GetWriteProtectionOptionByte(void);  /* 获取写保护选项字节寄存器值 */
FlagStatus FLASH_GetReadOutProtectionStatus(void);  /* 获取FLASH读出保护状态 */
FlagStatus FLASH_GetPrefetchBufferStatus(void);  /* 获取FLASH预取缓冲区状态 */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);  /* 使能或禁止指定的FLASH中断 */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);  /* 获取指定FLASH标志的状态 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG);  /* 清除FLASH挂起标志 */
FLASH_Status FLASH_GetStatus(void);  /* 获取FLASH状态 */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);  /* 等待FLASH上次操作完成或超时 */

/*------------ New function used for all STM32F10x devices -----*/
void FLASH_UnlockBank1(void);  /* 解锁FLASH存储块1编程擦除控制器 */
void FLASH_LockBank1(void);  /* 锁定FLASH存储块1编程擦除控制器 */
FLASH_Status FLASH_EraseAllBank1Pages(void);  /* 擦除FLASH存储块1的所有页 */
FLASH_Status FLASH_GetBank1Status(void);  /* 获取FLASH存储块1状态 */
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);  /* 等待存储块1上次FLASH操作完成或超时 */

#ifdef STM32F10X_XL
/*---- New Functions used only with STM32F10x_XL density devices -----*/
void FLASH_UnlockBank2(void);  /* 解锁FLASH存储块2编程擦除控制器 */
void FLASH_LockBank2(void);  /* 锁定FLASH存储块2编程擦除控制器 */
FLASH_Status FLASH_EraseAllBank2Pages(void);  /* 擦除FLASH存储块2的所有页 */
FLASH_Status FLASH_GetBank2Status(void);  /* 获取FLASH存储块2状态 */
FLASH_Status FLASH_WaitForLastBank2Operation(uint32_t Timeout);  /* 等待存储块2上次FLASH操作完成或超时 */
FLASH_Status FLASH_BootConfig(uint16_t FLASH_BOOT);  /* 配置从存储块1或存储块2启动 */
#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_FLASH_H */
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
