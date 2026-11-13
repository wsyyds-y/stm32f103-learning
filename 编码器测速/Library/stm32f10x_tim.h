/**
  ******************************************************************************
  * @file    stm32f10x_tim.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the TIM firmware 
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
#ifndef __STM32F10x_TIM_H
#define __STM32F10x_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 

/** @defgroup TIM_Exported_Types
  * @{
  */ 

/** 
  * @brief  TIM Time Base Init structure definition
  * @note   This structure is used with all TIMx except for TIM6 and TIM7.    
  */

typedef struct
{
  uint16_t TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between 0x0000 and 0xFFFF */
  /* 待载入比较寄存器(CCR)的脉冲值 */
  /* 预分频器值，0x0000~0xFFFF */

  uint16_t TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */
  /* 计数模式，向上/向下/中央对齐 */

  uint16_t TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */
  /* 自动重装载值(ARR)，0x0000~0xFFFF */ 

  uint16_t TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */
  /* 时钟分频系数(CKD) */

  uint8_t TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TIM1 and TIM8. */
  /* 重复计数器，仅TIM1/TIM8有效 */
} TIM_TimeBaseInitTypeDef;       

/** 
  * @brief  TIM Output Compare Init structure definition  
  */

typedef struct
{
  uint16_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */
  /* 输出比较模式 */

  uint16_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */
  /* 输出比较使能状态 */

  uint16_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1 and TIM8. */
  /* 互补输出比较使能状态，仅TIM1/TIM8 */

  uint16_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */
  /* 输出极性 */

  uint16_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */
  /* 互补输出极性，仅TIM1/TIM8 */

  uint16_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
  /* 空闲态时OCx输出电平，仅TIM1/TIM8 */

  uint16_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
  /* 空闲态时OCxN输出电平，仅TIM1/TIM8 */
} TIM_OCInitTypeDef;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */

typedef struct
{

  uint16_t TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */
  /* 输入捕获通道(TIM_Channel_x) */

  uint16_t TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */
  /* 输入触发极性（上升/下降/双边沿） */

  uint16_t TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */
  /* 输入捕获映射关系（直接/间接/TRC） */

  uint16_t TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */
  /* 输入捕获预分频 */

  uint16_t TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
  /* 输入捕获滤波长度，0x0~0xF */
} TIM_ICInitTypeDef;

/** 
  * @brief  BDTR structure definition 
  * @note   This structure is used only with TIM1 and TIM8.    
  */

typedef struct
{

  uint16_t TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state */
  /* 运行模式下关闭状态选择 */

  uint16_t TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state */
  /* 空闲模式下关闭状态选择 */

  uint16_t TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref Lock_level */
  /* 锁定等级 */ 

  uint16_t TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */
  /* 死区时间，0x00~0xFF */

  uint16_t TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not. 
                                      This parameter can be a value of @ref Break_Input_enable_disable */
  /* 刹车输入使能 */

  uint16_t TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref Break_Polarity */
  /* 刹车输入极性 */

  uint16_t TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
  /* 自动输出使能 */
} TIM_BDTRInitTypeDef;

/** @defgroup TIM_Exported_constants 
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2) || \
                                   ((PERIPH) == TIM3) || \
                                   ((PERIPH) == TIM4) || \
                                   ((PERIPH) == TIM5) || \
                                   ((PERIPH) == TIM6) || \
                                   ((PERIPH) == TIM7) || \
                                   ((PERIPH) == TIM8) || \
                                   ((PERIPH) == TIM9) || \
                                   ((PERIPH) == TIM10)|| \
                                   ((PERIPH) == TIM11)|| \
                                   ((PERIPH) == TIM12)|| \
                                   ((PERIPH) == TIM13)|| \
                                   ((PERIPH) == TIM14)|| \
                                   ((PERIPH) == TIM15)|| \
                                   ((PERIPH) == TIM16)|| \
                                   ((PERIPH) == TIM17))  /* 校验定时器外设参数 */

/* LIST1: TIM 1 and 8 */
#define IS_TIM_LIST1_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM8))  /* 校验外设是否属于TIM1/TIM8 */

/* LIST2: TIM 1, 8, 15 16 and 17 */
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                   ((PERIPH) == TIM17))  /* 校验外设是否属于TIM1/8/15/16/17 */

/* LIST3: TIM 1, 2, 3, 4, 5 and 8 */
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8))  /* 校验外设是否属于TIM1-5/TIM8 */ 
									                                 
/* LIST4: TIM 1, 2, 3, 4, 5, 8, 15, 16 and 17 */
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17))  /* 校验外设是否属于TIM1-5/8/15/16/17 */

/* LIST5: TIM 1, 2, 3, 4, 5, 8 and 15 */                                            
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15))  /* 校验外设是否属于TIM1-5/8/15 */ 

