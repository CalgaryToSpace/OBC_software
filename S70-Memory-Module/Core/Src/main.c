/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 **02****************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct DecoderInput {
	uint64_t Port;
	uint16_t Pin;
	uint8_t State;

} DecoderInput;

typedef struct CircularBuffer {
//	uint64_t size;
	uint8_t data[128];
	uint16_t head;
	uint16_t tail;
	uint16_t count;
// add counter for which of 1 out 8 memory modules we are in
// the buffersize should be changed to be the size of 1 module
// every time it passes it, this variable gets updated by mod 8

// receive stream of data, must turn into packet of some size (established soon)

} CircularBuffer;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUFFER_SIZE 128

// 256 KB per sector (256 * 1000) * 256 sectors
#define MEMORY_MODULE_SIZE (256 * 1000) * 256 // About 65 megabytes
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim15;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

// Equal to GPIO_PIN_SET, for this architecture
// 1 is the inactive state
// 0 is the active state
const uint8_t INACTIVE_STATE = 1;
const uint8_t ACTIVE_STATE = 0;

//static DecoderInput A0;
//static DecoderInput A1;
//static DecoderInput A2;

static CircularBuffer cb;

/***************************************
 * 	Look at Pages 75, 76, 77
 *
 ****************************************/

/* The following are defined in the S25... Manual
 * Section 7.6.1, 9.3
 */
//const uint8_t WRR_WriteRegister = 0x01;
const uint8_t CLSR_ClearStatusReg = 0x30;
//
//const uint8_t RDSR1_ReadStatusReg1 = 0x05;
//const uint8_t RDSR2_ReadStatusReg2 = 0x07;
//const uint8_t RDCR_ReadConfigReg = 0x35;
//const uint8_t BRRD_ReadBankReg = 0x16;
//
//const uint8_t BRWR_WriteBankReg = 0x17;
//const uint8_t BRAC_BankRegAccess = 0xB9;
////const uint8_t WriteReg = 0x01;
//const uint8_t WREN_WriteEnable = 0x06;
//const uint8_t WRDI_WriteDisable = 0x04;
//
//const uint8_t ECCRD_ECCRead = 0x18;
//

const uint8_t FLASH_READ = 0x03;
const uint8_t FLASH_WRITE = 0x02;
const uint8_t FLASH_WREN = 0x06;
const uint8_t FLASH_WRDI = 0x04;
const uint8_t FLASH_ER4 = 0x20;
const uint8_t FLASH_ER32 = 0x52;
const uint8_t FLASH_ER64 = 0xd8;
const uint8_t FLASH_ERCP = 0xC7;
const uint8_t FLASH_STATREG1 = 0X05;
const uint8_t FLASH_SECTOR_ERASE = 0xD8;

uint8_t memory_bank_counter = 0;

/*
 * The instruction
 * 03h (ExtAdd=0) is followed by a 3-byte address (A23-A0) or
 * 03h (ExtAdd=1) is followed by a 4-byte address (A31-A0) or
 * 13h is followed by a 4-byte address (A31-A0)
 *
 * Then the memory contents, at the address given, are shifted out on SO. The maximum operating clock frequency
 * for the READ command is 50 MHz.
 *
 * The address can start at any byte location of the memory array. The address is automatically incremented to the
 * next higher address in sequential order after each byte of data is shifted out.
 *
 * The entire memory can therefore
 * be read out with one single read instruction and address 000000h provided.
 *
 * When the highest address is reached,the address counter will wrap around and roll back to 000000h, allowing the read sequence to be continued
 * indefinitely.
 *
 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C3_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM15_Init(void);
static void MX_UART4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
//static void INIT_DECODER_INPUTS(void);
//static void init_buffer(void);

void PRINT_STRING_UART(void*);
void PULL_ALL_LOW();
void SET_CS();
void PRINT_NEW_LINE();
void READ_STATUS_REGISTER(void*);
void ENABLE_WREN();
void ENABLE_WRDI();
void PULL_CS();
void MEM_CLEAR(void *);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//typedef struct CircularBuffer{
//	uint8_t data[BUFFER_SIZE];
//	uint16_t head;
//	uint16_t tail;
//	uint16_t count;
//	// add counter for which of 1 out 8 memory modules we are in
//	// the buffersize should be changed to be the size of 1 module
//	// every time it passes it, this variable gets updated by mod 8
//
//	// receive stream of data, must turn into packet of some size (established soon)
//
//
//} CircularBuffer;
//
//	void setMemoryBank()
//	void init_buffer(CircularBuffer *cb) {
//		cb->head = 0;
//		cb->tail = 0;
//		cb->count = 0;
//	}
bool is_empty(void) {
	return cb.count == 0;
}
bool is_full(void) {
	return cb.count == BUFFER_SIZE;
}

/*
 * This to write data to memory
 * This only writes 8 bits of data at a time
 * Increments counter based on 8 bits of data
 */
