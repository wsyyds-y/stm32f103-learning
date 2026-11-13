#include "stm32f10x.h"
#include "AD.h"
#include "OLED.h"
#include "Delay.h"


uint16_t ad_value;  /* 存储ADC转换结果的变量 */
float voltage;  /* 存储电压值的变量 */


int main(void)
{
    /* 初始化代码写在这里 */
    ad_init();
    OLED_Init();

    while (1)    
    {
        ad_value = ad_start();  /* 启动ADC转换并获取结果 */
        voltage = (float)ad_value / 4095 * 3.3;  /* 将ADC值转换为电压值，假设参考电压为3.3V，12位ADC */
        OLED_ShowNum(1, 1, ad_value, 4);  /* 在OLED上显示ADC值，显示4位数字 */
        OLED_ShowNum(2, 1, voltage, 1);
        OLED_ShowNum(3, 2, (uint16_t)(voltage * 100) % 100,2);  /* 在OLED上显示电压值，显示4位数字 */
        Delay_ms(100);  /* 延时500毫秒 */
    }
}


