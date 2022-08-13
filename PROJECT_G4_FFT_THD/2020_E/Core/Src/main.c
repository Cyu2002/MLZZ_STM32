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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"	// 包含一个arm_math.h
#include "arm_const_structs.h"

#include "stdio.h"
#define MAX_RECV_LEN 128
uint8_t rx1_buff[MAX_RECV_LEN]={0};
uint8_t *pBuf=rx1_buff;
uint8_t line_flag=0;

#define FFT_LENGTH 1024

__IO uint8_t AdcConvEnd = 0;
uint16_t adcBuff[FFT_LENGTH];

float fft_inputbuf[FFT_LENGTH * 2];  
float fft_outputbuf[FFT_LENGTH];  

#define set0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,0)
#define set1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15,0)
#define set2 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,0)

#define reset0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,1)
#define reset1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15,1)
#define reset2 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,1)

#define d0 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)
#define d1 HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)
#define d2 HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
float data=0,thd,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11;
int j,check_enable=0,control_enable=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void modulus_value(void);
void control(void);
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
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1,pBuf,1);
	HAL_TIM_Base_Start(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
				set0;
				set1;
				set2;
  while (1)
  {
		
		if(line_flag){
			//printf("%s",rx1_buff);
			
			line_flag=0;
			if(rx1_buff[0]=='s'){
			//printf("t0.txt=\"%d\"\xff\xff\xff",j++); //一次性发完命令和结束符	 
				check_enable=1;
			}
			if(rx1_buff[0]=='1'){
				reset0;
				reset1;
				reset2;
			}
			if(rx1_buff[0]=='2'){
				set0;
				reset1;
				reset2;
			}
			if(rx1_buff[0]=='3'){
				reset0;
				set1;
				reset2;
			}
			if(rx1_buff[0]=='4'){
				set0;
				set1;
				reset2;
			}
			if(rx1_buff[0]=='5'){
				set0;
				set1;
				reset2;
			}
			if(rx1_buff[0]=='0'){
				set0;
				set1;
				set2;
			}
		}
		
		control();
		
		if(check_enable){
		for (int i = 0; i < FFT_LENGTH; i++)
		{
				adcBuff[i]=0;
		}
		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuff, FFT_LENGTH);
		
		HAL_Delay(100);
		while (!AdcConvEnd)       //等待转换完毕
			;
		
		for (int i = 0; i < FFT_LENGTH; i++)
		{
				fft_inputbuf[i * 2] = adcBuff[i] * 3.3 / 4096;//实部赋值，* 3.3 / 4096是为了将ADC采集到的值转换成实际电压
				fft_inputbuf[i * 2 + 1] = 0;//虚部赋值，固定为0.
		}

		arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_inputbuf, 0, 1);
		arm_cmplx_mag_f32(fft_inputbuf, fft_outputbuf, FFT_LENGTH); 
		/*fft_outputbuf[0] /= 1;

		for (int i = 1; i < FFT_LENGTH; i++)//输出各次谐波幅值
		{
				fft_outputbuf[i] /= 1;
		}*/
		//printf("FFT Result:\r\n");

		/*for (int i = 0; i < FFT_LENGTH; i++)//输出各次谐波幅值
		{
			//printf("%d:\t%.2f\r\n", i, fft_outputbuf[i]);
		}*/
		HAL_ADC_Stop_DMA(&hadc1);
		 check_enable=0;
		//printf("page main\xff\xff\xff");
		modulus_value();
		
		
		
		}
		


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
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){
if(UartHandle->Instance==USART1){
++pBuf;
	if(pBuf==rx1_buff+MAX_RECV_LEN)
		pBuf=rx1_buff;
	else if(*(pBuf-1)==0x0a){
	line_flag=1;
		*pBuf='\0';
		pBuf=rx1_buff;
	}
	__HAL_UNLOCK(UartHandle);
	HAL_UART_Receive_IT(UartHandle,pBuf,1);

}
}

void modulus_value(void){
int max=0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11;
	for(j=1;j<FFT_LENGTH/2;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s1=j;
		}
	}
	max=0;
	for(j=s1*2-5;j<s1*2+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s2=j;
		}
	}
	
	max=0;
		for(j=s1*3-5;j<s1*3+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s3=j;
		}
	}
	max=0;
		for(j=s1*4-5;j<s1*4+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s4=j;
		}
	}
	max=0;
		for(j=s1*5-5;j<s1*5+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s5=j;
		}
	}
	max=0;
		for(j=s1*6-5;j<s1*6+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s6=j;
		}
	}
	max=0;
		for(j=s1*7-5;j<s1*7+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s7=j;
		}
	}
	max=0;
		for(j=s1*8-5;j<s1*8+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s8=j;
		}
	}
	max=0;
		for(j=s1*9-5;j<s1*9+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s9=j;
		}
	}
	max=0;
		for(j=s1*10-5;j<s1*10+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s10=j;
		}
	}		
	max=0;
		for(j=s1*11-5;j<s1*11+5;j++){
		if(fft_outputbuf[j]>max){
			max=fft_outputbuf[j];
			s11=j;
		}
	}
	u1=fft_outputbuf[s1];
	u2=fft_outputbuf[s2];
	u3=fft_outputbuf[s3];
	u4=fft_outputbuf[s4];
	u5=fft_outputbuf[s5];
	u6=fft_outputbuf[s6];
	u7=fft_outputbuf[s7];
	u8=fft_outputbuf[s8];
	u9=fft_outputbuf[s9];
	u10=fft_outputbuf[s10];
	u11=fft_outputbuf[s11];
//printf("u1=%f\r\nu2=%f\r\nu3=%f\r\nu4=%f\r\nu5=%f\r\nu6=%f\r\nu7=%f\r\nu8=%f\r\nu9=%f\r\nu10=%f\r\nu11=%f\r\n",u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11);
thd=sqrt(u2*u2+u3*u3+u4*u4+u5*u5+u6*u6+u7*u7+u8*u8+u9*u9+u10*u10+u11*u11)/u1*100;
	//printf("THD=%.2f%%\r\n",thd);
	//printf("addt 2,0,1024\xff\xff\xff");
	fft_outputbuf[0]=0;
	for(j=0;j<FFT_LENGTH;j++){
		printf("add 2,0,%d\xff\xff\xff",(int)(fft_outputbuf[j]/u1*255));
	}
	printf("t1.txt=\"%.2f%%\"\xff\xff\xff",thd); //一次性发完命令和结束符	 
}

void control(void){
if(d0==0&&d1==0&&d2==0)
	control_enable=1;
else if(control_enable==1&&d0==1&&d1==0&&d2==0){
	check_enable=1;
	control_enable=0;
}
else if(control_enable==0&&d0==0&&d1==1&&d2==0){
	set0;
	set1;
	set2;
	control_enable=0;
}
else if(control_enable==1&&d0==1&&d1==1&&d2==0){
	reset0;
	reset1;
	reset2;
	control_enable=0;
}
else if(control_enable==1&&d0==0&&d1==0&&d2==1){
	set0;
	reset1;
	reset2;
	control_enable=0;
}
else if(control_enable==1&&d0==1&&d1==0&&d2==1){
	reset0;
	set1;
	reset2;
	control_enable=0;
}
else if(control_enable==1&&d0==0&&d1==1&&d2==1){
	set0;
	set1;
	reset2;
	control_enable=0;
}
else if(control_enable==1&&d0==1&&d1==1&&d2==1){
	reset0;
	reset1;
	set2;
	control_enable=0;
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

