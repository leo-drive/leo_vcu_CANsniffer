/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#include "stm32f1xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RELAY_COIL_Pin GPIO_PIN_1
#define RELAY_COIL_GPIO_Port GPIOC
#define LS_SWITCH_2_Pin GPIO_PIN_3
#define LS_SWITCH_2_GPIO_Port GPIOC
#define LS_SWITCH_1_Pin GPIO_PIN_0
#define LS_SWITCH_1_GPIO_Port GPIOA
#define HB_PULL_Pin GPIO_PIN_12
#define HB_PULL_GPIO_Port GPIOB
#define HB_PUSH_Pin GPIO_PIN_13
#define HB_PUSH_GPIO_Port GPIOB
#define CAN2_STBY_Pin GPIO_PIN_4
#define CAN2_STBY_GPIO_Port GPIOB
#define CAN1_STBY_Pin GPIO_PIN_7
#define CAN1_STBY_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
