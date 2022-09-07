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
#include "adc.h"
#include "dma.h"
#include "opamp.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "arm_math.h"
#include <stdio.h>
#include "delay.h"
#include "string.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void uspp(uint16_t usa,char words[]);



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

float32_t DATA_IN[5000],DATA_INB[5000];
float32_t DATA_OUT[5000];
uint16_t DATA[5000];
char buffer[10];
int i;

arm_fir_instance_f32 S;

const float32_t B[101] = {
   0.001416345223328, 0.001435384422246, 0.001486642035499, 0.001570116626859,
   0.001685670771667, 0.001833031141338, 0.002011789176834, 0.002221402350021,
   0.002461196009159, 0.002730365802191, 0.003027980668889, 0.003352986390318,
   0.003704209681613, 0.004080362811548, 0.004480048730026, 0.004901766682266,
   0.005343918286277, 0.005804814048062, 0.006282680286986, 0.006775666441868,
   0.007281852726575, 0.007799258102288, 0.008325848532123, 0.008859545482467,
   0.009398234634226, 0.009939774766166,  0.01048200677172,  0.01102276276991,
     0.0115598752707,  0.01209118635454,    0.012614556826,  0.01312787530131,
     0.0136290671898,  0.01411610352987,  0.01458700964048,  0.01503987355008,
     0.0154728541657,  0.01588418914636,  0.01627220244564,  0.01663531149046,
    0.01697203396399,   0.0172809941628,  0.01756092890008,  0.01781069292876,
     0.0180292638604,  0.01821574655821,   0.0183693769845,  0.01848952548564,
    0.01857569949985,  0.01862754567586,  0.01864485139299,  0.01862754567586,
    0.01857569949985,  0.01848952548564,   0.0183693769845,  0.01821574655821,
     0.0180292638604,  0.01781069292876,  0.01756092890008,   0.0172809941628,
    0.01697203396399,  0.01663531149046,  0.01627220244564,  0.01588418914636,
     0.0154728541657,  0.01503987355008,  0.01458700964048,  0.01411610352987,
     0.0136290671898,  0.01312787530131,    0.012614556826,  0.01209118635454,
     0.0115598752707,  0.01102276276991,  0.01048200677172, 0.009939774766166,
   0.009398234634226, 0.008859545482467, 0.008325848532123, 0.007799258102288,
   0.007281852726575, 0.006775666441868, 0.006282680286986, 0.005804814048062,
   0.005343918286277, 0.004901766682266, 0.004480048730026, 0.004080362811548,
   0.003704209681613, 0.003352986390318, 0.003027980668889, 0.002730365802191,
   0.002461196009159, 0.002221402350021, 0.002011789176834, 0.001833031141338,
   0.001685670771667, 0.001570116626859, 0.001486642035499, 0.001435384422246,
   0.001416345223328
};







const int BL = 101;
float32_t pState[10000];

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
  MX_ADC1_Init();
  MX_OPAMP1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	Delay_Init(170);
	HAL_OPAMP_Start(&hopamp1);
	HAL_TIM_Base_Start(&htim3);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)DATA,5000);
	Delay_ms(2000);
	for(i=0;i<5000;i++){
		DATA_IN[i]=((float32_t)DATA[i])/4095.0*3.3;
		sprintf(buffer,"%.2f",DATA_IN[i]*1000);
		uspp(1,buffer);
		uspp(1,"\r\n");
	}
	
	arm_fir_init_f32(&S, 101, (float32_t *)B, pState, 5000);//numtap:The order of the filter. blockSize:number of data
	arm_fir_f32(&S, DATA_IN , DATA_OUT , 5000);
	//DATA_IN[90]
	for(i=0;i<5000;i++){
		sprintf(buffer,"%.2f",DATA_OUT[i]*1000);
		uspp(1,buffer);
		uspp(1,"\r\n");
	}
	
	
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
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

void uspp(uint16_t usa,char words[]){
	int len;
	len=strlen((const char*)words);
	
	if(usa==1){
		HAL_UART_Transmit(&huart1,(uint8_t*)words,len,0xffff);
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

