#include "DAC8563.h"
#include "delay.h"
 
void DAC8563_Init(void){
	LD(0);
	CLR(1);
	SYN(1);
	DAC8563_Wirtereg(PWR_UP_DOWN,	DAC_A_B_UP);//power up A and B
	DAC8563_Wirtereg(LDAC_REG,LDAC_INAC_A_B);
	DAC8563_Wirtereg(INT_REF,EN_INT_RET);
}
void DAC8563_Wirtereg(u8 reg,u16 data){//low positive
	u8 i=0;
	u8 flag_d=0;
	SYN(0);
	Delay_us(10);
	for(i=0;i<8;i++){
		
		flag_d=(reg>>(7-i))&1;
		if(flag_d) DIN(1);
		else DIN(0);
		SCK(1);
		Delay_us(2);
		SCK(0);
		Delay_us(2);
	}
	for(i=0;i<16;i++){
		flag_d=(data>>(15-i))&1;
		if(flag_d) DIN(1);
		else DIN(0);
		SCK(1);
		Delay_us(2);
		SCK(0);
		Delay_us(2);	
	}

	SCK(1);
	SYN(1);
	Delay_us(2);
}
void DAC8563_SetVal(u8 chinnal,float val){
	
	u16 data;
	
	
	data=(u16)((val/2.0/2.5/4.06)*65536.0);
	if(chinnal==1){
		DAC8563_Wirtereg(WR_DAC_A_REG_UP_A,data);
	}
	else if(chinnal==2){
		DAC8563_Wirtereg(WR_DAC_B_REG_UP_B,data);
	}
	else if(chinnal==3){
		DAC8563_Wirtereg(WR_DAC_A_B_REG_UP_A_B,data);
	}
	
}