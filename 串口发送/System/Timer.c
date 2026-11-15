#include "stm32f10x.h"                  // Device header


//外部时钟
void Timer_Init(void )
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructue;                //初始化GPIO
	
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_IPU ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructue);
	
	/* 配置 ETR 外部时钟模式2：ETR 上每来一个有效沿，CNT 就加 1。
	 * 四个参数依次是：
	 *   ① TIM2
	 *   ② TIM_ExtTRGPSC_OFF    ：ETR 预分频器关闭（不分频，来一个沿算一个）
	 *   ③ TIM_ExtTRGPolarity_NonInverted
	 *        ：不反相，即"上升沿"有效（想改成下降沿有效就用 _Inverted）
	 *   ④ 0x0F = ETR 输入数字滤波器，范围 0x00 ~ 0x0F
	 *        0x00 = 不滤波（原来填的就是这个，等于对毛刺完全敞开）
	 *        0x0F = 最强滤波：以 f_DTS/32 采样，连续 8 次电平一致才认这个沿。
	 *               TIM2 时钟 72MHz，约 0.44us x 8 ≈ 3.6us，
	 *               只能滤掉微秒级的电路毛刺，滤不掉毫秒级的抖动 */
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	
	TIM_TimeBaseInitTypeDef TIM_InitStructue;
	TIM_InitStructue.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructue.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM_InitStructue.TIM_Period =10 - 1;
	TIM_InitStructue.TIM_Prescaler =1 - 1;
	TIM_InitStructue.TIM_RepetitionCounter = 0;
	
	
	TIM_TimeBaseInit(TIM2,&TIM_InitStructue);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructue;
	
	NVIC_InitStructue.NVIC_IRQChannel = TIM2_IRQn;

	NVIC_InitStructue.NVIC_IRQChannelCmd = ENABLE;

	NVIC_InitStructue.NVIC_IRQChannelPreemptionPriority =2;

	NVIC_InitStructue.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStructue);
	
	TIM_Cmd(TIM2,ENABLE);
	
}

uint16_t Timer_GetCounter(void)
{

	return TIM_GetCounter(TIM2);
}

/*
void TIM2_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	}

}*/
	
	
	


