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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
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
DMA_HandleTypeDef hdma_lpuart1_rx;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

//note assuming allocating all storage for MPI
const uint8_t FLASH_READ = 0x03;
const uint8_t FLASH_WRITE = 0x02;
const uint8_t FLASH_WREN = 0x06;
const uint8_t FLASH_WRDI = 0x04;
const uint8_t FLASH_ER4 = 0x20;
const uint8_t FLASH_ER32 = 0x52;
const uint8_t FLASH_ER64 = 0xd8;
const uint8_t FLASH_ERCP = 0xC7;
const uint8_t FLASH_STATREG1 = 0X05;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
uint8_t sendTelecommand(uint8_t commandCode, uint8_t *parameters);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t UART1_rxBuffer[160] = {0};
uint8_t MPI_sync_bytes[4] = {0x0c, 0xff, 0xff, 0x0c};
uint8_t MPI_housekeeping[18] = {0};
uint8_t UART1_txBuffer[160] = {0};
uint8_t flash_buffer[256] = {0};
uint8_t flash_buffer_capacity = 0;
uint32_t page_number = 0;
uint8_t address[3] = {0};
uint8_t spiRX_buf[256] = {0};


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
  MX_LPUART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  // This function sends commands to the MPI
  uint8_t parameter = NULL;
  uint8_t command_code = 4;
  sendTelecommand(command_code,&parameter);

  HAL_UART_Receive_DMA(&hlpuart1, UART1_rxBuffer, 160);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 30;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  hlpuart1.Init.BaudRate = 230400;
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPLED1_Pin|GPLED2_Pin|GPLED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, MPI_RX_NEN_Pin|MPI_TX_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : GPLED1_Pin GPLED2_Pin GPLED3_Pin */
  GPIO_InitStruct.Pin = GPLED1_Pin|GPLED2_Pin|GPLED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PD14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : MPI_RX_NEN_Pin MPI_TX_EN_Pin */
  GPIO_InitStruct.Pin = MPI_RX_NEN_Pin|MPI_TX_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void set_mpi_transceiver_state(mpi_transceiver_state_t new_state) {
	// Note: Can only send or receive at once

	if (new_state == MPI_TRANSCEIVER_STATE_MISO) {
		HAL_GPIO_WritePin(MPI_RX_NEN_GPIO_Port, MPI_RX_NEN_Pin, GPIO_PIN_RESET); // RESET to activate MISO
		HAL_GPIO_WritePin(MPI_TX_EN_GPIO_Port, MPI_TX_EN_Pin, GPIO_PIN_RESET); // SET to activate MOSI
	}
	else if (new_state == MPI_TRANSCEIVER_STATE_MOSI) {
		HAL_GPIO_WritePin(MPI_RX_NEN_GPIO_Port, MPI_RX_NEN_Pin, GPIO_PIN_SET); // RESET to activate MISO
		HAL_GPIO_WritePin(MPI_TX_EN_GPIO_Port, MPI_TX_EN_Pin, GPIO_PIN_SET); // SET to activate MOSI
	}
	else { // disable
		HAL_GPIO_WritePin(MPI_RX_NEN_GPIO_Port, MPI_RX_NEN_Pin, GPIO_PIN_SET); // RESET to activate MISO
		HAL_GPIO_WritePin(MPI_TX_EN_GPIO_Port, MPI_TX_EN_Pin, GPIO_PIN_RESET); // SET to activate MOSI
	}
}

