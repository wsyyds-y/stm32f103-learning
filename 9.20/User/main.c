#include "stm32f10x.h"                  // Device header
#include "Delay.h"
 int main(void)
 {	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_Out_PP ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructue);
	 
	 
	
	while (1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		
	}	
 
 
}
 
