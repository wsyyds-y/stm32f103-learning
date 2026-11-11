/**
  ******************************************************************************
  * @file    stm32f10x_gpio.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the GPIO 
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
#ifndef __STM32F10x_GPIO_H
#define __STM32F10x_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types
  * @{
  */

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG))
                                     
/** 
  * @brief  Output Maximum frequency selection  
  */

typedef enum
{ 
  GPIO_Speed_10MHz = 1,       /* 最高输出频率10MHz */
  GPIO_Speed_2MHz,            /* 最高输出频率2MHz */
  GPIO_Speed_50MHz            /* 最高输出频率50MHz */
}GPIOSpeed_TypeDef;
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz) || \
                              ((SPEED) == GPIO_Speed_50MHz))

/** 
  * @brief  Configuration Mode enumeration  
  */

typedef enum
{ GPIO_Mode_AIN = 0x0,                /* 模拟输入：关闭施密特触发器，引脚直接接ADC/DAC，无数字电平 */
  GPIO_Mode_IN_FLOATING = 0x04,       /* 浮空输入：无上下拉，电平完全由外部决定，悬空时电平不确定 */
  GPIO_Mode_IPD = 0x28,               /* 下拉输入：内部下拉，默认为低电平，外部拉高时才变高 */
  GPIO_Mode_IPU = 0x48,               /* 上拉输入：内部上拉，默认为高电平，外部拉低时才变低 */
  GPIO_Mode_Out_OD = 0x14,            /* 开漏输出：只能输出低电平或高阻态，输出高电平需外接上拉电阻 */
  GPIO_Mode_Out_PP = 0x10,            /* 推挽输出：可强输出高电平(VDD)和低电平(0V)，驱动能力强 */
  GPIO_Mode_AF_OD = 0x1C,             /* 复用开漏输出：由外设控制输出，如I2C的SCL/SDA */
  GPIO_Mode_AF_PP = 0x18              /* 复用推挽输出：由外设控制输出，如USART_TX/SPI/PWM */
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || \
                            ((MODE) == GPIO_Mode_IPD) || ((MODE) == GPIO_Mode_IPU) || \
                            ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP) || \
                            ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))

/** 
  * @brief  GPIO Init structure definition  
  */

typedef struct
{
  uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */
  /* 待配置的GPIO引脚 */

  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */
  /* 所选引脚的输出速度 */

  GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
  /* 所选引脚的工作模式 */
}GPIO_InitTypeDef;


/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */

