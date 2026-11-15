/**
  ******************************************************************************
  * @file    stm32f10x_rcc.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the RCC firmware 
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
#ifndef __STM32F10x_RCC_H
#define __STM32F10x_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Types
  * @{
  */

typedef struct
{
  uint32_t SYSCLK_Frequency; /* 系统时钟SYSCLK频率(Hz) */ /*!< returns SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency; /* AHB总线时钟HCLK频率(Hz) */ /*!< returns HCLK clock frequency expressed in Hz */
  uint32_t PCLK1_Frequency; /* APB1总线时钟PCLK1频率(Hz) */ /*!< returns PCLK1 clock frequency expressed in Hz */
  uint32_t PCLK2_Frequency; /* APB2总线时钟PCLK2频率(Hz) */ /*!< returns PCLK2 clock frequency expressed in Hz */
  uint32_t ADCCLK_Frequency; /* ADC时钟ADCCLK频率(Hz) */ /*!< returns ADCCLK clock frequency expressed in Hz */
}RCC_ClocksTypeDef;

/**
  * @}
  */

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup HSE_configuration 
  * @{
  */

#define RCC_HSE_OFF                      ((uint32_t)0x00000000)  /* 关闭HSE振荡器 */
#define RCC_HSE_ON                       ((uint32_t)0x00010000)  /* 开启HSE振荡器 */
#define RCC_HSE_Bypass                   ((uint32_t)0x00040000)  /* HSE旁路,由外部时钟驱动 */
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
  * @}
  */ 

/** @defgroup PLL_entry_clock_source 
  * @{
  */

#define RCC_PLLSource_HSI_Div2           ((uint32_t)0x00000000)  /* PLL输入源:HSI二分频 */

#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL) && !defined (STM32F10X_CL)
 #define RCC_PLLSource_HSE_Div1           ((uint32_t)0x00010000)  /* PLL输入源:HSE不分频 */
 #define RCC_PLLSource_HSE_Div2           ((uint32_t)0x00030000)  /* PLL输入源:HSE二分频 */
 #define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_HSE_Div1) || \
                                   ((SOURCE) == RCC_PLLSource_HSE_Div2))
#else
 #define RCC_PLLSource_PREDIV1            ((uint32_t)0x00010000)  /* PLL输入源:PREDIV1输出 */
 #define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_PREDIV1))
#endif /* STM32F10X_CL */ 

/**
  * @}
  */ 

/** @defgroup PLL_multiplication_factor 
  * @{
  */
#ifndef STM32F10X_CL
 #define RCC_PLLMul_2                    ((uint32_t)0x00000000)  /* PLL倍频系数x2 */
 #define RCC_PLLMul_3                    ((uint32_t)0x00040000)  /* PLL倍频系数x3 */
 #define RCC_PLLMul_4                    ((uint32_t)0x00080000)  /* PLL倍频系数x4 */
 #define RCC_PLLMul_5                    ((uint32_t)0x000C0000)  /* PLL倍频系数x5 */
 #define RCC_PLLMul_6                    ((uint32_t)0x00100000)  /* PLL倍频系数x6 */
 #define RCC_PLLMul_7                    ((uint32_t)0x00140000)  /* PLL倍频系数x7 */
 #define RCC_PLLMul_8                    ((uint32_t)0x00180000)  /* PLL倍频系数x8 */
 #define RCC_PLLMul_9                    ((uint32_t)0x001C0000)  /* PLL倍频系数x9 */
 #define RCC_PLLMul_10                   ((uint32_t)0x00200000)  /* PLL倍频系数x10 */
 #define RCC_PLLMul_11                   ((uint32_t)0x00240000)  /* PLL倍频系数x11 */
 #define RCC_PLLMul_12                   ((uint32_t)0x00280000)  /* PLL倍频系数x12 */
 #define RCC_PLLMul_13                   ((uint32_t)0x002C0000)  /* PLL倍频系数x13 */
 #define RCC_PLLMul_14                   ((uint32_t)0x00300000)  /* PLL倍频系数x14 */
 #define RCC_PLLMul_15                   ((uint32_t)0x00340000)  /* PLL倍频系数x15 */
 #define RCC_PLLMul_16                   ((uint32_t)0x00380000)  /* PLL倍频系数x16 */
 #define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
                              ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
                              ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
                              ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
                              ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
                              ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
                              ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
                              ((MUL) == RCC_PLLMul_16))

#else
 #define RCC_PLLMul_4                    ((uint32_t)0x00080000)  /* PLL倍频系数x4 */
 #define RCC_PLLMul_5                    ((uint32_t)0x000C0000)  /* PLL倍频系数x5 */
 #define RCC_PLLMul_6                    ((uint32_t)0x00100000)  /* PLL倍频系数x6 */
 #define RCC_PLLMul_7                    ((uint32_t)0x00140000)  /* PLL倍频系数x7 */
 #define RCC_PLLMul_8                    ((uint32_t)0x00180000)  /* PLL倍频系数x8 */
 #define RCC_PLLMul_9                    ((uint32_t)0x001C0000)  /* PLL倍频系数x9 */
 #define RCC_PLLMul_6_5                  ((uint32_t)0x00340000)  /* PLL倍频系数x6.5 */

 #define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5) || \
                              ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7) || \
                              ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9) || \
                              ((MUL) == RCC_PLLMul_6_5))