/* LIST6: TIM 1, 2, 3, 4, 5, 8, 9, 12 and 15 */
#define IS_TIM_LIST6_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM9) || \
									  ((PERIPH) == TIM12)|| \
                                      ((PERIPH) == TIM15))  /* 校验外设是否属于TIM1-5/8/9/12/15 */

/* LIST7: TIM 1, 2, 3, 4, 5, 6, 7, 8, 9, 12 and 15 */
#define IS_TIM_LIST7_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM6) || \
                                      ((PERIPH) == TIM7) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM9) || \
                                      ((PERIPH) == TIM12)|| \
                                      ((PERIPH) == TIM15))  /* 校验外设是否属于TIM1-9/12/15 */                                    

/* LIST8: TIM 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15, 16 and 17 */                                        
#define IS_TIM_LIST8_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM9) || \
                                      ((PERIPH) == TIM10)|| \
                                      ((PERIPH) == TIM11)|| \
                                      ((PERIPH) == TIM12)|| \
                                      ((PERIPH) == TIM13)|| \
                                      ((PERIPH) == TIM14)|| \
                                      ((PERIPH) == TIM15)|| \
                                      ((PERIPH) == TIM16)|| \
                                      ((PERIPH) == TIM17))  /* 校验外设是否属于除TIM6/7外的定时器 */

/* LIST9: TIM 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, and 17 */
#define IS_TIM_LIST9_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM6) || \
                                      ((PERIPH) == TIM7) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM15)|| \
                                      ((PERIPH) == TIM16)|| \
                                      ((PERIPH) == TIM17))  /* 校验外设是否属于TIM1-8/15/16/17 */  
                                                                                                                                                                                                                          
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_and_PWM_modes 
  * @{
  */

#define TIM_OCMode_Timing                  ((uint16_t)0x0000)  /* 输出比较：冻结（无动作） */
#define TIM_OCMode_Active                  ((uint16_t)0x0010)  /* 输出比较：匹配时置有效 */
#define TIM_OCMode_Inactive                ((uint16_t)0x0020)  /* 输出比较：匹配时置无效 */
#define TIM_OCMode_Toggle                  ((uint16_t)0x0030)  /* 输出比较：匹配时翻转 */
#define TIM_OCMode_PWM1                    ((uint16_t)0x0060)  /* PWM模式1 */
#define TIM_OCMode_PWM2                    ((uint16_t)0x0070)  /* PWM模式2 */
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))  /* 校验输出比较模式 */
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||	\
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))  /* 校验OC模式（含强制动作） */
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode 
  * @{
  */

#define TIM_OPMode_Single                  ((uint16_t)0x0008)  /* 单脉冲模式 */
#define TIM_OPMode_Repetitive              ((uint16_t)0x0000)  /* 重复模式 */
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))  /* 校验单脉冲模式 */
/**
  * @}
  */ 

/** @defgroup TIM_Channel 
  * @{
  */

#define TIM_Channel_1                      ((uint16_t)0x0000)  /* 通道1 */
#define TIM_Channel_2                      ((uint16_t)0x0004)  /* 通道2 */
#define TIM_Channel_3                      ((uint16_t)0x0008)  /* 通道3 */
#define TIM_Channel_4                      ((uint16_t)0x000C)  /* 通道4 */
#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))  /* 校验定时器通道 */
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))  /* 校验PWM输入捕获通道 */
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))  /* 校验互补输出通道 */
/**
  * @}
  */ 

/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */
 /* 时钟分频1 */
#define TIM_CKD_DIV1                       ((uint16_t)0x0000)  /* 时钟分频1 */
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)  /* 时钟分频2 */
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)  /* 时钟分频4 */
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))  /* 校验时钟分频 */
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode 
  * @{
  */
        /* 向上计数模式 */
#define TIM_CounterMode_Up                 ((uint16_t)0x0000)  
#define TIM_CounterMode_Down               ((uint16_t)0x0010)  /* 向下计数模式 */
#define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)  /* 中央对齐模式1 */
#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)  /* 中央对齐模式2 */
#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)  /* 中央对齐模式3 */
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))  /* 校验计数模式 */
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Polarity 
  * @{
  */

#define TIM_OCPolarity_High                ((uint16_t)0x0000)  /* 输出极性高（有效电平为高） */
#define TIM_OCPolarity_Low                 ((uint16_t)0x0002)  /* 输出极性低 */
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))  /* 校验输出极性 */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity 
  * @{
  */
  
#define TIM_OCNPolarity_High               ((uint16_t)0x0000)  /* 互补输出极性高 */
#define TIM_OCNPolarity_Low                ((uint16_t)0x0008)  /* 互补输出极性低 */
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))  /* 校验互补输出极性 */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_state 
  * @{
  */

#define TIM_OutputState_Disable            ((uint16_t)0x0000)  /* 关闭输出比较 */
#define TIM_OutputState_Enable             ((uint16_t)0x0001)  /* 使能输出比较 */
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))  /* 校验输出比较状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_state 
  * @{
  */

