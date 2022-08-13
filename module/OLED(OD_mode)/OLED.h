#ifndef _OLED_H_
#define _OLED_H_


#include "OLED_IIC.h"
#include "delay.h"
#include "main.h"

extern uint8_t RevState;
extern unsigned char brightness;



#define OLED_ADDRESS	0x78 //????0R??,???0x78?0x7A???? -- ??0x78




void OLED_Init();
void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch, unsigned char TextSize);
int OLED_ShowInt(unsigned char x, unsigned char y, int val, unsigned char TextSize);
void OLED_ShowRevStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowRevChar(unsigned char x, unsigned char y, unsigned char ch, unsigned char TextSize);
void OLED_SetBrightness(unsigned char val);
void OLED_Reverse(void);
int OLED_ShowFloat(unsigned char x, unsigned char y, double val, unsigned char TextSize);




#endif
