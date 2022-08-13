
#ifndef _AD9833_H
#define _AD9833_H
#include "main.h"

#define Sine_Wave     0X2008	//���Ҳ�
#define Triangle_Wave 0x2002	//���ǲ�
#define Square_Wave   0x2028	//����

#define AD9834_MCLK 75000000UL	//AD9834����Ƶ��

//���ƽ�A3-A6��FS��PS��B0,B1ֱ���õͣ��ɿ���λ����

#define AD9834_FSYNC_SET		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,1)

#define AD9834_FSYNC_CLR   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,0)

#define AD9834_SCLK_SET			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1) 

#define AD9834_SCLK_CLR			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0) 

#define AD9834_SDATA_SET   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,1) 

#define AD9834_SDATA_CLR   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,0)

#define AD9834_RESET_SET   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1) 

#define AD9834_RESET_CLR   	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0)

#define AD9834_FS_SET       HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,1)

#define AD9834_FS_CLR       HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,0)

#define AD9833_PS_SET				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,1)

#define AD9833_PS_CLR				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,0)



//Ƶ�ʼĴ���
#define FREQ_0      0 

#define FREQ_1      1 

/* AD9834�������� */ 

void AD9834_Write_Data(unsigned int data);			 //д16λ����

void AD9834_Select_Wave(unsigned int initdata) ;   //ѡ��������� 

void AD9834_Init(void);  													 //��ʼ������ 

void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq) ;		//ѡ������Ĵ��������Ƶ��ֵ 
	
#endif