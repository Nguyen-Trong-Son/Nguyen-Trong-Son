/**
 * @file Delay_Timer.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Delay_Timer.h"

/**
 * @brief Config is use mode timer base
 * 
 * @param htim 
 */
void Delay_Tim_Init(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Start(htim);
}

/**
 * @brief delay microsecond mode is used by timer
 * 
 * @param htim 
 * @param time 
 */
void Delay_Timer_Us(TIM_HandleTypeDef *htim, uint16_t time)
{
	__HAL_TIM_SET_COUNTER(htim,0);
	while(__HAL_TIM_GET_COUNTER(htim)<time){}
}

/**
 * @brief delay milisecond mode is used by timer
 * 
 * @param htim 
 * @param Time 
 */
void Delay_Tim_Ms(TIM_HandleTypeDef *htim, uint16_t Time)
{
	__HAL_TIM_SET_COUNTER(htim,0);
	while(Time--)
	{
		while(__HAL_TIM_GET_COUNTER(htim)<1000){}
	}
}