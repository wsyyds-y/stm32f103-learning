 #include "stm32f10x.h"                  // Device header



 void ic_init(void)
 {


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	TIM_InternalClockConfig(TIM3);	


	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period =65536 - 1 ;  //ARR
	TIM_InitStruct.TIM_Prescaler = 72 - 1;//PSC
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_InitStruct);

    TIM_ICInitTypeDef timic_initstruct;
    timic_initstruct.TIM_Channel = TIM_Channel_1;
    timic_initstruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    timic_initstruct.TIM_ICFilter = 0xF ;
    timic_initstruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    timic_initstruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM3,&timic_initstruct);


    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);

    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3,ENABLE);
 }



uint32_t ic_getfreq(void)
{
    
    return 1000000 / (TIM_GetCapture1(TIM3) + 1);                /* TIM3 计数频率 1 MHz */
}

uint32_t ic_getduty(void)
{
    return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1) ;   /* 占空比 = CCR2 / CCR1 */
}
 