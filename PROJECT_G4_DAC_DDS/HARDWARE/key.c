#include "key.h"


void KEY_Init(void){


}
u8 KEY_Scan(void){
	static u8 key_up=1;

	if(key_up&&(KEY1==1))
	{
		HAL_Delay(10);//????? 
		key_up=0;
		if(KEY1==1)return 1;
	}else if(KEY1==0)key_up=1; 	    
 	return 0;

}