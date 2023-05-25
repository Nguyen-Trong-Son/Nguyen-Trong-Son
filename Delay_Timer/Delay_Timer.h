/**
 * @file Delay_Timer.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DELAY_TIMER_H_
#define __DELAY_TIMER_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

void Delay_Tim_Init(TIM_HandleTypeDef *htim);
void Delay_Timer_Us(TIM_HandleTypeDef *htim, uint16_t time);
void Delay_Tim_Ms(TIM_HandleTypeDef *htim, uint16_t Time);


#endif 