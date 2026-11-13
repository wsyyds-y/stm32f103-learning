#ifndef __ENCODER_H
#define __ENCODER_H

void Encoder_Init(void);
int16_t Encoder_GetCount(void);

#endif


//#ifndef __ENCODER_H
//#define __ENCODER_H

///* 编码器模块的对外接口。
// *
// * 说明：这里用到了 int16_t 这种类型，它是在 stm32f10x.h 里定义的。
// * 目前能编译过，是因为 main.c 先包含了 stm32f10x.h。
// * 更稳妥的写法是在本文件开头加一行 #include "stm32f10x.h"，
// * 这样单独包含 Encoder.h 也不会报错（头文件里都有防重复包含的保护，放心加）。 */

///* 取走"这一段时间内编码器转动的增量"，同时把内部计数清零。
// * 返回值：正数 = 正转，负数 = 反转，0 = 没动 */
//int16_t Encoder_Get(void);

///* 初始化 PB0 / PB1 为外部中断输入，必须在 while(1) 之前调用一次 */
//void Encoder_Init(void);

///* 下面两行其实没必要写在这里：
// * EXTI0_IRQHandler / EXTI1_IRQHandler 是中断服务函数，
// * 由硬件自动调用，没有任何地方需要"先声明再调用"它们，
// * 放在头文件里反而容易误以为要被手动调用。
// * 保留着不影响编译，也可以直接删掉。 */
//void EXTI0_IRQHandler(void);
//void EXTI1_IRQHandler(void);

//#endif