#endif /* STM32F10X_CL */                              
/**
  * @}
  */

/** @defgroup PREDIV1_division_factor
  * @{
  */
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL)
 #define  RCC_PREDIV1_Div1               ((uint32_t)0x00000000)  /* PREDIV1分频系数1 */
 #define  RCC_PREDIV1_Div2               ((uint32_t)0x00000001)  /* PREDIV1分频系数2 */
 #define  RCC_PREDIV1_Div3               ((uint32_t)0x00000002)  /* PREDIV1分频系数3 */
 #define  RCC_PREDIV1_Div4               ((uint32_t)0x00000003)  /* PREDIV1分频系数4 */
 #define  RCC_PREDIV1_Div5               ((uint32_t)0x00000004)  /* PREDIV1分频系数5 */
 #define  RCC_PREDIV1_Div6               ((uint32_t)0x00000005)  /* PREDIV1分频系数6 */
 #define  RCC_PREDIV1_Div7               ((uint32_t)0x00000006)  /* PREDIV1分频系数7 */
 #define  RCC_PREDIV1_Div8               ((uint32_t)0x00000007)  /* PREDIV1分频系数8 */
 #define  RCC_PREDIV1_Div9               ((uint32_t)0x00000008)  /* PREDIV1分频系数9 */
 #define  RCC_PREDIV1_Div10              ((uint32_t)0x00000009)  /* PREDIV1分频系数10 */
 #define  RCC_PREDIV1_Div11              ((uint32_t)0x0000000A)  /* PREDIV1分频系数11 */
 #define  RCC_PREDIV1_Div12              ((uint32_t)0x0000000B)  /* PREDIV1分频系数12 */
 #define  RCC_PREDIV1_Div13              ((uint32_t)0x0000000C)  /* PREDIV1分频系数13 */
 #define  RCC_PREDIV1_Div14              ((uint32_t)0x0000000D)  /* PREDIV1分频系数14 */
 #define  RCC_PREDIV1_Div15              ((uint32_t)0x0000000E)  /* PREDIV1分频系数15 */
 #define  RCC_PREDIV1_Div16              ((uint32_t)0x0000000F)  /* PREDIV1分频系数16 */

 #define IS_RCC_PREDIV1(PREDIV1) (((PREDIV1) == RCC_PREDIV1_Div1) || ((PREDIV1) == RCC_PREDIV1_Div2) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div3) || ((PREDIV1) == RCC_PREDIV1_Div4) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div5) || ((PREDIV1) == RCC_PREDIV1_Div6) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div7) || ((PREDIV1) == RCC_PREDIV1_Div8) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div9) || ((PREDIV1) == RCC_PREDIV1_Div10) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div11) || ((PREDIV1) == RCC_PREDIV1_Div12) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div13) || ((PREDIV1) == RCC_PREDIV1_Div14) || \
                                  ((PREDIV1) == RCC_PREDIV1_Div15) || ((PREDIV1) == RCC_PREDIV1_Div16))
#endif
/**
  * @}
  */


/** @defgroup PREDIV1_clock_source
  * @{
  */
#ifdef STM32F10X_CL
/* PREDIV1 clock source (for STM32 connectivity line devices) */
 #define  RCC_PREDIV1_Source_HSE         ((uint32_t)0x00000000)   /* PREDIV1时钟源:HSE */
 #define  RCC_PREDIV1_Source_PLL2        ((uint32_t)0x00010000)   /* PREDIV1时钟源:PLL2 */

 #define IS_RCC_PREDIV1_SOURCE(SOURCE) (((SOURCE) == RCC_PREDIV1_Source_HSE) || \
                                        ((SOURCE) == RCC_PREDIV1_Source_PLL2)) 
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
/* PREDIV1 clock source (for STM32 Value line devices) */
 #define  RCC_PREDIV1_Source_HSE         ((uint32_t)0x00000000)   /* PREDIV1时钟源:HSE */

 #define IS_RCC_PREDIV1_SOURCE(SOURCE) (((SOURCE) == RCC_PREDIV1_Source_HSE)) 
#endif
/**
  * @}
  */

