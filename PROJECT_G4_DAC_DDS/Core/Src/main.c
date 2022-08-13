/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "opamp.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include "key.h"
#include <string.h>



#define PI 3.1415926
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

void shen_sin(u32 data);
void shen_tra(u32 data);
void shen_sqr(u32 data);
void shen_sin_1(u32 data);

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



u32 FRE=1000;

u8 key=0;

u32 AMP=0;
float AM_data=0.0;
 


u32 AMP_data=50;
uint16_t sin_data_fin[10000];
uint16_t sin_data_fin_1[10000];

uint16_t ADC_Data[480];
u8 flag_get1;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_DAC4_Init();
  MX_OPAMP4_Init();
  MX_TIM6_Init();
  MX_DAC3_Init();
  MX_OPAMP3_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
	
	
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_Base_Start(&htim8);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	
	HAL_TIM_Base_Start(&htim6);
	
	HAL_TIM_Base_Start(&htim7);
	HAL_OPAMP_Start(&hopamp3);
	HAL_OPAMP_Start(&hopamp4);
	AMP_data=10000000/FRE;
	
	shen_sin(AMP_data);
	HAL_Delay(100);
	HAL_DAC_Start_DMA(&hdac4,DAC_CHANNEL_1,(uint32_t*)sin_data_fin,AMP_data,DAC_ALIGN_12B_R);
	
	FRE=5000;
	AMP_data=10000000/FRE;
	shen_sin_1(AMP_data);
	HAL_Delay(100);
	HAL_DAC_Start_DMA(&hdac3,DAC_CHANNEL_2,(uint32_t*)sin_data_fin_1,AMP_data,DAC_ALIGN_12B_R);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		key=KEY_Scan();
//		if(key==1)
//			HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
//			HAL_DAC_Stop_DMA(&hdac4,DAC_CHANNEL_1);
//			FRE=5000;
//			AMP_data=10000000/FRE;
//			shen_sin_1(AMP_data);
//			HAL_DAC_Start_DMA(&hdac4,DAC_CHANNEL_1,(uint32_t*)sin_data_fin,AMP_data,DAC_ALIGN_12B_R);
		
//		if(flag_get1==1){
//			flag_get1=0;
//			if(USART_RX_BUF[0]=='S'){
//				HAL_ADC_Start_DMA(&hadc1,(u32*)ADC_Data,480);
//				
//			}
//		}
		
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



void shen_sin(u32 data){
	int mode,i0,j,k;
	int n,y,z=1;
	double x;

		for(i0=0;i0<data;i0++){
			x=(i0)*(360.0/data)*PI/180;
			sin_data_fin[i0]=(uint16_t)(sin(x)*1998*1.0+2048);
		}
}
void shen_sin_1(u32 data){
		int mode,i0,j,k;
	int n,y,z=1;
	double x;

		for(i0=0;i0<data;i0++){
			x=(i0)*(360.0/data)*PI/180;
			sin_data_fin_1[i0]=sin(x)*1998*1.25/3.3+1998*1.25/3.3+50;
		}
}

void shen_tra(u32 data){
		int mode,i,j,k;
	float pi;
	int n,y,z=1;
	double x;
	float vpp;
	
	for(i=0;i<=(data/2);i++){
			sin_data_fin[i]=1.0/data*(i)*3995*3.3/3.3*2+(3.3-3.3)/2/3.3*3995+100;
		}
		y=data/2;
		for(i=data/2+1;i<data;i++){
			sin_data_fin[i]=sin_data_fin[y-z];
			z=z+1;
		}
}
void shen_sqr(u32 data){
	int i;
	for(i=0;i<data/2;i++){
		sin_data_fin[i]=100;
	}
	for(i=data/2;i<data;i++){
		sin_data_fin[i]=4095;
	}
}



void uspp(uint16_t usa,char words[]){
	int len;
	len=strlen((const char*)words);
	
	if(usa==1){
		HAL_UART_Transmit(&huart1,(u8*)words,len,0xffff);
	}
}

u8 us1_i;
u8 flag_usart1_data=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance==USART1){
		if(aRxBuffer[0]==0x0D){
			flag_usart1_data=0;
			flag_get1=1;
		}
		if(flag_usart1_data==1){
			USART_RX_BUF[us1_i]=aRxBuffer[0];
			us1_i++;
		}
		if(aRxBuffer[0]==0x0F){
			flag_usart1_data=1;
			us1_i=0;
		}
	}
	
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

