#include "stm32f10x.h"
#include "DS18B20.h"
#include "Delay.h"

/**
  ******************************************************************************
  * @file    DS18B20.c
  * @brief   DS18B20 单总线驱动（软件模拟 1-Wire 时序）
  *
  * 单总线的三种基本时序，全部由“主机拉低 -> 保持 -> 释放 -> 在窗口内采样”组成：
  *   复位：拉低 480us 以上，释放后 15~60us 内从机拉低 60~240us 作为“存在脉冲”
  *   写 1：拉低 1~15us 后释放，整个时隙 60us 以上
  *   写 0：拉低 60~120us 后释放
  *   读位：拉低 1us 以上后释放，15us 内采样（从机在低电平期间给出数据），再等满 60us
  * 以上时间单位为微秒，全部用 Delay_us() 实现；本工程 Delay_us 基于 SysTick，
  * 前提是系统时钟 72MHz（模板 SystemInit 默认就是 72MHz）。
  ******************************************************************************
  */

/* 单总线引脚定义：换引脚只改这三行 */
#define DS18B20_GPIO_PORT   GPIOB
#define DS18B20_GPIO_PIN    GPIO_Pin_12
#define DS18B20_GPIO_CLK    RCC_APB2Periph_GPIOB

/* 拉低 DQ（主机主动输出 0） */
#define DS18B20_DQ_LOW()    GPIO_ResetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN)
/* 释放 DQ（开漏输出 1 = 高阻，由上拉电阻把线拉高；此时仍可读回引脚电平） */
#define DS18B20_DQ_HIGH()   GPIO_SetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN)
/* 读 DQ 当前电平，非 0 表示高电平 */
#define DS18B20_DQ_READ()   GPIO_ReadInputDataBit(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN)

/* 只在本文件内部使用的位操作：写一位 / 读一位 / 写一字节 / 读一字节 */
static void DS18B20_WriteBit(uint8_t bit);
static uint8_t DS18B20_ReadBit(void);
static void DS18B20_WriteByte(uint8_t byte);
static uint8_t DS18B20_ReadByte(void);

/* 计算 Dallas/Maxim 单总线 CRC8：对前 len 字节做多项式 0x8C 的移位异或。
 * 返回 0 表示校验通过（DS18B20 把 CRC 一起发回来，把 9 字节全算一遍结果为 0）。 */
static uint8_t DS18B20_CRC8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;
    uint8_t i, j;

    for (i = 0; i < len; i++)
    {
        uint8_t byte = data[i];
        for (j = 0; j < 8; j++)
        {
            uint8_t mix = (crc ^ byte) & 0x01;
            crc >>= 1;
            if (mix)
            {
                crc ^= 0x8C;
            }
            byte >>= 1;
        }
    }
    return crc;
}

/* 初始化 DQ 引脚为开漏输出。
 * 单总线是“线与”结构，主机只能在“拉低”和“释放（高阻）”之间切换，
 * 所以必须用 GPIO_Mode_Out_OD，不能配成推挽输出，否则会和从机对拉。 */
void DS18B20_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   /* 开漏输出，可读回引脚电平 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);

    DS18B20_DQ_HIGH();   /* 空闲时释放总线，由上拉电阻保持高电平 */
}

/* 复位：拉低 480us -> 释放 -> 15us 后采样 -> 再等 480us 让存在脉冲走完。
 * 存在脉冲期间从机会把线拉低（读到 0），所以读到 0 说明器件在线。 */
uint8_t DS18B20_Reset(void)
{
    uint8_t presence;

    DS18B20_DQ_LOW();
    Delay_us(480);
    DS18B20_DQ_HIGH();
    Delay_us(15);              /* 15~60us 内是从机拉低存在脉冲的窗口 */
    presence = DS18B20_DQ_READ();
    Delay_us(480);             /* 等存在脉冲（最长 240us）结束，总线回到高电平 */

    return (presence == 0) ? 1 : 0;
}

