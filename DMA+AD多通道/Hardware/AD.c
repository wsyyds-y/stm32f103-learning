#include "stm32f10x.h"                  // 设备头文件：所有寄存器和库函数的声明都在这里
#include "Delay.h"   
 
uint16_t AddrB[2];  /* DMA 目标地址数组，必须是全局变量或静态变量 */

void AD_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  /* 使能 DMA1 时钟 */
	 
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  /* 配置ADC时钟分频器 */



	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_AIN ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructue);

    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);  /* 配置ADC规则通道 */
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);  /* 配置ADC规则通道 */


	

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  /* 独立模式 */
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;  /* 扫描模式开启 */
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  /* 连续转换模式关闭 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  /* 外部触发关闭 */
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  /* 数据右对齐 */
    ADC_InitStructure.ADC_NbrOfChannel = 2;  /* 转换通道数为2    */
    ADC_Init(ADC1,&ADC_InitStructure);  /* 根据结构体参数初始化ADC */
  

    DMA_InitTypeDef DMA_InitStructure;  /* DMA 初始化结构体 */

    DMA_DeInit(DMA1_Channel1);  /* 先把通道 1 的寄存器复位为默认值 */

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;  /* 外设地址即源地址 a，注意不能写成 &AddrA */
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AddrB;  /* 存储器地址即目标地址 b，不能写成 &AddrB */
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  /* 方向：外设（a）→ 存储器（b） */
    DMA_InitStructure.DMA_BufferSize = 2;  /* 转运字节数，由调用者传入，不能用 sizeof(形参) */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  /* 源地址自增 */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  /* 目标地址自增 */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  /* 源数据宽度 16 位 */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  /* 目标数据宽度 16 位 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  /* 普通模式：搬完一次就停 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  /* 优先级高 */
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  /* 软件触发必须开 M2M，否则永远等不到请求 */

    DMA_Init(DMA1_Channel1, &DMA_InitStructure);  /* 写入通道 1 的配置寄存器 */


    DMA_Cmd(DMA1_Channel1, ENABLE);  /* 先不启动，等 MyDMA_Transfer() 来触发 */

    ADC_DMACmd(ADC1, ENABLE);  /* 使能ADC的DMA请求 */

    ADC_Cmd(ADC1,ENABLE);  /* 使能ADC */

    ADC_ResetCalibration(ADC1);  /* 复位校准寄存器 */
    while(ADC_GetResetCalibrationStatus(ADC1));  /* 等待复位校准完成 */

    ADC_StartCalibration(ADC1);  /* 开始校准 */
    while(ADC_GetCalibrationStatus(ADC1));  /* 等待校准完成 */



}

void AD_start(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);  /* 关闭DMA传输 */
    DMA_SetCurrDataCounter(DMA1_Channel1, 2);  /* 设置传输字节数为 2 */
    DMA_Cmd(DMA1_Channel1, ENABLE);  /* 启动DMA传输 */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);  /* 软件启动ADC转换 */

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);  /* 等待传输完成 */

    DMA_ClearFlag(DMA1_FLAG_TC1);  /* 清标志，便于下次判断 */       
}


