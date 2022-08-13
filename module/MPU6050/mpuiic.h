#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "sys.h"

//����ԭ��MPU6050ͨѶ������
	   		   
//IO��������
#define MPU_SDA_IN()  {GPIOC->MODER&=0xFFFF3FFF;GPIOC->MODER|=(u32)0<<14;}
#define MPU_SDA_OUT() {GPIOC->MODER&=0xFFFF3FFF;GPIOC->MODER|=(u32)1<<14;}


//IO��������	 
#define MPU_IIC_SCL    PCout(6) 		//SCL 
#define MPU_IIC_SDA    PCout(7) 		//SDA	 
#define MPU_READ_SDA   PCin(7) 		//����SDA PB2

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