#define TIM_OutputNState_Disable           ((uint16_t)0x0000)  /* 关闭互补输出 */
#define TIM_OutputNState_Enable            ((uint16_t)0x0004)  /* 使能互补输出 */
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))  /* 校验互补输出状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_state 
  * @{
  */

#define TIM_CCx_Enable                      ((uint16_t)0x0001)  /* 使能捕获/比较输出 */
#define TIM_CCx_Disable                     ((uint16_t)0x0000)  /* 关闭捕获/比较输出 */
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))  /* 校验捕获/比较使能 */
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_N_state 
  * @{
  */

#define TIM_CCxN_Enable                     ((uint16_t)0x0004)  /* 使能互补捕获/比较输出 */
#define TIM_CCxN_Disable                    ((uint16_t)0x0000)  /* 关闭互补捕获/比较输出 */
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))  /* 校验互补捕获/比较使能 */
/**
  * @}
  */ 

/** @defgroup Break_Input_enable_disable 
  * @{
  */

#define TIM_Break_Enable                   ((uint16_t)0x1000)  /* 使能刹车输入 */
#define TIM_Break_Disable                  ((uint16_t)0x0000)  /* 关闭刹车输入 */
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))  /* 校验刹车输入状态 */
/**
  * @}
  */ 

/** @defgroup Break_Polarity 
  * @{
  */

#define TIM_BreakPolarity_Low              ((uint16_t)0x0000)  /* 刹车输入低电平有效 */
#define TIM_BreakPolarity_High             ((uint16_t)0x2000)  /* 刹车输入高电平有效 */
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))  /* 校验刹车输入极性 */
/**
  * @}
  */ 

/** @defgroup TIM_AOE_Bit_Set_Reset 
  * @{
  */

#define TIM_AutomaticOutput_Enable         ((uint16_t)0x4000)  /* 使能自动输出 */
#define TIM_AutomaticOutput_Disable        ((uint16_t)0x0000)  /* 关闭自动输出 */
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                               ((STATE) == TIM_AutomaticOutput_Disable))  /* 校验自动输出状态 */
/**
  * @}
  */ 

/** @defgroup Lock_level 
  * @{
  */

#define TIM_LOCKLevel_OFF                  ((uint16_t)0x0000)  /* 锁定关闭 */
#define TIM_LOCKLevel_1                    ((uint16_t)0x0100)  /* 锁定等级1 */
#define TIM_LOCKLevel_2                    ((uint16_t)0x0200)  /* 锁定等级2 */
#define TIM_LOCKLevel_3                    ((uint16_t)0x0300)  /* 锁定等级3 */
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))  /* 校验锁定等级 */
/**
  * @}
  */ 

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */

#define TIM_OSSIState_Enable               ((uint16_t)0x0400)  /* 使能空闲关闭状态(OSSI) */
#define TIM_OSSIState_Disable              ((uint16_t)0x0000)  /* 关闭空闲关闭状态(OSSI) */
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))  /* 校验OSSI状态 */
/**
  * @}
  */

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state 
  * @{
  */

#define TIM_OSSRState_Enable               ((uint16_t)0x0800)  /* 使能运行关闭状态(OSSR) */
#define TIM_OSSRState_Disable              ((uint16_t)0x0000)  /* 关闭运行关闭状态(OSSR) */
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))  /* 校验OSSR状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Idle_State 
  * @{
  */

#define TIM_OCIdleState_Set                ((uint16_t)0x0100)  /* 空闲态OCx置位 */
#define TIM_OCIdleState_Reset              ((uint16_t)0x0000)  /* 空闲态OCx复位 */
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))  /* 校验OC空闲状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_Idle_State 
  * @{
  */

#define TIM_OCNIdleState_Set               ((uint16_t)0x0200)  /* 空闲态OCxN置位 */
#define TIM_OCNIdleState_Reset             ((uint16_t)0x0000)  /* 空闲态OCxN复位 */
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))  /* 校验OCN空闲状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Polarity 
  * @{
  */

