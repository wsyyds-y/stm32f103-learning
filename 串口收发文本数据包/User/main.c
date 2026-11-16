#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"
#include <string.h>
//uint8_t Serial_TX [4];
uint8_t RxData;		
	//定义用于接收串口数据的变量
//uint8_t Serial_RX [4];

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	LED_Init();			//LED初始化（把PA1配置成推挽输出，否则写引脚也不亮）
	Key_Init();
	Serial_Init();		//串口初始化
	LED_Init();			//把PA1配置成推挽输出，否则写引脚也不亮

	while (1)
	{  
		if (Serial_GetRxFlag () == 1)
		{	
			if  (strcmp(Serial_RX,"LED_ON") == 0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(4,1,"                ");
				OLED_ShowString(4,1,Serial_RX);

			}
			else if  (strcmp(Serial_RX,"LED_OFF") == 0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(4,1,"                ");
				OLED_ShowString(4,1,Serial_RX);

			}
			else
			{
				OLED_ShowString(3,1,"NO");

			}


		}
		
	}
}
