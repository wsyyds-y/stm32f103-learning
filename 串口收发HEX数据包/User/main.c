#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
//uint8_t Serial_TX [4];
uint8_t RxData;		
	//定义用于接收串口数据的变量
//uint8_t Serial_RX [4];

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Key_Init();
	/*显示静态字符串*/
	
	
	/*串口初始化*/
	Serial_Init();		//串口初始化
	
	

	while (1)
	{   uint8_t KeyNum = 0;
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			Serial_TX[0] ++;
			Serial_TX[1] ++;
			Serial_TX[2] ++;
			Serial_TX[3] ++;
			Serial_SendPacket();
			OLED_ShowHexNum(4,1,Serial_TX[0],2);
			OLED_ShowHexNum(4,4,Serial_TX[1],2);
			OLED_ShowHexNum(4,7,Serial_TX[2],2);
			OLED_ShowHexNum(4,10,Serial_TX[3],2);


		}
		if(Serial_GetRxFlag() == 1)
		{
			OLED_ShowHexNum(1,1,Serial_RX[0],2);
			OLED_ShowHexNum(1,4,Serial_RX[1],2);
			OLED_ShowHexNum(1,7,Serial_RX[2],2);
			OLED_ShowHexNum(1,10,Serial_RX[3],2);


		}
	}
}
