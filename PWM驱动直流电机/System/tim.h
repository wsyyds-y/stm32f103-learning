#ifndef __TIM__H
#define __TIM__H

void tim_init(void);

void TIM2_IRQHandler(void);

extern volatile uint16_t num;   /* 中断里累加的计数值，main 里要读它显示 */

#endif 

