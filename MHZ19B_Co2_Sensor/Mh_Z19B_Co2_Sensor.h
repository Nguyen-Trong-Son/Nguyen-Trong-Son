/**
 * @file Co2_Sensor.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MH_Z19B_CO2_SENSOR_H_
#define __MH_Z19B_CO2_SENSOR_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

typedef struct 
{
    UART_HandleTypeDef *uart_co2_sensor;
}Mh_Z19B_Co2_Sensor_Name;


void Mh_Z19B_Co2_Sensor_Init(Mh_Z19B_Co2_Sensor_Name *sensor_x, UART_HandleTypeDef *uart);

uint8_t Zero_Point_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x);

uint8_t Span_Point_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x);

uint8_t  Sensor_Detection_Range_Setting(Mh_Z19B_Co2_Sensor_Name *sensor_x);

void Mh_Z19B_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x,  uint16_t noload_raw, uint16_t load_raw, float scale);

uint16_t Mh_Z19B_Co2_Sensor_Concentration(Mh_Z19B_Co2_Sensor_Name *sensor_x);

uint8_t Sensor_Set_Auto_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x);

float Mh_Z19B_Co2_Sensor_Caclulator_Average(Mh_Z19B_Co2_Sensor_Name *sensor_x, uint8_t sample);


#endif