//Added the if statement to check if it's the first element being added
//If it is, we need to keep the tail value the same since we want the tail
//to point to the 0th element in data
//If it's not the first element being added
//add element to the index in front of tail
//This was implemented because the tail value would never reach 8 because of the mod BUFFER_SIZE = 8
//Could change the mod value to be 9 and revert to previous enqueue function
//	void enqueue(CircularBuffer *cb, uint8_t data) {
//		if (!is_full(cb)) {
//
//		    if ((cb->count) == 0) {
//		        cb->data[cb->tail] = data;
//		        cb->tail = (cb->tail) % BUFFER_SIZE;
//		    }
//		    else {
//		        cb->data[cb->tail+1] = data;
//		        cb->tail = (cb->tail + 1) % BUFFER_SIZE;
//		    }
//
//		    cb->count++;
//		}
//	}
/*
 * This is to retrieve memory
 */
//Just set the head to 0 for the dequeue before incrementing it
//		uint8_t dequeue(CircularBuffer *cb) {
//			if (!is_empty(cb)) {
//				uint8_t data = cb->data[cb->head];
//				cb->data[cb->head] = 0;
//				cb->head = (cb->head + 1) % BUFFER_SIZE;
//				cb->count--;
//
//				return data;
//			}
//			return 0;
//		}
/*
 * 	There are 7 memory banks on board this chip,
 * 	every time it reaches the end of the memory bank,
 * 	it will need to be incremented, done by Allocate function
 */
//void WHICH_MEMORY_BANK() {
//
//	uint8_t mem_bank = (memory_bank_counter % 8);
//	A0.State = mem_bank & 0x1; // LSB
//	A1.State = mem_bank & 0x2; // Middle Bit
//	A2.State = mem_bank & 0x4; // MSB
//
//
//}
//	bool is_empty(CircularBuffer *cb) {
//		return cb->count == 0;
//	}
//	bool is_full(CircularBuffer *cb) {
//		return cb->count == BUFFER_SIZE;
//	}
//	void enqueue(CircularBuffer *cb, uint8_t data) {
//		if (!is_full(cb)) {
//			cb->data[cb->tail] = data;
//			cb->tail = (cb->tail + 1) % BUFFER_SIZE;
//			cb->count++;
//		}
//	}
//	uint8_t dequeue(CircularBuffer *cb) {
//		if (!is_empty(cb)) {
//			uint8_t data = cb->data[cb->head];
//			cb->head = (cb->head + 1) % BUFFER_SIZE;
//			cb->count--;
//			return data;
//		}
//		return 0;
//	}


typedef enum {A, B, C} packet_type;

typedef struct telemetry {
	packet_type type;
	int secondsSinceBoot;
	double temperature;
} tel __attribute__ ((aligned));

