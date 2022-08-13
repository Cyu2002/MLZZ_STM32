#include "RDA5820.h"
#include "RDA_IIC.h"
#include "delay.h"


void RDA_SendData(u8 REGADD,u16 DATA){
	u8 DATA_H,DATA_L;
	DATA_H=DATA>>8;
	DATA_L=(u8)DATA;
	IIC_Start();
	IIC_Send_Byte((RDA_ADD<<1)+0);//W
	IIC_Wait_Ack();
	IIC_Send_Byte(REGADD);
	IIC_Wait_Ack();
	IIC_Send_Byte(DATA_H);
	IIC_Wait_Ack();
	IIC_Send_Byte(DATA_L);
	IIC_Wait_Ack();
	IIC_Stop();
}
u16 RDA_ReadData(u8 REGADD){
	u8 DATA_H,DATA_L;
	u16 DATA;
	IIC_Start();
	IIC_Send_Byte((RDA_ADD<<1)+0);//W
	IIC_Wait_Ack();
	IIC_Send_Byte(REGADD);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte((RDA_ADD<<1)+1);//R
	IIC_Wait_Ack();
	DATA_H=IIC_Read_Byte(1);
	DATA_L=IIC_Read_Byte(0);
	IIC_Stop();
	DATA=(DATA_H<<8)+DATA_L;
	return DATA;
}

u8 Rda5820Init(void)
{
    u16 id;
    
    id=RDA_ReadData(CHIPID); //??ID =0X5805
    if(id==0X5820) //??ID??
    {
        RDA_SendData(0x02,0x0002);  //?????
        Delay_ms(50);//??????
				RDA_SendData(0x02,0xC001);//????
//			Delay_ms(500);
         //芯片上电,不复位 正常天线 32.768时钟 循环搜索 不开始搜索 想上搜索 低音增强 立体声 非静音 非高阻抗
//				RDA_SendData(0x03,0x0000);//100k apace 87-108baud ?????
//				RDA_SendData(0x04,0x0000);//???? 0.75us??? ???iis io?????
//				RDA_SendData(0x05,0X8548);//????8,LNAN,1.8mA,VOL?? ??????
//				// RDA_SendData(RDA5820_R0A,0X7800);//0A????
//				// RDA_SendData(RDA5820_R0B,0X7800);//0b????
//				RDA_SendData(0x40,0X0000);//????? RX????
//				RDA_SendData(0x41,0X0000);//RDS???0 ???fifo fifo???0
//				// RDA_SendData(RDA5820_R42,0X0000);//42????
//				RDA_SendData(0x4A,0X0010);//fifo???
				//RDA_SendData(0X68,0X0F00);
				//Rda5820FreqSet(8700);//设置初始化频率87.00M
    }else return 1;//?????
    return 0;
}







void Rda5820RxMode(void)
{
    u16 temp;
    temp=RDA_ReadData(0X40); //??0X40???
    temp&=0xfff0; //RX ??   
    RDA_SendData(0X40,temp) ; //FM RX?? 
}



//?
void Rda5820TxMode(void)
{
    u16 temp;
    temp=RDA_ReadData(0X40); 
    temp&=0xfff0;
    temp|=0x0001;    //TX ??
    RDA_SendData(0X40,temp) ; //FM TM ?? 
}





u8 Rda5820RssiGet(void)
{
    u16 temp;
    temp=RDA_ReadData(0X0B); 
    return temp>>9;                //返回信号强度
}




void Rda5820VolSet(u8 vol)
{
    u16 temp;
    temp=RDA_ReadData(0X05); //??0X05???
    temp&=0XFFF0;
    temp|=vol&0X0F;    
    RDA_SendData(0X05,temp) ; //设置音量
}




//静音设置
//mute:0,不静音; 1,静音
void Rda5820MuteSet(u8 mute)
{
    u16 temp;
    temp=RDA_ReadData(0X02); //??0X02???
    if(mute)temp|=1<<14;
    else temp&=~(1<<14);       
    RDA_SendData(0X02,temp) ; //??MUTE
}




//设置灵敏度
//rssi:0~127;
void Rda5820RssiSet(u8 rssi)
{
    u16 temp;
    temp=RDA_ReadData(0X05); //??0X05???
    temp&=0X80FF;
    temp|=(u16)rssi<<8;    
    RDA_SendData(0X05,temp) ; //??RSSI
}




//设置TX发送功率
//gain:0~63
void Rda5820TxPagSet(u8 gain)
{
    u16 temp;
    temp=RDA_ReadData(0X42); //??0X42???
    temp&=0XFFC0;
    temp|=gain;   //GAIN
    RDA_SendData(0X42,temp) ; //??PA???
}




//设置TX 输入信号增益
//gain:0~7
void Rda5820TxPgaSet(u8 gain)
{
    u16 temp;
    temp=RDA_ReadData(0X42); //??0X42???
    temp&=0XF8FF;
    temp|=gain<<8;    //GAIN
    RDA_SendData(0X42,temp) ; //??PGA
}




//设置RDA5820的工作频段
//band:0,87~108Mhz; 1,76~91Mhz; 2,76~108Mhz; 3,用户自定义(53H~54H)
void Rda5820BandSet(u8 band)
{
    u16 temp;
    temp=RDA_ReadData(0X03); //??0X03???
    temp&=0XFFF3;
    temp|=band<<2;     
    RDA_SendData(0X03,temp) ; //??BAND
}




