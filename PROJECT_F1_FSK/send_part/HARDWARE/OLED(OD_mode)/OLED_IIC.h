#ifndef _OLED_IIC_H
#define _OLED_IIC_H



#include "main.h"
#include "gpio.h"
//SCL:PD10 SDA:PD9
#define SCL_L HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET)
#define SCL_H HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET)

#define SDA_L HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET)
#define SDA_H HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET)

#define SDA_read HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_9)

#define true 1
#define false 0 
#define bool uint8_t
	
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�





#endif