#ifdef STM32F10X_CL
/** @defgroup PREDIV2_division_factor
  * @{
  */
  
 #define  RCC_PREDIV2_Div1               ((uint32_t)0x00000000)  /* PREDIV2分频系数1 */
 #define  RCC_PREDIV2_Div2               ((uint32_t)0x00000010)  /* PREDIV2分频系数2 */
 #define  RCC_PREDIV2_Div3               ((uint32_t)0x00000020)  /* PREDIV2分频系数3 */
 #define  RCC_PREDIV2_Div4               ((uint32_t)0x00000030)  /* PREDIV2分频系数4 */
 #define  RCC_PREDIV2_Div5               ((uint32_t)0x00000040)  /* PREDIV2分频系数5 */
 #define  RCC_PREDIV2_Div6               ((uint32_t)0x00000050)  /* PREDIV2分频系数6 */
 #define  RCC_PREDIV2_Div7               ((uint32_t)0x00000060)  /* PREDIV2分频系数7 */
 #define  RCC_PREDIV2_Div8               ((uint32_t)0x00000070)  /* PREDIV2分频系数8 */
 #define  RCC_PREDIV2_Div9               ((uint32_t)0x00000080)  /* PREDIV2分频系数9 */
 #define  RCC_PREDIV2_Div10              ((uint32_t)0x00000090)  /* PREDIV2分频系数10 */
 #define  RCC_PREDIV2_Div11              ((uint32_t)0x000000A0)  /* PREDIV2分频系数11 */
 #define  RCC_PREDIV2_Div12              ((uint32_t)0x000000B0)  /* PREDIV2分频系数12 */
 #define  RCC_PREDIV2_Div13              ((uint32_t)0x000000C0)  /* PREDIV2分频系数13 */
 #define  RCC_PREDIV2_Div14              ((uint32_t)0x000000D0)  /* PREDIV2分频系数14 */
 #define  RCC_PREDIV2_Div15              ((uint32_t)0x000000E0)  /* PREDIV2分频系数15 */
 #define  RCC_PREDIV2_Div16              ((uint32_t)0x000000F0)  /* PREDIV2分频系数16 */

 #define IS_RCC_PREDIV2(PREDIV2) (((PREDIV2) == RCC_PREDIV2_Div1) || ((PREDIV2) == RCC_PREDIV2_Div2) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div3) || ((PREDIV2) == RCC_PREDIV2_Div4) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div5) || ((PREDIV2) == RCC_PREDIV2_Div6) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div7) || ((PREDIV2) == RCC_PREDIV2_Div8) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div9) || ((PREDIV2) == RCC_PREDIV2_Div10) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div11) || ((PREDIV2) == RCC_PREDIV2_Div12) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div13) || ((PREDIV2) == RCC_PREDIV2_Div14) || \
                                  ((PREDIV2) == RCC_PREDIV2_Div15) || ((PREDIV2) == RCC_PREDIV2_Div16))
/**
  * @}
  */


/** @defgroup PLL2_multiplication_factor
  * @{
  */
  
 #define  RCC_PLL2Mul_8                  ((uint32_t)0x00000600)  /* PLL2倍频系数x8 */
 #define  RCC_PLL2Mul_9                  ((uint32_t)0x00000700)  /* PLL2倍频系数x9 */
 #define  RCC_PLL2Mul_10                 ((uint32_t)0x00000800)  /* PLL2倍频系数x10 */
 #define  RCC_PLL2Mul_11                 ((uint32_t)0x00000900)  /* PLL2倍频系数x11 */
 #define  RCC_PLL2Mul_12                 ((uint32_t)0x00000A00)  /* PLL2倍频系数x12 */
 #define  RCC_PLL2Mul_13                 ((uint32_t)0x00000B00)  /* PLL2倍频系数x13 */
 #define  RCC_PLL2Mul_14                 ((uint32_t)0x00000C00)  /* PLL2倍频系数x14 */
 #define  RCC_PLL2Mul_16                 ((uint32_t)0x00000E00)  /* PLL2倍频系数x16 */
 #define  RCC_PLL2Mul_20                 ((uint32_t)0x00000F00)  /* PLL2倍频系数x20 */

 #define IS_RCC_PLL2_MUL(MUL) (((MUL) == RCC_PLL2Mul_8) || ((MUL) == RCC_PLL2Mul_9)  || \
                               ((MUL) == RCC_PLL2Mul_10) || ((MUL) == RCC_PLL2Mul_11) || \
                               ((MUL) == RCC_PLL2Mul_12) || ((MUL) == RCC_PLL2Mul_13) || \
                               ((MUL) == RCC_PLL2Mul_14) || ((MUL) == RCC_PLL2Mul_16) || \
                               ((MUL) == RCC_PLL2Mul_20))
/**
  * @}
  */


