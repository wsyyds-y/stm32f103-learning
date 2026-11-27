#include "stm32f10x.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @file    Serial.c
  * @brief   USART1 串口驱动，115200-8-N-1，printf 重定向
  *
  * 只做发送（TX）；接收中断本工程用不到，故未开启。
  ******************************************************************************
  */

/* 初始化 USART1：PA9=TX 复用推挽，PA10=RX 浮空输入，115200 波特率。 */
void Serial_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

/* 发送一个字节：先等 TXE（发送数据寄存器空），再写 DR。 */
void Serial_SendByte(uint8_t byte)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, byte);
}

/* 发送字符串：逐字节调用 Serial_SendByte，遇到 '\0' 结束。 */
void Serial_SendString(char *str)
{
    uint16_t i = 0;

    while (str[i] != '\0')
    {
        Serial_SendByte((uint8_t)str[i]);
        i++;
    }
}

/* 发送指定长度的数据：按数组下标逐个发，不受 0x00 影响。 */
void Serial_SendArray(uint8_t *data, uint16_t len)
{
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        Serial_SendByte(data[i]);
    }
}

/* printf 重定向：标准库的 printf 最终会一个字符一个字符地调用 fputc，
 * 这里把它接到 USART1，于是 printf("...") 就能直接输出到串口助手。
 * 需要工程使用标准库（Keil 默认）而不是 MicroLIB；若不勾 MicroLIB 也无所谓，
 * 两者写法都兼容。 */
int fputc(int ch, FILE *f)
{
    (void)f;
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, (uint8_t)ch);
    return ch;
}