//设置RDA5820的步进频率
//band:0,100Khz; 1,200Khz; 3,50Khz; 3,保留
void Rda5820SpaceSet(u8 spc)
{
    u16 temp;
    temp=RDA_ReadData(0X03); //??0X03???
    temp&=0XFFFC;
    temp|=spc;     
    RDA_SendData(0X03,temp) ; //??BAND
}



//设置RDA5820的频率
//freq:频率值(单位为10Khz),比如10805, 表示108.05Mhz
void Rda5820FreqSet(u16 freq)
{
    u16 temp;
    u8 spc=0,band=0;
    u16 fbtm,chan;
    temp=RDA_ReadData(0X03); //??0X03???
    temp&=0X001F;
    band=(temp>>2)&0x03; //????
    spc=temp&0x03; //?????
    if(spc==0)spc=10;
    else if(spc==1)spc=20;
    else spc=5;
    if(band==0)fbtm=8700;
    else if(band==1||band==2)fbtm=7600;
    else 
    {
        fbtm=RDA_ReadData(0X53);//??bottom??
        fbtm*=10;
    }
    if(freq)    chan=(freq-fbtm)/spc; //??CHAN??????
    chan&=0X3FF; //??10? 
    temp|=chan<<6;
    temp|=1<<4; //TONE ENABLE    
    RDA_SendData(0X03,temp) ; //????
    Delay_ms(20); //??20ms
    while((RDA_ReadData(0X0B)&(1<<7))==0);//??FM_READY
    
}
//??????
//???:???(??10Khz)
u16 Rda5820FreqGet(void)
{
    u16 temp;
    u8 spc=0,band=0;
    u16 fbtm,chan;
    temp=RDA_ReadData(0X03); //??0X03???
    chan=temp>>6;   
    band=(temp>>2)&0x03; //????
    spc=temp&0x03; //?????
    if(spc==0)spc=10;
    else if(spc==1)spc=20;
    else spc=5;
    if(band==0)fbtm=8700;
    else if(band==1||band==2)fbtm=7600;
    else 
    {
        fbtm=RDA_ReadData(0X53);//??bottom??
        fbtm*=10;
    }
    temp=fbtm+chan*spc;  
    return temp;//?????
}


void RdaSeek(void)
{
u16 temp;
u16 count = 0;
    temp=RDA_ReadData(0x02); //??0X03???
    temp|=0X0100;     
    RDA_SendData(0x02,temp) ; //????
do
{
Delay_ms(20);
temp = RDA_ReadData(0x02);//??????
temp&= 0x0100;
count++;
if(count > 5000)return;

}while(temp == 0x0100);
}
void TXpwa(u8 data){
	u16 l_data;
	l_data=RDA_ReadData(0x41);
	l_data=l_data&0XFFC0;
	l_data=l_data|data;
	RDA_SendData(0x41,l_data);
	
}
void FM_Gain(void){
	u16 l_data;
	//l_data=RDA_ReadData(0x68);
	l_data=0x00FF;
	RDA_SendData(0x68,l_data);
}

u8 RDA_check(){
	u16 l_data;
	l_data=RDA_ReadData(0x0B);
	 return l_data>>9; 
}

uint8_t RDA5820_SetFreq_0(double freq) //50~115, in MHz
{
  uint16_t reg3, reg7;
  uint16_t chNb;
  uint8_t band, chSp, mode50;

  reg3=RDA_ReadData(0x03);
  chSp = reg3 & 0x3;
  if (chSp == 0)
    chSp = 10;
  else if (chSp == 1)
    chSp = 5;
  else if (chSp == 2)
    chSp = 20;
  else // chSp == 3
    chSp = 40;

  mode50 = 0x1;  // default
  if (freq < 65) // 50~65
  {
    if (freq < 50)
      freq = 50;
    mode50 = 0x0; // 50M start

    band = 0x3; // 50~65/65~76
    freq -= 50;
  }
  else if (freq < 76) // 65~76
  {
    band = 0x3; // 50~65/65~76
    freq -= 65;
  }
  else if (freq < 101) // 76~101
  {
    band = 0x2; // 76~108
    freq -= 76;
  }
  else if (freq < 112.5875) // 101~112.575(0.575---0.5875---0.600)
  {
    band = 0x0; // 87~108
    freq -= 87;
  }
  else // 112.575~115
  {
    if (freq > 115)
      freq = 115;

    band = 0x0; // 87~108
    freq -= 87;
  }
  chNb = freq * chSp + 0.5;

  reg7=RDA_ReadData(0x07);
  reg7 &= 0xFDFF;
  reg7 |= mode50 << 9;
  reg7=RDA_ReadData(0x07);

  reg3 &= 0x23;                             //keep direct mode bit and channel space
  reg3 |= (band << 2 | 1 << 4 | chNb << 6); // tune
  reg3=RDA_ReadData(0x03);
//  printf("chNb, band, chSp, 50: %d, %d, %d, %d\r\n", chNb, band, 1000 / chSp, mode50);
  return 1; //TODO: Get tune status
}