struct MRI_Data {
	packet_type type;
	char data[100];
	int time_collected;
};

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	char spiRxBuffer[100] = {0};
	char spiTxBuffer[100] = {0};
	char statusRegBuffer[9] = {0};

	char testBuffer[100] = {0};
	char testBuffer2[100] = {0};

	memset(testBuffer, 0x0, 100);
	memset(testBuffer2, 0x0, 100);

	uint8_t addr[3] = { 0 };
	uint8_t wip;

	tel t;

	t.secondsSinceBoot = 12;
	t.temperature = 3.2;
	t.type = B;

	uint8_t typeSize = sizeof(t.type);
	uint8_t secondsSize = sizeof(t.secondsSinceBoot);

	memcpy(testBuffer, &t, sizeof(t));

	size_t i = 0;
	uint8_t del_size = 0;

	//7D 01 21 0C0C0C0C 21 FLOAT
	// 0  1  2  3 4 5 6  7 8

	while (i < sizeof(t) + 3) {
		if (i == 0) { // if i == 0, add starting character
			sprintf(testBuffer2 + (i * 2), "%02X", '}'); //7D
			del_size++;
		}
		else if (i < typeSize + 1) { // If i < 2, accessing i == 1, buffer indices 0
			sprintf(testBuffer2 + (i * 2), "%02X", testBuffer[i-del_size]);
		}
		else if (i == typeSize + 1) { // If i == 2, add a delimiter
			sprintf(testBuffer2 + (i * 2), "%02X", '!'); //21
			del_size++;
		}
		else if (i < secondsSize + typeSize + 2) { // If i < 7, accessing i == 3, 4, 5, 6, buffer indices 1, 2, 3, 4
			sprintf(testBuffer2 + (i * 2), "%02X", testBuffer[i-del_size]);
		}
		else if (i == secondsSize + typeSize + 2) { // i == 7, add a delimiter
			sprintf(testBuffer2 + (i * 2), "%02X", '!');
			del_size++;
		}
		else { // If i > 7, accessing i == 8, 9, ..., 15, buffer indices 5, 6, ... ,12
			sprintf(testBuffer2 + (i * 2), "%02X", testBuffer[i-del_size]);
		}
		i++;
	}

//
//	for (size_t i = 0; i < sizeof(tel); i++) {
//		sprintf(&testBuffer2[i * 2], "%02X", testBuffer[i]);
//	}
//
//	PRINT_STRING_UART(testBuffer2);

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
	MX_I2C1_Init();
	MX_I2C2_Init();
	MX_I2C3_Init();
	MX_SPI1_Init();
	MX_TIM15_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */

	//Turn on LED1 to indicate program starting
	HAL_GPIO_WritePin(GPLED1_GPIO_Port, GPLED1_Pin, GPIO_PIN_SET);

	//Clear Memory before using memory
	MEM_CLEAR(addr);

	//Read the Status Register and store it in the corresponding buffer
	READ_STATUS_REGISTER(spiRxBuffer);

	// Clear 1 sector starting from 0x0
	// Note how I am sending 3 bytes from addr,
	// This is because the Sector Erase requires a 3 byte address

	ENABLE_WREN();
	PULL_CS();
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_SECTOR_ERASE, 1, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &addr, 3, 100);
	SET_CS();

	wip = 1;
	while (wip) {
		READ_STATUS_REGISTER(spiRxBuffer);

		wip = spiRxBuffer[0] & 1;
	}

	// Write data
	ENABLE_WREN();

//	strcpy((char*) spiTxBuffer, "jhbgtyty 654646");
	strcpy((char*) spiTxBuffer, testBuffer2);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_WRITE, 1, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &spiTxBuffer, 100, 100);
	SET_CS();

	wip = 1;
	while (wip) {
		READ_STATUS_REGISTER(spiRxBuffer);

		wip = spiRxBuffer[0] & 1;
	}

	// Read
	PULL_CS();
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_READ, 1, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Receive(&hspi1, (uint8_t*) spiRxBuffer, 100, 100);
	SET_CS();

	PRINT_STRING_UART(spiRxBuffer);

	// Turn off LED
	HAL_GPIO_WritePin(GPLED1_GPIO_Port, GPLED1_Pin, GPIO_PIN_RESET);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00606092;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void) {

	/* USER CODE BEGIN I2C2_Init 0 */

	/* USER CODE END I2C2_Init 0 */

	/* USER CODE BEGIN I2C2_Init 1 */

	/* USER CODE END I2C2_Init 1 */
	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x00606092;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C2_Init 2 */

	/* USER CODE END I2C2_Init 2 */

}

