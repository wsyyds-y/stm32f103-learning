#include "stm32f10x.h"
#include "OLED.h"
#include"temperature.h"
#include <stdio.h>
#include "Delay.h"



int main(void)
{   int16_t a;
    int16_t b;
    char v[20];
    OLED_Init();
    temperature__init();
    OLED_ShowChinese(1,1,17);
    OLED_ShowChinese(1,3,18);

    while (1)   
    {
        a = suan_init();
        b = (a < 0) ? (int16_t)(-a) : a;      /* b = |a|，用来拆整数位和小数位 */
        if (a < 0) { sprintf(v, "-%d.%dC", b / 10, b % 10); }   /* 判断原来的 a，不是 b */
        else       { sprintf(v, "%d.%dC",  b / 10, b % 10); }
        OLED_ShowString(1, 6, "        ");
        OLED_ShowString(1, 6, v);
        Delay_ms(500);  
    }
}


