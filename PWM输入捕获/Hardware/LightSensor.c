#include "stm32f10x.h"                  // Device header




void LightSensor_Init(void)
{
	//初始化代码
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructue);
	
	
	 
}
uint8_t LightSensot_Get(void)
	//读取13端口的电平
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}




