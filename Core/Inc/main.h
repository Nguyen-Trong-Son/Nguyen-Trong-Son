/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define SR_Data_Pin GPIO_PIN_13
#define SR_Data_GPIO_Port GPIOC
#define SR_CLK_Pin GPIO_PIN_14
#define SR_CLK_GPIO_Port GPIOC
#define SR_LAT_Pin GPIO_PIN_15
#define SR_LAT_GPIO_Port GPIOC
#define USART2_Dust_Sensor_Tx_Pin GPIO_PIN_2
#define USART2_Dust_Sensor_Tx_GPIO_Port GPIOA
#define USART2_Dust_Sensor_Rx_Pin GPIO_PIN_3
#define USART2_Dust_Sensor_Rx_GPIO_Port GPIOA
#define I2C1_Select1_Pin GPIO_PIN_7
#define I2C1_Select1_GPIO_Port GPIOA
#define Ctl_AI_Dust_Sensor_Pin GPIO_PIN_1
#define Ctl_AI_Dust_Sensor_GPIO_Port GPIOB
#define DHT22_Sensor_Pin GPIO_PIN_2
#define DHT22_Sensor_GPIO_Port GPIOB
#define RELAY_01_Pin GPIO_PIN_7
#define RELAY_01_GPIO_Port GPIOE
#define RELAY_02_Pin GPIO_PIN_8
#define RELAY_02_GPIO_Port GPIOE
#define I2C2_SCL_Pin GPIO_PIN_10
#define I2C2_SCL_GPIO_Port GPIOB
#define I2C2_SDA_Pin GPIO_PIN_11
#define I2C2_SDA_GPIO_Port GPIOB
#define UART3_TX_Debug_Pin GPIO_PIN_8
#define UART3_TX_Debug_GPIO_Port GPIOD
#define UART3_RX_Debug_Pin GPIO_PIN_9
#define UART3_RX_Debug_GPIO_Port GPIOD
#define So2_Hx711_Data_Pin GPIO_PIN_11
#define So2_Hx711_Data_GPIO_Port GPIOD
#define So2_Hx711_Clk_Pin GPIO_PIN_14
#define So2_Hx711_Clk_GPIO_Port GPIOD
#define USART1_Co2_Sensor_Tx_Pin GPIO_PIN_9
#define USART1_Co2_Sensor_Tx_GPIO_Port GPIOA
#define USART1_Co2_SenSor_Rx_Pin GPIO_PIN_10
#define USART1_Co2_SenSor_Rx_GPIO_Port GPIOA
#define BUTTON_05_UP_Pin GPIO_PIN_11
#define BUTTON_05_UP_GPIO_Port GPIOC
#define BUTTON_06_DOWN_Pin GPIO_PIN_12
#define BUTTON_06_DOWN_GPIO_Port GPIOC
#define LED_SST3_Pin GPIO_PIN_0
#define LED_SST3_GPIO_Port GPIOD
#define LED_SST2_Pin GPIO_PIN_1
#define LED_SST2_GPIO_Port GPIOD
#define LED_SST1_Pin GPIO_PIN_2
#define LED_SST1_GPIO_Port GPIOD
#define BUTTON_01_OPTION_Pin GPIO_PIN_3
#define BUTTON_01_OPTION_GPIO_Port GPIOD
#define BUTTON_02_SAVE_Pin GPIO_PIN_4
#define BUTTON_02_SAVE_GPIO_Port GPIOD
#define BUTTON_03_MONITOR_Pin GPIO_PIN_5
#define BUTTON_03_MONITOR_GPIO_Port GPIOD
#define BUTTON_04_SET_GROUP_SENOR_Pin GPIO_PIN_6
#define BUTTON_04_SET_GROUP_SENOR_GPIO_Port GPIOD
#define SR_RST_Pin GPIO_PIN_9
#define SR_RST_GPIO_Port GPIOB
#define Buzz_Pin GPIO_PIN_0
#define Buzz_GPIO_Port GPIOE
#define Led_MCH_Pin GPIO_PIN_1
#define Led_MCH_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
