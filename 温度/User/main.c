#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "Delay.h"
#include "OLED.h"
#include "ChipTemp.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @file    main.c
  * @brief   STM32F103 片内温度传感器测温：OLED 显示 + 串口输出 + 心跳
  *
  * 显示（4 行 × 16 列）：
  *   TEMP: 25.3°C     平滑后的温度
  *   VSEN: 1428mV     内部传感器输出电压（原始量，判断准不准看它）
  *   ADC : 1773       12 位原始码值
  *   OFS : +0.0°C     编译进固件的修正量，对着标准温度计改 ChipTemp.c
  *
  * 串口每 500ms 一行：T=25.3C VSEN=1428mV ADC=1773 OFS=+0.0C
  *
  * 为什么不用那块 4 脚 MH 模块：它背面是 TCRT5000 红外反射式光电开关，
  * AO 随反射光变化（遮住就掉、毫秒级响应、吹气不动），测不了温度。
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

/* 把 0.1 单位的定点数格式化成 "25.3"（不带单位）。
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
    int16_t temp_x10;
    int16_t offset_x10;
    int32_t filt_x10 = 0;
    uint8_t filt_ready = 0;
    uint8_t len;
    char buf_temp[16];
    char buf_vsen[12];
    char buf_adc[10];
    char buf_ofs[12];
    char line[64];

    /* 上电先闪两下心跳（也给 OLED 留出上电稳定的时间），再点屏写标签。 */
    Heartbeat_Init();
    Heartbeat_Toggle();
    Delay_ms(250);
    Heartbeat_Toggle();
    Delay_ms(250);

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "TEMP:");
    OLED_ShowString(2, 1, "VSEN:");
    OLED_ShowString(3, 1, "ADC :");

    Serial_Init();
    ChipTemp_Init();

    Serial_SendString("\r\n[CHIPTEMP] STM32F103 internal sensor\r\n");
    Serial_SendString("T = 25 + (1430mV - VSEN) / 4.3mV\r\n");

    /* 修正量是编译期常量，开机画一次即可（要改就改 ChipTemp.c 里的宏） */
    offset_x10 = ChipTemp_GetOffsetX10();
    FormatX10(buf_ofs, offset_x10, 1);
    OLED_ShowString(4, 1, "OFS :");
    OLED_ShowString(4, 7, buf_ofs);
    len = (uint8_t)strlen(buf_ofs);
    OLED_ShowDegree(4, 7 + len);
    OLED_ShowChar(4, 7 + len + 1, 'C');

    while (1)    /* 主循环：每 500ms 采一次并刷新显示 */
    {
        /* 8 次平均压噪声；内部传感器噪声约 ±1 码，平均后末位不跳 */
        adc = ChipTemp_ReadAdcAve(8);
        mv = ChipTemp_AdcToMv(adc);
        temp_x10 = ChipTemp_AdcToTempX10(adc);

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

        sprintf(buf_vsen, "%4umV  ", mv);
        OLED_ShowString(2, 6, buf_vsen);

        sprintf(buf_adc, "%4u    ", adc);
        OLED_ShowString(3, 6, buf_adc);

        /* 串口：sprintf 拼好整行再发，不经过 printf，不依赖 MicroLIB */
        sprintf(line, "T=%sC VSEN=%umV ADC=%u OFS=%sC\r\n",
                buf_temp, mv, adc, buf_ofs);
        Serial_SendString(line);

        Heartbeat_Toggle();
        Delay_ms(500);
    }
}