/**
 * @brief I2C3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C3_Init(void) {

	/* USER CODE BEGIN I2C3_Init 0 */

	/* USER CODE END I2C3_Init 0 */

	/* USER CODE BEGIN I2C3_Init 1 */

	/* USER CODE END I2C3_Init 1 */
	hi2c3.Instance = I2C3;
	hi2c3.Init.Timing = 0x00606092;
	hi2c3.Init.OwnAddress1 = 0;
	hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c3.Init.OwnAddress2 = 0;
	hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c3) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C3_Init 2 */

	/* USER CODE END I2C3_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

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
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 7;
	hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief TIM15 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM15_Init(void) {

	/* USER CODE BEGIN TIM15_Init 0 */

	/* USER CODE END TIM15_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = { 0 };

	/* USER CODE BEGIN TIM15_Init 1 */

	/* USER CODE END TIM15_Init 1 */
	htim15.Instance = TIM15;
	htim15.Init.Prescaler = 0;
	htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim15.Init.Period = 65535;
	htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim15.Init.RepetitionCounter = 0;
	htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim15) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM15_Init 2 */

	/* USER CODE END TIM15_Init 2 */
	HAL_TIM_MspPostInit(&htim15);

}

/**
 * @brief UART4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_UART4_Init(void) {

	/* USER CODE BEGIN UART4_Init 0 */

	/* USER CODE END UART4_Init 0 */

	/* USER CODE BEGIN UART4_Init 1 */

	/* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart4) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */

	/* USER CODE END UART4_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

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
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK) {
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
static void MX_USART3_UART_Init(void) {

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
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK) {
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
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	HAL_PWREx_EnableVddIO2();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE,
			GPLED1_Pin | GPLED2_Pin | GPLED3_Pin | FLASH_CS_A0_Pin
					| FRAM_NCS_1_Pin | FRAM_NCS_0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(CAMERA_EN_GPIO_Port, CAMERA_EN_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOG,
	FLASH_NCS_A2_Pin | FLASH_NCS_A1_Pin | MPI_RX_NEN_Pin | MPI_TX_EN_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, MOTOR_NFAULT_Pin | MOTOR_NEN_Pin | MOTOR_DIR_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD,
	ENCODER_EN_Pin | ENCODER_I_Pin | ENCODER_B_Pin | ENCODER_A_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : GPLED1_Pin GPLED2_Pin GPLED3_Pin FLASH_CS_A0_Pin
	 FRAM_NCS_1_Pin FRAM_NCS_0_Pin */
	GPIO_InitStruct.Pin = GPLED1_Pin | GPLED2_Pin | GPLED3_Pin | FLASH_CS_A0_Pin
			| FRAM_NCS_1_Pin | FRAM_NCS_0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : CAMERA_EN_Pin */
	GPIO_InitStruct.Pin = CAMERA_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CAMERA_EN_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : GPS_PPS_Pin */
	GPIO_InitStruct.Pin = GPS_PPS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPS_PPS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : FLASH_NCS_A2_Pin FLASH_NCS_A1_Pin MPI_RX_NEN_Pin MPI_TX_EN_Pin */
	GPIO_InitStruct.Pin = FLASH_NCS_A2_Pin | FLASH_NCS_A1_Pin | MPI_RX_NEN_Pin
			| MPI_TX_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pins : MOTOR_NFAULT_Pin MOTOR_NEN_Pin MOTOR_DIR_Pin */
	GPIO_InitStruct.Pin = MOTOR_NFAULT_Pin | MOTOR_NEN_Pin | MOTOR_DIR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : ENCODER_EN_Pin ENCODER_I_Pin ENCODER_B_Pin ENCODER_A_Pin */
	GPIO_InitStruct.Pin = ENCODER_EN_Pin | ENCODER_I_Pin | ENCODER_B_Pin
			| ENCODER_A_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void PULL_CS() {
//	// same as memory_bank_counter % 8
//	uint8_t mem_bank = (memory_bank_counter & 0x7);
//	uint8_t lsb = mem_bank & 0x1;
//	uint8_t middle_bit = mem_bank & 0x2;
//	uint8_t msb = mem_bank & 0x4;
//
//	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // LSB
////	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET); // Middle Input
////	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET); // MSB
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // LSB

}

