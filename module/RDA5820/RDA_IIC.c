#include "RDA_IIC.h"
#include "delay.h"

void IIC_Start(void){
	SDA_H;
	SCL_H;
	Delay_us(2);
	SDA_L;
	Delay_us(2);
	SCL_L;
}

 //????IIC???z?
 //SCL??????SDA?????
 //IIC?????SCL??SDA?????????????????????????????????
/*
	SCL:????????
	SDA:???|??
 */
void IIC_Stop(void){
	SCL_L;
	SDA_L;
	Delay_us(2);
	SCL_H;
	SDA_H;
	Delay_us(2);
}

void IIC_Send_Byte(u8 txd){
		 uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (txd & 0x80)
        {
					SDA_H;
        }
        else
        {
            
					SDA_L;
        }
				Delay_us(1);      
				SCL_H;
				Delay_us(1); 
        SCL_L;
        if (i == 7)
        {
					SDA_H;
        }
        txd <<= 1;
				Delay_us(2);
    }
}
u8 IIC_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	SDA_H;//SDA 
	for(i=0;i<8;i++ )
	{
		SCL_L;
		Delay_us(1);
		SCL_H;
		receive<<=1;
		if(SDA_read)receive++;
		Delay_us(1);
	}
		if (!ack)
		IIC_NAck();
		else
		IIC_Ack();
		return receive;
	
}
u8 IIC_Wait_Ack(void){
	u8 ucErrTime=0;
	SDA_H; 
	SDA_H;Delay_us(1);
	SCL_H;Delay_us(1);
	while(SDA_read)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL_L;
	return 0;
	
	
}
void IIC_Ack(void){
	SCL_L;
	Delay_us(1);
	SDA_L;
	Delay_us(1);
	SCL_H;
	Delay_us(1); 
	SCL_L;
}
void IIC_NAck(void){
	SCL_L;
	Delay_us(1);
	SDA_H;
	Delay_us(1);
	SCL_H;
	Delay_us(1);
	SCL_L;
	
}