/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "uart.h"
#include "threads.h"
#include "queue.h"
#include "queueManagement.h"


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


/* Definitions for defaultTask */

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

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
  startUart();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  //osThreadNew(StartTest1, NULL, 8*128);

  //osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of uartMutex */

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
  QueueHandle_t xQueue = xQueueCreate(5, sizeof(Data_t));
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */


  /* USER CODE BEGIN RTOS_THREADS */

  //QueueHandle_t xQueue = xQueueCreate(5, sizeof(Data_t));

  DataSend_t mpiData = {xQueue, (xStructsToSend[0])};
  DataSend_t cameraData = {xQueue, (xStructsToSend[1])};
  DataSend_t gpsData = {xQueue, (xStructsToSend[2])};

  struct threadInfo running[6];
  running[0] = startThread(StartTest1, osPriorityLow, "ThreadOne", NULL, 8*128);
  running[1] = startThread(StartTest2, osPriorityHigh, "ThreadTwo", NULL, 8*128);

  if(xQueue != NULL) {

  		running[2] = startThread(vSenderTask, osPriorityLow, "MPI",  &mpiData, 8*128); //changed startThread() in threadManagement.c to add another parameter
  		running[3] = startThread(vSenderTask, osPriorityLow, "Camera", &cameraData, 8*128);
  		running[4] = startThread(vSenderTask, osPriorityLow, "GPS", &gpsData, 8*128);

  		//Sender tasks have lower priority than receiving task
  		running[5] = startThread(vReceiverTask, osPriorityHigh, "Receiver", (void*)xQueue , 8*128);

  	} else {

  		sendUartMessage("Queue could not be created.", 27);
  		sendUartMessage("\n", 1);
  		sendUartMessage("\r", 1);

  	}
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
   osKernelStart();
  //char* functionName = "StartTest1";
  //char* taskName = "Test 1";
  //startTask(functionName, 10, taskName, 4*128);
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

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */


/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the threadTwo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */


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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
