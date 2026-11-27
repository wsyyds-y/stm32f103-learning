#include "stm32f10x.h"
#include <stdio.h>
#include "Delay.h"
#include "OLED.h"
#include "DS18B20.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @file    main.c
  * @brief   DS18B20 实时温度显示：OLED 显示当前/最高/最低温度，串口同步打印
  ******************************************************************************
  */

/* 把 0.1℃ 单位的温度格式化成 "25.6C" 这样的字符串，尾部补空格覆盖上一次的长数字。
 * buf 至少 12 字节；temp_x10 为负时自动加负号（如 -55 -> "-5.5C"）。 */
static void FormatTemp(char *buf, int16_t temp_x10)
{
    int16_t abs_val;

    abs_val = (temp_x10 < 0) ? (int16_t)(-temp_x10) : temp_x10;
    sprintf(buf, "%s%d.%dC   ", (temp_x10 < 0) ? "-" : "", abs_val / 10, abs_val % 10);
}

int main(void)
{
    int16_t temp_x10 = 0;
    int16_t max_x10 = -550;      /* DS18B20 量程 -55 ~ +125℃ */
    int16_t min_x10 = 1250;
    uint8_t ret;
    char buf_now[16];
    char buf_max[16];
    char buf_min[16];

    OLED_Init();
    OLED_Clear();
    Serial_Init();
    DS18B20_Init();

    OLED_ShowChineseString(1, 1, "温度:");
    OLED_ShowString(2, 1, "MAX:");
    OLED_ShowString(3, 1, "MIN:");
    OLED_ShowString(4, 1, "READY");

    printf("DS18B20 demo start\r\n");

    while (1)    /* 主循环：每约 1 秒测一次（读温度内部要等 750ms 转换） */
    {
        ret = DS18B20_ReadTemp(&temp_x10);

        if (ret == 0)            /* 读取成功 */
        {
            if (temp_x10 > max_x10) max_x10 = temp_x10;
            if (temp_x10 < min_x10) min_x10 = temp_x10;

            FormatTemp(buf_now, temp_x10);
            FormatTemp(buf_max, max_x10);
            FormatTemp(buf_min, min_x10);

            OLED_ShowString(1, 6, buf_now);   /* “温度:”占 1~5 列，数值从第 6 列开始 */
            OLED_ShowString(2, 5, buf_max);   /* “MAX:”占 1~4 列 */
            OLED_ShowString(3, 5, buf_min);   /* “MIN:”占 1~4 列 */
            OLED_ShowString(4, 1, "OK       ");

            printf("T=%s MAX=%s MIN=%s\r\n", buf_now, buf_max, buf_min);
        }
        else                     /* 1=无应答，2=CRC 错 */
        {
            OLED_ShowString(4, 1, "ERR      ");
            printf("read error: %d\r\n", ret);
        }
    }
}
