
#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	//LED初始化代码
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_Out_PP ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructue);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);//将指定引脚设置为高电平
	 
}


void LED1_ON(void)
	
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
}

//翻转信号
void LED1_TURN(void)
{
		if (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		
		}
		else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
	

}
void LED1_OFF(void)
	
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	
}
void LED2_ON(void)
	
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	
}


void LED2_OFF(void)
	
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	
}

//翻转信号
void LED2_TURN(void)
{
		if (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
		
		}
		else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		}
	

}
