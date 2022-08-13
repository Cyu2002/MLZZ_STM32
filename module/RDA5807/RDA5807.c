#include "stdio.h"
#include "sys.h"
#include "delay.h"
#include "RDA5807.h" 
#include "led.h"
#include "myiic2.h"


u16 RXFreq=0;
u8  Vol=0;
u8  RDA_State=0;

//��ʼ��I2C 
void rda5807_i2c_init(void)
{
	IIC_Init2();
}


u16 RDA_ReadReg(u8 regAddr)
{
	 u16 buf;
    
    IIC_Start2();
    IIC_Send_Byte2(RDA_WRITE);//����оƬ��ַ ����Ϊд
    IIC_Wait_Ack2();	
    IIC_Send_Byte2(regAddr);//���ͼĴ�����ַ
    IIC_Wait_Ack2();		
    IIC_Start2();
    IIC_Send_Byte2(RDA_READ);//����оƬ��ַ ����Ϊ��
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
    IIC_Send_Byte2(RDA_WRITE);	//����оƬ��ַ ����Ϊд
    IIC_Wait_Ack2();	 
    IIC_Send_Byte2(regAddr);	//���ͼĴ�����ַ
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
//�ź�ǿ�Ȼ�ȡ	0~127
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





//��̨���� 1�������� 0��������
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
    RDA_WriteReg(RDA_R02,temp) ;		  //SEEKλ��һ  ʹ���Զ���̨
    while((RDA_ReadReg(RDA_R0A)&(1<<14)) == 0)  // �ȴ�STCλ��һ ��ʾ�������
    {
        delay_ms(10);  //��ʱ10ms    
    }
    temp = (RDA_ReadReg(RDA_R0A)&0x3FF) + 870 ;  //��ȡ��ǰƵ��
    return temp;   //�����ѵ���̨Ƶ�� ��λ�ǣ�100Khz	 
}
//Ƶ������ ��λ�ǣ�100KHz 87~108MHz
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
//1 ʹ��оƬ 0 ����оƬ
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

    RDA_WriteReg(RDA_R02,0x0002);        //�����λ
    delay_ms(30);
    RDA_WriteReg(RDA_R02,0xd281);        //����ѡ��32.768Khz �������� �ص��� ������  SKMODE = 1��������Ƶʱֹͣ 
    RDA_WriteReg(RDA_R03,0x0000);        //����100Khz Ƶ��Ϊ87M~108M	
    RDA_WriteReg(RDA_R04,0x0040);        //��������	
    RDA_WriteReg(RDA_R05,0x88A2);        //��������Ϊvol=2 ������ֵΪ8      
    
    RDA_Set_Freq(RXFreq);
    RDA_SPK();
} 

void RDA_Freq_Down(void)
{ 
    RXFreq-=1;	        //Ƶ�ʼ�������100KHZ    
    if(RXFreq<870)     RXFreq=870;                           
    RDA_Set_Freq(RXFreq);	//Ƶ������
}

void RDA_Freq_Up(void)
{
    RXFreq+=1;		//Ƶ�ʼӣ�����100KHZ
    if(RXFreq>1080)    RXFreq=1080;
    RDA_Set_Freq(RXFreq);	//Ƶ������    
}
//��
void RDA_Vol_Big(void)
{  
    if(Vol<15)
    {
        Vol++;		//������ 
        RDA_Vol(Vol);   //��������   0~15    
    }else Vol=0;
}

void RDA_Vol_Small(void)//��
{
    if(Vol>0)           //������ 
    {
        Vol--;
        RDA_Vol(Vol);		   
    }
}


//����
void RDA_SPK(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOF, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	 GPIO_SetBits(GPIOF,GPIO_Pin_5);						 //PB.5 �����


}
//�˴��ü� ͷ�ļ� myiic.h gpio.h �Լ���ʱ������.h �Լ�LED.h 
 


 
