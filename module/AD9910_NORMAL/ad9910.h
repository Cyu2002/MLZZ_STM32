#ifndef __AD9910_H__
#define __AD9910_H__

#include "stm32f4xx.h"

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int

//新增IO
//#define SDO PAout(4)
//#define PDCLK PCout(6)//PDCLK
//#define PLL_LOCK PCout(7)//悬空
//#define SYNC_CLK PCout(9)//悬空
//#define TXENABLE PCout(11)//TXEN
//#define RSO PCout(12)//RAM-SWP-OVR
#define AD9910_PWR PCout(12)//0
//原始IO


#define AD9910_SDIO PAout(5)
#define DRHOLD PCout(1)
#define DROVER PCout(2)
#define UP_DAT PCout(3)
#define PROFILE1 PCout(10)//PF1
#define MAS_REST PAout(6)//RST
#define SCLK PAout(2)//
#define DRCTL  PAout(4)//
#define OSK PCout(11)
#define PROFILE0 PCout(4)
#define PROFILE2 PCout(5)
#define CS  PBout(10)// CSB

//void Init_AD9910(void);  //INIT 9910 
//void AD9910WriteByte (unsigned char commond, unsigned char *databyte,unsigned char lengh);
void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_Amp_set(u32 Freq,float Amp);										//写频率
//void Write_Amplitude(bit Channel,unsigned int Amplitude);	//写幅度

#endif
