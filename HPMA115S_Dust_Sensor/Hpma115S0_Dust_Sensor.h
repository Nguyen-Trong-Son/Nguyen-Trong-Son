/**
 * @file Hpma115S0_Dust_Sensor.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __HPMA155S0_H_
#define __HPMA155S0_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

typedef struct 
{
    UART_HandleTypeDef *uart_dust_sensor;
    uint16_t offset;
}Hpma115S0_Dust_Sensor_Name;


void Hpma115S0_Dust_Sensor_Init(Hpma115S0_Dust_Sensor_Name *sensor_x, UART_HandleTypeDef *uart);

uint8_t Hpma115S0_Start_Particle_Measure(Hpma115S0_Dust_Sensor_Name *sensor_x);

uint8_t Hpma115S0_Stop_Particle_Measurement(Hpma115S0_Dust_Sensor_Name *sensor_x);

uint8_t Hpma115S0_Enable_Auto_Send(Hpma115S0_Dust_Sensor_Name *sensor_x);

uint8_t Hpma115S0_Stop_Auto_Send(Hpma115S0_Dust_Sensor_Name *sensor_x);
;
uint16_t Hpma115S0_Read_Particle_Measuring(Hpma115S0_Dust_Sensor_Name *sensor_x);

void Hpma115S0_Set_Adjustment_Cofficient(Hpma115S0_Dust_Sensor_Name *sensor_x, uint8_t coffcicient);

uint16_t Hpma115S0_Adjustment_Cofficient(Hpma115S0_Dust_Sensor_Name *sensor_x);

float Hpma115S0_Caclulator_Average(Hpma115S0_Dust_Sensor_Name *sensor_x, uint16_t sample);


#endif
