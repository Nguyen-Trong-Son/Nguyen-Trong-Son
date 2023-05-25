/**
 * @file Driver_74HC595.h
 * @author  Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DRIVER_74HC595_H_
#define __DRIVER_74HC595_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"

void shiftOut(uint8_t myDataOut);
void Send_Data_74HC595(uint8_t data);

#endif