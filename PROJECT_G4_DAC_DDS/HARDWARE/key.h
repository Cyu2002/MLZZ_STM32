#ifndef __KEY_H
#define __KEY_H	 

#include "main.h"

#define KEY1 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)


void KEY_Init(void);	
u8 KEY_Scan(void);  		



#endif
