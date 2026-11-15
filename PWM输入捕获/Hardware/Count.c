#include "stm32f10x.h"                  // 设备头文件：所有寄存器和库函数的声明都在这里
#include "Delay.h"                      // 用到 Delay_ms()，所以要把延时的头文件包含进来

/* ============================================================================
 * 全局变量
 * ==========================================================================*/

/* 遮挡次数。
 * static   ：只能在本文件（Count.c）里使用，别的文件看不到，避免重名冲突
 * volatile ：告诉编译器"这个变量的值可能被中断随时改掉"，
 *            所以每次都老老实实去内存里读，不许优化成寄存器缓存。
 *            中断和主循环共享的变量必须加它，否则可能出现"数字不刷新"的怪现象
 * uint16_t ：无符号 16 位整数，范围 0 ~ 65535，够计数用 */
static volatile uint16_t Coun = 0;

/* 消抖用的"锁"。
 * 1 = 本次遮挡已经计过数了，抖动产生的后续中断不再重复计数
 * 0 = 光束已经恢复（人把手拿开了），允许下一次遮挡重新计数
 * 只表示 0 和 1 两种状态，所以用最小的 uint8_t（范围 0 ~ 255）就够了 */
static volatile uint8_t Count_Lock = 0;


/* ============================================================================
 * 初始化函数：配置 PB14 为外部中断输入
 *
 * 整体流程（记住这四步，以后配任何引脚中断都一样）：
 *   ① 开时钟      —— 不给外设供电，写它的寄存器是无效的
 *   ② 配 GPIO     —— 把引脚设成输入模式
 *   ③ 配 EXTI     —— 选择触发边沿（上升沿/下降沿），把引脚和中断线连起来
 *   ④ 配 NVIC     —— 打开中断通道，让 CPU 真正能响应它
 * ==========================================================================*/
void Coint_Init(void)
{
	/* ---------- ① 开启时钟 ---------- */
	/* STM32 的外设默认是"断电"状态，用之前必须先使能它的时钟。
	 * GPIOB   ：因为我们要用 PB14 这个引脚
	 * APB2    ：GPIOA~GPIOE 都挂在 APB2 总线上，所以用 APB2PeriphClockCmd */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	/* AFIO 是"复用功能 IO"，只有两件事会用到它：
	 *   ① 引脚重映射  ② 配置外部中断 EXTI 的引脚来源
	 * 我们下面要用 GPIO_EXTILineConfig，所以必须先开 AFIO 的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	/* ---------- ② 配置 GPIO ---------- */
	/* GPIO_InitTypeDef 是库定义好的一个"参数打包结构体"，
	 * 我们只要把成员的成员填好，再交给 GPIO_Init() 一次性写进寄存器，
	 * 就不用自己去算那些二进制位了（这就是标准库的作用） */
	GPIO_InitTypeDef GPIO_InitStructue;                //初始化GPIO
	/* 工作模式：IPU = Input Pull-Up = 上拉输入。
	 * 上拉的意思是芯片内部接了一个电阻到 3.3V，
	 * 引脚悬空时读到 1，被外部拉低时读到 0。
	 * 红外对射模块的输出通常是"集电极开路/开漏"型，必须靠上拉才能得到高电平，
	 * 所以这里用上拉输入（如果模块输出是强推挽，用 IPU 也没坏处） */
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_IPU ;
	/* 指定要配置哪几个引脚：GPIO_Pin_14 就是 PB14。
	 * 多个引脚可以按位或写，比如 GPIO_Pin_1 | GPIO_Pin_11 */
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_14;
	/* 输出速度。这个成员只对"输出模式"有意义，
	 * 我们这里是输入模式，填什么都无所谓，写 50MHz 是照抄模板的习惯 */
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	/* 把上面填好的参数应用到 GPIOB 上，这一步才真正写进寄存器 */
	GPIO_Init(GPIOB,&GPIO_InitStructue);
	
	/* ---------- ③ 配置 EXTI 外部中断 ---------- */
	/* 关键的一步：EXTI 只有 16 条中断线 EXTI0~EXTI15，
	 * 而每个端口（PA/PB/PC...）都有 PA14、PB14、PC14……
	 * 也就是说 EXTI14 这条线同一时刻只能接一个端口，必须"选择"一次。
	 * 这行代码的意思：把 EXTI14 这条中断线接到 GPIOB 上。
	 * 注意它靠的就是上面开的 AFIO 时钟 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	/* 下面开始填 EXTI 的参数结构体 */
	EXTI_InitTypeDef EXTI_InitStructue;					//设置中断
	/* 使用哪条中断线：EXTI_Line14，对应刚才的 PB14 */
	EXTI_InitStructue.EXTI_Line = EXTI_Line14;
	/* 使能这条线（ENABLE = 打开，DISABLE = 关闭） */
	EXTI_InitStructue.EXTI_LineCmd = ENABLE;
	/* 中断模式：EXTI_Mode_Interrupt = 产生中断，去执行中断服务函数；
	 * 另一个可选值是 EXTI_Mode_Event = 只产生事件，不中断（给别的外设用） */
	EXTI_InitStructue.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 触发方式，共 4 种：
	 *   EXTI_Trigger_Rising       上升沿（低 -> 高）触发  ← 本工程用这个
	 *   EXTI_Trigger_Falling      下降沿（高 -> 低）触发
	 *   EXTI_Trigger_Rising_Falling  两个边沿都触发
	 *   EXTI_Trigger_...           （用 DISABLE 关闭）
	 * 如果实测发现"遮挡不加数、松手才加数"，说明模块极性相反，
	 * 把这里改成 EXTI_Trigger_Falling，并把下面中断里的判断一起反过来 */
	EXTI_InitStructue.EXTI_Trigger = EXTI_Trigger_Rising;
	/* 把参数写进 EXTI 寄存器 */
	EXTI_Init(&EXTI_InitStructue);
	
	
	
	/* ---------- ④ 配置 NVIC 中断控制器 ---------- */
	/* 光配好 EXTI 还不够！EXTI 只是"发出请求"，
	 * 真正决定 CPU 要不要理会这个请求的是 NVIC（嵌套向量中断控制器）。
	 * 没配 NVIC 的话，中断永远不会进，这是初学者最常踩的坑 */
	
	/* 优先级分组：决定"抢占优先级"和"响应(子)优先级"各占几个二进制位。
	 * NVIC_PriorityGroup_0 表示：0 位给抢占优先级，4 位给子优先级。
	 * 也就是"大家都不许互相打断，谁先来谁先服务"。
	 * 注意这是整个芯片的全局设置，只需要在程序里设置一次；
	 * 只用了 1 个中断时，用 Group_0 最简单。
	 * （因为 Group_0 下抢占优先级恒为 0，所以下面填的 0 其实没起作用） */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* 填 NVIC 参数结构体 */
	NVIC_InitTypeDef NVIC_InitStructue;
	/* 要开哪个中断通道。函数名必须和它对应：
	 * 中断线 EXTI10 ~ EXTI15 共用同一个中断入口 EXTI15_10_IRQHandler，
	 * 所以这里填 EXTI15_10_IRQn（注意末尾的 n） */
	NVIC_InitStructue.NVIC_IRQChannel = EXTI15_10_IRQn;
	/* 使能这个通道，打开 = 允许 CPU 响应 */
	NVIC_InitStructue.NVIC_IRQChannelCmd = ENABLE;
	/* 抢占优先级：数字越小级别越高，高的可以打断低的。
	 * Group_0 下这一项被忽略 */
	NVIC_InitStructue.NVIC_IRQChannelPreemptionPriority =0 ;
	/* 子优先级（响应优先级）：抢占级相同时才比它，数字越小越优先。
	 * 只有一个中断时，填什么都不会影响实验 */
	NVIC_InitStructue.NVIC_IRQChannelSubPriority = 1;
	/* 写进 NVIC 寄存器，到此中断配置全部完成 */
	NVIC_Init(&NVIC_InitStructue);
}


