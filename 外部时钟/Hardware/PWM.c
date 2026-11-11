#include "stm32f10x.h"                  // Device header
void PWM_Init(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructue;                //初始化GPIO
	
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_AF_PP ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructue);
	
	/* 选择内部时钟源（PWM 实验的做法）：TIM2 的计数时钟 = 72MHz 主频。
	 * 注意：光调 TIM_InternalClockConfig 只清了 SMS 位、清不掉 ECE 位，
	 * 如果之前有人调过 TIM_ETRClockMode2Config，TIM2 还是会把 PA0 当计数时钟，
	 * 所以这里顺手把 ECE 也清掉，保证时钟来源一定是内部 72MHz */
	TIM_InternalClockConfig(TIM2);
	TIM2->SMCR &= (uint16_t)~TIM_SMCR_ECE;
	
	TIM_TimeBaseInitTypeDef TIM_InitStructue;
	TIM_InitStructue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructue.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM_InitStructue.TIM_Period =100 - 1;		//ARR
	TIM_InitStructue.TIM_Prescaler =720 - 1;	//PSC
	TIM_InitStructue.TIM_RepetitionCounter = 0;
	
	
	TIM_TimeBaseInit(TIM2,&TIM_InitStructue);
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure .TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	
	TIM_Cmd(TIM2,ENABLE);
	



}

void PWM_SetCompare1 (uint16_t Compare)
{

TIM_SetCompare1 (TIM2,Compare);

}