typedef enum
{ Bit_RESET = 0,          /* 复位（输出低电平） */
  Bit_SET                 /* 置位（输出高电平） */
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define 
  * @{
  */

#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */  /* 引脚0 */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */  /* 引脚1 */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */  /* 引脚2 */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */  /* 引脚3 */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */  /* 引脚4 */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */  /* 引脚5 */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */  /* 引脚6 */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */  /* 引脚7 */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */  /* 引脚8 */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */  /* 引脚9 */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */  /* 引脚10 */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */  /* 引脚11 */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */  /* 引脚12 */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */  /* 引脚13 */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */  /* 引脚14 */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */  /* 引脚15 */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */  /* 全部引脚 */

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
  * @}
  */

/** @defgroup GPIO_Remap_define 
  * @{
  */

#define GPIO_Remap_SPI1             ((uint32_t)0x00000001)  /*!< SPI1 Alternate Function mapping */  /* SPI1复用功能映射 */
#define GPIO_Remap_I2C1             ((uint32_t)0x00000002)  /*!< I2C1 Alternate Function mapping */  /* I2C1复用功能映射 */
#define GPIO_Remap_USART1           ((uint32_t)0x00000004)  /*!< USART1 Alternate Function mapping */  /* USART1复用功能映射 */
#define GPIO_Remap_USART2           ((uint32_t)0x00000008)  /*!< USART2 Alternate Function mapping */  /* USART2复用功能映射 */
#define GPIO_PartialRemap_USART3    ((uint32_t)0x00140010)  /*!< USART3 Partial Alternate Function mapping */  /* USART3部分重映射 */
#define GPIO_FullRemap_USART3       ((uint32_t)0x00140030)  /*!< USART3 Full Alternate Function mapping */  /* USART3完全重映射 */
#define GPIO_PartialRemap_TIM1      ((uint32_t)0x00160040)  /*!< TIM1 Partial Alternate Function mapping */  /* TIM1部分重映射 */
#define GPIO_FullRemap_TIM1         ((uint32_t)0x001600C0)  /*!< TIM1 Full Alternate Function mapping */  /* TIM1完全重映射 */
#define GPIO_PartialRemap1_TIM2     ((uint32_t)0x00180100)  /*!< TIM2 Partial1 Alternate Function mapping */  /* TIM2部分重映射1 */
#define GPIO_PartialRemap2_TIM2     ((uint32_t)0x00180200)  /*!< TIM2 Partial2 Alternate Function mapping */  /* TIM2部分重映射2 */
#define GPIO_FullRemap_TIM2         ((uint32_t)0x00180300)  /*!< TIM2 Full Alternate Function mapping */  /* TIM2完全重映射 */
#define GPIO_PartialRemap_TIM3      ((uint32_t)0x001A0800)  /*!< TIM3 Partial Alternate Function mapping */  /* TIM3部分重映射 */
#define GPIO_FullRemap_TIM3         ((uint32_t)0x001A0C00)  /*!< TIM3 Full Alternate Function mapping */  /* TIM3完全重映射 */
#define GPIO_Remap_TIM4             ((uint32_t)0x00001000)  /*!< TIM4 Alternate Function mapping */  /* TIM4复用功能映射 */
#define GPIO_Remap1_CAN1            ((uint32_t)0x001D4000)  /*!< CAN1 Alternate Function mapping */  /* CAN1复用功能映射1 */
#define GPIO_Remap2_CAN1            ((uint32_t)0x001D6000)  /*!< CAN1 Alternate Function mapping */  /* CAN1复用功能映射2 */
#define GPIO_Remap_PD01             ((uint32_t)0x00008000)  /*!< PD01 Alternate Function mapping */  /* PD01复用功能映射 */
#define GPIO_Remap_TIM5CH4_LSI      ((uint32_t)0x00200001)  /*!< LSI connected to TIM5 Channel4 input capture for calibration */  /* LSI接至TIM5通道4用于校准 */
#define GPIO_Remap_ADC1_ETRGINJ     ((uint32_t)0x00200002)  /*!< ADC1 External Trigger Injected Conversion remapping */  /* ADC1外部触发注入转换重映射 */
#define GPIO_Remap_ADC1_ETRGREG     ((uint32_t)0x00200004)  /*!< ADC1 External Trigger Regular Conversion remapping */  /* ADC1外部触发规则转换重映射 */
#define GPIO_Remap_ADC2_ETRGINJ     ((uint32_t)0x00200008)  /*!< ADC2 External Trigger Injected Conversion remapping */  /* ADC2外部触发注入转换重映射 */
#define GPIO_Remap_ADC2_ETRGREG     ((uint32_t)0x00200010)  /*!< ADC2 External Trigger Regular Conversion remapping */  /* ADC2外部触发规则转换重映射 */
#define GPIO_Remap_ETH              ((uint32_t)0x00200020)  /*!< Ethernet remapping (only for Connectivity line devices) */  /* 以太网重映射 */
#define GPIO_Remap_CAN2             ((uint32_t)0x00200040)  /*!< CAN2 remapping (only for Connectivity line devices) */  /* CAN2重映射 */
#define GPIO_Remap_SWJ_NoJTRST      ((uint32_t)0x00300100)  /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */  /* 全SWJ使能但不含JTRST */
#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */  /* 禁用JTAG-DP并使能SW-DP */
#define GPIO_Remap_SWJ_Disable      ((uint32_t)0x00300400)  /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */  /* 完全禁用SWJ */
#define GPIO_Remap_SPI3             ((uint32_t)0x00201100)  /*!< SPI3/I2S3 Alternate Function mapping (only for Connectivity line devices) */  /* SPI3/I2S3复用功能映射 */
#define GPIO_Remap_TIM2ITR1_PTP_SOF ((uint32_t)0x00202000)  /*!< Ethernet PTP output or USB OTG SOF (Start of Frame) connected
                                                                 to TIM2 Internal Trigger 1 for calibration
                                                                 (only for Connectivity line devices) */  /* 以太网PTP输出或USB OTG SOF接至TIM2触发1 */
#define GPIO_Remap_PTP_PPS          ((uint32_t)0x00204000)  /*!< Ethernet MAC PPS_PTS output on PB05 (only for Connectivity line devices) */  /* 以太网MAC PPS_PTS输出 */

#define GPIO_Remap_TIM15            ((uint32_t)0x80000001)  /*!< TIM15 Alternate Function mapping (only for Value line devices) */  /* TIM15复用功能映射 */
#define GPIO_Remap_TIM16            ((uint32_t)0x80000002)  /*!< TIM16 Alternate Function mapping (only for Value line devices) */  /* TIM16复用功能映射 */
#define GPIO_Remap_TIM17            ((uint32_t)0x80000004)  /*!< TIM17 Alternate Function mapping (only for Value line devices) */  /* TIM17复用功能映射 */
#define GPIO_Remap_CEC              ((uint32_t)0x80000008)  /*!< CEC Alternate Function mapping (only for Value line devices) */  /* CEC复用功能映射 */
#define GPIO_Remap_TIM1_DMA         ((uint32_t)0x80000010)  /*!< TIM1 DMA requests mapping (only for Value line devices) */  /* TIM1的DMA请求映射 */

#define GPIO_Remap_TIM9             ((uint32_t)0x80000020)  /*!< TIM9 Alternate Function mapping (only for XL-density devices) */  /* TIM9复用功能映射 */
#define GPIO_Remap_TIM10            ((uint32_t)0x80000040)  /*!< TIM10 Alternate Function mapping (only for XL-density devices) */  /* TIM10复用功能映射 */
#define GPIO_Remap_TIM11            ((uint32_t)0x80000080)  /*!< TIM11 Alternate Function mapping (only for XL-density devices) */  /* TIM11复用功能映射 */
#define GPIO_Remap_TIM13            ((uint32_t)0x80000100)  /*!< TIM13 Alternate Function mapping (only for High density Value line and XL-density devices) */  /* TIM13复用功能映射 */
#define GPIO_Remap_TIM14            ((uint32_t)0x80000200)  /*!< TIM14 Alternate Function mapping (only for High density Value line and XL-density devices) */  /* TIM14复用功能映射 */
#define GPIO_Remap_FSMC_NADV        ((uint32_t)0x80000400)  /*!< FSMC_NADV Alternate Function mapping (only for High density Value line and XL-density devices) */  /* FSMC_NADV复用功能映射 */

#define GPIO_Remap_TIM67_DAC_DMA    ((uint32_t)0x80000800)  /*!< TIM6/TIM7 and DAC DMA requests remapping (only for High density Value line devices) */  /* TIM6/TIM7与DAC的DMA请求重映射 */
#define GPIO_Remap_TIM12            ((uint32_t)0x80001000)  /*!< TIM12 Alternate Function mapping (only for High density Value line devices) */  /* TIM12复用功能映射 */
#define GPIO_Remap_MISC             ((uint32_t)0x80002000)  /*!< Miscellaneous Remap (DMA2 Channel5 Position and DAC Trigger remapping, 
                                                                 only for High density Value line devices) */  /* 杂项重映射 */                                                       

