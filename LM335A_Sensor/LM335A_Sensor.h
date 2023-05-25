#ifndef __LM335A_SENSOR_H_
#define __LM335A_SENSOR_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"

typedef struct  
{
    ADC_HandleTypeDef *ADC_LM335A;
    float temperature;
    uint32_t Chanel, Rank, Sample_Time;
    uint32_t offset;
    float coef;
}LM335A_HandleTypeDef;

void LM335A_Init(LM335A_HandleTypeDef *Lm335a_x,ADC_HandleTypeDef *adc);

float LM335A_Measuring(LM335A_HandleTypeDef *Lm335a_x, uint8_t sample);


#endif