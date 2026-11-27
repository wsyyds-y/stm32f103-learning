#include "stm32f10x.h"
#include "OLED_Font.h"
#include "OLED_ChineseFont.h"

/*引脚配置*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(x))

/*引脚初始化*/
void OLED_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(!!(Byte & (0x80 >> i)));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  UTF-8 解码：把字符串中当前位置的一个字符解成 Unicode 码点
  * @param  String 指向字符串中当前字符的指针
  * @param  Length 输出参数，返回这个字符占用了几个字节（ASCII 为 1，汉字为 3）
  * @retval 解码出的 Unicode 码点；编码非法时返回 0xFFFD（替换符）
  * @note   仅内部使用。源文件必须是 UTF-8 编码，GBK 编码的字符串解不出来。
  */
static uint16_t OLED_Utf8Decode(const char *String, uint8_t *Length)
{
	uint8_t b0 = (uint8_t)String[0];

	if (b0 < 0x80)							//单字节，就是 ASCII
	{
		*Length = 1;
		return b0;
	}
	if ((b0 & 0xE0) == 0xC0 && ((uint8_t)String[1] & 0xC0) == 0x80)	//双字节（拉丁文扩展等）
	{
		*Length = 2;
		return ((uint16_t)(b0 & 0x1F) << 6) | ((uint8_t)String[1] & 0x3F);
	}
	if ((b0 & 0xF0) == 0xE0									//三字节，汉字走这一支
		&& ((uint8_t)String[1] & 0xC0) == 0x80
		&& ((uint8_t)String[2] & 0xC0) == 0x80)
	{
		*Length = 3;
		return ((uint16_t)(b0 & 0x0F) << 12)
			 | ((uint16_t)((uint8_t)String[1] & 0x3F) << 6)
			 | ((uint8_t)String[2] & 0x3F);
	}
	*Length = 1;							//非法编码，跳过一个字节继续
	return 0xFFFD;
}

/**
  * @brief  在汉字字库里按 Unicode 码点查找字模
  * @param  Code 要查找的汉字 Unicode 码点
  * @retval 找到返回字模记录的指针；字库里没有这个字则返回 0
  * @note   仅内部使用。查表是逐条比对的，字库越大越慢，一次显示几十个汉字仍然很快。
  */
static const OLED_ChineseFont_TypeDef *OLED_FindChinese(uint16_t Code)
{
	uint16_t i;
	for (i = 0; i < OLED_CHINESE_FONT_NUM; i++)
	{
		if (OLED_ChineseFont16x16[i].Code == Code)
		{
			return &OLED_ChineseFont16x16[i];
		}
	}
	return 0;
}

/**
  * @brief  按字模数据画一个 16x16 汉字
  * @param  Line   行位置，范围：1~4
  * @param  Column 列位置，范围：1~15（汉字占 2 列，第 16 列放不下）
  * @param  Data   32 字节的字模数据，前 16 字节上半部分，后 16 字节下半部分
  * @retval 无
  * @note   仅内部使用。汉字高 16 像素，要分两个 Page 写，所以 Line 会占用两行的高度。
  */
static void OLED_ShowChineseFont(uint8_t Line, uint8_t Column, const uint8_t *Data)
{
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);				//光标移到上半部分
	for (i = 0; i < 16; i++)
	{
		OLED_WriteData(Data[i]);									//上半部分 16 列
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);			//光标移到下半部分
	for (i = 0; i < 16; i++)
	{
		OLED_WriteData(Data[i + 16]);								//下半部分 16 列
	}
}

/**
  * @brief  OLED显示一个汉字（按字库序号取字）
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~15（汉字占 2 列 x 2 行）
  * @param  Index 字库序号，范围：1~OLED_CHINESE_FONT_NUM
  * @retval 无
  * @note   序号就是 OLED_ChineseFont.h 里每个字后面的注释编号。
  *         汉字占右下两行的空间，会覆盖该位置原来的内容，显示前一般先 OLED_Clear()。
  */
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t Index)
{
	if (Index < 1 || Index > OLED_CHINESE_FONT_NUM)				//序号越界就不显示，避免读到字库外面
	{
		return;
	}
	OLED_ShowChineseFont(Line, Column, OLED_ChineseFont16x16[Index - 1].Data);
}

/**
  * @brief  OLED显示混合字符串（中英文混排）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，必须以 '\0' 结尾
  * @retval 无
  * @note   ASCII 字符用 8x16 字库、占 1 列；汉字用 16x16 字库、占 2 列并往下占 2 行。
  *         字库里没有的汉字显示为 '?'，所以调用前要先确认字库收录了要显示的字。
  *         源文件必须是 UTF-8 编码。超出屏幕右边界的部分自动截断。
  */
void OLED_ShowChineseString(uint8_t Line, uint8_t Column, char *String)
{
	uint16_t i = 0;							//用 16 位，字符串再长也不会回绕
	uint8_t Length;
	uint16_t Code;
	const OLED_ChineseFont_TypeDef *Font;

	while (String[i] != '\0')
	{
		Code = OLED_Utf8Decode(&String[i], &Length);
		if (Code < 0x80)										//ASCII 字符，按 8x16 显示
		{
			if (Column > 16) break;
			OLED_ShowChar(Line, Column, (char)Code);
			Column += 1;
		}
		else													//汉字，按 16x16 查表显示
		{
			if (Column > 15) break;
			Font = OLED_FindChinese(Code);
			if (Font != 0)
			{
				OLED_ShowChineseFont(Line, Column, Font->Data);
			}
			else
			{
				OLED_ShowChar(Line, Column, '?');				//字库没收录，显示问号提示
			}
			Column += 2;
		}
		i += Length;
	}
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//端口初始化
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
		
	OLED_Clear();				//OLED清屏
}
