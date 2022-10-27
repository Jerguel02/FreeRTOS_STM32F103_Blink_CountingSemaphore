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
#include "cmsis_os.h"
#include "string.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

osThreadId Task1Handle;
osThreadId Task2Handle;
osThreadId Task3Handle;
osSemaphoreId CountSemHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
void Task01(void const * argument);
void Task02(void const * argument);
void Task03(void const * argument);

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of CountSem */
  osSemaphoreDef(CountSem);
  CountSemHandle = osSemaphoreCreate(osSemaphore(CountSem), 2);
  CountSemHandle= xSemaphoreCreateCounting(2,0);

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
  /* definition and creation of Task1 */
  osThreadDef(Task1, Task01, osPriorityHigh, 0, 128);
  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* definition and creation of Task2 */
  osThreadDef(Task2, Task02, osPriorityNormal, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  /* definition and creation of Task3 */
  osThreadDef(Task3, Task03, osPriorityNormal, 0, 128);
  Task3Handle = osThreadCreate(osThread(Task3), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_Task01 */
/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task01 */
void Task01(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	uint8_t str1[] = "Enter Task 1\r\n";
    HAL_UART_Transmit(&huart1, str1, strlen((char*)str1), 1000);

    osSemaphoreWait(CountSemHandle, osWaitForever);
    uint8_t str2[] = "Take 1 Semaphore\r\n";
    HAL_UART_Transmit(&huart1, str2, strlen((char*)str2), 1000);

    osSemaphoreWait(CountSemHandle, osWaitForever);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    uint8_t str3[] = "Leave Task 1\r\n";
    HAL_UART_Transmit(&huart1, str3, strlen((char*)str3), 1000);

  }

}


void Task02(void const * argument)
{

  for(;;)
  {
    uint8_t str4[] = "Enter Task2\r\n";
    HAL_UART_Transmit(&huart1, str4, strlen((char *)str4), 1000);
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1)
    {
    	uint8_t str5[] = "Pin A1 on\r\n";
    	HAL_UART_Transmit(&huart1, str5, strlen((char *)str5), 1000);
    	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);


    }

    //while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1);
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 1)
    {
    	uint8_t str6[] = "Pin A2 on\r\n";
    	HAL_UART_Transmit(&huart1, str6, strlen((char *)str6), 1000);
    	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
    }
    //while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 1);
    osSemaphoreRelease(CountSemHandle);
    uint8_t str7[] = "Leave Task2\r\n";
    HAL_UART_Transmit(&huart1, str7, strlen((char *)str7), 1000);
    osDelay(1000);
    }
  }




void Task03(void const * argument)
{

  for(;;)
  {
    uint8_t str7[] = "Enter Task 3\r\n";
    HAL_UART_Transmit(&huart1, str7, strlen((char *)str7), 1000);
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
    	{

    	uint8_t str8[] = "Pin A3 on\r\n";
    	HAL_UART_Transmit(&huart1, str8, strlen((char *)str8), 1000);

    	vTaskSuspend(Task1Handle);
    	uint8_t str9[] = "Task 1 Suspend\r\n";
    	  HAL_UART_Transmit(&huart1, str9, strlen((char *)str9), 1000);
    	}
    	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
    	{

    	uint8_t str10[] = "Pin A3 off\r\n";
    	  HAL_UART_Transmit(&huart1, str10, strlen((char *)str10), 1000);
    	vTaskResume(Task1Handle);
    	uint8_t str11[] = "Task 1 continue\r\n";
    	 HAL_UART_Transmit(&huart1, str11, strlen((char *)str11), 1000);
        osSemaphoreRelease(CountSemHandle);
        uint8_t str12[] = "Leave Task 3\r\n";
         HAL_UART_Transmit(&huart1, str12, strlen((char *)str12), 1000);
        osDelay(1000);
  }
  /* USER CODE END Task03 */
}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
