/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
//#define B1_Pin GPIO_PIN_13
//#define B1_GPIO_Port GPIOC
//#define LD3_Pin GPIO_PIN_14
//#define LD3_GPIO_Port GPIOB
//#define STLK_RX_Pin GPIO_PIN_8
//#define STLK_RX_GPIO_Port GPIOD
//#define STLK_TX_Pin GPIO_PIN_9
//#define STLK_TX_GPIO_Port GPIOD
//#define USB_PowerSwitchOn_Pin GPIO_PIN_5
//#define USB_PowerSwitchOn_GPIO_Port GPIOG
//#define USB_OverCurrent_Pin GPIO_PIN_6
//#define USB_OverCurrent_GPIO_Port GPIOG
//#define STLINK_TX_Pin GPIO_PIN_7
//#define STLINK_TX_GPIO_Port GPIOG
//#define STLINK_RX_Pin GPIO_PIN_8
//#define STLINK_RX_GPIO_Port GPIOG
//#define TMS_Pin GPIO_PIN_13
//#define TMS_GPIO_Port GPIOA
//#define TCK_Pin GPIO_PIN_14
//#define TCK_GPIO_Port GPIOA
//#define SWO_Pin GPIO_PIN_3
//#define SWO_GPIO_Port GPIOB
//#define LD2_Pin GPIO_PIN_7
//#define LD2_GPIO_Port GPIOB

// Assignments from Memory Module code
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

//#define MOTOR_NFAULT_Pin GPIO_PIN_12
//#define MOTOR_NFAULT_GPIO_Port GPIOB
//#define MOTOR_NEN_Pin GPIO_PIN_13
#define MOTOR_NEN_GPIO_Port GPIOB
#define MOTOR_PWM_Pin GPIO_PIN_14
#define MOTOR_PWM_GPIO_Port GPIOB
#define MOTOR_DIR_Pin GPIO_PIN_15
//#define MOTOR_DIR_GPIO_Port GPIOB
//#define ENCODER_EN_Pin GPIO_PIN_8
#define ENCODER_EN_GPIO_Port GPIOD
//#define ENCODER_I_Pin GPIO_PIN_9
#define ENCODER_I_GPIO_Port GPIOD
#define ENCODER_B_Pin GPIO_PIN_10
#define ENCODER_B_GPIO_Port GPIOD
#define ENCODER_A_Pin GPIO_PIN_11
#define ENCODER_A_GPIO_Port GPIOD

#define MPI_RX_NEN_Pin GPIO_PIN_4
#define MPI_RX_NEN_GPIO_Port GPIOG
#define MPI_TX_EN_Pin GPIO_PIN_5
#define MPI_TX_EN_GPIO_Port GPIOG

// Assignments from MPI Code
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_12		// Modified from GPIO_PIN_5 to GPIO_PIN_12
#define USB_PowerSwitchOn_GPIO_Port GPIOB		// Modified from GPIOG to GPIOB
#define USB_OverCurrent_Pin GPIO_PIN_4			// Modified from GPIO_PIN_6 to GPIO_PIN_4
#define USB_OverCurrent_GPIO_Port GPIOG
#define STLINK_TX_Pin GPIO_PIN_7
#define STLINK_TX_GPIO_Port GPIOG
#define STLINK_RX_Pin GPIO_PIN_8
#define STLINK_RX_GPIO_Port GPIOG
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB



/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
