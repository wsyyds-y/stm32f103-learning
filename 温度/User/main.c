#include "stm32f10x.h"
#include <stdio.h>
#include "Delay.h"
#include "OLED.h"
#include "NTC.h"

/**
  * 最小测温程序：初始化屏幕和 ADC，然后循环「读温度 → 显示」。
  * 屏幕上显示一行：TEMP:25.3C   （字库只有 ASCII，所以没有度符号）
  *
  * 想继续加功能，常见顺序：
  *   1) 显示 ADC 原始码值和电压   —— 排查接线
  *   2) 串口打印一行              —— 用电脑看曲线
  *   3) 超过阈值点亮 LED          —— 温度报警
  */

int main(void)
{
    int16_t t10;        /* 温度 ×10，253 表示 25.3℃ */
    int16_t abs10;      /* 绝对值，用来拼字符串 */
    char buf[12];

    OLED_Init();        /* 屏幕（PB8/PB9 软件 I2C） */
    OLED_Clear();
    NTC_Init();         /* ADC1 + PA0 */

    OLED_ShowString(1, 1, "TEMP:");

    while (1)
    {
        t10 = NTC_GetTempX10();

        /* 拼成 "25.3C" 这样的字符串：整数部分 + '.' + 一位小数 + 'C' */
        abs10 = (t10 < 0) ? (int16_t)(-t10) : t10;
        if (t10 < 0)
        {
            sprintf(buf, "-%d.%dC", abs10 / 10, abs10 % 10);
        }
        else
        {
            sprintf(buf, "%d.%dC", abs10 / 10, abs10 % 10);
        }

        OLED_ShowString(1, 6, "        ");   /* 先擦掉上一次的数字，防止残留 */
        OLED_ShowString(1, 6, buf);

        Delay_ms(500);                       /* 半秒刷新一次就够了 */
    }
}
