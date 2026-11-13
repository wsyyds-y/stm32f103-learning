#include "stm32f10x.h"
#include "Encoder.h"
#include "OLED.h"
#include "Delay.h"

int main(void)
{
    Encoder_Init();
    OLED_Init();
   
    while (1)
    {
        OLED_ShowSignedNum(1, 1, Encoder_GetCount(), 5);
        Delay_ms(1000);

    }
}
    
