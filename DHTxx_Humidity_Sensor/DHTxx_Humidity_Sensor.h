/**
 * @file DHTxx_Humidity_Sensor.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DTHXX_HUMIDITY_H_
#define __DTHXX_HUMIDITY_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

#define DHT11_STARTTIME 18000
#define DHT22_STARTTIME 12000
#define DHT11 0x01
#define DHT22 0x02

typedef struct 
{
    TIM_HandleTypeDef* Timer_DHTxx;
    uint16_t Pin;
    GPIO_TypeDef* Port_DHTxx;
    float Temperature;
    float Humidity;
}DHTxx_Humidity_Sensor_Name;

void DHT_Init(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, TIM_HandleTypeDef* Timer, GPIO_TypeDef* DHTxx_PORT, uint16_t DHTxx_Pin);

uint8_t DHT_Read_Temperature_Humidity(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, float *temperature, float *humidity);

void DHT_Read_Temperature_Humidity_Average(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, float *temperature, float *humidity, uint8_t sample);


#endif
