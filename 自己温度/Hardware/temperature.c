#include "stm32f10x.h"
#include "math.h"
#include "temperature.h"



void temperature__init(void)//温度初始化函数

{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode= DISABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   /* 右对齐：12 位结果直接放低 12 位，和 /4095 配套 */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode =ADC_Mode_Independent ;
    ADC_InitStructure.ADC_NbrOfChannel =1 ;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;

    ADC_Init(ADC1,&ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

float dianya_init(uint16_t a)//算电压
{

    return (float)a / 4095.0f * 3.3f;   /* 必须转 float：整型相除会把 2048/4095 算成 0 */

}

float dianzu_init(float b)//算电阻
{
    if (b < 0.02f)                b = 0.02f;
    if (b >3.28f)     b = 3.28f;
    return 10000.0f * b / (3.3f - b);   /* 上拉电阻 10k 不能漏：Rt = Rs·V/(3.3−V) */
}
float wendu_init(float c)//算温度
{
    return 1.0f / (1.0f /  298.15f  + logf(c /  10000.0f) / 3950.0f) - 273.15f;
}

uint16_t zhuanhuan(void)//开始读取码值
{
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

int16_t suan_init(void)
{
    int16_t t10;
    float a;
    float b;
    float c;
    uint32_t sum = 0;                    /* 必须初始化：否则从栈上垃圾值开始累加 */
    uint8_t i;

    for (i = 0; i < 8; i++)              /* 循环变量用 i，别和上面的 float a 重名 */
    {
        sum += zhuanhuan();
    }
    a = dianya_init((uint16_t)(sum / 8));
    b = dianzu_init(a);
    c = wendu_init(b);

    t10 = (int32_t)roundf(c * 10.0f);

    return (int16_t)t10;
}