/*
 * @param expects a char pointer
 * @return Nothing, just prints the string to UART
 */
void PRINT_STRING_UART(void *string) {
//	char *buff = (char*) string;
	HAL_UART_Transmit(&huart1, (uint8_t*) string, strlen((char*) string), 100);
	PRINT_NEW_LINE();
//	memset(string, 0, strlen((char*) string));
}

/*
 * Pulls all Chip Selects Low
 * Essentially, accessing Memory bank 0, (000)
 */
void PULL_ALL_LOW() {
//	HAL_GPIO_WritePin(FLASH_CS_A0_GPIO_Port, FLASH_CS_A0_Pin, GPIO_PIN_RESET);
	// Below is A0
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	// A1
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
	// A2
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(FLASH_NCS_A1_GPIO_Port, FLASH_NCS_A1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(FLASH_NCS_A2_GPIO_Port, FLASH_NCS_A2_Pin, GPIO_PIN_RESET);
}

/*
 * Pull Chip Select High
 *
 * This is the default state of the CS
 */
void SET_CS() {
//	// Below is A0
//	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
//	// A1
////	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
//////	// A2
////	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
}

/*
 * Write's new Line to UART
 */
void PRINT_NEW_LINE() {
	char buf[] = "\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, strlen(buf), 100);
}
/*
 * @param Takes any type of array/pointer, always converts to uint8_t pointer
 * @return Nothing, Reads Status Register, stores value in param
 * Sets Decoder Inputs BeforeHand
 * Pull All Decoder Inputs High After
 *
 */
void READ_STATUS_REGISTER(void *rxBuf) {
	PULL_CS();
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_STATREG1, 1, 100);
	HAL_SPI_Receive(&hspi1, (uint8_t*) rxBuf, 1, 100);
	SET_CS();
}
/*
 * Just Transmit WREN Command
 * Sets Decoder Inputs beforehand
 * Pull all Decoder Inputs High After
 */
void ENABLE_WREN() {
	PULL_CS();
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_WREN, 1, 100);
	SET_CS();
}

/*
 * Just Transmit WRDI Command
 * As noted  in Section 9.3.9 of the Manual,
 * ALL Chip Selects must be pulled high in order for this command
 * to go through
 */
void ENABLE_WRDI() {
	SET_CS();
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_WRDI, 1, 100);

}

void MEM_CLEAR(void * addr) {
	ENABLE_WREN();

	PULL_CS();
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&FLASH_SECTOR_ERASE, 1, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&addr, 3, 100);
	SET_CS();

	uint8_t wip = 1;
	while (wip) {
		uint8_t buf[100];
		READ_STATUS_REGISTER(buf);
		wip = 1 & buf[0];
	}
}

//static void init_DecoderInputs(DecoderInput * LSB, DecoderInput * MiddleBit, DecoderInput * MSB) {
////		LSB->ACTIVE_STATE, MiddleBit->ACTIVE_STATE, MSB->ACTIVE_STATE = 0;
////		LSB->INACTIVE_STATE, MiddleBit->INACTIVE_STATE, MSB->INACTIVE_STATE = 1;
//
//	LSB->Port = FLASH_CS_A0_GPIO_Port;
//	MiddleBit->Port = FLASH_NCS_A1_GPIO_Port;
//	MSB->Port = FLASH_NCS_A2_GPIO_Port;
//
//	LSB->Pin = FLASH_CS_A0_Pin;
//	MiddleBit->Pin = FLASH_NCS_A1_Pin;
//	MSB->Pin = FLASH_NCS_A2_Pin;
//
//	// Equivalent to making state = GPIO_PIN_SET
//	LSB->State, MiddleBit->State, MSB->State = INACTIVE_STATE;
//}
//

//void init_buffer(void) {
////			cb.size = BUFFER_SIZE;
//	cb.head = 0;
//	cb.tail = 0;
//	cb.count = 0;
//}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
