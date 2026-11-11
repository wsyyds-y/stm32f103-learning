#include "stm32f10x.h"
#include "PWM.h"
#include "motor.h"
#include "Key.h"

int main(void)
{
    motor_init();
    motor_speed(60);
    while (1)
    {
        
    }
}



