#include "stdio.h"
#include "sys.h"
#include "delay.h"
#include "RDA5807.h" 
#include "led.h"
#include "myiic2.h"


u16 RXFreq=0;
u8  Vol=0;
u8  RDA_State=0;

//初始化I2C 
void rda5807_i2c_init(void)
{
	IIC_Init2();
}


u16 RDA_ReadReg(u8 regAddr)
{
	 u16 buf;
    
    IIC_Start2();
    IIC_Send_Byte2(RDA_WRITE);//发送芯片地址 方向为写
    IIC_Wait_Ack2();	
    IIC_Send_Byte2(regAddr);//发送寄存器地址
    IIC_Wait_Ack2();		
    IIC_Start2();
    IIC_Send_Byte2(RDA_READ);//发送芯片地址 方向为读
    IIC_Wait_Ack2();	
    buf = IIC_Read_Byte2(1); 
    buf = buf<<8;
    buf =buf|IIC_Read_Byte2(0); 
    IIC_Stop2();
    return buf;
}
void RDA_WriteReg(u8 regAddr,u16 val)
{
	
    IIC_Start2();
    IIC_Send_Byte2(RDA_WRITE);	//发送芯片地址 方向为写
    IIC_Wait_Ack2();	 
    IIC_Send_Byte2(regAddr);	//发送寄存器地址
    IIC_Wait_Ack2();	 
    IIC_Send_Byte2(val>>8);
    IIC_Wait_Ack2();	
    IIC_Send_Byte2(val&0xFF);
    IIC_Wait_Ack2();	
    IIC_Stop2();
}

void RDA_Vol(u8 vol)
{
    u16 temp=0;

    if(RDA_State==1)
    {  
        temp=RDA_ReadReg(RDA_R05);		
        temp&=0xfff0;				   
        RDA_WriteReg(RDA_R05,temp|vol);			
    }
}
//信号强度获取	0~127
u16 RDA_RSSI(void)
{
    u16 temp=0;

    if(RDA_State==1)
    {
        temp=RDA_ReadReg(RDA_R0B);		
        temp=(temp>>9)&0x7f;    
    }
    
    if(temp<30)
    {
        LED0=0;
        LED1=0;
    }
    else if(temp>=30 && temp<50)
    {
       LED0=0;
       LED1=1;
    }
    else if(temp>=50 && temp<70)
    {
        LED0=1;
        LED1=0;
    }
    else if(temp>=70)
    {
        LED0=1;
        LED1=1;
    }
    
    return temp;     
}





//搜台方向 1向上搜索 0向下搜索
void RDA_Seek_Direction(u8 direction)
{
    u16 temp; 
    
    if(RDA_State==1)
    {
        temp=RDA_ReadReg(RDA_R02);        
        if(direction == 1)
            temp|= 1<<9;	//1<<9 => 1000000000		
        else
            temp&=~(1<<9);
        
        RDA_WriteReg(RDA_R02,temp);
    }
}

u16 RDA_Search_Freq(void)  
{
    u16 temp;

    temp=RDA_ReadReg(RDA_R02);		
    temp |= (1<<8);     
    RDA_WriteReg(RDA_R02,temp) ;		  //SEEK位置一  使能自动搜台
    while((RDA_ReadReg(RDA_R0A)&(1<<14)) == 0)  // 等待STC位置一 表示搜索完成
    {
        delay_ms(10);  //延时10ms    
    }
    temp = (RDA_ReadReg(RDA_R0A)&0x3FF) + 870 ;  //获取当前频率
    return temp;   //返回搜到电台频率 单位是：100Khz	 
}
//频率设置 单位是：100KHz 87~108MHz
void RDA_Set_Freq(u16 freq)
{
    u16 temp=0,chan=0;    
        
    temp=RDA_ReadReg(RDA_R03);	
    temp&=0x3F;
    
    chan=freq-870;
       
    temp|=chan<<6;
    
    
    temp|=1<<4;
    RDA_WriteReg(RDA_R03,temp) ;	
    delay_ms(50);
    
//    RDA_Freq_View(freq);
}
//1 使能芯片 0 禁用芯片
void RDA_Enable(void)
{
    u16 temp;
    
    temp=RDA_ReadReg(RDA_R02);

    if((temp&0x01)==0)
    {
        RDA_Init();
        RDA_State=1;
    }
    else
    {      
        RDA_WriteReg(RDA_R02,0);		
        
        RDA_State=0;
    }    
}
void RDA_Init(void)		  
{	
    RXFreq=998;
    Vol=2;
    RDA_State=1;

    RDA_WriteReg(RDA_R02,0x0002);        //软件复位
    delay_ms(30);
    RDA_WriteReg(RDA_R02,0xd281);        //晶振选择32.768Khz 向上搜索 重低音 立体声  SKMODE = 1搜索到边频时停止 
    RDA_WriteReg(RDA_R03,0x0000);        //步进100Khz 频带为87M~108M	
    RDA_WriteReg(RDA_R04,0x0040);        //基本配置	
    RDA_WriteReg(RDA_R05,0x88A2);        //音量设置为vol=2 搜索阀值为8      
    
    RDA_Set_Freq(RXFreq);
    RDA_SPK();
} 

void RDA_Freq_Down(void)
{ 
    RXFreq-=1;	        //频率减，步进100KHZ    
    if(RXFreq<870)     RXFreq=870;                           
    RDA_Set_Freq(RXFreq);	//频率设置
}

void RDA_Freq_Up(void)
{
    RXFreq+=1;		//频率加，步进100KHZ
    if(RXFreq>1080)    RXFreq=1080;
    RDA_Set_Freq(RXFreq);	//频率设置    
}
//大
void RDA_Vol_Big(void)
{  
    if(Vol<15)
    {
        Vol++;		//音量加 
        RDA_Vol(Vol);   //音量设置   0~15    
    }else Vol=0;
}

void RDA_Vol_Small(void)//下
{
    if(Vol>0)           //音量减 
    {
        Vol--;
        RDA_Vol(Vol);		   
    }
}


//功放
void RDA_SPK(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOF,GPIO_Pin_5);						 //PB.5 输出高


}
//此处得加 头文件 myiic.h gpio.h 以及延时函数的.h 以及LED.h 
 


 
