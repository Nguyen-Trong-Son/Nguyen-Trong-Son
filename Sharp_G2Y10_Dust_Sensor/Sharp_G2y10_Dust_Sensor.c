/**
 * @file Sharp_G2y10_Dust_Sensor.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Sharp_G2y10_Dust_Sensor.h"
#include "Delay_Timer.h"
#include "math.h"
#include "stdlib.h"


static void G2y10_Delay_Init(SharpG2y10DustSensor_Name *sensor_x);
static void G2y10_Delay_Us(SharpG2y10DustSensor_Name *sensor_x, uint16_t Time);
static void G2y10_ADC_Channel_Config(SharpG2y10DustSensor_Name *sensor_x);

/**
 * @brief G2y10_Delay_Init
 * 
 * @param sensor_x 
 */
static void G2y10_Delay_Init(SharpG2y10DustSensor_Name *sensor_x)
{
	Delay_Tim_Init(sensor_x->Timerx);
}

/**
 * @brief G2y10_Delay_Us
 * 
 * @param sensor_x 
 * @param Time 
 */
static void G2y10_Delay_Us(SharpG2y10DustSensor_Name *sensor_x, uint16_t Time)
{
	Delay_Timer_Us(sensor_x->Timerx, Time);
}


/**
 * @brief G2y10_ADC_Channel_Config
 *
 * @param sensor_x
 */
static void G2y10_ADC_Channel_Config(SharpG2y10DustSensor_Name *sensor_x)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_10;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
    if (HAL_ADC_ConfigChannel(sensor_x->G2y10_ADC, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

}

/**
 * @brief Sharp_G2y10_Dust_Sensor_Init
 *
 * @param sensor_x
 * @param G2y10_ADCx
 * @param Timer
 * @param G2y10_Chanel_ADC
 * @param G2y10_Rank_ADC
 * @param G2y10_Sample_Time_ADC
 * @param G2y10_Port
 * @param G2y10_Pin
 */
void Sharp_G2y10_Dust_Sensor_Init(SharpG2y10DustSensor_Name *sensor_x, ADC_HandleTypeDef *G2y10_ADCx,  TIM_HandleTypeDef* Timer,GPIO_TypeDef *G2y10_Port, uint16_t G2y10_Pin)
{
    sensor_x->G2y10_ADC = G2y10_ADCx;
    sensor_x->Timerx = Timer;
    sensor_x->PORT = G2y10_Port;
    sensor_x->Pin = G2y10_Pin;
    G2y10_Delay_Init(sensor_x);
}


/**
 * @brief Read_Particle_Measuring_Mode_Analog
 *
 * @param hadc
 * @param chanel
 * @param rank
 * @param sample_time
 * @param GPIOx
 * @param GPIO_Pin
 * @param time_out
 * @return uint16_t
 */
float Sharp_G2y10_Dust_Sensor_Measuring_Average(SharpG2y10DustSensor_Name *sensor_x, uint8_t sample)
{
    uint16_t arr_buff[sample];
    uint16_t copy_buff[sample];
    uint16_t min, max;
    uint32_t sum  = 0;
    float data = 0;
    uint8_t index = 0;
    float calcVoltage = 0.0, dust_density = 0.0;

    for(uint8_t i = 0; i< sample; i++)
    {
        G2y10_ADC_Channel_Config(sensor_x);
        HAL_ADC_Start(sensor_x->G2y10_ADC);
        HAL_ADC_PollForConversion(sensor_x->G2y10_ADC, 1000);
        HAL_GPIO_WritePin(sensor_x->PORT, sensor_x->Pin, GPIO_PIN_SET);
        G2y10_Delay_Us(sensor_x, 280);
        arr_buff[i]= HAL_ADC_GetValue(sensor_x->G2y10_ADC);
        G2y10_Delay_Us(sensor_x, 19);
        G2y10_Delay_Us(sensor_x, 9680);
        HAL_GPIO_WritePin(sensor_x->PORT, sensor_x->Pin, GPIO_PIN_RESET);
        HAL_ADC_Stop(sensor_x->G2y10_ADC);
        //G2y10_Delay_Us(sensor_x, 5000);
    }

    for(uint8_t i = 0; i < sample; i++)
    {
        sum += arr_buff[i];
    }

    data = (float)(sum - max - min) / sample;

    for(uint8_t i = 0; i< sample; i++)
    {
    	 if(abs(data - arr_buff[i]) < data)
    	 {
    		 copy_buff[index] = arr_buff[i];
    		 index ++;
    	 }
    }

    max = copy_buff[0];
    min = copy_buff[0];
    sum = copy_buff[0];

    for(uint8_t i = 0; i < index; i++)
    {
		if(max < copy_buff[i])
		{
			max = copy_buff[i];
		}
		else if(min >  copy_buff[i])
		{
			min = copy_buff[i];
		}

		sum+=copy_buff[i];
    }

    data = (float)(sum - max - min)/index;

    calcVoltage = data * (3.3 / 4095);

    dust_density =  data * 0.17f - 0.1f;

    if(dust_density >= 500)
    {
    	dust_density = 500;
    }

    if(dust_density <= 0)
    {
    	dust_density = 0;
    }

    return dust_density;
}

