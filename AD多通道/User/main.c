#include "stm32f10x.h"
#include "AD.h"
#include "OLED.h"
#include "Delay.h"


uint16_t ad_value;  /* 存储ADC转换结果的变量 */
float voltage;  /* 存储电压值的变量 */
uint16_t AD1,AD2;


int main(void)
{
    /* 初始化代码写在这里 */
    ad_init();
    OLED_Init();

    while (1)    
    {
        AD1 = ad_start(ADC_Channel_0);  /* 启动ADC转换并获取结果 */
        AD2 = ad_start(ADC_Channel_1);  /* 启动ADC转换并获取结果 */
  
        OLED_ShowNum(1, 1, AD1, 4);  /* 在OLED上显示AD1的值 */
        OLED_ShowNum(2, 1, AD2, 4);  /* 在OLED上显示AD2的值 */
        //Delay_ms(500);  /* 延时500毫秒 */
    }
}


