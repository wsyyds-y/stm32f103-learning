
#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	//LED初始化代码
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_Out_PP ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructue);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//将指定引脚设置为高电平
	 
}


void Buzzer_ON(void)
	
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	
}
void Buzzer_TURN(void)//翻转信号

{
		if (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
		
		}
		else
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		}
	

}
void Buzzer_OFF(void)
	
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
}

