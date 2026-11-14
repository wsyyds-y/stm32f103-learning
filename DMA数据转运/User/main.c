#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t a [] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};  /* 定义一个8字节的数组a */
uint8_t b [] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  /* 定义一个8字节的数组b，并初始化为全零 */




int main(void)
{
    OLED_Init();  /* 初始化OLED显示屏 */
  

    OLED_ShowHexNum(1, 1, a[0], 2);  /* 在OLED上显示数组a的第一个元素 */
    OLED_ShowHexNum(1, 4, a[1], 2);  /* 在OLED上显示数组a的第二个元素 */
    OLED_ShowHexNum(1, 7, a[2], 2);  /* 在OLED上显示数组a的第三个元素 */
    OLED_ShowHexNum(1, 10, a[3], 2);  /* 在OLED上显示数组a的第四个元素 */
    OLED_ShowHexNum(2, 1, b[0], 2);  /* 在OLED上显示数组b的第一个元素 */
    OLED_ShowHexNum(2, 4, b[1], 2);  /* 在OLED上显示数组b的第二个元素 */
    OLED_ShowHexNum(2, 7, b[2], 2);  /* 在OLED上显示数组b的第三个元素 */
    OLED_ShowHexNum(2, 10, b[3], 2);  /* 在OLED上显示数组b的第四个元素 */

    MyDMA_Init((uint32_t)a, (uint32_t)b, sizeof(a));  /* 配置DMA：源a、目标b、长度sizeof(a)=8字节 */
    MyDMA_Transfer();  /* 启动转运并等待完成，这一步之后b里才是a的数据 */

      
    OLED_ShowHexNum(3, 1, a[0], 2);  /* 在OLED上显示数组a的第一个元素 */
    OLED_ShowHexNum(3, 4, a[1], 2);  /* 在OLED上显示数组a的第二个元素 */
    OLED_ShowHexNum(3, 7, a[2], 2);  /* 在OLED上显示数组a的第三个元素 */
    OLED_ShowHexNum(3, 10, a[3], 2);  /* 在OLED上显示数组a的第四个元素 */
    OLED_ShowHexNum(4, 1, b[0], 2);  /* 在OLED上显示数组b的第一个元素 */
    OLED_ShowHexNum(4, 4, b[1], 2);  /* 在OLED上显示数组b的第二个元素 */
    OLED_ShowHexNum(4, 7, b[2], 2);  /* 在OLED上显示数组b的第三个元素 */
    OLED_ShowHexNum(4, 10, b[3], 2);  /* 在OLED上显示数组b的第四个元素 */



    while (1)    /* 主循环 */
    {
    }
}


