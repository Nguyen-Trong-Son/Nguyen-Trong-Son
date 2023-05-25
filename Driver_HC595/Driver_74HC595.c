/**
 * @file Driver_74HC595.c
 * @author  Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Driver_74HC595.h"
// #include "Delay_Timer.h"

#define SR_Data_Pin GPIO_PIN_13
#define SR_Data_GPIO_Port GPIOC
#define SR_CLK_Pin GPIO_PIN_14
#define SR_CLK_GPIO_Port GPIOC
#define SR_LAT_Pin GPIO_PIN_15
#define SR_LAT_GPIO_Port GPIOC
#define SR_RST_Pin GPIO_PIN_9
#define SR_RST_GPIO_Port GPIOB


void shiftOut(uint8_t myDataOut) 
{
	uint8_t pinState = 0;
	for (int i=7; i>=0; i--) 
    { 
		HAL_GPIO_WritePin(SR_CLK_GPIO_Port, SR_CLK_Pin,GPIO_PIN_RESET);
		if ( myDataOut & (1<<i) ) 
        {
			pinState= 1;
		} 
        else
        {
			pinState= 0;
		} 

		HAL_GPIO_WritePin(SR_Data_GPIO_Port,SR_Data_Pin, pinState);
		HAL_GPIO_WritePin(SR_CLK_GPIO_Port, SR_CLK_Pin , GPIO_PIN_SET);
		HAL_GPIO_WritePin(SR_Data_GPIO_Port, SR_Data_Pin, GPIO_PIN_RESET);

	} 
	//stop shifting
	HAL_GPIO_WritePin(SR_CLK_GPIO_Port, SR_CLK_Pin,GPIO_PIN_SET);
}

/**
 * @brief Send_Data_74HC595
 * 
 * @param data 
 */
void Send_Data_74HC595(uint8_t data)
{
    HAL_GPIO_WritePin(SR_RST_GPIO_Port,SR_RST_Pin,GPIO_PIN_RESET);
    //releas reset HC595;
    HAL_GPIO_WritePin(SR_RST_GPIO_Port,SR_RST_Pin,GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(SR_LAT_GPIO_Port,SR_LAT_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SR_LAT_GPIO_Port,SR_LAT_Pin,GPIO_PIN_SET);
    //turn latch mcu on
    HAL_GPIO_WritePin(SR_LAT_GPIO_Port,SR_LAT_Pin,GPIO_PIN_RESET);
    shiftOut(data);
    HAL_GPIO_WritePin(SR_LAT_GPIO_Port,SR_LAT_Pin,GPIO_PIN_SET);
}