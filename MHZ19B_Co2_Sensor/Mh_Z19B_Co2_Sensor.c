/**
 * @file Co2_Sensor.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Mh_Z19B_Co2_Sensor.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

uint8_t particle_measure[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
uint8_t zero_point_calibration[]={0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78};
uint8_t span_point_calibration[] = {0xFF, 0x01, 0x88, 2000 >> 8, 2000 & 0xFF, 0x00, 0x00, 0x00, 0x2F};
uint8_t sensor_detetion_range_setting[] = {0xFF, 0x01, 0x99, 2500 >> 8, 2500 & 0xFF, 0x00, 0x00, 0x00, 0x78};
uint8_t sensor_auto_calibration[] = {0xFF, 0x01, 0x79, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xFF-282};
uint8_t particle_measure_data_co2_sensor[9];

/**
 * @brief Mh_Z19B_Co2_Sensor_Init
 * 
 * @param sensor_x 
 */
void Mh_Z19B_Co2_Sensor_Init(Mh_Z19B_Co2_Sensor_Name *sensor_x, UART_HandleTypeDef *uart)
{
    sensor_x->uart_co2_sensor = uart;
}

/**
 * @brief Zero_Point_Calibration
 * ZERO POINT is 400PPM, PLS MAKE SURE THE SENSOR HAD BEEN WORKED UNDER 400PPM FOR OVER 20MINUTES
 * @param sensor_x 
 */
uint8_t Zero_Point_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_co2_sensor, (uint8_t*)(zero_point_calibration), sizeof(zero_point_calibration)/sizeof(uint8_t), 1000);
    return 0;
}

/**
 * @brief 
 * Note: Pls do ZERO calibration before span calibration
 * Please make sure the sensor worked under a certain level co2 for over 20 minutes.
 * Suggest using 2000ppm as span, at least 1000ppm
 * @param sensor_x 
 * @return uint8_t 
 */
uint8_t Span_Point_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_co2_sensor, (uint8_t*)(span_point_calibration), sizeof(span_point_calibration)/sizeof(uint8_t), 1000);
    return 0;
}

/**
 * @brief Sensor_Detection_Range_Setting
 * 
 * @param sensor_x 
 * @return uint8_t 
 */
uint8_t Sensor_Detection_Range_Setting(Mh_Z19B_Co2_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_co2_sensor,(uint8_t*)sensor_detetion_range_setting, sizeof(sensor_detetion_range_setting)/sizeof(uint8_t), 1000);
    return 0;
}

/**
 * @brief Sensor_Set_Auto_Calibration
 * 
 * @param sensor_x 
 * @return uint8_t 
 */
uint8_t Sensor_Set_Auto_Calibration(Mh_Z19B_Co2_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_co2_sensor,(uint8_t*)sensor_auto_calibration, sizeof(sensor_auto_calibration)/sizeof(uint8_t), 1000);
    return 0;
}

/**
 * @brief 
 * 
 * @param huart1_Co2_Sensor 
 * @param huart3_Debug 
 * @param time_out 
 * @return uint16_t 
 */
uint16_t Mh_Z19B_Co2_Sensor_Concentration(Mh_Z19B_Co2_Sensor_Name *sensor_x)
{
    
    /**
     * @brief The Data transmission frame of 8 byte in which the 3rd byte is byte command 
     * The returned result consists of 8 btye, where the 2nd and 3rd bytes are the low and high bytes 
     * containing the parameters of the co2 gas in the environment.
     */  

    uint16_t ppm_co2 = 0;
    HAL_UART_Transmit(sensor_x->uart_co2_sensor, (uint8_t*)(particle_measure), sizeof(particle_measure)/sizeof(uint8_t), 1000);
    if(HAL_UART_Receive(sensor_x->uart_co2_sensor, (uint8_t*)particle_measure_data_co2_sensor, sizeof(particle_measure_data_co2_sensor)/sizeof(uint8_t), 5000) == HAL_OK)
    {
       ppm_co2 = particle_measure_data_co2_sensor[2] << 8;
       ppm_co2 = ppm_co2 | particle_measure_data_co2_sensor[3];
    }
    return ppm_co2;
}


/**
 * @brief Mh_Z19B_Co2_Sensor_Result
 * 
 * @param sensor_x 
 * @param sample 
 * @return uint16_t 
 */
float Mh_Z19B_Co2_Sensor_Caclulator_Average(Mh_Z19B_Co2_Sensor_Name *sensor_x, uint8_t sample)
{
    float data = 0;
    uint16_t arr_buff[sample];
    uint16_t copy_buff[sample];
    uint32_t sum =0;
    uint8_t index = 0;
    
    for(uint8_t i = 0; i< sample; i++)
    {
        arr_buff[i] = Mh_Z19B_Co2_Sensor_Concentration(sensor_x);
        HAL_Delay(5);
    }

    for(uint8_t i =0; i < sample; i++)
    {
        sum += arr_buff[i];
    }

    data = (float)sum / sample;

    for(uint8_t i =0; i < sample; i++)
    {
        if(abs(data - arr_buff[i]) < data)
        {
        	copy_buff[index]= arr_buff[i];
            index ++;
        }
    }

    sum = 0;
    data = 0;
    for(uint8_t i =0; i < index; i++)
    {
        sum += copy_buff[i];
    }

    data = (float)sum / index;

    if(data >= 1000)
    {
        data = 1000;
    }

    if(data <= 0)
    {
    	data = 0;
    }

    return data;

}