#define IS_GPIO_REMAP(REMAP) (((REMAP) == GPIO_Remap_SPI1) || ((REMAP) == GPIO_Remap_I2C1) || \
                              ((REMAP) == GPIO_Remap_USART1) || ((REMAP) == GPIO_Remap_USART2) || \
                              ((REMAP) == GPIO_PartialRemap_USART3) || ((REMAP) == GPIO_FullRemap_USART3) || \
                              ((REMAP) == GPIO_PartialRemap_TIM1) || ((REMAP) == GPIO_FullRemap_TIM1) || \
                              ((REMAP) == GPIO_PartialRemap1_TIM2) || ((REMAP) == GPIO_PartialRemap2_TIM2) || \
                              ((REMAP) == GPIO_FullRemap_TIM2) || ((REMAP) == GPIO_PartialRemap_TIM3) || \
                              ((REMAP) == GPIO_FullRemap_TIM3) || ((REMAP) == GPIO_Remap_TIM4) || \
                              ((REMAP) == GPIO_Remap1_CAN1) || ((REMAP) == GPIO_Remap2_CAN1) || \
                              ((REMAP) == GPIO_Remap_PD01) || ((REMAP) == GPIO_Remap_TIM5CH4_LSI) || \
                              ((REMAP) == GPIO_Remap_ADC1_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC1_ETRGREG) || \
                              ((REMAP) == GPIO_Remap_ADC2_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC2_ETRGREG) || \
                              ((REMAP) == GPIO_Remap_ETH) ||((REMAP) == GPIO_Remap_CAN2) || \
                              ((REMAP) == GPIO_Remap_SWJ_NoJTRST) || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable) || \
                              ((REMAP) == GPIO_Remap_SWJ_Disable)|| ((REMAP) == GPIO_Remap_SPI3) || \
                              ((REMAP) == GPIO_Remap_TIM2ITR1_PTP_SOF) || ((REMAP) == GPIO_Remap_PTP_PPS) || \
                              ((REMAP) == GPIO_Remap_TIM15) || ((REMAP) == GPIO_Remap_TIM16) || \
                              ((REMAP) == GPIO_Remap_TIM17) || ((REMAP) == GPIO_Remap_CEC) || \
                              ((REMAP) == GPIO_Remap_TIM1_DMA) || ((REMAP) == GPIO_Remap_TIM9) || \
                              ((REMAP) == GPIO_Remap_TIM10) || ((REMAP) == GPIO_Remap_TIM11) || \
                              ((REMAP) == GPIO_Remap_TIM13) || ((REMAP) == GPIO_Remap_TIM14) || \
                              ((REMAP) == GPIO_Remap_FSMC_NADV) || ((REMAP) == GPIO_Remap_TIM67_DAC_DMA) || \
                              ((REMAP) == GPIO_Remap_TIM12) || ((REMAP) == GPIO_Remap_MISC))
                              
