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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
 UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */
enum Capture_Status Capture_Image(bool flash, char lighting);
void receiveImage();
enum Capture_Status{Transmit_Success, Wrong_input};
uint32_t hex2int(char *hex);
uint64_t xtou64(const char *str);
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



/*****************************************/


  /* USER CODE BEGIN 1 */
	//lpuart1 for communication between laptop and board
	//huart2 for communication between board and camera
	const char *h2 = "huart2\n";
	const char *h3 = "m\n";
	const char *lp = "000F";
	uint8_t bruh[6];
	int testhex;
	char testi[10];


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
  MX_USART2_UART_Init();
  //MX_USART3_UART_Init();
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  HAL_UART_Transmit(&hlpuart1, (uint8_t*)lp, strlen(lp), HAL_MAX_DELAY);

	  /*
	   * char hex_string[] = "0x1F";
		 char *endptr;
		 int hex_int = (int) strtol(hex_string, &endptr, 16);
	   *
	   */
	  	  	  memset(bruh, '\0', 4);
//	  	  	  HAL_UART_Receive(&hlpuart1, bruh, 6, HAL_MAX_DELAY);
//	  	  	  HAL_UART_Transmit(&hlpuart1, bruh, 4, HAL_MAX_DELAY);


//	  	  	  testhex = hex2int(((char*)bruh));
//	  	  	  itoa(testhex,testi,10);

//	  	  	  int hex_int = (int) strtol(bruh, NULL, 16);

//	  	  	  uint8_t hex_uint8 = hex_int;

//	  	  	  HAL_UART_Transmit(&hlpuart1, &hex_uint8, strlen(hex_int), HAL_MAX_DELAY);
//	  	  	  HAL_UART_Transmit(&hlpuart1, (uint8_t*)testi, strlen(testi), HAL_MAX_DELAY);
//	  	  	  HAL_UART_Transmit(&hlpuart1, (uint8_t*)h3, 2, HAL_MAX_DELAY);
//	  	  	  HAL_Delay(500);
//	  	  	  HAL_UART_Transmit(&hlpuart1, (uint8_t*)h2, 7, HAL_MAX_DELAY);
//	  	  	  HAL_Delay(500);
//	  	  	  HAL_UART_Transmit(&hlpuart1, bruh, 6, HAL_MAX_DELAY);
	  		  Capture_Image(false, 'd');
//	  		  HAL_UART_Transmit(&hlpuart1, bruh, 4, HAL_MAX_DELAY);
//

//	  	  	  HAL_Delay(1000);

//	  	  	  HAL_UART_Transmit(&huart2, (uint8_t*)h3, 1, HAL_MAX_DELAY);
//	  	  	  for(int i = 0; i <100; i++){
//	  	  		  HAL_UART_Receive(&huart2, (uint8_t*)bruh, 67, HAL_MAX_DELAY);
//	  	  		  HAL_UART_Transmit(&hlpuart1, (uint8_t*)bruh, 67, HAL_MAX_DELAY);
//	  	  	  }

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOD_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        uint8_t byte = *hex++;
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}

uint64_t xtou64(const char *str)
{
    uint64_t res = 0;
    char c;

    while ((c = *str++)) {
        char v = (c & 0xF) + (c >> 6) | ((c >> 3) & 0x8);
        res = (res << 4) | (uint64_t) v;
    }

    return res;
}