/* 写一位：先拉低（写 1 只拉 2us，写 0 拉满 60us），再释放并补足到 60us 时隙。 */
static void DS18B20_WriteBit(uint8_t bit)
{
    DS18B20_DQ_LOW();
    if (bit)
    {
        Delay_us(2);           /* 写 1：短低脉冲，从机在 15~60us 内采样到高电平 */
        DS18B20_DQ_HIGH();
        Delay_us(60);
    }
    else
    {
        Delay_us(60);          /* 写 0：低电平保持整个时隙 */
        DS18B20_DQ_HIGH();
        Delay_us(2);           /* 释放后留一点恢复时间 */
    }
}

/* 读一位：主机拉低 2us 后释放，等 10us 再采样。
 * 从机要发 0 就会把线继续拉低，要发 1 就放开让上拉拉高。 */
static uint8_t DS18B20_ReadBit(void)
{
    uint8_t bit;

    DS18B20_DQ_LOW();
    Delay_us(2);
    DS18B20_DQ_HIGH();
    Delay_us(10);              /* 采样点要落在从机输出有效期内（拉低后 15us 内） */
    bit = DS18B20_DQ_READ();
    Delay_us(50);              /* 补满 60us 时隙，再开始下一位 */

    return bit;
}

/* 写一字节：单总线规定低位先发（LSB first）。 */
static void DS18B20_WriteByte(uint8_t byte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        DS18B20_WriteBit(byte & 0x01);
        byte >>= 1;
    }
}

/* 读一字节：同样低位先收，逐位拼回。 */
static uint8_t DS18B20_ReadByte(void)
{
    uint8_t i;
    uint8_t byte = 0;

    for (i = 0; i < 8; i++)
    {
        byte >>= 1;
        if (DS18B20_ReadBit())
        {
            byte |= 0x80;
        }
    }
    return byte;
}

/* 启动转换 + 读温度（阻塞约 750ms）。
 * 流程：复位 -> 跳过 ROM（总线上只有一个器件）-> 0x44 启动转换
 *       -> 等 750ms -> 复位 -> 跳过 ROM -> 0xBE 读暂存器 9 字节 -> CRC 校验 -> 换算。 */
uint8_t DS18B20_ReadTemp(int16_t *temp_x10)
{
    uint8_t scratchpad[9];
    uint8_t i;
    int16_t raw;
    int32_t scaled;

    if (temp_x10 == 0)
    {
        return 1;
    }

    if (DS18B20_Reset() == 0)
    {
        return 1;                        /* 没有器件应答 */
    }
    DS18B20_WriteByte(0xCC);             /* Skip ROM：总线上只有一片，不用读 64 位 ID */
    DS18B20_WriteByte(0x44);             /* Convert T：启动一次温度转换 */

    Delay_ms(750);                       /* 12 位分辨率最长需要 750ms，期间总线可做别的事 */

    if (DS18B20_Reset() == 0)
    {
        return 1;
    }
    DS18B20_WriteByte(0xCC);
    DS18B20_WriteByte(0xBE);             /* Read Scratchpad：连读 9 字节 */
    for (i = 0; i < 9; i++)
    {
        scratchpad[i] = DS18B20_ReadByte();
    }

    if (DS18B20_CRC8(scratchpad, 9) != 0)
    {
        return 2;                        /* CRC 错，数据不可信 */
    }

    /* 温度寄存器：低字节在前，12 位有符号数，最低 4 位是小数（1/16℃） */
    raw = (int16_t)(((uint16_t)scratchpad[1] << 8) | scratchpad[0]);

    /* 换算成 0.1℃ 并四舍五入：raw/16 是摄氏度，×10 后取整 */
    scaled = (int32_t)raw * 10;
    if (scaled >= 0)
    {
        scaled = (scaled + 8) / 16;
    }
    else
    {
        scaled = (scaled - 8) / 16;
    }
    *temp_x10 = (int16_t)scaled;

    return 0;
}
