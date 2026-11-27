#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"
#include <stdio.h>

/**
  ******************************************************************************
  * @file    Serial.h
  * @brief   USART1 串口驱动（115200-8-N-1）—— 对外接口
  *
  * 硬件连接：
  *   PA9  -> USART1_TX -> USB 转串口模块的 RX
  *   PA10 -> USART1_RX -> USB 转串口模块的 TX
  *   GND  -> GND（必须共地）
  *
  * 重定向了 fputc，所以可以直接用 printf 往串口发字符串。
  ******************************************************************************
  */

/* 初始化 USART1：PA9 复用推挽输出、PA10 浮空输入，波特率 115200。 */
void Serial_Init(void);

/* 发送一个字节（阻塞到发送寄存器空）。 */
void Serial_SendByte(uint8_t byte);

/* 发送以 '\0' 结尾的字符串。 */
void Serial_SendString(char *str);

/* 发送一段指定长度的数据（可含 0x00，适合发 HEX 数据包）。 */
void Serial_SendArray(uint8_t *data, uint16_t len);

#endif
