#include "ad9833.h"
#include "delay.h"




#define FCLK 25000000
//#define RealFreDat    268435456.0/FCLK//????? Fout=(Fclk/2?28??)*28??????
double RealFreDat = 268435456.0/FCLK;


void ad9833_init(void){
	
	
	AD9833_FSYNC(1);
	Delay_us(2);
	
	AD9833_CLK(1);
	
	AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);

}

void AD9833_SendByte(uint8_t date){

//#if MODE_SERIAL
  uint8_t j;
  for (j = 0; j < 8; j++)
  {
		
		
		AD9833_DA((date >>(7-j))&1);
		AD9833_CLK(0);
		Delay_us(1);
		AD9833_CLK(1);
		Delay_us(1);
  }
}
void ad9833_delay(void){
	HAL_Delay(1);
	
}
void ad9833_pu(uint8_t i){
	if(i==0){
	AD9833_CLK(0);
	}
	else{
	AD9833_CLK(1);
	}
	
}
void ad9833_wclk(void){
	AD9833_CLK(1);
	ad9833_delay();
	AD9833_CLK(0);
	ad9833_delay();
}

unsigned char AD9833_SPI_Write(unsigned char* data,
                        unsigned char bytesNumber)
{
	unsigned char i =0,j = 0;
	unsigned char writeData[5]	= {0,0, 0, 0, 0};
	AD9833_CLK(1);
	Delay_us(1);
	AD9833_FSYNC(0);
	for(i = 0;i < bytesNumber;i ++)
	{
		writeData[i] = data[i + 1];
	}
	for(i=0 ;i<bytesNumber ;i++) 
	{					 	
	//while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); //?????SPI???????:????????
		AD9833_SendByte(writeData[i]);
	}
	AD9833_FSYNC(1);
	Delay_us(5);
	return i;	
}


void AD9833_SetRegisterValue(unsigned short regValue)
{
	unsigned char data[5] = {0x03, 0x00, 0x00};	
	
	data[1] = (unsigned char)((regValue & 0xFF00) >> 8);
	data[2] = (unsigned char)((regValue & 0x00FF) >> 0);    
	AD9833_SPI_Write(data,2);
}




void AD9833_SetFrequency(unsigned short reg, float fout)
{
	unsigned short freqHi = reg;
	unsigned short freqLo = reg;
	unsigned long val=RealFreDat*fout;
	freqHi |= (val & 0xFFFC000) >> 14 ;
	freqLo |= (val & 0x3FFF);
	AD9833_SetRegisterValue(AD9833_B28);
	AD9833_SetRegisterValue(freqLo);
	AD9833_SetRegisterValue(freqHi);
}
void AD9833_Setup(unsigned short freq,
				  unsigned short phase,
			 	  unsigned short type)
{
	unsigned short val = 0;
	
	val = freq | phase | type;
	AD9833_SetRegisterValue(val);
}
void AD9833_SetFrequencyQuick(float fout,unsigned short type)
{
	AD9833_SetFrequency(AD9833_REG_FREQ0, fout*1000);// 400 kHz
	AD9833_Setup(AD9833_FSEL0, AD9833_PSEL0, type);
}

