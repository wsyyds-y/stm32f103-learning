#include "stm32f10x.h"
#include "Delay.h"
#include "Servo.h"
#include "OLED.h"
#include "TIM.h"
#include "PWM.h"
#include "Key.h"



uint8_t getnum;

float angle = 0;

int main(void)
{
    key_Init();
	OLED_Init();
	
    Servo_Init();

    OLED_ShowString(1,1,"Angle:");
	while (1)
	{	
        getnum = Key_GetNum();
        if(getnum == 1)
        {
            angle += 30;
            if(angle > 180) angle = 0;
            
        }
        Servo_SetAngle(angle);
        OLED_ShowNum(2,1,angle,3);

	}
	
}




