#include "stm32f10x.h"  
#include "PWM.h"
#include "motor.h"

void motor_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_Out_PP ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructue);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5);   //先让 IN1=IN2=1（刹车），避免上电乱转
	
    pwm_init();
}

/* speed : -100 ~ +100，单位是占空比百分比 */
void motor_speed(int8_t speed)
{
    if(speed > 100)  speed = 100;
    if(speed < -100) speed = -100;

    if(speed >= 0)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        speed = -speed;
    }
    // PWM.c 里 ARR+1 = 2000（PSC=72-1 → 1 MHz，500 Hz），所以 1% = 20 个计数
    PWM_SetCompare3((uint16_t)speed * 20);   //百分比 × 20 → CCR（ARR=2000）
}



