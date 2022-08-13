#ifndef __MU_KEY_H
#define __MU_KEY_H	 
#include "main.h" 
void Matrix_button_init(void);
uint8_t Button_Scan(uint8_t flag);

//#define start GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);\
//								 GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_10);
//#define c1 GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
//								 GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_10);
//#define c2 GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
//								 GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_10);
//#define c3 GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);\
//										GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_10);
//#define c4 GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
//										 GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_10);
//										 
//#define r1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
//#define r2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
//#define r3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
//#define r4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)

#define start 		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);\
									HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
								 
#define c1      	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);\
									HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
									
#define c2 				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);\
									HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
									
#define c3 				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);\
									HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
										
#define c4 				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);\
									HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
										 
#define r1				HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)
#define r2 				HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)
#define r3 				HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)
#define r4 				HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)

#endif