#define  TIM_ICPolarity_Rising             ((uint16_t)0x0000)  /* 上升沿捕获 */
#define  TIM_ICPolarity_Falling            ((uint16_t)0x0002)  /* 下降沿捕获 */
#define  TIM_ICPolarity_BothEdge           ((uint16_t)0x000A)  /* 双边沿捕获 */
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling))  /* 校验捕获极性 */
#define IS_TIM_IC_POLARITY_LITE(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                           ((POLARITY) == TIM_ICPolarity_Falling)|| \
                                           ((POLARITY) == TIM_ICPolarity_BothEdge))  /* 校验捕获极性（含双边沿） */                                      
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Selection 
  * @{
  */

#define TIM_ICSelection_DirectTI           ((uint16_t)0x0001) /*!< TIM Input 1, 2, 3 or 4 is selected to be 
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */  /* 直接映射：TIx连接到对应ICx */
#define TIM_ICSelection_IndirectTI         ((uint16_t)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */  /* 间接映射：TIx交叉连接到ICx */
#define TIM_ICSelection_TRC                ((uint16_t)0x0003) /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */  /* 连接到触发输入TRC */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))  /* 校验输入捕获映射 */
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Prescaler 
  * @{
  */

#define TIM_ICPSC_DIV1                     ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */  /* 每次捕获事件均触发 */
#define TIM_ICPSC_DIV2                     ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */  /* 每2个事件捕获一次 */
#define TIM_ICPSC_DIV4                     ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */  /* 每4个事件捕获一次 */
#define TIM_ICPSC_DIV8                     ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */  /* 每8个事件捕获一次 */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))  /* 校验捕获预分频 */
/**
  * @}
  */ 

/** @defgroup TIM_interrupt_sources 
  * @{
  */

#define TIM_IT_Update                      ((uint16_t)0x0001)  /* 更新中断 */
#define TIM_IT_CC1                         ((uint16_t)0x0002)  /* 捕获/比较通道1中断 */
#define TIM_IT_CC2                         ((uint16_t)0x0004)  /* 捕获/比较通道2中断 */
#define TIM_IT_CC3                         ((uint16_t)0x0008)  /* 捕获/比较通道3中断 */
#define TIM_IT_CC4                         ((uint16_t)0x0010)  /* 捕获/比较通道4中断 */
#define TIM_IT_COM                         ((uint16_t)0x0020)  /* 换相中断 */
#define TIM_IT_Trigger                     ((uint16_t)0x0040)  /* 触发中断 */
#define TIM_IT_Break                       ((uint16_t)0x0080)  /* 刹车中断 */
#define IS_TIM_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))  /* 校验定时器中断源 */

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))  /* 校验待查询中断源 */
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Base_address 
  * @{
  */

#define TIM_DMABase_CR1                    ((uint16_t)0x0000)  /* DMA传输基址：CR1 */
#define TIM_DMABase_CR2                    ((uint16_t)0x0001)  /* DMA传输基址：CR2 */
#define TIM_DMABase_SMCR                   ((uint16_t)0x0002)  /* DMA传输基址：SMCR */
#define TIM_DMABase_DIER                   ((uint16_t)0x0003)  /* DMA传输基址：DIER */
#define TIM_DMABase_SR                     ((uint16_t)0x0004)  /* DMA传输基址：SR */
#define TIM_DMABase_EGR                    ((uint16_t)0x0005)  /* DMA传输基址：EGR */
#define TIM_DMABase_CCMR1                  ((uint16_t)0x0006)  /* DMA传输基址：CCMR1 */
#define TIM_DMABase_CCMR2                  ((uint16_t)0x0007)  /* DMA传输基址：CCMR2 */
#define TIM_DMABase_CCER                   ((uint16_t)0x0008)  /* DMA传输基址：CCER */
#define TIM_DMABase_CNT                    ((uint16_t)0x0009)  /* DMA传输基址：CNT */
#define TIM_DMABase_PSC                    ((uint16_t)0x000A)  /* DMA传输基址：PSC */
#define TIM_DMABase_ARR                    ((uint16_t)0x000B)  /* DMA传输基址：ARR */
#define TIM_DMABase_RCR                    ((uint16_t)0x000C)  /* DMA传输基址：RCR */
#define TIM_DMABase_CCR1                   ((uint16_t)0x000D)  /* DMA传输基址：CCR1 */
#define TIM_DMABase_CCR2                   ((uint16_t)0x000E)  /* DMA传输基址：CCR2 */
#define TIM_DMABase_CCR3                   ((uint16_t)0x000F)  /* DMA传输基址：CCR3 */
#define TIM_DMABase_CCR4                   ((uint16_t)0x0010)  /* DMA传输基址：CCR4 */
#define TIM_DMABase_BDTR                   ((uint16_t)0x0011)  /* DMA传输基址：BDTR */
#define TIM_DMABase_DCR                    ((uint16_t)0x0012)  /* DMA传输基址：DCR */
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
                               ((BASE) == TIM_DMABase_CR2) || \
                               ((BASE) == TIM_DMABase_SMCR) || \
                               ((BASE) == TIM_DMABase_DIER) || \
                               ((BASE) == TIM_DMABase_SR) || \
                               ((BASE) == TIM_DMABase_EGR) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) || \
                               ((BASE) == TIM_DMABase_CNT) || \
                               ((BASE) == TIM_DMABase_PSC) || \
                               ((BASE) == TIM_DMABase_ARR) || \
                               ((BASE) == TIM_DMABase_RCR) || \
                               ((BASE) == TIM_DMABase_CCR1) || \
                               ((BASE) == TIM_DMABase_CCR2) || \
                               ((BASE) == TIM_DMABase_CCR3) || \
                               ((BASE) == TIM_DMABase_CCR4) || \
                               ((BASE) == TIM_DMABase_BDTR) || \
                               ((BASE) == TIM_DMABase_DCR))  /* 校验DMA传输基址 */
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Burst_Length 
  * @{
  */

#define TIM_DMABurstLength_1Transfer           ((uint16_t)0x0000)  /* DMA突发长度：1次传送 */
#define TIM_DMABurstLength_2Transfers          ((uint16_t)0x0100)  /* DMA突发长度：2次传送 */
#define TIM_DMABurstLength_3Transfers          ((uint16_t)0x0200)  /* DMA突发长度：3次传送 */
#define TIM_DMABurstLength_4Transfers          ((uint16_t)0x0300)  /* DMA突发长度：4次传送 */
#define TIM_DMABurstLength_5Transfers          ((uint16_t)0x0400)  /* DMA突发长度：5次传送 */
#define TIM_DMABurstLength_6Transfers          ((uint16_t)0x0500)  /* DMA突发长度：6次传送 */
#define TIM_DMABurstLength_7Transfers          ((uint16_t)0x0600)  /* DMA突发长度：7次传送 */
#define TIM_DMABurstLength_8Transfers          ((uint16_t)0x0700)  /* DMA突发长度：8次传送 */
#define TIM_DMABurstLength_9Transfers          ((uint16_t)0x0800)  /* DMA突发长度：9次传送 */
#define TIM_DMABurstLength_10Transfers         ((uint16_t)0x0900)  /* DMA突发长度：10次传送 */
#define TIM_DMABurstLength_11Transfers         ((uint16_t)0x0A00)  /* DMA突发长度：11次传送 */
#define TIM_DMABurstLength_12Transfers         ((uint16_t)0x0B00)  /* DMA突发长度：12次传送 */
#define TIM_DMABurstLength_13Transfers         ((uint16_t)0x0C00)  /* DMA突发长度：13次传送 */
#define TIM_DMABurstLength_14Transfers         ((uint16_t)0x0D00)  /* DMA突发长度：14次传送 */
#define TIM_DMABurstLength_15Transfers         ((uint16_t)0x0E00)  /* DMA突发长度：15次传送 */
#define TIM_DMABurstLength_16Transfers         ((uint16_t)0x0F00)  /* DMA突发长度：16次传送 */
#define TIM_DMABurstLength_17Transfers         ((uint16_t)0x1000)  /* DMA突发长度：17次传送 */
#define TIM_DMABurstLength_18Transfers         ((uint16_t)0x1100)  /* DMA突发长度：18次传送 */
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Transfers))  /* 校验DMA突发长度 */
/**
  * @}
  */ 

