#include "stm32f10x.h"
#include "PWM.h"
#include "OLED.h"
#include "ic.h"


int main(void)
{
   /*模块初始化*/
	OLED_Init();		//OLED初始化
	pwm_init();			//PWM初始化
	ic_init();			//输入捕获初始化
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Freq:00000Hz");		//1行1列显示字符串Freq:00000Hz
	
	/*使用PWM模块提供输入捕获的测试信号*/
	PWM_Setprescaler(720 - 1);					//PWM频率Freq = 72M / (PSC + 1) / 100
	PWM_SetCompare1(1);						//PWM占空比Duty = CCR / 100
	
	while (1)
	{
		OLED_ShowNum(1, 6, ic_getfreq(), 5);	//不断刷新显示输入捕获测得的频率

        OLED_ShowNum(2, 1, ic_getduty(), 5); 
        OLED_ShowNum(3, 1, TIM_GetCapture1(TIM3), 5); 
        OLED_ShowNum(4, 1, TIM_GetCapture2(TIM3), 5); 
    }
        
}



