#ifndef _MLX90614_H
#define _MLX90614_H
//#include "stm8s.h"
#include "main.h"

#define ACK	 0
#define	NACK 1  //不应答或否定的应答
#define SA				0x00 //从机地址，单个MLX90614时地址为0x00,多个时地址默认为0x5a
#define RAM_ACCESS		0x00 //RAM access command
#define EEPROM_ACCESS	0x20 //EEPROM access command
#define RAM_TOBJ1		0x07 //To1 address in the eeprom

#include "delay.h"

#define SMBUS_SDA_INPUT()  HAL_GPIO_WritePin(GPIO_SDA,GPIO_PIN_SDA,1)
#define SMBUS_SDA_PIN HAL_GPIO_ReadPin(GPIO_SDA, GPIO_PIN_SDA)

#define SMBUS_SCK_H HAL_GPIO_WritePin(GPIO_SCL,GPIO_PIN_SCL,1)
#define SMBUS_SCK_L HAL_GPIO_WritePin(GPIO_SCL,GPIO_PIN_SCL,0)
#define SMBUS_SDA_H HAL_GPIO_WritePin(GPIO_SDA,GPIO_PIN_SDA,1)
#define SMBUS_SDA_L HAL_GPIO_WritePin(GPIO_SDA,GPIO_PIN_SDA,0)

#define u8 uint8_t
#define u16 uint16_t
#define delay_us Delay_us
#define GPIO_SCL GPIOD
#define GPIO_PIN_SCL GPIO_PIN_2
#define GPIO_SDA GPIOD
#define GPIO_PIN_SDA GPIO_PIN_3
#define READ_SDA   HAL_GPIO_ReadPin(GPIO_SDA, GPIO_PIN_SDA)


void SMBus_StartBit(void);
void SMBus_StopBit(void);
void SMBus_SendBit(unsigned char);
unsigned char SMBus_SendByte(unsigned char);
unsigned char SMBus_ReceiveBit(void);
unsigned char SMBus_ReceiveByte(unsigned char);
void SMBus_Delay(unsigned int);
void MLX90614_SMBus_Init(void);
unsigned int SMBus_ReadMemory(unsigned char, unsigned char);
unsigned char PEC_Calculation(unsigned char*);
float SMBus_ReadTemp(void);    //获取温度值


void MLX_IIC_Start(void);				//发送IIC开始信号
void MLX_IIC_Stop(void);	  			//发送IIC停止信号
void MLX_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 MLX_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 MLX_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MLX_IIC_Ack(void);					//IIC发送ACK信号
void MLX_IIC_NAck(void);				//IIC不发送ACK信号


#endif

