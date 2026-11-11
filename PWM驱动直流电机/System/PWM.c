 #include "stm32f10x.h"                  // Device header


void pwm_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period =2000 - 1 ;  //ARR
	TIM_InitStruct.TIM_Prescaler = 72 - 1;//PSC
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);
	
	TIM_OCInitTypeDef TIMOC_InitStruct;
	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIMOC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIMOC_InitStruct.TIM_Pulse = 0;//CCR
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High ;

	TIM_OC3Init(TIM2,&TIMOC_InitStruct);
	TIM_OC3PolarityConfig(TIM2,TIM_OCPolarity_High);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}


void PWM_SetCompare3(uint16_t ccr)
{
		TIM_SetCompare3(TIM2,ccr);
}








