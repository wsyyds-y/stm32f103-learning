#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"
#include "AD.h"



int main(void)
{
    OLED_Init();  /* 初始化OLED显示屏 */
  
    AD_init();  /* 初始化ADC和DMA */

    while (1)    /* 主循环 */
    {
        
        AD_start();  /* 启动ADC采样并通过DMA传输到AddrB数组 */
        OLED_ShowHexNum(1, 1, AddrB[0], 4);  /* 在OLED上显示AddrB数组的第一个元素 */
        OLED_ShowHexNum(4, 1, AddrB[1], 4);     /* 在OLED上显示AddrB数组的第二个元素 */
        Delay_ms(500);  /* 延时500毫秒 */


    }
}


