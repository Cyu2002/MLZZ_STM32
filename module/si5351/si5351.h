/********************************************
????:STM32F405RGT6??168Mhz
????:HSE=8Mhz  SYSCLK=168Mhz
????:STM32?????
????:
????:Si5351????
??:???
??:??????,????
********************************************/
#ifndef _si5351a_h
#define _si5351a_h


#include "main.h"


//Si5351?????
#define SI_CLK0_CONTROL	16			// Register definitions
#define SI_CLK1_CONTROL	17
#define SI_CLK2_CONTROL	18
#define SI_SYNTH_PLL_A	26
#define SI_SYNTH_PLL_B	34
#define SI_SYNTH_MS_0		42
#define SI_SYNTH_MS_1		50
#define SI_SYNTH_MS_2		58
#define SI_PLL_RESET		177

#define SI_R_DIV_1		0x00			// R-division ratio definitions
#define SI_R_DIV_2		0x10
#define SI_R_DIV_4		0x20
#define SI_R_DIV_8		0x30
#define SI_R_DIV_16		0x40
#define SI_R_DIV_32		0x50
#define SI_R_DIV_64		0x60
#define SI_R_DIV_128		0x70
#define SI_CLK_SRC_PLL_A	0x00
#define SI_CLK_SRC_PLL_B	0x20
#define XTAL_FREQ	25000000			// Crystal frequency
//IIC??????
#define SDA(n) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,n)
#define CLK(n) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,n)
//??????
void Si5351Init(void);//???Si5351?GPIO
void SetPLLClk(uint8_t pll, uint8_t mult, uint32_t num, uint32_t denom);//??PPL??
void SetFrequency(uint32_t frequency);//??Si5351????
void SetMultisynth(uint8_t synth,uint32_t divider,uint8_t rDiv);//???synth
#endif