// Send telecommand without parameters
// TODO: Add error check
uint8_t sendTelecommand(uint8_t commandCode, uint8_t *parameters) {
	// set to OBC transmitting
	set_mpi_transceiver_state(MPI_TRANSCEIVER_STATE_MOSI);

	// Turn on frame transmitting TC
	UART1_txBuffer[0] = 0x54;
	UART1_txBuffer[1] = 0x43;
	UART1_txBuffer[2] = commandCode;

	// Command with no parameters detected: Transmit command
	if(parameters != NULL){
		UART1_txBuffer[3] = *parameters;
	}

	// Transmit Telecommand
	HAL_UART_Transmit(&hlpuart1, (uint8_t *)UART1_txBuffer, strlen((char*)UART1_txBuffer), 100);

	// set back to the OBC receiving
	set_mpi_transceiver_state(MPI_TRANSCEIVER_STATE_MISO);

	return 1;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hlpuart1)
{
	//if its a data frame
	if(UART1_rxBuffer[0] == MPI_sync_bytes[0] && UART1_rxBuffer[1] == MPI_sync_bytes[1] && UART1_rxBuffer[2] == MPI_sync_bytes[2] && UART1_rxBuffer[3] == MPI_sync_bytes[3]){

		//calculate address array from page number
		address[0] = (page_number*0xff)& 0x000000ff;
		address[1] = (page_number*0xff)& 0x0000ff00;
		address[2] = (page_number*0xff)& 0x00ff0000;

		//store header data (uncomment in needed)
//		for(int i = 0; i < 18; i++){
//			MPI_housekeeping[i] = UART1_rxBuffer[4+i];
//		}
		
		//store into MPI buffer
		for(int i = 0; i<160; i++){
			//if buffer if full (time to write a full page)
			if(flash_buffer_capacity == 255){
			//add stored bytes
				
				//erase sector if needed
				if(page_number % 16 == 0){//if onto new sector erase that sector so it can be properly written to
				   //write enable
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, (uint8_t*)&FLASH_WREN, 1, 100);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
					
					//erase sector (16 pages)
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, (uint8_t*)&FLASH_ER4, 1, 100);
					HAL_SPI_Transmit(&hspi1, (uint8_t*)&address, 3, 100);			//write address
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

					uint8_t wip = 1;
					while (wip)	//wait will erase is done
					{
						// Read status register
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
						HAL_SPI_Transmit(&hspi1, (uint8_t *)&FLASH_STATREG1, 1, 100);	//opcode for read
						HAL_SPI_Receive(&hspi1, (uint8_t *)spiRX_buf, 1, 100);	//Receive data
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

						// Mask out WIP bit
						wip = spiRX_buf[0] & 0b00000001;
					}
				}
				
			//write new data
				//write enable
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
				HAL_SPI_Transmit(&hspi1, (uint8_t*)&FLASH_WREN, 1, 100);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

				//write data
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);	//cs low
				HAL_SPI_Transmit(&hspi1, (uint8_t*)&FLASH_WRITE, 1, 100);	//write opcode
				HAL_SPI_Transmit(&hspi1, (uint8_t*)&address, 3, 100);			//write address
				HAL_SPI_Transmit(&hspi1, (uint8_t*)&flash_buffer, 256, 100);//data
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

				//wait till write is done
				uint8_t wip = 1;
				while (wip)
				{
					// Read status register
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
					HAL_SPI_Transmit(&hspi1, (uint8_t *)&FLASH_STATREG1, 1, 100);	//opcode for read
					HAL_SPI_Receive(&hspi1, (uint8_t *)spiRX_buf, 1, 100);	//Receive data
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

					// Mask out WIP bit
					wip = spiRX_buf[0] & 0b00000001;
				}
				
				page_number+=1;
				
				//TODO: determine if need to clear flash_buffer? (is it safe?)
				flash_buffer_capacity = 1;
				flash_buffer[0] = UART1_rxBuffer[i];
			}
			
			else if(flash_buffer_capacity < 255){	//buffer not full yet...
				flash_buffer[flash_buffer_capacity] = UART1_rxBuffer[i];
				flash_buffer_capacity++;
			}
		
		}
		
	}
	
	
	
	else if(UART1_rxBuffer[0] == 0x54 && UART1_rxBuffer[1] == 0x43){
		
		if(0){	//if telecommand fails TODO: create array with TC codes, where the verification byte is. if failed, then try again 3 times max, then give up. 
			//HAL_UART_Transmit(&hlpuart1, UART1_txBuffer, strlen((char*)UART1_txBuffer), 100);
		}
	}


    HAL_UART_Receive_DMA(hlpuart1, UART1_rxBuffer, 100);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
