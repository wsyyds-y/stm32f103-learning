#include "stm32f10x.h"
#include "PWM.h"


void Servo_Init(void)
{
    pwm_init();
  
}
void Servo_SetAngle(float angle)
{
   PWM_SetCompare1(angle / 180 * 2000 + 500);
    
}


