/**
 * @file Debug_Program.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SYSTEM_FUNTION_H_
#define __SYSTEM_FUNTION_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

typedef struct 
{
    UART_HandleTypeDef *usart;
    GPIO_TypeDef *Port;
    uint16_t Pin;
    uint32_t time_out_uart;
}Debug_Program_Name;

void Debug_Program_Config(Debug_Program_Name *program_x, UART_HandleTypeDef *uart_debug,  GPIO_TypeDef *port_led_debug, uint16_t pin__led_debug, uint32_t time_out);

void Transmit_Data_To_Computer(Debug_Program_Name *program_x, uint8_t *data, uint16_t size_data);

void Blink_Led01(Debug_Program_Name *program_x);

#endif