/** @defgroup TIM_DMA_sources 
  * @{
  */

#define TIM_DMA_Update                     ((uint16_t)0x0100)  /* 更新DMA请求 */
#define TIM_DMA_CC1                        ((uint16_t)0x0200)  /* 捕获/比较通道1 DMA请求 */
#define TIM_DMA_CC2                        ((uint16_t)0x0400)  /* 捕获/比较通道2 DMA请求 */
#define TIM_DMA_CC3                        ((uint16_t)0x0800)  /* 捕获/比较通道3 DMA请求 */
#define TIM_DMA_CC4                        ((uint16_t)0x1000)  /* 捕获/比较通道4 DMA请求 */
#define TIM_DMA_COM                        ((uint16_t)0x2000)  /* 换相DMA请求 */
#define TIM_DMA_Trigger                    ((uint16_t)0x4000)  /* 触发DMA请求 */
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))  /* 校验DMA请求源 */

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Prescaler 
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  ((uint16_t)0x0000)  /* 外部触发预分频：关闭 */
#define TIM_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)  /* 外部触发预分频：2分频 */
#define TIM_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)  /* 外部触发预分频：4分频 */
#define TIM_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)  /* 外部触发预分频：8分频 */
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))  /* 校验外部触发预分频 */
/**
  * @}
  */ 

/** @defgroup TIM_Internal_Trigger_Selection 
  * @{
  */

#define TIM_TS_ITR0                        ((uint16_t)0x0000)  /* 内部触发源ITR0 */
#define TIM_TS_ITR1                        ((uint16_t)0x0010)  /* 内部触发源ITR1 */
#define TIM_TS_ITR2                        ((uint16_t)0x0020)  /* 内部触发源ITR2 */
#define TIM_TS_ITR3                        ((uint16_t)0x0030)  /* 内部触发源ITR3 */
#define TIM_TS_TI1F_ED                     ((uint16_t)0x0040)  /* TI1边沿检测触发 */
#define TIM_TS_TI1FP1                      ((uint16_t)0x0050)  /* TI1FP1触发 */
#define TIM_TS_TI2FP2                      ((uint16_t)0x0060)  /* TI2FP2触发 */
#define TIM_TS_ETRF                        ((uint16_t)0x0070)  /* 外部触发ETRF */
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                             ((SELECTION) == TIM_TS_ITR1) || \
                                             ((SELECTION) == TIM_TS_ITR2) || \
                                             ((SELECTION) == TIM_TS_ITR3) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) || \
                                             ((SELECTION) == TIM_TS_TI2FP2) || \
                                             ((SELECTION) == TIM_TS_ETRF))  /* 校验触发源选择 */
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))  /* 校验内部触发源选择 */
/**
  * @}
  */ 

