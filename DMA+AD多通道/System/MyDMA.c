#include "stm32f10x.h"

uint16_t MyDMA_Size;  /* 保存配置时的转运字节数，重装计数器时要用 */

/**
 * @brief  配置 DMA1 通道 1，在存储器到存储器（M2M）模式下把 AddrA 处的 Size 个字节搬到 AddrB
 * @param  AddrA 源地址，调用时传数组 a 的地址 (uint32_t)a
 * @param  AddrB 目标地址，调用时传数组 b 的地址 (uint32_t)b
 * @param  Size  要转运的字节数，调用时传 sizeof(a)
 * @retval 无
 * @note   本函数只做配置，不启动转运；启动请调用 MyDMA_Transfer()
 */
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  /* 使能 DMA1 时钟 */

    DMA_InitTypeDef DMA_InitStructure;  /* DMA 初始化结构体 */

    DMA_DeInit(DMA1_Channel1);  /* 先把通道 1 的寄存器复位为默认值 */

    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;  /* 外设地址即源地址 a，注意不能写成 &AddrA */
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;  /* 存储器地址即目标地址 b，不能写成 &AddrB */
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  /* 方向：外设（a）→ 存储器（b） */
    DMA_InitStructure.DMA_BufferSize = Size;  /* 转运字节数，由调用者传入，不能用 sizeof(形参) */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;  /* 源地址自增 */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  /* 目标地址自增 */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  /* 源数据宽度 8 位 */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  /* 目标数据宽度 8 位 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  /* 普通模式：搬完一次就停 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  /* 优先级高 */
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;  /* 软件触发必须开 M2M，否则永远等不到请求 */

    DMA_Init(DMA1_Channel1, &DMA_InitStructure);  /* 写入通道 1 的配置寄存器 */

    MyDMA_Size = Size;  /* 记下长度，供 Transfer 重新装载 */
    DMA_Cmd(DMA1_Channel1, DISABLE);  /* 先不启动，等 MyDMA_Transfer() 来触发 */
}

/**
 * @brief  启动一次 DMA 转运，并等待传输完成
 * @param  无
 * @retval 无
 * @note   普通模式下搬完 CNDTR 会归零、通道自动停止，所以每次转运前都要重装计数器再使能
 */
void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);  /* 改计数器前必须先关闭通道 */
    DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);  /* 重装传输数量 */
    DMA_ClearFlag(DMA1_FLAG_TC1);  /* 清掉上一次的传输完成标志 */
    DMA_Cmd(DMA1_Channel1, ENABLE);  /* 使能通道，M2M 模式下立即开始搬运 */

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);  /* 等待传输完成 */

    DMA_ClearFlag(DMA1_FLAG_TC1);  /* 清标志，便于下次判断 */
}
