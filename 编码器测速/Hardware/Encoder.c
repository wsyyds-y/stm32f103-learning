#include "stm32f10x.h"  







void Encoder_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);




    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_Period = 65536 - 1;
    TIM_InitStruct.TIM_Prescaler = 0;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_InitStruct);

    TIM_ICInitTypeDef TIM_ICInitStruct;
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;  
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter = 0x0F;
    TIM_ICInit(TIM3, &TIM_ICInitStruct);
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;  
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter = 0x0F;
    TIM_ICInit(TIM3, &TIM_ICInitStruct);


    TIM_CCPreloadControl(TIM3, ENABLE);
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3, ENABLE);


}

int16_t Encoder_GetCount(void)
{   
    int16_t count = (int16_t)TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0);
    return count ;
}



























































































































//#include "stm32f10x.h"                  // 设备头文件：寄存器和库函数的声明都在这里


///* ============================================================================
// * 全局变量
// * ==========================================================================*/

///* 编码器计数（带方向的计数值，可以是负数，所以用有符号的 int16_t）。
// *
// * 注意：这个变量有一个隐患 —— 中断里改它，主循环里读它，
// * 按规范应该加 volatile（和 Count.c 里的 Coun 一样），
// * 否则编译器可能把它缓存进寄存器，出现"转动旋钮但数字不更新"的怪现象。
// * 这里先保持你原来的写法，等你确认要改我再一起处理。
// *
// * 范围 -32768 ~ 32767，转得太多会溢出回绕。 */
//volatile int16_t Encoder_Count;