/** @defgroup TIM_TIx_External_Clock_Source 
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)  /* TI1外部时钟源 */
#define TIM_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)  /* TI2外部时钟源 */
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)  /* TI1边沿检测外部时钟源 */
#define IS_TIM_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TIM_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI1ED))  /* 校验TIx外部时钟源 */
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Polarity 
  * @{
  */ 
#define TIM_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)  /* 外部触发极性反相 */
#define TIM_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)  /* 外部触发极性非反相 */
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))  /* 校验外部触发极性 */
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode 
  * @{
  */

#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)  /* 预分频器在更新事件时重载 */
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)  /* 预分频器立即重载 */
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))  /* 校验预分频重载模式 */
/**
  * @}
  */ 

/** @defgroup TIM_Forced_Action 
  * @{
  */

#define TIM_ForcedAction_Active            ((uint16_t)0x0050)  /* 强制OCxREF为有效电平 */
#define TIM_ForcedAction_InActive          ((uint16_t)0x0040)  /* 强制OCxREF为无效电平 */
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))  /* 校验强制动作 */
/**
  * @}
  */ 

/** @defgroup TIM_Encoder_Mode 
  * @{
  */

#define TIM_EncoderMode_TI1                ((uint16_t)0x0001)  /* 编码器模式：仅TI1计数 */
#define TIM_EncoderMode_TI2                ((uint16_t)0x0002)  /* 编码器模式：仅TI2计数 */
#define TIM_EncoderMode_TI12               ((uint16_t)0x0003)  /* 编码器模式：TI1和TI2均计数 */
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))  /* 校验编码器模式 */
/**
  * @}
  */ 


/** @defgroup TIM_Event_Source 
  * @{
  */

#define TIM_EventSource_Update             ((uint16_t)0x0001)  /* 更新事件 */
#define TIM_EventSource_CC1                ((uint16_t)0x0002)  /* 捕获/比较通道1事件 */
#define TIM_EventSource_CC2                ((uint16_t)0x0004)  /* 捕获/比较通道2事件 */
#define TIM_EventSource_CC3                ((uint16_t)0x0008)  /* 捕获/比较通道3事件 */
#define TIM_EventSource_CC4                ((uint16_t)0x0010)  /* 捕获/比较通道4事件 */
#define TIM_EventSource_COM                ((uint16_t)0x0020)  /* 换相事件 */
#define TIM_EventSource_Trigger            ((uint16_t)0x0040)  /* 触发事件 */
#define TIM_EventSource_Break              ((uint16_t)0x0080)  /* 刹车事件 */
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))  /* 校验事件源 */

/**
  * @}
  */ 

/** @defgroup TIM_Update_Source 
  * @{
  */

#define TIM_UpdateSource_Global            ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */  /* 更新源：全局更新 */
#define TIM_UpdateSource_Regular           ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */  /* 更新源：仅计数器溢出/下溢 */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))  /* 校验更新源 */
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Preload_State 
  * @{
  */

#define TIM_OCPreload_Enable               ((uint16_t)0x0008)  /* 使能OC预装载 */
#define TIM_OCPreload_Disable              ((uint16_t)0x0000)  /* 关闭OC预装载 */
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))  /* 校验OC预装载状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Fast_State 
  * @{
  */

#define TIM_OCFast_Enable                  ((uint16_t)0x0004)  /* 使能OC快速模式 */
#define TIM_OCFast_Disable                 ((uint16_t)0x0000)  /* 关闭OC快速模式 */
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))  /* 校验OC快速模式 */
                                     
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Clear_State 
  * @{
  */

#define TIM_OCClear_Enable                 ((uint16_t)0x0080)  /* 使能OC参考信号清零 */
#define TIM_OCClear_Disable                ((uint16_t)0x0000)  /* 关闭OC参考信号清零 */
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))  /* 校验OC清零状态 */
/**
  * @}
  */ 

/** @defgroup TIM_Trigger_Output_Source 
  * @{
  */

#define TIM_TRGOSource_Reset               ((uint16_t)0x0000)  /* TRGO源：复位 */
#define TIM_TRGOSource_Enable              ((uint16_t)0x0010)  /* TRGO源：使能 */
#define TIM_TRGOSource_Update              ((uint16_t)0x0020)  /* TRGO源：更新事件 */
#define TIM_TRGOSource_OC1                 ((uint16_t)0x0030)  /* TRGO源：OC1 */
#define TIM_TRGOSource_OC1Ref              ((uint16_t)0x0040)  /* TRGO源：OC1REF */
#define TIM_TRGOSource_OC2Ref              ((uint16_t)0x0050)  /* TRGO源：OC2REF */
#define TIM_TRGOSource_OC3Ref              ((uint16_t)0x0060)  /* TRGO源：OC3REF */
#define TIM_TRGOSource_OC4Ref              ((uint16_t)0x0070)  /* TRGO源：OC4REF */
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))  /* 校验TRGO源 */
/**
  * @}
  */ 

