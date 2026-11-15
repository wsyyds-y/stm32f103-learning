#include "stm32f10x.h"
#include "serial.h"
#include "OLED.h"
#include <string.h>


int main(void)
{

    uint8_t data[] = "ABCDEF"; // 要发送的数据
    uint16_t size = sizeof(data) - 1; // 数据大小，不包括字符串
  

   OLED_Init(); // 初始化OLED显示屏
   serial_init(); // 初始化串口
   serial_send(data, size); // 发送数据


   //printf("\r\n你好, World!%d\n", 123); // 使用printf发送数据
    char buffer[50];
    sprintf(buffer, "你好, World!%d\n", 123); // 使用sprintf
    serial_send(buffer, strlen(buffer)); // 发送格式化后的数据
    sprintf((char *)data, "你好, World!%d\n", 123); // 使用sprintf格式化数据
    serial_send(data, strlen((char *)data)); // 发送格式化后的数据


    while (1)    /* 主循环 */
    {
    }
}