/** @defgroup PLL3_multiplication_factor
  * @{
  */

 #define  RCC_PLL3Mul_8                  ((uint32_t)0x00006000)  /* PLL3倍频系数x8 */
 #define  RCC_PLL3Mul_9                  ((uint32_t)0x00007000)  /* PLL3倍频系数x9 */
 #define  RCC_PLL3Mul_10                 ((uint32_t)0x00008000)  /* PLL3倍频系数x10 */
 #define  RCC_PLL3Mul_11                 ((uint32_t)0x00009000)  /* PLL3倍频系数x11 */
 #define  RCC_PLL3Mul_12                 ((uint32_t)0x0000A000)  /* PLL3倍频系数x12 */
 #define  RCC_PLL3Mul_13                 ((uint32_t)0x0000B000)  /* PLL3倍频系数x13 */
 #define  RCC_PLL3Mul_14                 ((uint32_t)0x0000C000)  /* PLL3倍频系数x14 */
 #define  RCC_PLL3Mul_16                 ((uint32_t)0x0000E000)  /* PLL3倍频系数x16 */
 #define  RCC_PLL3Mul_20                 ((uint32_t)0x0000F000)  /* PLL3倍频系数x20 */

 #define IS_RCC_PLL3_MUL(MUL) (((MUL) == RCC_PLL3Mul_8) || ((MUL) == RCC_PLL3Mul_9)  || \
                               ((MUL) == RCC_PLL3Mul_10) || ((MUL) == RCC_PLL3Mul_11) || \
                               ((MUL) == RCC_PLL3Mul_12) || ((MUL) == RCC_PLL3Mul_13) || \
                               ((MUL) == RCC_PLL3Mul_14) || ((MUL) == RCC_PLL3Mul_16) || \
                               ((MUL) == RCC_PLL3Mul_20))
/**
  * @}
  */

#endif /* STM32F10X_CL */


/** @defgroup System_clock_source 
  * @{
  */

#define RCC_SYSCLKSource_HSI             ((uint32_t)0x00000000)  /* 系统时钟源:HSI */
#define RCC_SYSCLKSource_HSE             ((uint32_t)0x00000001)  /* 系统时钟源:HSE */
#define RCC_SYSCLKSource_PLLCLK          ((uint32_t)0x00000002)  /* 系统时钟源:PLL输出 */
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))
/**
  * @}
  */

/** @defgroup AHB_clock_source 
  * @{
  */

#define RCC_SYSCLK_Div1                  ((uint32_t)0x00000000)  /* AHB时钟=SYSCLK/1 */
#define RCC_SYSCLK_Div2                  ((uint32_t)0x00000080)  /* AHB时钟=SYSCLK/2 */
#define RCC_SYSCLK_Div4                  ((uint32_t)0x00000090)  /* AHB时钟=SYSCLK/4 */
#define RCC_SYSCLK_Div8                  ((uint32_t)0x000000A0)  /* AHB时钟=SYSCLK/8 */
#define RCC_SYSCLK_Div16                 ((uint32_t)0x000000B0)  /* AHB时钟=SYSCLK/16 */
#define RCC_SYSCLK_Div64                 ((uint32_t)0x000000C0)  /* AHB时钟=SYSCLK/64 */
#define RCC_SYSCLK_Div128                ((uint32_t)0x000000D0)  /* AHB时钟=SYSCLK/128 */
#define RCC_SYSCLK_Div256                ((uint32_t)0x000000E0)  /* AHB时钟=SYSCLK/256 */
#define RCC_SYSCLK_Div512                ((uint32_t)0x000000F0)  /* AHB时钟=SYSCLK/512 */
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */ 

/** @defgroup APB1_APB2_clock_source 
  * @{
  */

#define RCC_HCLK_Div1                    ((uint32_t)0x00000000)  /* APB时钟=HCLK/1 */
#define RCC_HCLK_Div2                    ((uint32_t)0x00000400)  /* APB时钟=HCLK/2 */
#define RCC_HCLK_Div4                    ((uint32_t)0x00000500)  /* APB时钟=HCLK/4 */
#define RCC_HCLK_Div8                    ((uint32_t)0x00000600)  /* APB时钟=HCLK/8 */
#define RCC_HCLK_Div16                   ((uint32_t)0x00000700)  /* APB时钟=HCLK/16 */
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))
/**
  * @}
  */

/** @defgroup RCC_Interrupt_source 
  * @{
  */

#define RCC_IT_LSIRDY                    ((uint8_t)0x01)  /* LSI就绪中断 */
#define RCC_IT_LSERDY                    ((uint8_t)0x02)  /* LSE就绪中断 */
#define RCC_IT_HSIRDY                    ((uint8_t)0x04)  /* HSI就绪中断 */
#define RCC_IT_HSERDY                    ((uint8_t)0x08)  /* HSE就绪中断 */
#define RCC_IT_PLLRDY                    ((uint8_t)0x10)  /* PLL就绪中断 */
#define RCC_IT_CSS                       ((uint8_t)0x80)  /* 时钟安全系统中断 */

#ifndef STM32F10X_CL
 #define IS_RCC_IT(IT) ((((IT) & (uint8_t)0xE0) == 0x00) && ((IT) != 0x00))
 #define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                            ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                            ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS))
 #define IS_RCC_CLEAR_IT(IT) ((((IT) & (uint8_t)0x60) == 0x00) && ((IT) != 0x00))
