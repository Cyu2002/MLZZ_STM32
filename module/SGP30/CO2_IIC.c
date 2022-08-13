#include "CO2_IIC.h"
#include "delay.h"

void CO2_IIC_Start(void){
	IIC_SCL(1);
	IIC_SDA(1);
	Delay_us(1);
	IIC_SDA(0);
	Delay_us(1);
	IIC_SCL(0);
	Delay_us(1);
}
void CO2_IIC_Stop(void){
	IIC_SCL(0);
	IIC_SDA(0);
	Delay_us(1);
	IIC_SCL(1);
	Delay_us(1);
	IIC_SDA(1);
	Delay_us(2);
}
void CO2_IIC_Send_Byte(u8 txd){
	u8 t;
	IIC_SCL(0);
	for(t=0;t<8;t++){
		IIC_SDA((txd&0x80)>>7);
		txd<<=1;
		Delay_us(2);
		IIC_SCL(1);
		Delay_us(2);
		IIC_SCL(0);
		Delay_us(2);
	}
}	
u8 CO2_IIC_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	IIC_SDA(1);
	for(i=0;i<8;i++){
		IIC_SCL(0);
		Delay_us(2);
		IIC_SCL(1);
		receive<<=1;
		if(READ_SDA)receive++;
		Delay_us(1);
	}
	  if (!ack)
        CO2_IIC_NAck();//·¢ËÍnACK
    else
        CO2_IIC_Ack(); //·¢ËÍACK   
    return receive;
}
u8 CO2_IIC_Wait_Ack(void){
	  uint16_t waitTime = 0;
  uint8_t result = 0;
  IIC_SDA(1);
  IIC_SCL(0);
  Delay_us(1);
  IIC_SCL(1);
  Delay_us(2); // data setup time
  result = READ_SDA;
  Delay_us(1);
  IIC_SCL(0);
  Delay_us(1); // data setup time & SCL_LOW & SMBus requirement
  if (result == 1)
    CO2_IIC_Stop();
  return result;
}
void CO2_IIC_Ack(void){
	IIC_SCL(0);
	Delay_us(2);
	IIC_SDA(0);
	Delay_us(2);
	IIC_SCL(1);
	Delay_us(2); 
	IIC_SCL(0);
}
void CO2_IIC_NAck(void){
	IIC_SCL(0);
	Delay_us(2);
	IIC_SDA(1);
	Delay_us(2);
	IIC_SCL(1);
	Delay_us(2);
	IIC_SCL(0);
}