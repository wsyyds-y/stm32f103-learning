#ifndef __OLED_H
#define __OLED_H

/**
  ******************************************************************************
  * @file    OLED.h
  * @brief   0.96 寸 OLED（SSD1306，128x64）显示驱动 —— 对外接口
  *
  * 硬件连接（软件 I2C，见 OLED.c 顶部宏定义）：
  *   SCL -> PB8
  *   SDA -> PB9
  *   若实际接线不同，改 OLED.c 里的 OLED_W_SCL / OLED_W_SDA 两个宏即可
  *
  * 坐标约定：整个屏幕按 8x16 点阵字符划分为 4 行 x 16 列
  *   Line   行号，从 1 开始，范围 1~4
  *   Column 列号，从 1 开始，范围 1~16
  * 注意：位置参数都是从 1 开始，不是从 0
  ******************************************************************************
  */

/* 初始化 OLED：配置 I2C 引脚并发送 SSD1306 的初始化命令序列。
 * 调用一次即可，之后才能显示内容；上电后屏幕可能是花屏，通常紧接着调 OLED_Clear()。 */
void OLED_Init(void);

/* 清屏：把 128x64 的显存全部写 0，屏幕变空白（不会关闭显示）。 */
void OLED_Clear(void);

/* 在指定位置显示一个字符（8x16 点阵，占 1 列）。
 * Line   行位置 1~4
 * Column 列位置 1~16
 * Char   要显示的字符，只支持 ASCII 可见字符（' ' ~ '~'），中文不支持 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);

/* 从指定位置开始显示字符串（逐字符调用 OLED_ShowChar，占用的列数 = 字符串长度）。
 * Line   起始行位置 1~4
 * Column 起始列位置 1~16
 * String 要显示的字符串，必须以 '\0' 结尾，只支持 ASCII 可见字符
 * 例：OLED_ShowString(1, 1, "Num:"); */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);

/* 显示无符号十进制整数（高位补 0，不省略前导零）。
 * Line   起始行位置 1~4
 * Column 起始列位置 1~16
 * Number 要显示的数字，范围 0~4294967295
 * Length 显示位数（固定宽度），范围 1~10；长度不够会截断高位
 * 例：OLED_ShowNum(1, 5, num, 5);  // num=12 时显示 "00012" */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/* 显示带符号十进制整数：先显示 '+' 或 '-'，后面再跟 Length 位数字。
 * Line   起始行位置 1~4
 * Column 起始列位置 1~16
 * Number 要显示的数字，范围 -2147483648~2147483647
 * Length 数字位数（不含符号位），范围 1~10；符号 + 数字共占 Length+1 列
 * 例：OLED_ShowSignedNum(1, 5, -25, 3);  // 显示 "-025" */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/* 显示十六进制整数（大写字母 A~F，高位补 0，不带 0x 前缀）。
 * Line   起始行位置 1~4
 * Column 起始列位置 1~16
 * Number 要显示的数字，范围 0~0xFFFFFFFF
 * Length 显示位数，范围 1~8
 * 例：OLED_ShowHexNum(2, 1, 0x1A, 2);  // 显示 "1A" */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/* 显示二进制整数（高位补 0，不带 0b 前缀）。
 * Line   起始行位置 1~4
 * Column 起始列位置 1~16
 * Number 要显示的数字，范围 0~0xFFFF
 * Length 显示位数，范围 1~16
 * 例：OLED_ShowBinNum(3, 1, 0x05, 4);  // 显示 "0101" */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