#else
 #define RCC_IT_PLL2RDY                  ((uint8_t)0x20)  /* PLL2就绪中断 */
 #define RCC_IT_PLL3RDY                  ((uint8_t)0x40)  /* PLL3就绪中断 */
 #define IS_RCC_IT(IT) ((((IT) & (uint8_t)0x80) == 0x00) && ((IT) != 0x00))
 #define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                            ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                            ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS) || \
                            ((IT) == RCC_IT_PLL2RDY) || ((IT) == RCC_IT_PLL3RDY))
 #define IS_RCC_CLEAR_IT(IT) ((IT) != 0x00)
#endif /* STM32F10X_CL */ 


/**
  * @}
  */

#ifndef STM32F10X_CL
/** @defgroup USB_Device_clock_source 
  * @{
  */

 #define RCC_USBCLKSource_PLLCLK_1Div5   ((uint8_t)0x00)  /* USB时钟源:PLL/1.5 */
 #define RCC_USBCLKSource_PLLCLK_Div1    ((uint8_t)0x01)  /* USB时钟源:PLL/1 */

 #define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      ((SOURCE) == RCC_USBCLKSource_PLLCLK_Div1))
/**
  * @}
  */
#else
/** @defgroup USB_OTG_FS_clock_source 
  * @{
  */
 #define RCC_OTGFSCLKSource_PLLVCO_Div3    ((uint8_t)0x00)  /* OTG_FS时钟源:PLLVCO/3 */
 #define RCC_OTGFSCLKSource_PLLVCO_Div2    ((uint8_t)0x01)  /* OTG_FS时钟源:PLLVCO/2 */

 #define IS_RCC_OTGFSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_OTGFSCLKSource_PLLVCO_Div3) || \
                                         ((SOURCE) == RCC_OTGFSCLKSource_PLLVCO_Div2))
/**
  * @}
  */
#endif /* STM32F10X_CL */ 


#ifdef STM32F10X_CL
/** @defgroup I2S2_clock_source 
  * @{
  */
 #define RCC_I2S2CLKSource_SYSCLK        ((uint8_t)0x00)  /* I2S2时钟源:SYSCLK */
 #define RCC_I2S2CLKSource_PLL3_VCO      ((uint8_t)0x01)  /* I2S2时钟源:PLL3 VCO */

 #define IS_RCC_I2S2CLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S2CLKSource_SYSCLK) || \
                                        ((SOURCE) == RCC_I2S2CLKSource_PLL3_VCO))
/**
  * @}
  */

/** @defgroup I2S3_clock_source 
  * @{
  */
 #define RCC_I2S3CLKSource_SYSCLK        ((uint8_t)0x00)  /* I2S3时钟源:SYSCLK */
 #define RCC_I2S3CLKSource_PLL3_VCO      ((uint8_t)0x01)  /* I2S3时钟源:PLL3 VCO */

 #define IS_RCC_I2S3CLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S3CLKSource_SYSCLK) || \
                                        ((SOURCE) == RCC_I2S3CLKSource_PLL3_VCO))    
/**
  * @}
  */
#endif /* STM32F10X_CL */  
  

/** @defgroup ADC_clock_source 
  * @{
  */

#define RCC_PCLK2_Div2                   ((uint32_t)0x00000000)  /* ADCCLK=PCLK2二分频 */
#define RCC_PCLK2_Div4                   ((uint32_t)0x00004000)  /* ADCCLK=PCLK2四分频 */
#define RCC_PCLK2_Div6                   ((uint32_t)0x00008000)  /* ADCCLK=PCLK2六分频 */
#define RCC_PCLK2_Div8                   ((uint32_t)0x0000C000)  /* ADCCLK=PCLK2八分频 */
#define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_PCLK2_Div2) || ((ADCCLK) == RCC_PCLK2_Div4) || \
                               ((ADCCLK) == RCC_PCLK2_Div6) || ((ADCCLK) == RCC_PCLK2_Div8))
/**
  * @}
  */

/** @defgroup LSE_configuration 
  * @{
  */

#define RCC_LSE_OFF                      ((uint8_t)0x00)  /* 关闭LSE振荡器 */
#define RCC_LSE_ON                       ((uint8_t)0x01)  /* 开启LSE振荡器 */
#define RCC_LSE_Bypass                   ((uint8_t)0x04)  /* LSE旁路,由外部时钟驱动 */
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))
/**
  * @}
  */

/** @defgroup RTC_clock_source 
  * @{
  */

#define RCC_RTCCLKSource_LSE             ((uint32_t)0x00000100)  /* RTC时钟源:LSE */
#define RCC_RTCCLKSource_LSI             ((uint32_t)0x00000200)  /* RTC时钟源:LSI */
#define RCC_RTCCLKSource_HSE_Div128      ((uint32_t)0x00000300)  /* RTC时钟源:HSE/128 */
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div128))
/**
  * @}
  */

/** @defgroup AHB_peripheral 
  * @{
  */

