#include "stm32f10x.h"
#include <stdio.h>
#include "Delay.h"
#include "OLED.h"
#include "NTC.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @file    main.c
  * @brief   NTC 温度模块（AO + DO）实时显示
  *
  * 注意：本工程的 OLED 驱动用的是 AD单通道 里已在实物上验证过的版本，
  *       只支持 ASCII，因此界面文字全部用英文，不再依赖中文点阵字库。
  ******************************************************************************
  */

/* 把 0.1℃ 的整数格式化成 "25.3C   " 这样的字符串（尾部补空格覆盖旧内容）。
 * buf 至少 12 字节；负数会带 '-'（如 -55 -> "-5.5C"）。 */
static void FormatTemp(char *buf, int16_t temp_x10)
{
    int16_t abs_val = (temp_x10 < 0) ? (int16_t)(-temp_x10) : temp_x10;

    sprintf(buf, "%s%d.%dC   ", (temp_x10 < 0) ? "-" : "", abs_val / 10, abs_val % 10);
}

int main(void)
{
    uint16_t adc;
    uint16_t adc_sum;
    uint16_t mv;
    int16_t temp_x10;
    uint8_t alarm;
    uint8_t i;
    char buf_temp[16];
    char buf_ao[12];
    char buf_adc[8];

    /* 先初始化 OLED 并立刻写死标签：即使后面 ADC/串口哪里卡住，
     * 屏幕也应该能看到这四行标签，便于判断是显示问题还是采样问题。 */
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "TEMP:");
    OLED_ShowString(2, 1, "DO:");
    OLED_ShowString(3, 1, "AO:");
    OLED_ShowString(4, 1, "ADC:");

    Serial_Init();
    NTC_Init();

    printf("NTC module demo start\r\n");

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

        FormatTemp(buf_temp, temp_x10);
        OLED_ShowString(1, 6, buf_temp);                /* "TEMP:" 占 1~5 列 */

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

        printf("T=%s AO=%umV ADC=%u DO=%s\r\n",
               buf_temp, mv, adc, alarm ? "ALARM" : "NORMAL");

        Delay_ms(500);
    }
}
