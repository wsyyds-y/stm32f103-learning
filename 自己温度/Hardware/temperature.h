#ifndef __TEMPERATURE__H
#define __TEMPERATURE__H



void temperature__init(void);//温度初始化函数


float dianya_init(uint16_t a);//算电压


float dianzu_init(float b);//算电阻

float wendu_init(float c);//算温度


uint16_t zhuanhuan(void);//开始读取码值

int16_t suan_init(void);




#endif




