#include "stm32f10x.h"
#include "serial.h"
#include "OLED.h"




int main(void)
{

    uint8_t data[] = "Hello, World!"; // 要发送的数据
    uint16_t size = sizeof(data) - 1; // 数据大小，不包括字符串

   OLED_Init(); // 初始化OLED显示屏
   serial_init(); // 初始化串口
   serial_send(data, size); // 发送数据

    while (1)    /* 主循环 */
    {
    }
}



