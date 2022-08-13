#ifndef __RDA5807_H
#define __RDA5807_H
#include "myiic2.h"   
#include "sys.h"


extern u16 RXFreq;
extern u8 Vol;
extern u8 RDA_State;
extern u16 add;

//#define SPK_PIN        GPIO_PIN_5
//#define SPK_PORT       GPIOF
//#define SPK_R GPIO_WriteReverse(SPK_PORT,SPK_PIN);

//RDA 的寄存器地址
#define RDA_R02		0X02  //DHIZ[15],DMUTE[14]静音,MONO[13]声道,BASS[12]重低音,SEEKUP[9],SEEK[8],SKMODE[7],CLK_MODE[6:4]时钟源选择,SOFTRESET[1]软复位,ENABLE[0]电源使能
#define RDA_R03		0X03  //CHAN[15:6],TUNE[4],BAND[3:2],SPACE[1:0] 设置频率 带宽 步长
#define RDA_R04		0X04  //STCIEN[14],DE[11],I2Senable[6],
#define RDA_R05		0X05  //INT_MODE[15],SEEKTH[14:8](设定自动搜索信号强度阀值),LNA_PORT_SEL[7:6]=0b10,LNA_ICSEL_BIT[5:4],VOLUME[3:0]音量;
#define RDA_R0A		0X0A  //STC[14]seek complete SF[13]seek fail readchan[9:0]当前频道
#define RDA_R0B		0X0B  //RSSI[15:9],FM TRUE[8]当前频道是一个节目台
#define RDA_R0E   0X0E
#define RDA_READ        0x23  //读RDA5807
#define RDA_WRITE	0x22  //写RDA5807

u16 RDA_ReadReg(u8 regAddr); 
void RDA_WriteReg(u8 regAddr,u16 val);
void RDA_Init(void);
void RDA_Enable(void);
u16  RDA_RSSI(void);
void RDA_Seek_Direction(u8 direction);
u16  RDA_Search_Freq(void);
void RDA_Set_Freq(u16 freq);
void RDA_Freq_Down(void);
void RDA_Freq_Up(void);
//void RDA_Freq_View(u16 freq);
void RDA_Vol(u8 vol);
void RDA_Vol_Big(void);
void RDA_Vol_Small(void);
void RDA_SPK(void);

#endif

