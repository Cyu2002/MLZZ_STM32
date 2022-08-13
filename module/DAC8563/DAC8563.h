#ifndef _DAC8563_H
#define _DAC8563_H

#include "main.h"

#define LD(x) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,x)
#define DIN(x) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,x)
#define CLR(x) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,x)
#define SYN(x) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,x)
#define SCK(x) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,x)

#define PWR_UP_DOWN 0x20   //power down or up
#define DAC_A_UP 0x0001
#define DAC_B_UP 0x0002
#define DAC_A_B_UP 0x0003
#define DAC_A_DOWN1 0x0011
#define DAC_B_DOWN1 0x0012
#define DAC_A_B_DOWN1 0x0013
#define DAC_A_DOWN2 0x0021
#define DAC_B_DOWN2 0x0022
#define DAC_A_B_DOWN2 0x0023
#define DAC_A_DOWN3 0x0031
#define DAC_B_DOWN3 0x0032
#define DAC_A_B_DOWN3 0x0033

#define WR_DAC_A_REG 0x00   //dac input registers
#define WR_DAC_B_REG 0x01
#define WR_DAC_A_B_REG 0x07
#define WR_DAC_A_REG_UP_ALL 0x10
#define WR_DAC_B_REG_UP_ALL 0x11
#define WR_DAC_A_B_REG_UP_ALL 0x17
#define WR_DAC_A_REG_UP_A 0x18
#define WR_DAC_B_REG_UP_B 0x19
#define WR_DAC_A_B_REG_UP_A_B 0x1F
#define UP_DAC_A 0x08
#define UP_DAC_B 0x09
#define UP_ALL_DAC 0x0F

#define GAIN_REG 0x02        //GAIN REG
#define DAC_A2_DAC_B2 0x0000
#define DAC_A1_DAC_B2 0x0001
#define DAC_A2_DAC_B1 0x0002
#define DAC_A1_DAC_B1 0x0003

#define REST_REG 0x28				//rest part
#define REST_ALL_DAC 0x0000
#define REST_ALL 0x0001



#define LDAC_REG 0x06//LDAC reg
#define LDAC_AC_A_B 0x0000
#define LDAC_AC_A 0x0002
#define LDAC_AC_B 0x0001
#define LDAC_INAC_A_B 0x0003

#define INT_REF 0x38
#define EN_INT_RET 0x0001
#define DISEN_INT_RET 0x0000

void DAC8563_Init(void);
void DAC8563_Wirtereg(u8 reg,u16 data);
void DAC8563_SetVal(u8 chinnal,float val);

#endif