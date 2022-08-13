#ifndef RDA_IIC_H
#define RDA_IIC_H


#include "main.h"

//SDA:PA11   SCL:PA12


#define true 1
#define false 0 
#define bool uint8_t

#define SCL_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET)
#define SCL_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET)

#define SDA_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET)
#define SDA_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET)

#define SDA_read HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)


void IIC_Start(void);				//????IIC??'?z?
void IIC_Stop(void);	  			//????IIC???z?
void IIC_Send_Byte(u8 txd);			//IIC????h?????
u8 IIC_Read_Byte(unsigned char ack);//IIC???h?????
u8 IIC_Wait_Ack(void); 				//IIC???ACK?z?
void IIC_Ack(void);					//IIC????ACK?z?
void IIC_NAck(void);				//IIC??????ACK?z?



#endif