#define RCC_AHBPeriph_DMA1               ((uint32_t)0x00000001)  /* AHB外设:DMA1 */
#define RCC_AHBPeriph_DMA2               ((uint32_t)0x00000002)  /* AHB外设:DMA2 */
#define RCC_AHBPeriph_SRAM               ((uint32_t)0x00000004)  /* AHB外设:SRAM */
#define RCC_AHBPeriph_FLITF              ((uint32_t)0x00000010)  /* AHB外设:FLITF */
#define RCC_AHBPeriph_CRC                ((uint32_t)0x00000040)  /* AHB外设:CRC */

#ifndef STM32F10X_CL
 #define RCC_AHBPeriph_FSMC              ((uint32_t)0x00000100)  /* AHB外设:FSMC */
 #define RCC_AHBPeriph_SDIO              ((uint32_t)0x00000400)  /* AHB外设:SDIO */
 #define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFAA8) == 0x00) && ((PERIPH) != 0x00))
#else
 #define RCC_AHBPeriph_OTG_FS            ((uint32_t)0x00001000)  /* AHB外设:OTG_FS */
 #define RCC_AHBPeriph_ETH_MAC           ((uint32_t)0x00004000)  /* AHB外设:以太网MAC */
 #define RCC_AHBPeriph_ETH_MAC_Tx        ((uint32_t)0x00008000)  /* AHB外设:以太网MAC发送 */
 #define RCC_AHBPeriph_ETH_MAC_Rx        ((uint32_t)0x00010000)  /* AHB外设:以太网MAC接收 */

 #define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFE2FA8) == 0x00) && ((PERIPH) != 0x00))
 #define IS_RCC_AHB_PERIPH_RESET(PERIPH) ((((PERIPH) & 0xFFFFAFFF) == 0x00) && ((PERIPH) != 0x00))
#endif /* STM32F10X_CL */
/**
  * @}
  */

/** @defgroup APB2_peripheral 
  * @{
  */

#define RCC_APB2Periph_AFIO              ((uint32_t)0x00000001)  /* APB2外设:AFIO */
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)  /* APB2外设:GPIOA */
#define RCC_APB2Periph_GPIOB             ((uint32_t)0x00000008)  /* APB2外设:GPIOB */
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)  /* APB2外设:GPIOC */
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)  /* APB2外设:GPIOD */
#define RCC_APB2Periph_GPIOE             ((uint32_t)0x00000040)  /* APB2外设:GPIOE */
#define RCC_APB2Periph_GPIOF             ((uint32_t)0x00000080)  /* APB2外设:GPIOF */
#define RCC_APB2Periph_GPIOG             ((uint32_t)0x00000100)  /* APB2外设:GPIOG */
#define RCC_APB2Periph_ADC1              ((uint32_t)0x00000200)  /* APB2外设:ADC1 */
#define RCC_APB2Periph_ADC2              ((uint32_t)0x00000400)  /* APB2外设:ADC2 */
#define RCC_APB2Periph_TIM1              ((uint32_t)0x00000800)  /* APB2外设:TIM1 */
#define RCC_APB2Periph_SPI1              ((uint32_t)0x00001000)  /* APB2外设:SPI1 */
#define RCC_APB2Periph_TIM8              ((uint32_t)0x00002000)  /* APB2外设:TIM8 */
#define RCC_APB2Periph_USART1            ((uint32_t)0x00004000)  /* APB2外设:USART1 */
#define RCC_APB2Periph_ADC3              ((uint32_t)0x00008000)  /* APB2外设:ADC3 */
#define RCC_APB2Periph_TIM15             ((uint32_t)0x00010000)  /* APB2外设:TIM15 */
#define RCC_APB2Periph_TIM16             ((uint32_t)0x00020000)  /* APB2外设:TIM16 */
#define RCC_APB2Periph_TIM17             ((uint32_t)0x00040000)  /* APB2外设:TIM17 */
#define RCC_APB2Periph_TIM9              ((uint32_t)0x00080000)  /* APB2外设:TIM9 */
#define RCC_APB2Periph_TIM10             ((uint32_t)0x00100000)  /* APB2外设:TIM10 */
#define RCC_APB2Periph_TIM11             ((uint32_t)0x00200000)  /* APB2外设:TIM11 */

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFC00002) == 0x00) && ((PERIPH) != 0x00))
/**
  * @}
  */ 

/** @defgroup APB1_peripheral 
  * @{
  */