/**
  * @}
  */ 

/** @defgroup GPIO_Port_Sources 
  * @{
  */

#define GPIO_PortSourceGPIOA       ((uint8_t)0x00)  /* GPIOA端口源 */
#define GPIO_PortSourceGPIOB       ((uint8_t)0x01)  /* GPIOB端口源 */
#define GPIO_PortSourceGPIOC       ((uint8_t)0x02)  /* GPIOC端口源 */
#define GPIO_PortSourceGPIOD       ((uint8_t)0x03)  /* GPIOD端口源 */
#define GPIO_PortSourceGPIOE       ((uint8_t)0x04)  /* GPIOE端口源 */
#define GPIO_PortSourceGPIOF       ((uint8_t)0x05)  /* GPIOF端口源 */
#define GPIO_PortSourceGPIOG       ((uint8_t)0x06)  /* GPIOG端口源 */
#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOE))

#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOE) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOF) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOG))

/**
  * @}
  */

/** @defgroup GPIO_Pin_sources 
  * @{
  */

#define GPIO_PinSource0            ((uint8_t)0x00)  /* 引脚源0 */
#define GPIO_PinSource1            ((uint8_t)0x01)  /* 引脚源1 */
#define GPIO_PinSource2            ((uint8_t)0x02)  /* 引脚源2 */
#define GPIO_PinSource3            ((uint8_t)0x03)  /* 引脚源3 */
#define GPIO_PinSource4            ((uint8_t)0x04)  /* 引脚源4 */
#define GPIO_PinSource5            ((uint8_t)0x05)  /* 引脚源5 */
#define GPIO_PinSource6            ((uint8_t)0x06)  /* 引脚源6 */
#define GPIO_PinSource7            ((uint8_t)0x07)  /* 引脚源7 */
#define GPIO_PinSource8            ((uint8_t)0x08)  /* 引脚源8 */
#define GPIO_PinSource9            ((uint8_t)0x09)  /* 引脚源9 */
#define GPIO_PinSource10           ((uint8_t)0x0A)  /* 引脚源10 */
#define GPIO_PinSource11           ((uint8_t)0x0B)  /* 引脚源11 */
#define GPIO_PinSource12           ((uint8_t)0x0C)  /* 引脚源12 */
#define GPIO_PinSource13           ((uint8_t)0x0D)  /* 引脚源13 */
#define GPIO_PinSource14           ((uint8_t)0x0E)  /* 引脚源14 */
#define GPIO_PinSource15           ((uint8_t)0x0F)  /* 引脚源15 */

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))

/**
  * @}
  */

/** @defgroup Ethernet_Media_Interface 
  * @{
  */ 
#define GPIO_ETH_MediaInterface_MII    ((u32)0x00000000)  /* MII媒体接口 */ 
#define GPIO_ETH_MediaInterface_RMII   ((u32)0x00000001)  /* RMII媒体接口 */                                       

#define IS_GPIO_ETH_MEDIA_INTERFACE(INTERFACE) (((INTERFACE) == GPIO_ETH_MediaInterface_MII) || \
                                                ((INTERFACE) == GPIO_ETH_MediaInterface_RMII))

/**
  * @}
  */                                                
/**
  * @}
  */

/** @defgroup GPIO_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions
  * @{
  */

void GPIO_DeInit(GPIO_TypeDef* GPIOx);  /* 将GPIOx端口寄存器复位为默认值 */
void GPIO_AFIODeInit(void);  /* 将AFIO复用功能寄存器复位为默认值 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);  /* 根据结构体参数初始化指定GPIO端口 */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);  /* 将GPIO初始化结构体成员设为默认值 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  /* 读取指定输入引脚的电平 */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);  /* 读取GPIO端口输入数据 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  /* 读取指定输出引脚的电平 */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);  /* 读取GPIO端口输出数据 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  /* 将指定引脚置为高电平 */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  /* 将指定引脚置为低电平 */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);  /* 设置或清除指定引脚 */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);  /* 向GPIO端口写入数据 */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  /* 锁定GPIO引脚配置寄存器 */
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);  /* 选择用作事件输出的GPIO引脚 */
void GPIO_EventOutputCmd(FunctionalState NewState);  /* 使能或关闭事件输出 */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);  /* 改变指定引脚的复用重映射 */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);  /* 选择用作EXTI线的GPIO引脚 */
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);  /* 选择以太网媒体接口 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_GPIO_H */
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
