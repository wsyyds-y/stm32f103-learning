#include "stm32f10x.h"
#include "stdio.h"

void serial_init (void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 使能USART1时钟




    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // 选择引脚9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置引脚速度为50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 设置引脚模式为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA引脚9    

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600; // 设置波特率    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 设置数据位长度为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 设置停止位为1位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 设置无硬件流控制
    USART_InitStructure.USART_Parity = USART_Parity_No; // 设置无校验
    USART_InitStructure.USART_Mode = USART_Mode_Tx; // 设置为发送模式
    USART_Init(USART1, &USART_InitStructure); // 初始化USART1


    USART_Cmd(USART1, ENABLE); // 使能USART1

}

void serial_send (uint8_t *data, uint16_t size)
{
    
    for (uint16_t i = 0; i < size; i++)
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送缓冲区为空
        USART_SendData(USART1, data[i]); // 发送数据
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送缓冲区为空
    }
}

int fputc(int ch,FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送缓冲区为空
    USART_SendData(USART1, (uint8_t) ch); // 发送数据
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送缓冲区为空
    return ch;
}





