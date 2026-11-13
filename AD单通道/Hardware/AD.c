#include "stm32f10x.h"                  // 设备头文件：所有寄存器和库函数的声明都在这里
#include "Delay.h"   


void ad_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	 
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  /* 配置ADC时钟分频器 */



	GPIO_InitTypeDef GPIO_InitStructue;
	GPIO_InitStructue.GPIO_Mode =GPIO_Mode_AIN ;
	GPIO_InitStructue.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructue);


    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);  /* 配置ADC规则通道 */
	

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  /* 独立模式 */
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;  /* 扫描模式关闭 */
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  /* 连续转换模式开启 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  /* 外部触发关闭 */
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  /* 数据右对齐 */
    ADC_InitStructure.ADC_NbrOfChannel = 1;  /* 转换通道数为1 */
    ADC_Init(ADC1,&ADC_InitStructure);  /* 根据结构体参数初始化ADC */

    ADC_Cmd(ADC1,ENABLE);  /* 使能ADC */

    ADC_ResetCalibration(ADC1);  /* 复位校准寄存器 */
    while(ADC_GetResetCalibrationStatus(ADC1));  /* 等待复位校准完成 */

    ADC_StartCalibration(ADC1);  /* 开始校准 */
    while(ADC_GetCalibrationStatus(ADC1));  /* 等待校准完成 */



}

uint16_t ad_start(void)
{
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);  /* 软件启动ADC转换 */
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);  /* 等待转换结束 */

    return ADC_GetConversionValue(ADC1);

}

