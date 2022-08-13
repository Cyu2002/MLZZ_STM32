#ifndef _CO2_IIC_H
#define _CO2_IIC_H

#include "main.h"
//SCL:PB7  SDA:PB6
//#define SDA_IN()  {GPIOB->MODER&=~(3<<(6*2));GPIOB->MODER|=0<<6*2;}	//PB9����ģʽ
//#define SDA_OUT() {GPIOB->MODER&=~(3<<(6*2));GPIOB->MODER|=1<<6*2;} //PB9���ģʽ
//IO����
#define IIC_SCL(x)   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,x)
#define IIC_SDA(x) 	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,x)
#define READ_SDA 		 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)

//IIC���в�������			 
void CO2_IIC_Start(void);				//����IIC��ʼ�ź�
void CO2_IIC_Stop(void);	  			//����IICֹͣ�ź�
void CO2_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CO2_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 CO2_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CO2_IIC_Ack(void);					//IIC����ACK�ź�
void CO2_IIC_NAck(void);				//IIC������ACK�ź�

#endif