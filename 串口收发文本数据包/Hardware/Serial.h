#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"		//提供 uint8_t 等类型定义，保证本头文件可独立包含
#include <stdio.h>
extern uint8_t Serial_TX [4];
extern char Serial_RX[100];	
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
void Serial_SendPacket(void);
uint8_t Serial_GetRxFlag(void);


#endif
