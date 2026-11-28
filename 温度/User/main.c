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
  * @brief   NTC 热敏电阻测温：OLED 显示 + 串口输出（无心跳闪烁）
  *
  * 显示（4 行 × 16 列）：
  *   TEMP: 24.8°C     平滑后的温度
  *   AO  :1650mV      分压点电压，判断接线对不对先看它
  *   ADC :2048        12 位原始码值
  *   Rt  :10.0k       反推出的热敏电阻值，拿万用表和它对一下就知道模型准不准
  *
  * 串口每 500ms 一行：T=24.8C AO=1650mV ADC=2048 Rt=10000R OFS=+0.0C
  *
  * 蓝灯（PC13 板载 LED）：上电只闪一下表示固件跑起来了，之后一直灭，
  * 不再做心跳闪烁。不想要这一下就把 LED_BOOT_PULSE 改成 0。
  *
  * 度符号：OLED 字库只有 ASCII，没有 '°'，所以由本文件的 OLED_ShowDegree()
  * 直接画 8x16 点阵补上，不修改已验证的 OLED 驱动文件。
  *
  * 串口：只用 sprintf 拼字符串 + Serial_SendString，**不调用 printf**。
  * printf 在没开 MicroLIB 时会走半主机卡死，而 Keil 打开工程时会把内存里的
  * 工程选项写回 .uvprojx，之前设的 MicroLIB 就被改回去过。去掉 printf 后，
  * 开不开 MicroLIB 都能跑。
  ******************************************************************************
  */

/* 上电是否闪一下 LED（1=闪 100ms，0=全程不亮） */
#define LED_BOOT_PULSE          1
#define LED_PORT                GPIOC
#define LED_PIN                 GPIO_Pin_13
#define LED_CLK                 RCC_APB2Periph_GPIOC

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

/* 板载 LED（PC13，低电平点亮）初始化：先置高电平让灯灭掉。
 * 之前那版用 PC13/PB12 每 500ms 翻转做心跳，蓝灯一直闪，这里去掉心跳，
 * 只在需要时闪一下。 */
static void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    GPIO_SetBits(LED_PORT, LED_PIN);        /* 高电平 = 灭 */
}

/* 把 0.1 单位的定点数格式化成 "24.8"（不带单位）。
 * force_sign=1 时正数也带 '+'，用于显示修正量（如 "+0.0"）；负数总是带 '-'。 */
static void FormatX10(char *buf, int16_t val_x10, uint8_t force_sign)
{
    int16_t abs_val = (val_x10 < 0) ? (int16_t)(-val_x10) : val_x10;
    char sign;

    if (val_x10 < 0)
    {
        sign = '-';
    }
    else if (force_sign)
    {
        sign = '+';
    }
    else
    {
        sign = '\0';
    }

    if (sign == '\0')
    {
        sprintf(buf, "%d.%d", abs_val / 10, abs_val % 10);
    }
    else
    {
        sprintf(buf, "%c%d.%d", sign, abs_val / 10, abs_val % 10);
    }
}

int main(void)
{
    uint16_t adc;
    uint16_t mv;
    uint32_t ohm;
    uint32_t ohm_k10;
    int16_t temp_x10;
    int32_t filt_x10 = 0;
    uint8_t filt_ready = 0;
    uint8_t len;
    char buf_temp[16];
    char buf_ao[12];
    char buf_adc[10];
    char buf_rt[12];
    char buf_ofs[8];
    char line[72];

    /* 灯先灭掉；需要的话给一次 100ms 的闪光，表示固件已经跑起来了 */
    LED_Init();
#if LED_BOOT_PULSE
    GPIO_ResetBits(LED_PORT, LED_PIN);
    Delay_ms(100);
    GPIO_SetBits(LED_PORT, LED_PIN);
#endif

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "TEMP:");
    OLED_ShowString(2, 1, "AO  :");
    OLED_ShowString(3, 1, "ADC :");
    OLED_ShowString(4, 1, "Rt  :");

    Serial_Init();
    NTC_Init();

    FormatX10(buf_ofs, NTC_GetOffsetX10(), 1);

    Serial_SendString("\r\n[NTC] 10k NTC + 10k series, AO->PA0\r\n");
    Serial_SendString("T = 1/(1/T0 + ln(Rt/R0)/B) - 273.15\r\n");

    while (1)    /* 主循环：每 500ms 采一次并刷新显示 */
    {
        /* 8 次平均压噪声（单次采样末位常有 ±2 的跳动） */
        adc = NTC_ReadAdcAve(8);
        mv = NTC_AdcToMv(adc);
        ohm = NTC_AdcToOhm(adc);
        temp_x10 = NTC_AdcToTempX10(adc);

        /* 一阶惯性滤波：新值占 1/4，显示不会因为 ±0.1 抖动来回跳。
         * 上电第一次直接取原值，避免从 0 慢慢爬上来。 */
        if (!filt_ready)
        {
            filt_x10 = temp_x10;
            filt_ready = 1;
        }
        else
        {
            filt_x10 = (filt_x10 * 3 + temp_x10) / 4;
        }

        /* 温度行：先清空数值区，再画数字 + 度符号 + C（防止旧数字残留） */
        FormatX10(buf_temp, (int16_t)filt_x10, 0);
        OLED_ShowString(1, 6, "        ");
        OLED_ShowString(1, 6, buf_temp);
        len = (uint8_t)strlen(buf_temp);
        OLED_ShowDegree(1, 6 + len);
        OLED_ShowChar(1, 6 + len + 1, 'C');

        sprintf(buf_ao, "%4umV  ", mv);
        OLED_ShowString(2, 6, buf_ao);

        sprintf(buf_adc, "%4u    ", adc);
        OLED_ShowString(3, 6, buf_adc);

        /* 阻值按 kΩ 显示，一位小数：10000Ω -> "10.0k" */
        ohm_k10 = ohm / 100;
        sprintf(buf_rt, "%u.%uk  ", (unsigned int)(ohm_k10 / 10), (unsigned int)(ohm_k10 % 10));
        OLED_ShowString(4, 6, buf_rt);

        /* 串口：sprintf 拼好整行再发，不经过 printf，不依赖 MicroLIB */
        sprintf(line, "T=%sC AO=%umV ADC=%u Rt=%uR OFS=%sC\r\n",
                buf_temp, mv, adc, (unsigned int)ohm, buf_ofs);
        Serial_SendString(line);

        Delay_ms(500);
    }
}