/* ============================================================================
 * 读取当前计数值，给主循环显示用
 * 写成函数的好处：主循环不需要知道 Coun 是什么类型、放在哪
 * ==========================================================================*/
uint16_t Count_Get(void)
{
	return Coun ;
}


/* ============================================================================
 * 主循环里反复调用的"后台任务"
 * 作用：检测光束是否已经恢复。
 * 中断里只会"上锁"，解锁必须靠这个函数，否则遮挡一次之后就再也不计数了。
 * 这里不能放在中断里做，因为"松手"这个过程本身也可能带抖动，
 * 交给主循环慢慢轮询最省事也最稳
 * ==========================================================================*/
/* 在主循环里反复调用：光束恢复（未遮挡）时解除锁定，为下一次遮挡做准备 */
void Count_Task(void)
{
	/* 读到 0 说明引脚被拉低 = 光束恢复/没人遮挡 = 可以给下一次遮挡计数了 */
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
	{
		Count_Lock = 0;
	}
}


/* ============================================================================
 * 中断服务函数
 *
 * 函数名不能乱起！必须是启动文件 startup_stm32f10x_md.s 里
 * __Vectors 表中写好的名字 EXTI15_10_IRQHandler，
 * 否则中断发生时 CPU 找不到函数，会跳进启动文件里的死循环。
 * 特点：① 没有返回值 ② 没有参数 ③ 由硬件自动调用，谁都不许手动调用
 * ==========================================================================*/
//中断函数
void EXTI15_10_IRQHandler(void)
{/* 先判断"是不是 EXTI14 这条线真的触发了"。
  * 因为 EXTI10~EXTI15 共用一个入口，PB10 ~ PB15 任何一个中断都会进这里，
  * EXTI_GetITStatus() 读的是挂起标志位（Pending），返回 SET 表示确实有请求。
  * 写成 if 而不是直接干活，是为了防止"别的线触发、却误加了我的数" */
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		/* 必须清标志！这个标志位硬件置 1 之后不会自动归零，
		 * 不清的话函数一返回，硬件发现标志还在，立刻又进来一次 —— 死循环，
		 * 主程序再也跑不动（现象：OLED 卡死、数字乱跳） */
		EXTI_ClearITPendingBit(EXTI_Line14);		//先清标志，避免退出后立刻又进来

		/* 消抖第一层：本次遮挡如果已经计过数，就直接跳过。
		 * 抖动会在几毫秒内产生十几个边沿，但都落在这把锁的保护期内 */
		if (Count_Lock == 0)						//本次遮挡还没计过数
		{
			/* 消抖第二层：等 20ms 让信号稳定下来。
			 * 中断里做延时平时不推荐（会卡住主程序），
			 * 但这里只有 20ms，而且能保证后面那次电平判断读到的是稳定值，
			 * 对你这个实验来说是最简单可靠的做法 */
			Delay_ms(20);							//等抖动过去（10~50ms 都可）

			/* 稳定之后再确认一次：20ms 后引脚还是高电平，
			 * 才说明这是真遮挡；如果只是干扰毛刺，这时候早就掉回低电平了，
			 * 于是这个数就不会被误加 */
			/* 20ms 后电平仍然是高，说明是真的被遮挡，而不是干扰毛刺 */
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1)
			{
				Coun ++;							//确认无误，计数加一
				Count_Lock = 1;						//上锁：抖动产生的后续中断不再计数
			}
		}
	}
}