const char *hm = "d";

	  void receiveImage(){

	  		  // create group of 100 sentences
	  		  char group[100][68];
	  		  // create counter for number of sentences
	  		  int SentencesNum = 0;
	  		  bool loop = true;
	  		  // initialize chars and ints for hex values
	  		  char hexTotal[5];

	  		  char *mockSentence = "000003DEFFD8FFDB0084000D09090B0A080D0B0A0B0E0E0D0F13201513121213";
	  		  uint64_t totalSentences = 0;

	  		  while(loop){
	  			// receive first sentence, get total number of sentences and send
			  char sentence[100];
			  memset(sentence, '\0', sizeof(sentence));
//	  			memset(sentence, 0, sizeof(sentence));
	  			HAL_UART_Transmit(&hlpuart1, (uint8_t*)"TTT3", 4, HAL_MAX_DELAY);
	  			  // get sentence
//	  			  HAL_UART_Receive(&huart2, (uint8_t*)sentence, 67, HAL_MAX_DELAY);
	  			  HAL_UART_Receive(&hlpuart1, (uint8_t*)sentence, 68, 10000);
//	  			HAL_UART_Receive_DMA (&hlpuart1, sentence, 67);
	  			HAL_UART_Transmit(&hlpuart1, (uint8_t*)"test", 4, HAL_MAX_DELAY);

	  				  strncpy(&hexTotal, &sentence[5], 4);
	  				  hexTotal[4] = '\0';
	//  		  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)hexTotal, 5, HAL_MAX_DELAY);

//	  		    		  char *ptr;

	  				  totalSentences = hex2int(hexTotal);

//	  				  	  totalSentences = strtol(hexTotal, &ptr, 0);
//	  				  	  totalSentences = hex2int(hexTotal);

//	  		  		  HAL_UART_Transmit(&hlpuart1, &hexTotal, 4, HAL_MAX_DELAY);

	  			  // add sentence to group at index SentenceNum(starts at 0 and increases by 1 every iteration)
	  			  strcpy(group[SentencesNum],sentence);
	  			  SentencesNum += 1;
	  			  //if SentencesNum becomes = to 100, write group to mem, and subtract 100 from totalSentences and make SentencesNum =0
	  			  if(SentencesNum == 100){
	  				  HAL_UART_Transmit(&hlpuart1, (uint8_t*)group, ((SentencesNum)*67), HAL_MAX_DELAY);
	  				  //memWrite(CAMERA_DATA, group, ((sentencesNum)*67));

	  				  totalSentences -= 100;
	  				  SentencesNum = 0;
	  				  // re initialize group to empty it
	  				  char group[100][68];
	  			  }

//	  			   if totalSentences becomes less than 100 then break out of loop and use for loop to get the remaining sentences
	  			  if(totalSentences < 100){
	  				  loop = false;
	  			  }
	  		  }
	  		// receive first sentence, get total number of sentences and send
	  			  		  char sentence[67];
	  		  // if totalSetences is less than 100, add the rest to group and write to mem
	  		  	  if(totalSentences < 100){
	  		  		  for(int i=0; i<totalSentences; i++){
	  		  			// get sentence
	  		  			HAL_UART_Receive(&huart2, (uint8_t*)sentence, 67, HAL_MAX_DELAY);
	  		  			// add to group
	  		  			strcpy(group[i],sentence);
	  		  			SentencesNum += 1;
	  		  		  }
	  		  		  // once all are added then write group to mem
	  		  		//memWrite(CAMERA_DATA, group, ((sentencesNum)*67));
	  		  		HAL_UART_Transmit(&hlpuart1, (uint8_t*)group, ((SentencesNum)*67), HAL_MAX_DELAY);
	  		  	  }

	  		  // receive final telemetry sentence
	  		  	HAL_UART_Receive(&huart2, (uint8_t*)sentence, 67, HAL_MAX_DELAY);
	  		  	HAL_UART_Transmit(&hlpuart1, (uint8_t*)sentence, 67, HAL_MAX_DELAY);
	  		  	//memWrite(CAMERA_DATA, group, 67);


	  }




	    /**
	     * Transmits ASCII telecommand based on input
	     * @param lighting - lighting should be a *lower case* char
	     * 			d - daylight ambient light
	     * 			m - medium ambient light
	     * 			n - night ambient light
	     * 			s - solar sail contrast and light
	     */
	    enum Capture_Status Capture_Image(bool flash, char lighting){
  			HAL_UART_Transmit(&hlpuart1, (uint8_t*)"TTT1", 4, HAL_MAX_DELAY);

	  	  switch(lighting){
	  	  case 'd':
	  		  if(flash){
	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"D", 1, HAL_MAX_DELAY);
	  			  HAL_Delay(25);
	  		  }
	  		  else{
	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"d", 1, HAL_MAX_DELAY);
	  			  HAL_Delay(25);
	  		  }
	  		break;
	  	  case 'm':
	  	  		  if(flash){
	  	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"M", 1, HAL_MAX_DELAY);
	  	  			  HAL_Delay(25);
	  	  		  }
	  	  		  else{
	  	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"m", 1, HAL_MAX_DELAY);
	  	  			  HAL_Delay(25);
	  	  		  }
	  	  		break;
	  	  case 'n':
	  	  		  if(flash){
	  	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"N", 1, HAL_MAX_DELAY);
	  	  			  HAL_Delay(25);
	  	  		  }
	  	  		  else{
	  	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"n", 1, HAL_MAX_DELAY);
	  	  			  HAL_Delay(25);
	  	  		  }
	  	  		break;
	  	  case 's':
	  	  		  if(flash){
	  	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"S", 1, HAL_MAX_DELAY);
	  	  			  HAL_Delay(25);
	  	  		  }
	  	  		  else{
	  	  			  HAL_UART_Transmit(&hlpuart1, (uint8_t*)"s", 1, HAL_MAX_DELAY);
	  	  			  HAL_Delay(25);
	  	  		  }
	  	  		  break;
	  	  default:
	  		  return Wrong_input;
	  	  }
			HAL_UART_Transmit(&hlpuart1, (uint8_t*)"TTT2", 4, HAL_MAX_DELAY);
	  	receiveImage();
	  	return Transmit_Success;

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