///* ============================================================================
// * 初始化函数：配置 PB0、PB1 两个引脚为外部中断输入
// *
// * 硬件背景：
// *   旋转编码器（或另一组对射/霍尔传感器）有两路输出 A、B，接到 PB0 和 PB1。
// *   转动时两路会输出相位差 90° 的方波，靠"谁先跳变"就能判断转向。
// *
// * 整体流程（记住这四步，以后配任何引脚中断都一样）：
// *   ① 开时钟      —— 不给外设供电，写它的寄存器是无效的
// *   ② 配 GPIO     —— 把引脚设成输入模式
// *   ③ 配 EXTI     —— 选择触发边沿，把引脚和中断线连起来
// *   ④ 配 NVIC     —— 打开中断通道，让 CPU 真正能响应它
// *
// * 函数名说明：Encodetr 应为 Encoder_Init（拼写笔误），
// * 要改的话 .h 和 main.c 里的调用处要一起改，这里先不动。
// * ==========================================================================*/
//void Encoder_Init(void)
//{
//	/* ---------- ① 开启时钟 ---------- */
//	/* STM32 的外设默认是"断电"状态，用之前必须先使能它的时钟。
//	 * GPIOB ：因为我们要用 PB0 和 PB1 这两个引脚
//	 * APB2  ：GPIOA~GPIOE 都挂在 APB2 总线上，所以用 APB2PeriphClockCmd */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
//	/* AFIO 是"复用功能 IO"，只有两件事会用到它：
//	 *   ① 引脚重映射  ② 配置外部中断 EXTI 的引脚来源
//	 * 我们下面要用 GPIO_EXTILineConfig，所以必须先开 AFIO 的时钟 */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//	/* ---------- ② 配置 GPIO ---------- */
//	/* GPIO_InitTypeDef 是库定义好的一个"参数打包结构体"，
//	 * 我们把成员填好，再交给 GPIO_Init() 一次性写进寄存器，
//	 * 就不用自己去算那些二进制位了（这就是标准库的作用） */
//	GPIO_InitTypeDef GPIO_InitStructue;                //初始化GPIO
//	/* 工作模式：IPU = Input Pull-Up = 上拉输入。
//	 * 上拉的意思是芯片内部接了一个电阻到 3.3V，
//	 * 引脚悬空时读到 1，被外部拉低时读到 0。
//	 * 编码器一般是"开关对地"或"集电极开路"输出，本身不会输出高电平，
//	 * 必须靠上拉电阻才能得到稳定的高电平，所以这里用上拉输入 */
//	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_IPU ;
//	/* 要配置哪几个引脚：GPIO_Pin_0 是 PB0（A 相），GPIO_Pin_1 是 PB1（B 相）。
//	 * 多个引脚用按位或 "|" 连起来，这样一次就能把两个引脚配成同样的模式，
//	 * 等于省掉了再写一遍 GPIO_Init() 的功夫 */
//	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//	/* 输出速度。这个成员只对"输出模式"有意义，
//	 * 我们这里是输入模式，填什么都无所谓，写 50MHz 是照抄模板的习惯 */
//	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
//	/* 把上面填好的参数应用到 GPIOB 上，这一步才真正写进寄存器 */
//	GPIO_Init(GPIOB,&GPIO_InitStructue);
//	
//	/* ---------- ③ 配置 EXTI 外部中断 ---------- */
//	/* 关键的一步：EXTI 只有 16 条中断线 EXTI0~EXTI15，
//	 * 而每个端口（PA/PB/PC...）都有 PA0、PB0、PC0……
//	 * 也就是说 EXTI0 这条线同一时刻只能接一个端口，必须"选择"一次。
//	 * 这两行的意思：
//	 *   把 EXTI0 这条中断线接到 GPIOB 上（也就是接 PB0）
//	 *   把 EXTI1 这条中断线接到 GPIOB 上（也就是接 PB1）
//	 * 注意它靠的就是上面开的 AFIO 时钟 */
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
//	
//	/* 下面开始填 EXTI 的参数结构体 */
//	EXTI_InitTypeDef EXTI_InitStructue;					//设置中断
//	/* 使用哪两条中断线：EXTI_Line0 对应 PB0，EXTI_Line1 对应 PB1。
//	 * 同样用 "|" 把两条线合并在一次配置里 */
//	EXTI_InitStructue.EXTI_Line = EXTI_Line1|EXTI_Line0;
//	/* 使能这两条线（ENABLE = 打开，DISABLE = 关闭） */
//	EXTI_InitStructue.EXTI_LineCmd = ENABLE;
//	/* 中断模式：EXTI_Mode_Interrupt = 产生中断，去执行中断服务函数；
//	 * 另一个可选值是 EXTI_Mode_Event = 只产生事件，不中断（给别的外设用） */
//	EXTI_InitStructue.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* 触发方式（这里因为是两条线一起配置的，所以两路用的是同一种边沿）：
//	 *   EXTI_Trigger_Falling  下降沿（高 -> 低）触发   ← 本工程两路都用这个
//	 *   EXTI_Trigger_Rising   上升沿（低 -> 高）触发
//	 *   EXTI_Trigger_Rising_Falling  两个边沿都触发
//	 * 编码器判断方向只需要一路的"一个边沿"，所以下降沿足够。
//	 * 注意：如果改成 Rising_Falling（两个边沿都触发），
//	 * 计数会翻倍，想接就自己在中断里把方向判断逻辑改对 */
//	EXTI_InitStructue.EXTI_Trigger = EXTI_Trigger_Falling;
//	/* 把参数写进 EXTI 寄存器 */
//	EXTI_Init(&EXTI_InitStructue);
//	
//	
//	
//	/* ---------- ④ 配置 NVIC 中断控制器 ---------- */
//	/* 光配好 EXTI 还不够！EXTI 只是"发出请求"，
//	 * 真正决定 CPU 要不要理会这个请求的是 NVIC（嵌套向量中断控制器）。
//	 * 没配 NVIC 的话，中断永远不会进，这是初学者最常踩的坑。
//	 * 这里要开两个通道：EXTI0 一个、EXTI1 一个，所以下面写了两次 NVIC_Init() */
//	
//	/* 优先级分组：决定"抢占优先级"和"响应(子)优先级"各占几个二进制位。
//	 * NVIC_PriorityGroup_0 表示：0 位给抢占优先级，4 位给子优先级。
//	 * 也就是"大家都不许互相打断，谁先来谁先服务"。
//	 * 注意这是整个芯片的全局设置，只需要设置一次；
//	 * 因为选的是 Group_0，下面填的抢占优先级 0 和 1 其实都不起作用，
//	 * 两个中断谁也无法打断谁，只能排队 */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	
//	/* 填 NVIC 参数结构体（下面两个通道共用这一个结构体，
//	 * 每次改完成员变量就调用一次 NVIC_Init()，不要重复定义结构体） */
//	NVIC_InitTypeDef NVIC_InitStructue;
//	/* 要开哪个中断通道。中断线和通道名是一一对应的：
//	 * EXTI0 单独用一个入口 EXTI0_IRQHandler，所以这里填 EXTI0_IRQn */
//	NVIC_InitStructue.NVIC_IRQChannel = EXTI0_IRQn;
//	/* 使能这个通道，打开 = 允许 CPU 响应 */
//	NVIC_InitStructue.NVIC_IRQChannelCmd = ENABLE;
//	/* 抢占优先级：数字越小级别越高，高的可以打断低的。
//	 * Group_0 下这一项被忽略 */
//	NVIC_InitStructue.NVIC_IRQChannelPreemptionPriority =0 ;
//	/* 子优先级（响应优先级）：抢占级相同时才比它，数字越小越优先。
//	 * 两个通道同时挂起时，子优先级小的先执行 */
//	NVIC_InitStructue.NVIC_IRQChannelSubPriority = 1;
//	/* 写进 NVIC 寄存器，EXTI0 通道配置完成 */
//	NVIC_Init(&NVIC_InitStructue);
//	
//	
//	/* 第二个通道：EXTI1（PB1 那一侧） */
//	NVIC_InitStructue.NVIC_IRQChannel = EXTI1_IRQn;
//	/* 使能这个通道，打开 = 允许 CPU 响应 */
//	NVIC_InitStructue.NVIC_IRQChannelCmd = ENABLE;
//	/* 抢占优先级：数字越小级别越高，高的可以打断低的。
//	 * Group_0 下这一项被忽略 */
//	NVIC_InitStructue.NVIC_IRQChannelPreemptionPriority =1 ;
//	/* 子优先级（响应优先级）：抢占级相同时才比它，数字越小越优先 */
//	NVIC_InitStructue.NVIC_IRQChannelSubPriority = 2;
//	/* 写进 NVIC 寄存器，EXTI1 通道配置完成，到此中断配置全部结束 */
//	NVIC_Init(&NVIC_InitStructue);

