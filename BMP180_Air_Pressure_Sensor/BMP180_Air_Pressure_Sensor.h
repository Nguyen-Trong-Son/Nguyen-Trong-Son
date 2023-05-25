/**
 * @file BMP180_Air_Pressure_Sensor.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ARI_PRESSUARE_SENSOR_H
#define __ARI_RRESSUARE_SENSOR_H

#include "stm32f1xx_hal.h"
// #include "stdint.h"
// #include "math.h"

#define BMP180_ADDRESS 0xEE
#define atmPress 101325 

typedef struct 
{
    I2C_HandleTypeDef *hi2c_bmp180_air_pressure_sensor;
    int16_t AC1, AC2, AC3, B1, B2, MB, MC, MD, oss;
    uint16_t AC4, AC5, AC6;
    int32_t UT, UP, X1, X2, X3, B3, B5, B6, Press, Temp;
    uint32_t B4, B7;
}BMP180_Air_Pressure_Sensor_Name;

void BMP_180_Air_Pressure_Sensor_Init(BMP180_Air_Pressure_Sensor_Name *sensor_x, I2C_HandleTypeDef *hi2c_x, uint16_t oversmapling_setting);

uint8_t BMP180_Start_Read_Calliberation_Data(BMP180_Air_Pressure_Sensor_Name *sensor_x);

float BMP180_GetTemp(BMP180_Air_Pressure_Sensor_Name *sensor_x);

int32_t BMP180_GetPress(BMP180_Air_Pressure_Sensor_Name *sensor_x);

float BMP180_GetAlt (BMP180_Air_Pressure_Sensor_Name *sensor_x);

// void BMP180_Start (void);

// float BMP180_GetTemp (void);

// float BMP180_GetPress (int oss);

// float BMP180_GetAlt (int oss);


#endif

