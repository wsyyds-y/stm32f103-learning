#include "stm32f10x.h"
#include "PWM.h"
#include "motor.h"
#include "Key.h"

/*int main(void)
{
    motor_init();
    motor_speed(60);
    while (1)
    {
        
    }
}*/




int main(void)
{
    GPIO_InitTypeDef g;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    g.GPIO_Mode  = GPIO_Mode_Out_PP;
    g.GPIO_Speed = GPIO_Speed_50MHz;
    g.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOA, &g);

    GPIO_SetBits(GPIOA, GPIO_Pin_2);    // PWMA = 100%
    GPIO_SetBits(GPIOA, GPIO_Pin_4);    // AIN1 = 1
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);  // AIN2 = 0  → 正转

    while (1) { }
}
    
