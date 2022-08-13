#include "si5351.h"
#include "delay.h"
void IICstart()//IIC??????
{
	  SDA(1);
	  CLK(1);
	  SDA(0);
    Delay_us(100); 
	  CLK(0);
    Delay_us(100); 	
}
void IICstop()//IIC??????
{
	  CLK(0);
    Delay_us(100); 
	  SDA(0);
    Delay_us(100); 
	  CLK(1);
    Delay_us(100); 
	  SDA(1);	
    Delay_us(100); 
}
void IICsend(uint8_t DATA)//IIC???????
{
		uint16_t i;
    for(i=0;i<8;i++) //???????? 
    {     
        CLK(0); 		 //?????,?????SDA??
			
        if((DATA&0x80)==0)  
        {SDA(0);}  
        else  
        {SDA(1);}  
				
        DATA<<=1;  
        Delay_us(100);    
        CLK(1);
        Delay_us(100);      //???????????
		}  
    CLK(0);  
    SDA(1);	 				   //?????   
    Delay_us(100);   
    CLK(1); 
    Delay_us(100); 
		while(i<1000){i++;}//???????ACK 
		CLK(0); 					 //?????,????????
}
void IICsendreg(uint8_t reg, uint8_t data)
{
  IICstart();      //????
  Delay_us(200);  
  IICsend(0xC0);   //??????+???
  Delay_us(200);  
  IICsend(reg);    //???????
  Delay_us(200);  
  IICsend(data);   //???????
  Delay_us(200);  
  IICstop(); 
}

void SetFrequency(uint32_t frequency)//??????
{
  uint32_t pllFreq;
  uint32_t xtalFreq = XTAL_FREQ;// ????
  uint32_t l;
  float f;
  uint8_t mult;
  uint32_t num;
  uint32_t denom;
  uint32_t divider;
  divider = 900000000 / frequency;	//?????:900 mhz
  if (divider % 2) divider--;				//???????????
  pllFreq = divider * frequency;		//??pllFrequency:???*???????
  mult = pllFreq / xtalFreq;				//?????pllFrequency???
  l = pllFreq % xtalFreq;						//??????:
  f = l;														//??????,???15 . . 90
  f *= 1048575;											//num?????????,?????
  f /= xtalFreq;										//?20?(??0 . . 1048575)
  num = f;													//???????+ num /???
  denom = 1048575;									//????????????1048575
																		//????????????
  SetPLLClk(SI_SYNTH_PLL_A, mult, num, denom);
		//??MultiSynth???0????
		//??R????????2??,?1 . . 128?
		//???SI_R_DIV1 reprented SI_R_DIV128(?si5351a?h???)
		//?????1???????,?????
		//??R????

  SetMultisynth(SI_SYNTH_MS_0,divider,SI_R_DIV_1);
		//??????????????????????
		//??,????????,????

  IICsendreg(SI_PLL_RESET,0xA0);	
		//????CLK0??(0 x4f)
		//???MultiSynth0???????
  IICsendreg(SI_CLK0_CONTROL, 0x4F|SI_CLK_SRC_PLL_A);
}
void SetPLLClk(uint8_t pll, uint8_t mult, uint32_t num, uint32_t denom)//??PPL??
{
  uint32_t P1;					// PLL config register P1
  uint32_t P2;					// PLL config register P2
  uint32_t P3;					// PLL config register P3

  P1 = (uint32_t)(128 * ((float)num / (float)denom));
  P1 = (uint32_t)(128 * (uint32_t)(mult) + P1 - 512);
  P2 = (uint32_t)(128 * ((float)num / (float)denom));
  P2 = (uint32_t)(128 * num - denom * P2);
  P3 = denom;

  IICsendreg(pll + 0, (P3 & 0x0000FF00) >> 8);
  IICsendreg(pll + 1, (P3 & 0x000000FF));
  IICsendreg(pll + 2, (P1 & 0x00030000) >> 16);
  IICsendreg(pll + 3, (P1 & 0x0000FF00) >> 8);
  IICsendreg(pll + 4, (P1 & 0x000000FF));
  IICsendreg(pll + 5, ((P3 & 0x000F0000) >> 12) | ((P2 & 0x000F0000) >> 16));
  IICsendreg(pll + 6, (P2 & 0x0000FF00) >> 8);
  IICsendreg(pll + 7, (P2 & 0x000000FF));
}
void SetMultisynth(uint8_t synth,uint32_t divider,uint8_t rDiv)//???synth
{
  uint32_t P1;					// Synth config register P1
  uint32_t P2;					// Synth config register P2
  uint32_t P3;					// Synth config register P3

  P1 = 128 * divider - 512;
  P2 = 0;							// P2 = 0, P3 = 1 forces an integer value for the divider
  P3 = 1;

  IICsendreg(synth + 0,   (P3 & 0x0000FF00) >> 8);
  IICsendreg(synth + 1,   (P3 & 0x000000FF));
  IICsendreg(synth + 2,   ((P1 & 0x00030000) >> 16) | rDiv);
  IICsendreg(synth + 3,   (P1 & 0x0000FF00) >> 8);
  IICsendreg(synth + 4,   (P1 & 0x000000FF));
  IICsendreg(synth + 5,   ((P3 & 0x000F0000) >> 12) | ((P2 & 0x000F0000) >> 16));
  IICsendreg(synth + 6,   (P2 & 0x0000FF00) >> 8);
  IICsendreg(synth + 7,   (P2 & 0x000000FF));
}