#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void key_Init(void)
{
	//按键初始化：PB1 上拉输入，按下时被拉低
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_IPU ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructue);
	
	
	 
}
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
		Delay_ms(20);
		KeyNum = 1;
		
	}
	
	
	return KeyNum;
	
	
}




