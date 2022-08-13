#include "CO2.h"
#include "delay.h"

void SGP_30_Init(void){
	CO2_IIC_Start();
	CO2_IIC_Send_Byte(SGP30_address<<1&WR);
	CO2_IIC_Wait_Ack();
	CO2_IIC_Send_Byte(0x20);
	CO2_IIC_Wait_Ack();
	CO2_IIC_Send_Byte(0x03);
	CO2_IIC_Wait_Ack();
	CO2_IIC_Stop();
	HAL_Delay(1000);
}
void SGP_30_Writedata(u16 data){
	
	
}
u32 SGP_30_Readdata(){
		u32 Read_CO2_TVOC=0;
		u8  CRC_Check;
		CO2_IIC_Start();							//??????	
		/* ??????+????bit(0 = w, 1 = r)bit7 ??*/
		CO2_IIC_Send_Byte(SGP30_address<<1|WR);
		CO2_IIC_Wait_Ack();		//?????ACK??
		CO2_IIC_Send_Byte(0x20);
		CO2_IIC_Wait_Ack();		//?????ACK??
		CO2_IIC_Send_Byte(0x08);
		CO2_IIC_Wait_Ack();		//?????ACK??
		CO2_IIC_Stop();								//??????	
		Delay_ms(1000);
		CO2_IIC_Start();							//??????
		CO2_IIC_Send_Byte(SGP30_address<<1|RR);   //????????	
		CO2_IIC_Wait_Ack();		//?????ACK??
		Read_CO2_TVOC |= (u16)(CO2_IIC_Read_Byte(1)<<8);
		Read_CO2_TVOC |= (u16)(CO2_IIC_Read_Byte(1));
		CRC_Check = CO2_IIC_Read_Byte(1);
		Read_CO2_TVOC |= (u32)(CO2_IIC_Read_Byte(1)<<24);
		Read_CO2_TVOC |= (u32)(CO2_IIC_Read_Byte(1)<<16);
		CRC_Check = CO2_IIC_Read_Byte(0);
		CO2_IIC_Stop();								//??????
		return Read_CO2_TVOC;
	
}