//}


///* ============================================================================
// * 读取编码器"这一段时间内转了多少格"，读完就把计数清零
// *
// * 主循环每隔一小会儿调用一次，把返回值累加到自己的 Num 上，
// * 这样即使编码器转得很快也不会漏数（不是"读当前值"，而是"取走增量"）。
// * ==========================================================================*/
//int16_t Encoder_Get(void)
//{

//	int16_t one;              // 临时变量，用来保存"取走"的数值
//	one = Encoder_Count;      // 先取出当前累计的增量
//	Encoder_Count = 0;        // 立刻清零，下一次从 0 重新累计
//	return one; 

//	/* 小提示：这两行如果是"取出后、清零前"刚好来了一个中断，
//	 * 那一格就会丢。严格的做法是关中断再操作：
//	 *   __disable_irq(); one = Encoder_Count; Encoder_Count = 0; __enable_irq();
//	 * 现在的写法实验基本看不出问题，先了解有这回事即可 */
//}


///* ============================================================================
// * 中断服务函数 —— A 相（PB0）的下降沿
// *
// * 两个要点：
// *   ① 函数名不能乱起！必须是启动文件 startup_stm32f10x_md.s 里
// *      向量表中写好的 EXTI0_IRQHandler，否则硬件找不到它，
// *      会跳进启动文件的死循环，程序就像卡死一样。
// *   ② EXTI0 和 EXTI1 各有一个独立入口，不像 EXTI10~15 那样五个共用一个。
// * ==========================================================================*/
//void EXTI0_IRQHandler(void)
//{	
//	/* 判断方向的经典做法：A 相跳变的时候，去读 B 相此刻的电平。
//	 * B 相为低 → 这一格是"反转"，计数减一
//	 * B 相为高 → 这一格是"正转"，计数加一（在下面的 EXTI1 里处理） */
//	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
//	{
//	
//		Encoder_Count -- ;         // 反转：倒着转的一格
//	
//	}
//	/* 必须清标志！标志位硬件置 1 后不会自动归零，
//	 * 不清的话函数一返回就立刻又进来，主程序再也跑不动
//	 * （现象：OLED 卡死、数字疯狂乱跳） */
//	EXTI_ClearITPendingBit(EXTI_Line0);
//	

//}


///* ============================================================================
// * 中断服务函数 —— B 相（PB1）的下降沿
// * 逻辑和上面完全对称，只是读的是另一路的电平、清的是 EXTI_Line1 的标志
// * ==========================================================================*/
//void EXTI1_IRQHandler(void)
//{
//	/* B 相跳变时读 A 相（PB0）的电平，为低说明是正转方向 */
//	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
//	{
//	
//		Encoder_Count ++ ;
//	
//	}
//	/* 清 EXTI1 的挂起标志，理由同上 */
//	EXTI_ClearITPendingBit(EXTI_Line1);
//	

//}
