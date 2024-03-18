/*
 * MemoryUtilities.h
 *
 *  Created on: Jul. 4, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_MEMORYUTILITIES_H_
#define INC_MEMORYUTILITIES_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "./LittleFS/lfs_util.h"
#include "./LittleFS/lfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPLED1_Pin GPIO_PIN_2
#define GPLED1_GPIO_Port GPIOE
#define GPLED2_Pin GPIO_PIN_3
#define GPLED2_GPIO_Port GPIOE
#define GPLED3_Pin GPIO_PIN_4
#define GPLED3_GPIO_Port GPIOE
#define CAMERA_EN_Pin GPIO_PIN_2
#define CAMERA_EN_GPIO_Port GPIOA
#define GPS_PPS_Pin GPIO_PIN_6
#define GPS_PPS_GPIO_Port GPIOA
#define FLASH_NCS_A2_Pin GPIO_PIN_0
#define FLASH_NCS_A2_GPIO_Port GPIOG
#define FLASH_NCS_A1_Pin GPIO_PIN_1
#define FLASH_NCS_A1_GPIO_Port GPIOG
#define FLASH_CS_A0_Pin GPIO_PIN_7
#define FLASH_CS_A0_GPIO_Port GPIOE
#define FRAM_NCS_1_Pin GPIO_PIN_8
#define FRAM_NCS_1_GPIO_Port GPIOE
#define FRAM_NCS_0_Pin GPIO_PIN_9
#define FRAM_NCS_0_GPIO_Port GPIOE
#define MOTOR_NFAULT_Pin GPIO_PIN_12
#define MOTOR_NFAULT_GPIO_Port GPIOB
#define MOTOR_NEN_Pin GPIO_PIN_13
#define MOTOR_NEN_GPIO_Port GPIOB
#define MOTOR_PWM_Pin GPIO_PIN_14
#define MOTOR_PWM_GPIO_Port GPIOB
#define MOTOR_DIR_Pin GPIO_PIN_15
#define MOTOR_DIR_GPIO_Port GPIOB
#define ENCODER_EN_Pin GPIO_PIN_8
#define ENCODER_EN_GPIO_Port GPIOD
#define ENCODER_I_Pin GPIO_PIN_9
#define ENCODER_I_GPIO_Port GPIOD
#define ENCODER_B_Pin GPIO_PIN_10
#define ENCODER_B_GPIO_Port GPIOD
#define ENCODER_A_Pin GPIO_PIN_11
#define ENCODER_A_GPIO_Port GPIOD
#define MPI_RX_NEN_Pin GPIO_PIN_4
#define MPI_RX_NEN_GPIO_Port GPIOG
#define MPI_TX_EN_Pin GPIO_PIN_5
#define MPI_TX_EN_GPIO_Port GPIOG

static const uint8_t FLASH_READ = 0x03;
static const uint8_t FLASH_WRITE = 0x02;
static const uint8_t FLASH_WREN = 0x06;
static const uint8_t FLASH_WRDI = 0x04;
static const uint8_t FLASH_ER4 = 0x20;
static const uint8_t FLASH_ER32 = 0x52;
static const uint8_t FLASH_ER64 = 0xd8;
static const uint8_t FLASH_ERCP = 0xC7;
static const uint8_t FLASH_STATREG1 = 0X05;
static const uint8_t FLASH_SECTOR_ERASE = 0xD8;

typedef struct CircularBuffer {
	uint32_t head;
	uint32_t tail;
	uint16_t count;
} CircularBuffer;

void PULL_CS();
void SET_CS();
void READ_STATUS_REGISTER(SPI_HandleTypeDef *, uint8_t *);
void ENABLE_WREN(SPI_HandleTypeDef *);
void ENABLE_WRDI(SPI_HandleTypeDef *);
void BULK_MEM_CLEAR(SPI_HandleTypeDef *);
void MEM_CLEAR(SPI_HandleTypeDef *, uint8_t *);
void MEM_CLEAR_LFS(SPI_HandleTypeDef *, lfs_block_t);

#endif /* INC_MEMORYUTILITIES_H_ */
