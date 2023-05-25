/**
 * @file Debug_Program.c
 * @author  Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Debug_Program.h"

/**
 * @brief Debug_Program_Config
 * 
 * @param program_x 
 * @param uart_debug 
 * @param port_led_debug 
 * @param pin__led_debug 
 * @param time_out 
 */
void Debug_Program_Config(Debug_Program_Name *program_x, UART_HandleTypeDef *uart_debug,  GPIO_TypeDef *port_led_debug, uint16_t pin__led_debug, uint32_t time_out)
{
    program_x->usart = uart_debug;
    program_x->Port = port_led_debug;
    program_x->Pin = pin__led_debug;
    program_x->time_out_uart = time_out;
}

/**
 * @brief Transmit_Data_To_Computer
 * 
 * @param program_x 
 * @param data 
 * @param size_data 
 */
void Transmit_Data_To_Computer(Debug_Program_Name *program_x, uint8_t *data, uint16_t size_data)
{
    HAL_UART_Transmit(program_x->usart, data, size_data, program_x->time_out_uart);

}

/**
 * @brief Blink_Led01
 * 
 * @param program_x 
 */
void Blink_Led01(Debug_Program_Name *program_x)
{
    HAL_GPIO_TogglePin(program_x->Port, program_x->Pin);

}

