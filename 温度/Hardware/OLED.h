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
  *
  * 中英文尺寸不同：英文/数字是 8x16 点阵（占 1 列），汉字是 16x16 点阵（占 2 列 x 2 行）。
  * 所以显示汉字时 Column 最大到 15，且一个汉字会压住它下面那一行的一部分。
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

/* 显示一个汉字（16x16 点阵，占 2 列 x 2 行，即右下两行的空间）。
 * Line   行位置 1~4
 * Column 列位置 1~15（汉字宽 16 像素，第 16 列放不下）
 * Index  字库序号 1~OLED_CHINESE_FONT_NUM，序号见 OLED_ChineseFont.h 里每个字后的注释
 * 例：OLED_ShowChinese(1, 1, 1);  // 显示字库里的第 1 个字
 * 注意：汉字只能显示字库里已收录的字，换字要用 tools/oled-font-gen.py 重新生成字库 */
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t Index);

/* 显示中英文混排的字符串（ASCII 占 1 列，汉字占 2 列，自动往后排）。
 * Line   起始行位置 1~4
 * Column 起始列位置 1~16，超出右边界的部分自动截断
 * String 要显示的字符串，必须以 '\0' 结尾，源文件必须保存为 UTF-8 编码
 * 例：OLED_ShowChineseString(1, 1, "温度:25C");
 * 注意：字库里没有的汉字会显示成 '?'，说明需要重新生成字库把它加进去 */
void OLED_ShowChineseString(uint8_t Line, uint8_t Column, char *String);

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
