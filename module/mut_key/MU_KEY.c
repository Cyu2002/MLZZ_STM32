#include "MU_KEY.h"
#include "delay.h"

void Matrix_button_init(void){
	


}

u8 Button_Scan(u8 flag){
	//int t=0;
	static u8 mark=1;
	if(flag)mark=1;
	start;
	if(mark==1&&(r1==1||r2==1||r3==1||r4==1)){
		Delay_ms(10);
		mark=0;
		
		c1;	
		if(r1==1){
			return 1;
		}
		if(r2==1){
			return 5;
		}
		if(r3==1){
			return 9;
		}
		if(r4==1){
			return 13;
		}

		c2;	
		if(r1==1){
			return 2;
		}
		if(r2==1){
			return 6;
		}
		if(r3==1){
			return 10;
		}
		if(r4==1){
			return 14;
		}

		c3;	
		if(r1==1){
			return 3;
		}
		if(r2==1){
			return 7;
		}
		if(r3==1){
			return 11;
		}
		if(r4==1){
			return 15;
		}

		c4;	
		if(r1==1){
			return 4;
		}
		if(r2==1){
			return 8;
		}
		if(r3==1){
			return 12;
		}
		if(r4==1){
			return 16;
		}
	}
	else if(r1==0&&r2==0&&r3==0&&r4==0)mark=1;

return 0;

}
