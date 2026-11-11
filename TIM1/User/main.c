#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "Count.h"
#include "Encoder.h"
#include "Timer.h"
#include "PWM.h"

/* 计数结果。在 TIM2 中断里加 1，在主循环里显示，
 * 中断和主循环共享的变量必须加 volatile，
 * 否则编译器可能把它缓存进寄存器，出现"数字不刷新"的现象 */
volatile int16_t Num;


int main(void)
{
    uint8_t i;

    OLED_Init();
    key_Init();
	Buzzer_Init();
	LightSensor_Init();
	Coint_Init();
	Encoder_Init();
	PWM_Init();
	OLED_ShowString(1,1,"Num");
	OLED_ShowString(2,1,"Cnt");
	
    while (1)
    {
		/* 呼吸灯：占空比 0 -> 100 -> 0 循环，灯由暗到亮、再由亮到暗 */
		for (i = 0; i <= 100; i ++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for (i = 0; i <= 100; i ++)
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}
    }
}

void TIM2_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	}

}


