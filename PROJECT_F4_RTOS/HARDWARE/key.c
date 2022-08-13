#include "key.h"
//#include "tim.h"
uint8_t key_scan(void){
	uint8_t b=0;
	static u8 key_up=1;
	if(key_up&&(key10==0||key2==0||key3==0||key4==0||key5==1||key6==1))
	{
		HAL_Delay(10);//去抖动 
		key_up=0;
		if(key10==0)return 1;
		else if(key2==0)return 2;
		else if(key3==0)return 3;
		else if(key4==0)return 4;
		else if(key5==1)return 5;
		else if(key6==1)return 6;
	}else if(key10==1&&key2==1&&key3==1&&key4==1&&key5==0&&key6==0)key_up=1; 	    
 	return 0;// 无按键按下
	



}
void led_scan(u8 led){
	
	switch(led){
			case 0:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,1);break;
			case 1:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,1);break;
			case 2:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,1);break;
			case 3:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);break;
			case 4:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);break;
			case 5:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);break;
			case 6:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,1);break;
			case 7:HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,1);break;
			default:break;
		
	}
	
}


//void bee_ok(u32 arr){
//	
//	TIM3->PSC=arr;
//	
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
//	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 2);
//	
//	
//}