#define RCC_APB1Periph_TIM2              ((uint32_t)0x00000001)  /* APB1外设:TIM2 */
#define RCC_APB1Periph_TIM3              ((uint32_t)0x00000002)  /* APB1外设:TIM3 */
#define RCC_APB1Periph_TIM4              ((uint32_t)0x00000004)  /* APB1外设:TIM4 */
#define RCC_APB1Periph_TIM5              ((uint32_t)0x00000008)  /* APB1外设:TIM5 */
#define RCC_APB1Periph_TIM6              ((uint32_t)0x00000010)  /* APB1外设:TIM6 */
#define RCC_APB1Periph_TIM7              ((uint32_t)0x00000020)  /* APB1外设:TIM7 */
#define RCC_APB1Periph_TIM12             ((uint32_t)0x00000040)  /* APB1外设:TIM12 */
#define RCC_APB1Periph_TIM13             ((uint32_t)0x00000080)  /* APB1外设:TIM13 */
#define RCC_APB1Periph_TIM14             ((uint32_t)0x00000100)  /* APB1外设:TIM14 */
#define RCC_APB1Periph_WWDG              ((uint32_t)0x00000800)  /* APB1外设:WWDG */
#define RCC_APB1Periph_SPI2              ((uint32_t)0x00004000)  /* APB1外设:SPI2 */
#define RCC_APB1Periph_SPI3              ((uint32_t)0x00008000)  /* APB1外设:SPI3 */
#define RCC_APB1Periph_USART2            ((uint32_t)0x00020000)  /* APB1外设:USART2 */
#define RCC_APB1Periph_USART3            ((uint32_t)0x00040000)  /* APB1外设:USART3 */
#define RCC_APB1Periph_UART4             ((uint32_t)0x00080000)  /* APB1外设:UART4 */
#define RCC_APB1Periph_UART5             ((uint32_t)0x00100000)  /* APB1外设:UART5 */
#define RCC_APB1Periph_I2C1              ((uint32_t)0x00200000)  /* APB1外设:I2C1 */
#define RCC_APB1Periph_I2C2              ((uint32_t)0x00400000)  /* APB1外设:I2C2 */
#define RCC_APB1Periph_USB               ((uint32_t)0x00800000)  /* APB1外设:USB */
#define RCC_APB1Periph_CAN1              ((uint32_t)0x02000000)  /* APB1外设:CAN1 */
#define RCC_APB1Periph_CAN2              ((uint32_t)0x04000000)  /* APB1外设:CAN2 */
#define RCC_APB1Periph_BKP               ((uint32_t)0x08000000)  /* APB1外设:BKP */
#define RCC_APB1Periph_PWR               ((uint32_t)0x10000000)  /* APB1外设:PWR */
#define RCC_APB1Periph_DAC               ((uint32_t)0x20000000)  /* APB1外设:DAC */
#define RCC_APB1Periph_CEC               ((uint32_t)0x40000000)  /* APB1外设:CEC */
 
#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x81013600) == 0x00) && ((PERIPH) != 0x00))

/**
  * @}
  */

/** @defgroup Clock_source_to_output_on_MCO_pin 
  * @{
  */

#define RCC_MCO_NoClock                  ((uint8_t)0x00)  /* MCO引脚:无时钟输出 */
#define RCC_MCO_SYSCLK                   ((uint8_t)0x04)  /* MCO引脚:输出SYSCLK */
#define RCC_MCO_HSI                      ((uint8_t)0x05)  /* MCO引脚:输出HSI */
#define RCC_MCO_HSE                      ((uint8_t)0x06)  /* MCO引脚:输出HSE */
#define RCC_MCO_PLLCLK_Div2              ((uint8_t)0x07)  /* MCO引脚:输出PLL/2 */

#ifndef STM32F10X_CL
 #define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI) || \
                          ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) || \
                          ((MCO) == RCC_MCO_PLLCLK_Div2))
#else
 #define RCC_MCO_PLL2CLK                 ((uint8_t)0x08)  /* MCO引脚:输出PLL2 */
 #define RCC_MCO_PLL3CLK_Div2            ((uint8_t)0x09)  /* MCO引脚:输出PLL3/2 */
 #define RCC_MCO_XT1                     ((uint8_t)0x0A)  /* MCO引脚:输出XT1 */
 #define RCC_MCO_PLL3CLK                 ((uint8_t)0x0B)  /* MCO引脚:输出PLL3 */

 #define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI) || \
                          ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) || \
                          ((MCO) == RCC_MCO_PLLCLK_Div2) || ((MCO) == RCC_MCO_PLL2CLK) || \
                          ((MCO) == RCC_MCO_PLL3CLK_Div2) || ((MCO) == RCC_MCO_XT1) || \
                          ((MCO) == RCC_MCO_PLL3CLK))
#endif /* STM32F10X_CL */ 

/**
  * @}
  */

/** @defgroup RCC_Flag 
  * @{
  */

#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)  /* HSI就绪标志 */
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)  /* HSE就绪标志 */
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)  /* PLL就绪标志 */
#define RCC_FLAG_LSERDY                  ((uint8_t)0x41)  /* LSE就绪标志 */
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x61)  /* LSI就绪标志 */
#define RCC_FLAG_PINRST                  ((uint8_t)0x7A)  /* NRST引脚复位标志 */
#define RCC_FLAG_PORRST                  ((uint8_t)0x7B)  /* 上电/掉电复位标志 */
#define RCC_FLAG_SFTRST                  ((uint8_t)0x7C)  /* 软件复位标志 */
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)  /* 独立看门狗复位标志 */
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)  /* 窗口看门狗复位标志 */
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x7F)  /* 低功耗复位标志 */

