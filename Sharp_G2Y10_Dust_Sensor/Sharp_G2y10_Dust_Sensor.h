/**
 * @file Sharp_G2y10_Dust_Sensor.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SHARP_GY210_DUST_SENSOR_H_
#define __SHARP_GY210_DUST_SENSOR_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

typedef struct 
{
    ADC_HandleTypeDef *G2y10_ADC;
    GPIO_TypeDef *PORT;
    TIM_HandleTypeDef* Timerx;
    uint32_t Chanel, Rank, Sample_Time;
    uint16_t Pin;
    float calcVoltage, dust_density;
    uint16_t voMeasured;
}SharpG2y10DustSensor_Name;


void Sharp_G2y10_Dust_Sensor_Init(SharpG2y10DustSensor_Name *sensor_x, ADC_HandleTypeDef *G2y10_ADCx,  TIM_HandleTypeDef* Timer,GPIO_TypeDef *G2y10_Port, uint16_t G2y10_Pin);

float Sharp_G2y10_Dust_Sensor_Measuring_Average(SharpG2y10DustSensor_Name *sensor_x, uint8_t sample);


#endif
