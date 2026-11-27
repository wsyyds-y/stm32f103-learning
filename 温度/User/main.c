#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "Delay.h"
#include "OLED.h"
#include "NTC.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @file    main.c
  * @brief   NTC 温度模块（AO + DO）实时显示 + 心跳指示
  *
  * 显示：TEMP:25.3°C / DO:NORMAL / AO:1650mV / ADC:2048
  *   OLED 字库只有 ASCII，没有 '°'，所以度符号由本文件的 OLED_ShowDegree()
  *   直接画 8x16 点阵补上，不修改已验证的 OLED 驱动文件。
  *
  * 串口：只用 sprintf 拼字符串 + Serial_SendString 发送，**不再调用 printf**。
  *   printf 在没开 MicroLIB 时会走半主机（semihosting）卡死，而 Keil 打开着工程时
  *   会把它自己内存里的工程选项写回 .uvprojx，之前设的 MicroLIB 就是这样被改回去的。
  *   去掉 printf 后，开不开 MicroLIB 都能正常运行。
  *
  * 心跳：PC13（多数最小系统板的板载 LED）和 PB12 每 500ms 翻转一次。
  ******************************************************************************
  */

/* OLED 驱动里没有在头文件里声明的底层函数，这里按原型引用（不改驱动文件本身） */
extern void OLED_SetCursor(uint8_t Y, uint8_t X);
extern void OLED_WriteData(uint8_t Data);

/* “度”符号的 8x16 点阵：上面 4x4 的小圆圈，下面留空。
 * 每字节是一列 8 个像素，最低位在最上面一行。 */
static const uint8_t OLED_DegreeGlyph[8] =
{
    0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00
};

/* 在指定行列画一个“°”（占 1 列，和 8x16 字符同高）。
 * Line 行号 1~4，Column 列号 1~16。 */
static void OLED_ShowDegree(uint8_t Line, uint8_t Column)
{
    uint8_t i;

    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);      /* 上半部分 */
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_DegreeGlyph[i]);
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);  /* 下半部分清空 */
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(0x00);
    }
}

/* 心跳引脚初始化：PC13 + PB12 推挽输出，上电先输出高电平。 */
static void Heartbeat_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/* 两个心跳脚一起翻转（PC13 板载 LED 是低电平点亮，翻转即可看到闪烁）。 */
static void Heartbeat_Toggle(void)
{
    static uint8_t level = 0;

    level = !level;
    if (level)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    }
    else
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
    }
}

/* 把 0.1℃ 的整数格式化成 "25.3" 这样的字符串（不带单位）。
 * buf 至少 12 字节；负数会带 '-'（如 -55 -> "-5.5"）。 */
static void FormatTemp(char *buf, int16_t temp_x10)
{
    int16_t abs_val = (temp_x10 < 0) ? (int16_t)(-temp_x10) : temp_x10;

    sprintf(buf, "%s%d.%d", (temp_x10 < 0) ? "-" : "", abs_val / 10, abs_val % 10);
}

int main(void)
{
    uint16_t adc;
    uint16_t adc_sum;
    uint16_t mv;
    int16_t temp_x10;
    uint8_t alarm;
    uint8_t i;
    uint8_t len;
    char buf_temp[16];
    char buf_ao[12];
    char buf_adc[8];
    char line[48];

    /* 上电先闪一下心跳（也给 OLED 留出上电稳定的时间），再点屏写标签。 */
    Heartbeat_Init();
    Heartbeat_Toggle();
    Delay_ms(250);
    Heartbeat_Toggle();
    Delay_ms(250);

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "TEMP:");
    OLED_ShowString(2, 1, "DO:");
    OLED_ShowString(3, 1, "AO:");
    OLED_ShowString(4, 1, "ADC:");

    Serial_Init();
    NTC_Init();

    while (1)    /* 主循环：每 500ms 采一次 AO 并刷新显示 */
    {
        /* 连续采 8 次取平均，压低 ADC 噪声（单次采样末位常有 ±2 的跳动） */
        adc_sum = 0;
        for (i = 0; i < 8; i++)
        {
            adc_sum += NTC_ReadAdc();
        }
        adc = adc_sum / 8;

        temp_x10 = NTC_AdcToTempX10(adc);
        alarm = NTC_IsAlarm();
        mv = (uint16_t)((uint32_t)adc * 3300 / 4095);   /* 换算成毫伏，避免显示浮点 */

        /* 温度行：先清空数值区，再画数字 + 度符号 + C */
        FormatTemp(buf_temp, temp_x10);
        OLED_ShowString(1, 6, "        ");              /* 8 个空格覆盖旧内容 */
        OLED_ShowString(1, 6, buf_temp);
        len = (uint8_t)strlen(buf_temp);
        OLED_ShowDegree(1, 6 + len);                    /* 25.3° */
        OLED_ShowChar(1, 6 + len + 1, 'C');             /* 25.3°C */

        if (alarm)
        {
            OLED_ShowString(2, 4, "ALARM  ");           /* DO 已过阈值 */
        }
        else
        {
            OLED_ShowString(2, 4, "NORMAL ");
        }

        sprintf(buf_ao, "%4umV  ", mv);                 /* 补空格，覆盖上一次的长数字 */
        OLED_ShowString(3, 4, buf_ao);
        sprintf(buf_adc, "%4u    ", adc);
        OLED_ShowString(4, 5, buf_adc);

        /* 串口输出：sprintf 拼好整行再发，不经过 printf，不依赖 MicroLIB */
        sprintf(line, "T=%sC AO=%umV ADC=%u DO=%s\r\n",
                buf_temp, mv, adc, alarm ? "ALARM" : "NORMAL");
        Serial_SendString(line);

        Heartbeat_Toggle();
        Delay_ms(500);
    }
}