#ifndef STM32F10X_CL
 #define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                            ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                            ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) || \
                            ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) || \
                            ((FLAG) == RCC_FLAG_IWDGRST)|| ((FLAG) == RCC_FLAG_WWDGRST)|| \
                            ((FLAG) == RCC_FLAG_LPWRRST))
#else
 #define RCC_FLAG_PLL2RDY                ((uint8_t)0x3B)   /* PLL2就绪标志 */
 #define RCC_FLAG_PLL3RDY                ((uint8_t)0x3D)   /* PLL3就绪标志 */
 #define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                            ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                            ((FLAG) == RCC_FLAG_PLL2RDY) || ((FLAG) == RCC_FLAG_PLL3RDY) || \
                            ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) || \
                            ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) || \
                            ((FLAG) == RCC_FLAG_IWDGRST)|| ((FLAG) == RCC_FLAG_WWDGRST)|| \
                            ((FLAG) == RCC_FLAG_LPWRRST))
#endif /* STM32F10X_CL */ 

#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions
  * @{
  */

void RCC_DeInit(void);  /* 将RCC寄存器复位为默认值 */
void RCC_HSEConfig(uint32_t RCC_HSE);  /* 配置HSE振荡器 */
ErrorStatus RCC_WaitForHSEStartUp(void);  /* 等待HSE启动稳定 */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);  /* 调整HSI校准值 */
void RCC_HSICmd(FunctionalState NewState);  /* 使能或关闭HSI */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);  /* 配置PLL时钟源和倍频系数 */
void RCC_PLLCmd(FunctionalState NewState);  /* 使能或关闭PLL */

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL)
 void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Source, uint32_t RCC_PREDIV1_Div);  /* 配置PREDIV1分频 */
#endif

#ifdef  STM32F10X_CL
 void RCC_PREDIV2Config(uint32_t RCC_PREDIV2_Div);  /* 配置PREDIV2分频 */
 void RCC_PLL2Config(uint32_t RCC_PLL2Mul);  /* 配置PLL2倍频系数 */
 void RCC_PLL2Cmd(FunctionalState NewState);  /* 使能或关闭PLL2 */
 void RCC_PLL3Config(uint32_t RCC_PLL3Mul);  /* 配置PLL3倍频系数 */
 void RCC_PLL3Cmd(FunctionalState NewState);  /* 使能或关闭PLL3 */
#endif /* STM32F10X_CL */ 

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);  /* 配置系统时钟源 */
uint8_t RCC_GetSYSCLKSource(void);  /* 获取当前系统时钟源 */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);  /* 配置AHB(HCLK)分频 */
void RCC_PCLK1Config(uint32_t RCC_HCLK);  /* 配置APB1(PCLK1)分频 */
void RCC_PCLK2Config(uint32_t RCC_HCLK);  /* 配置APB2(PCLK2)分频 */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);  /* 使能或关闭RCC中断 */

#ifndef STM32F10X_CL
 void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);  /* 配置USB时钟 */
#else
 void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLKSource);  /* 配置OTG_FS时钟 */
#endif /* STM32F10X_CL */ 

void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);  /* 配置ADC时钟分频器 */

#ifdef STM32F10X_CL
 void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLKSource);                                    /* 配置I2S2时钟 */
 void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLKSource);  /* 配置I2S3时钟 */
#endif /* STM32F10X_CL */ 

void RCC_LSEConfig(uint8_t RCC_LSE);  /* 配置LSE振荡器 */
void RCC_LSICmd(FunctionalState NewState);  /* 使能或关闭LSI */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);  /* 配置RTC时钟源 */
void RCC_RTCCLKCmd(FunctionalState NewState);  /* 使能或关闭RTC时钟 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);  /* 获取各总线时钟频率 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);  /* 使能或关闭AHB外设时钟 */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);  /* 使能或关闭APB2外设时钟 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);  /* 使能或关闭APB1外设时钟 */

#ifdef STM32F10X_CL
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);  /* 复位AHB外设 */
#endif /* STM32F10X_CL */ 

void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);  /* 复位APB2外设 */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);  /* 复位APB1外设 */
void RCC_BackupResetCmd(FunctionalState NewState);  /* 复位备份域 */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);  /* 使能或关闭时钟安全系统 */
void RCC_MCOConfig(uint8_t RCC_MCO);  /* 配置MCO引脚时钟输出 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);  /* 获取RCC标志状态 */
void RCC_ClearFlag(void);  /* 清除RCC复位标志 */
ITStatus RCC_GetITStatus(uint8_t RCC_IT);  /* 获取RCC中断状态 */
void RCC_ClearITPendingBit(uint8_t RCC_IT);  /* 清除RCC中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_RCC_H */
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