/** @defgroup TIM_Slave_Mode 
  * @{
  */

#define TIM_SlaveMode_Reset                ((uint16_t)0x0004)  /* 从模式：复位模式 */
#define TIM_SlaveMode_Gated                ((uint16_t)0x0005)  /* 从模式：门控模式 */
#define TIM_SlaveMode_Trigger              ((uint16_t)0x0006)  /* 从模式：触发模式 */
#define TIM_SlaveMode_External1            ((uint16_t)0x0007)  /* 从模式：外部时钟模式1 */
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))  /* 校验从模式 */
/**
  * @}
  */ 

/** @defgroup TIM_Master_Slave_Mode 
  * @{
  */

#define TIM_MasterSlaveMode_Enable         ((uint16_t)0x0080)  /* 使能主从模式 */
#define TIM_MasterSlaveMode_Disable        ((uint16_t)0x0000)  /* 关闭主从模式 */
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))  /* 校验主从模式 */
/**
  * @}
  */ 

/** @defgroup TIM_Flags 
  * @{
  */

#define TIM_FLAG_Update                    ((uint16_t)0x0001)  /* 更新标志 */
#define TIM_FLAG_CC1                       ((uint16_t)0x0002)  /* 捕获/比较通道1标志 */
#define TIM_FLAG_CC2                       ((uint16_t)0x0004)  /* 捕获/比较通道2标志 */
#define TIM_FLAG_CC3                       ((uint16_t)0x0008)  /* 捕获/比较通道3标志 */
#define TIM_FLAG_CC4                       ((uint16_t)0x0010)  /* 捕获/比较通道4标志 */
#define TIM_FLAG_COM                       ((uint16_t)0x0020)  /* 换相标志 */
#define TIM_FLAG_Trigger                   ((uint16_t)0x0040)  /* 触发标志 */
#define TIM_FLAG_Break                     ((uint16_t)0x0080)  /* 刹车标志 */
#define TIM_FLAG_CC1OF                     ((uint16_t)0x0200)  /* 捕获/比较通道1重复捕获标志 */
#define TIM_FLAG_CC2OF                     ((uint16_t)0x0400)  /* 捕获/比较通道2重复捕获标志 */
#define TIM_FLAG_CC3OF                     ((uint16_t)0x0800)  /* 捕获/比较通道3重复捕获标志 */
#define TIM_FLAG_CC4OF                     ((uint16_t)0x1000)  /* 捕获/比较通道4重复捕获标志 */
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))  /* 校验待查询标志 */
                               
                               
#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint16_t)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000))  /* 校验待清除标志 */
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Filer_Value 
  * @{
  */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)  /* 校验输入捕获滤波值 */ 
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Filter 
  * @{
  */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)  /* 校验外部触发滤波值 */
/**
  * @}
  */ 

/** @defgroup TIM_Legacy 
  * @{
  */

