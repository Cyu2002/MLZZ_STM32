#ifndef __AD9910_H__
#define __AD9910_H__

#include "main.h"

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int

//????IO
//#define SDO PAout(4)
//#define PDCLK PCout(6)//PDCLK
//#define PLL_LOCK PCout(7)//????
//#define SYNC_CLK PCout(9)//????
//#define TXENABLE PCout(11)//TXEN
//#define RSO PCout(12)//RAM-SWP-OVR
#define AD9910_PWR(x) 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,x)
//?'IO


#define AD9910_SDIO(x) 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,x)
#define AD9910_DRHOLD(x) 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,x)
#define AD9910_DROVER(x) 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,x) 
#define AD9910_UP_DAT(x) 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,x) 
#define AD9910_PROFILE1(x)		 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,x) //PF1
#define AD9910_MAS_REST(x) 		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,x)//RST
#define AD9910_SCLK(x) 				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,x)//
#define AD9910_DRCTL(x)  			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,x)//
#define AD9910_OSK(x) 					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,x)
#define AD9910_PROFILE0(x) 		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,x) 
#define AD9910_PROFILE2(x) 		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,x)
#define AD9910_CS(x)  					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,x)// CSB

void Init_ad9910(void);
void Freq_convert(ulong Freq);                                                            //写频率
void Amp_convert(unsigned int Amplitude);                                                 //写幅度
void Txramdata(int wave_num);                                                             //任意波形发生，参数：波形序号1-2
void Square_wave(uint Sample_interval);                                                   //方波;
void Sawtooth_wave(uint Sample_interval);                                                 //三角波
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime); //扫频：Hz, Hz,Hz,us

void Set_RefCLK_OUT(uint8_t mode);

void Txcfr(void);
void AD9910_ram_Init(void);
void TxRAMFM(void);
void Tx32bite(uint32_t data);
void FM_DATA_GET(ulong FRE_CAR);

#endif
