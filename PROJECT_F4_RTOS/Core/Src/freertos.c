/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
u8 key;
u8 led_sc;
u8 i;
u8 flag_ur=0;
u8 len;	

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UART */
osThreadId_t UARTHandle;
const osThreadAttr_t UART_attributes = {
  .name = "UART",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UART2 */
osThreadId_t UART2Handle;
const osThreadAttr_t UART2_attributes = {
  .name = "UART2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for LED */
osThreadId_t LEDHandle;
const osThreadAttr_t LED_attributes = {
  .name = "LED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void UART_T(void *argument);
void UART_R(void *argument);
void LED_T(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of UART */
  UARTHandle = osThreadNew(UART_T, NULL, &UART_attributes);

  /* creation of UART2 */
  UART2Handle = osThreadNew(UART_R, NULL, &UART2_attributes);

  /* creation of LED */
  LEDHandle = osThreadNew(LED_T, NULL, &LED_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_UART_T */
/**
* @brief Function implementing the UART thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UART_T */
void UART_T(void *argument)
{
  /* USER CODE BEGIN UART_T */
  /* Infinite loop */
  for(;;)
  {
		//printf("\r\n您发送的消息为:\r\n");
//		if(flag_ur==1){
//			
//			
//			flag_ur=0;
//		
//		}
    osDelay(1);
  }
  /* USER CODE END UART_T */
}

/* USER CODE BEGIN Header_UART_R */
/**
* @brief Function implementing the UART2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UART_R */
void UART_R(void *argument)
{
  /* USER CODE BEGIN UART_R */
  /* Infinite loop */
  for(;;)
  {
		
		if(USART_RX_STA&0x8000){
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("0123456789\r\n");
			printf("9876543210\r\n");
			USART_RX_STA=0;
			flag_ur=1;
		}
    osDelay(1);
  }
  /* USER CODE END UART_R */
}

/* USER CODE BEGIN Header_LED_T */
/**
* @brief Function implementing the LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_T */
void LED_T(void *argument)
{
  /* USER CODE BEGIN LED_T */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LED_T */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

