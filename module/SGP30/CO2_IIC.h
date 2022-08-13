#ifndef _CO2_IIC_H
#define _CO2_IIC_H

#include "main.h"
//SCL:PB7  SDA:PB6
//#define SDA_IN()  {GPIOB->MODER&=~(3<<(6*2));GPIOB->MODER|=0<<6*2;}	//PB9输入模式
//#define SDA_OUT() {GPIOB->MODER&=~(3<<(6*2));GPIOB->MODER|=1<<6*2;} //PB9输出模式
//IO操作
#define IIC_SCL(x)   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,x)
#define IIC_SDA(x) 	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,x)
#define READ_SDA 		 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)

//IIC所有操作函数			 
void CO2_IIC_Start(void);				//发送IIC开始信号
void CO2_IIC_Stop(void);	  			//发送IIC停止信号
void CO2_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 CO2_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 CO2_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void CO2_IIC_Ack(void);					//IIC发送ACK信号
void CO2_IIC_NAck(void);				//IIC不发送ACK信号

#endif