#define TIM_DMABurstLength_1Byte           TIM_DMABurstLength_1Transfer  /* 兼容旧名：DMA突发长度1次传送 */
#define TIM_DMABurstLength_2Bytes          TIM_DMABurstLength_2Transfers  /* 兼容旧名：DMA突发长度2次传送 */
#define TIM_DMABurstLength_3Bytes          TIM_DMABurstLength_3Transfers  /* 兼容旧名：DMA突发长度3次传送 */
#define TIM_DMABurstLength_4Bytes          TIM_DMABurstLength_4Transfers  /* 兼容旧名：DMA突发长度4次传送 */
#define TIM_DMABurstLength_5Bytes          TIM_DMABurstLength_5Transfers  /* 兼容旧名：DMA突发长度5次传送 */
#define TIM_DMABurstLength_6Bytes          TIM_DMABurstLength_6Transfers  /* 兼容旧名：DMA突发长度6次传送 */
#define TIM_DMABurstLength_7Bytes          TIM_DMABurstLength_7Transfers  /* 兼容旧名：DMA突发长度7次传送 */
#define TIM_DMABurstLength_8Bytes          TIM_DMABurstLength_8Transfers  /* 兼容旧名：DMA突发长度8次传送 */
#define TIM_DMABurstLength_9Bytes          TIM_DMABurstLength_9Transfers  /* 兼容旧名：DMA突发长度9次传送 */
#define TIM_DMABurstLength_10Bytes         TIM_DMABurstLength_10Transfers  /* 兼容旧名：DMA突发长度10次传送 */
#define TIM_DMABurstLength_11Bytes         TIM_DMABurstLength_11Transfers  /* 兼容旧名：DMA突发长度11次传送 */
#define TIM_DMABurstLength_12Bytes         TIM_DMABurstLength_12Transfers  /* 兼容旧名：DMA突发长度12次传送 */
#define TIM_DMABurstLength_13Bytes         TIM_DMABurstLength_13Transfers  /* 兼容旧名：DMA突发长度13次传送 */
#define TIM_DMABurstLength_14Bytes         TIM_DMABurstLength_14Transfers  /* 兼容旧名：DMA突发长度14次传送 */
#define TIM_DMABurstLength_15Bytes         TIM_DMABurstLength_15Transfers  /* 兼容旧名：DMA突发长度15次传送 */
#define TIM_DMABurstLength_16Bytes         TIM_DMABurstLength_16Transfers  /* 兼容旧名：DMA突发长度16次传送 */
#define TIM_DMABurstLength_17Bytes         TIM_DMABurstLength_17Transfers  /* 兼容旧名：DMA突发长度17次传送 */
#define TIM_DMABurstLength_18Bytes         TIM_DMABurstLength_18Transfers  /* 兼容旧名：DMA突发长度18次传送 */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup TIM_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup TIM_Exported_Functions
  * @{
  */

void TIM_DeInit(TIM_TypeDef* TIMx);  /* 复位TIM外设至默认值 */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);  /* 初始化定时器时基单元 */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);  /* 初始化输出比较通道1 */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);  /* 初始化输出比较通道2 */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);  /* 初始化输出比较通道3 */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);  /* 初始化输出比较通道4 */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);  /* 初始化输入捕获通道 */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);  /* 配置PWM输入捕获模式 */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);  /* 配置刹车、死区与自动输出 */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);  /* 用默认值填充时基初始化结构体 */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);  /* 用默认值填充输出比较结构体 */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);  /* 用默认值填充输入捕获结构体 */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);  /* 用默认值填充BDTR结构体 */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭定时器 */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭主PWM输出 */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);  /* 使能或关闭定时器中断 */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);  /* 软件产生指定事件 */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);  /* 配置DMA传输基址与突发长度 */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);  /* 使能或关闭定时器DMA请求 */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);  /* 选择内部时钟 */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);  /* 配置内部触发作为外部时钟 */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);  /* 配置TIx作为外部时钟 */
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);  /* 配置ETR外部时钟模式1 */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);  /* 配置ETR外部时钟模式2 */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);  /* 配置外部触发ETR */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);  /* 设置预分频器及重载模式 */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);  /* 设置计数模式 */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);  /* 选择输入触发源 */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);  /* 配置编码器接口 */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);  /* 强制通道1输出为指定电平 */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);  /* 强制通道2输出为指定电平 */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);  /* 强制通道3输出为指定电平 */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);  /* 强制通道4输出为指定电平 */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭ARR预装载 */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭换相事件 */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭捕获/比较DMA */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭捕获/比较预装载 */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);  /* 配置通道1的OC预装载 */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);  /* 配置通道2的OC预装载 */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);  /* 配置通道3的OC预装载 */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);  /* 配置通道4的OC预装载 */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);  /* 配置通道1的OC快速模式 */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);  /* 配置通道2的OC快速模式 */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);  /* 配置通道3的OC快速模式 */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);  /* 配置通道4的OC快速模式 */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);  /* 配置通道1的OCREF清零 */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);  /* 配置通道2的OCREF清零 */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);  /* 配置通道3的OCREF清零 */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);  /* 配置通道4的OCREF清零 */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);  /* 配置通道1输出极性 */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);  /* 配置通道1互补输出极性 */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);  /* 配置通道2输出极性 */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);  /* 配置通道2互补输出极性 */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);  /* 配置通道3输出极性 */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);  /* 配置通道3互补输出极性 */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);  /* 配置通道4输出极性 */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);  /* 使能或关闭指定通道输出 */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);  /* 使能或关闭指定通道互补输出 */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);  /* 选择指定通道的输出比较模式 */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭更新事件 */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);  /* 选择更新事件来源 */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);  /* 使能或关闭霍尔传感器接口 */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);  /* 选择单脉冲模式 */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);  /* 选择TRGO触发输出源 */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);  /* 选择从模式 */
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);  /* 使能或关闭主从模式 */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);  /* 设置计数器值 */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);  /* 设置自动重装载值 */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);  /* 设置通道1比较值 */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);  /* 设置通道2比较值 */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);  /* 设置通道3比较值 */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);  /* 设置通道4比较值 */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);  /* 设置通道1输入捕获预分频 */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);  /* 设置通道2输入捕获预分频 */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);  /* 设置通道3输入捕获预分频 */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);  /* 设置通道4输入捕获预分频 */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);  /* 设置时钟分频 */
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx);  /* 读取通道1捕获值 */
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx);  /* 读取通道2捕获值 */
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx);  /* 读取通道3捕获值 */
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx);  /* 读取通道4捕获值 */
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);  /* 读取计数器值 */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);  /* 读取预分频器值 */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);  /* 检查指定标志位状态 */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);  /* 清除指定标志位 */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);  /* 检查指定中断是否发生 */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);  /* 清除指定中断挂起位 */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F10x_TIM_H */
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
