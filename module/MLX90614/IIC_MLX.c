#include "mlx90614.h"



void MLX_IIC_Start(void){
		SMBUS_SCK_H;
	SMBUS_SCK_H;
	Delay_us(4);
	SMBUS_SDA_L;
	Delay_us(4);
	SMBUS_SCK_L;
}
void MLX_IIC_Stop(void){
	SMBUS_SCK_L;
	SMBUS_SDA_L;
	Delay_us(4);
	SMBUS_SCK_H;
	SMBUS_SDA_H;
	Delay_us(4);

}	//发送IIC停止信号
void MLX_IIC_Send_Byte(u8 txd){

		 uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (txd & 0x80)
        {
					SMBUS_SDA_H;
        }
        else
        {
            
					SMBUS_SDA_L;
        }
				Delay_us(2);      
				SMBUS_SCK_H;
				Delay_us(2); 
        SMBUS_SCK_L;
        if (i == 7)
        {
					SMBUS_SDA_H;
        }
        txd <<= 1;
				Delay_us(4);
    }
}	//IIC发送一个字节
u8 MLX_IIC_Read_Byte(unsigned char ack){
		unsigned char i,receive=0;
	SMBUS_SDA_H;//SDA 
	for(i=0;i<8;i++ )
	{
		SMBUS_SCK_L;
		Delay_us(2);
		SMBUS_SCK_H;
		receive<<=1;
		if(READ_SDA)receive++;
		Delay_us(1);
	}
		if (!ack)
		MLX_IIC_NAck();
		else
		MLX_IIC_Ack();
		return receive;
}
u8 MLX_IIC_Wait_Ack(void){
		u8 ucErrTime=0;
	SMBUS_SDA_H; 
	SMBUS_SDA_H;Delay_us(1);
	SMBUS_SCK_H;Delay_us(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MLX_IIC_Stop();
			return 1;
		}
	}
	SMBUS_SCK_L;
	return 0;
	

}
void MLX_IIC_Ack(void){
	
		SMBUS_SCK_L;
	Delay_us(2);
	SMBUS_SDA_L;
	Delay_us(2);
	SMBUS_SCK_H;
	Delay_us(2); 
	SMBUS_SCK_L;
	
}
void MLX_IIC_NAck(void){
	
	
		SMBUS_SCK_L;
	Delay_us(2);
	SMBUS_SDA_H;
	Delay_us(2);
	SMBUS_SCK_H;
	Delay_us(2);
	SMBUS_SCK_L;
	
}


