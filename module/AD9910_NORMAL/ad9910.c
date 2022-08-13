#include "stm32f4xx.h"
#include "ad9910.h"
#include "delay.h"
#include "sys.h"

const uchar cfr1[]={0x00,0x40,0x00,0x00};       //cfr1控制字
const uchar cfr2[]={0x01,0x00,0x00,0x00};       //cfr2控制字
const uchar cfr3[]={0x05,0x0F,0x41,0x32};       //cfr3控制字  40M输入  25倍频  VC0=101   ICP=001;
uchar profile11[]={0xf0,0xff,0x00,0x00,0x25,0x09,0x7b,0x42};       //profile1控制字 01振幅控制 23相位控制 4567频率调谐字
void AD9110_IOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure ; 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_Init(GPIOB ,&GPIO_InitStructure) ; 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_8| GPIO_Pin_2; 
	GPIO_Init(GPIOA ,&GPIO_InitStructure) ;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All^(GPIO_Pin_14| GPIO_Pin_15); 
	GPIO_Init(GPIOC ,&GPIO_InitStructure) ;
}

//=====================================================================


//======================发送8位数据程序===================================
void txd_8bit(uchar txdat)
{
  uchar i,sbt;
  sbt=0x80;
  SCLK=0;
  for (i=0;i<8;i++)
   {
	   if ((txdat & sbt)==0) 
	   {
		   AD9910_SDIO=0;
	   }		   
	   else 
	   {
		   AD9910_SDIO=1;
	   }
       SCLK=1;
	   sbt=sbt>>1;
	   SCLK=0;
   }
 }    

//======================ad9910初始化程序================================
void Init_ad9910(void)
{
	uchar k,m;
	
	AD9110_IOInit();//IO初始化
	
	AD9910_PWR = 0;//软件拉低
	PROFILE2=0;
	PROFILE1=0;
	PROFILE0=0;
	DRCTL=0;
	DRHOLD=0;
	MAS_REST=1; 
	delay_ms(5);
	MAS_REST=0; 
	
	CS=0;
	txd_8bit(0x00);    //发送CFR1控制字地址
	for (m=0;m<4;m++)
	{
		txd_8bit(cfr1[m]);
	}		
	CS=1;  
	for (k=0;k<10;k++);
	
	CS=0;
	txd_8bit(0x01);    //发送CFR2控制字地址
	for (m=0;m<4;m++)
	{
		txd_8bit(cfr2[m]);
	}		
	CS=1;  
	for (k=0;k<10;k++);

	CS=0;
	txd_8bit(0x02);    //发送CFR3控制字地址
	for (m=0;m<4;m++)
	{
		txd_8bit(cfr3[m]);
	}
	CS=1;
	for (k=0;k<10;k++);

	UP_DAT=1;
	for(k=0;k<10;k++);
	UP_DAT=0;
	delay_ms(1);
}      
//=====================================================================

//======================ad9910发送频率值程序===================================
void Txfrc(void)
{
	uchar m,k;

	CS=0;
	txd_8bit(0x0e);    //发送profile1控制字地址
	for (m=0;m<8;m++)
	{
		txd_8bit(profile11[m]);
	}
	CS=1;
 for(k=0;k<10;k++);

	UP_DAT=1;
 for(k=0;k<10;k++);
	UP_DAT=0;
 delay_ms(1);
}         
//=====================================================================
//===================计算频偏字、频率字和发送程序======================
void Freq_Amp_set(u32 Freq,float Amp)
{
	  u32 Temp_freq;
	  u16 Temp_amp;	
	  Temp_freq=(u32)Freq*4.294967296;	   //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000
	  Temp_amp=Amp*65535;
	
	  profile11[7]=(u8)Temp_freq;
	  profile11[6]=(u8)(Temp_freq>>8);
	  profile11[5]=(u8)(Temp_freq>>16);
	  profile11[4]=(u8)(Temp_freq>>24);
	  profile11[1]=(u8)Temp_amp;
	  profile11[0]=(u8)(Temp_amp>>8);
	  Txfrc();
}
