#include "stm32f10x.h"                  // Device header

volatile uint16_t num;

void tim_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef tim ;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 10000 - 1; //计数周期，即ARR的值
	tim.TIM_Prescaler = 7200 - 1;//预分频器，即PSC的值
	tim.TIM_RepetitionCounter = 0;//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2,&tim);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = TIM2_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 2;
	nvic.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvic);
	
	TIM_Cmd(TIM2,ENABLE);
	
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


