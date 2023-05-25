/**
 * @file Hpma115S0_Dust_Sensor.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Hpma115S0_Dust_Sensor.h"
#include "stdlib.h"


uint8_t fame_data_start_particle_peasure[]     =          {0x68,0x01,0x01,0x96};
uint8_t fame_data_stop_particle_peasure[]      =          {0x68,0x01,0x02,0x95};
uint8_t fame_data_enable_auto_send[]           =          {0x68,0x01,0x40,0x57};
uint8_t fame_datat_stop_auto_send[]            =          {0x68,0x01,0x20,0x77};
uint8_t fame_data_read_particle_measure[]      =          {0x68,0x01,0x04,0x93};
uint8_t fame_data_set_particle_adjustment_coefficient[] = {0x68,0x02,0x08,64,0x2A};  //default
uint8_t fame_data_read_customer_adjustment_coffcicient[] = {0x68,0x01,0x10,0x87};    //default
uint8_t ackn[2];
uint8_t particle_measure_data_hpma115s0_sensor[32];

/**
 * @brief 
 * 
 * @param sensor_x 
 * @param uart 
 * @param time_out 
 */
void Hpma115S0_Dust_Sensor_Init(Hpma115S0_Dust_Sensor_Name *sensor_x, UART_HandleTypeDef *uart)
{
    sensor_x->uart_dust_sensor = uart;
    sensor_x->offset = 0;
}

/**
 * @brief Start_Particle_Measure
 * 
 * @param huart_Dust_Sensor 
 * @param huart_Display 
 * @param time_out 
 * @return uint8_t 
 */
uint8_t Hpma115S0_Start_Particle_Measure(Hpma115S0_Dust_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_dust_sensor, (uint8_t*)fame_data_start_particle_peasure, sizeof(fame_data_start_particle_peasure)/sizeof(uint8_t), 1000);
    if(HAL_UART_Receive(sensor_x->uart_dust_sensor, (uint8_t*)ackn, sizeof(ackn)/sizeof(uint8_t), 5000) == HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Stop_Particle_Measurement
 * 
 * @param huart2_Dust_Sensor 
 * @param huart1_Display 
 * @param time_out 
 * @return uint8_t 
 */
uint8_t Hpma115S0_Stop_Particle_Measurement(Hpma115S0_Dust_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_dust_sensor, (uint8_t*)fame_data_stop_particle_peasure, sizeof(fame_data_stop_particle_peasure)/sizeof(uint8_t), 1000);
    if(HAL_UART_Receive(sensor_x->uart_dust_sensor, (uint8_t*)ackn, sizeof(ackn)/sizeof(uint8_t), 5000) == HAL_OK)
    {
        return 1;
    }
    return 0;
}
/**
 * @brief Enable_Auto_Send
 * 
 * @param huart_Dust_Sensor 
 * @param huart_Display 
 * @param time_out 
 * @return uint8_t 
 */
uint8_t Hpma115S0_Enable_Auto_Send(Hpma115S0_Dust_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_dust_sensor, (uint8_t*)fame_data_enable_auto_send, sizeof(fame_data_enable_auto_send)/sizeof(uint8_t), 1000);
    if(HAL_UART_Receive(sensor_x->uart_dust_sensor, (uint8_t*)ackn, sizeof(ackn)/sizeof(uint8_t),  5000) == HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Stop_Auto_Send
 * 
 * @param huart2_Dust_Sensor 
 * @param huart1_Display 
 * @param time_out 
 * @return uint8_t 
 */
uint8_t Hpma115S0_Stop_Auto_Send(Hpma115S0_Dust_Sensor_Name *sensor_x)
{
    HAL_UART_Transmit(sensor_x->uart_dust_sensor, (uint8_t*)fame_datat_stop_auto_send, sizeof(fame_datat_stop_auto_send)/sizeof(uint8_t), 1000);
    if(HAL_UART_Receive(sensor_x->uart_dust_sensor, (uint8_t*)ackn, sizeof(ackn)/sizeof(uint8_t), 5000) == HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Hpma115S0_Set_Adjustment_Cofficient
 * 
 * @param sensor_x 
 * @param coef 
 */
void Hpma115S0_Set_Adjustment_Cofficient(Hpma115S0_Dust_Sensor_Name *sensor_x, uint8_t coffcicient)
{
    if(coffcicient < 30 ) 
    {
        coffcicient = 30;
    }
    if(coffcicient > 200)
    {
        coffcicient = 200;
    }
    fame_data_set_particle_adjustment_coefficient[3] = coffcicient;
    fame_data_set_particle_adjustment_coefficient[4] = ((0xFFFF-(fame_data_set_particle_adjustment_coefficient[0] + \
                                                                fame_data_set_particle_adjustment_coefficient[1] + \
                                                                fame_data_set_particle_adjustment_coefficient[2] + \
                                                                fame_data_set_particle_adjustment_coefficient[3])) % 256);
}


/**
 * @brief Read_Particle_Measuring
 * 
 * @param huart_Dust_Sensor 
 * @param huart_Display 
 * @param rx_data_lenght 
 * @param time_out 
 * @return uint8_t 
 */
uint16_t Hpma115S0_Read_Particle_Measuring(Hpma115S0_Dust_Sensor_Name *sensor_x)
{
    uint16_t pm2_5 = 0;
    HAL_UART_Transmit(sensor_x->uart_dust_sensor, (uint8_t*)fame_data_read_particle_measure, sizeof(fame_data_read_particle_measure)/sizeof(uint8_t), 1000);
    if(HAL_UART_Receive(sensor_x->uart_dust_sensor, (uint8_t*)particle_measure_data_hpma115s0_sensor, sizeof(particle_measure_data_hpma115s0_sensor)/sizeof(uint8_t), 5000) == HAL_OK)
    {
        pm2_5=  particle_measure_data_hpma115s0_sensor[7] << 8;
        pm2_5 = pm2_5 | particle_measure_data_hpma115s0_sensor[8];
    }
    return pm2_5;
}

/**
 * @brief Hpma115S0_Adjustment_Cofficient
 * 
 * @param sensor_x 
 * @return uint16_t 
 */
uint16_t Hpma115S0_Adjustment_Cofficient(Hpma115S0_Dust_Sensor_Name *sensor_x)
{
   uint16_t pm2_5 =0 ;
    if(HAL_UART_Receive(sensor_x->uart_dust_sensor, (uint8_t*)(particle_measure_data_hpma115s0_sensor), sizeof(particle_measure_data_hpma115s0_sensor)/sizeof(uint8_t), 5000) == HAL_OK)
    {
        if(particle_measure_data_hpma115s0_sensor[4] < 30)
        {
        	particle_measure_data_hpma115s0_sensor[4] = 30;
        }
        if(particle_measure_data_hpma115s0_sensor[4] > 200)
        {
        	particle_measure_data_hpma115s0_sensor[4] = 200;
        }
        pm2_5 = particle_measure_data_hpma115s0_sensor[3] << 8;
        pm2_5 = pm2_5 | particle_measure_data_hpma115s0_sensor[4];
    }
    return 0;
}

/**
 * @brief Hpma115S0_Caclulator_Average
 * 
 * @param sensor_x 
 * @param sample 
 * @return uint16_t 
 */
float Hpma115S0_Caclulator_Average(Hpma115S0_Dust_Sensor_Name *sensor_x, uint16_t sample)
{
    float data = 0;
    uint16_t arr_buff[sample];
    uint16_t copy_buff[sample];
    uint32_t sum = 0;
    uint8_t index = 0;

    for(uint8_t i = 0; i < sample; i++)
    {
        arr_buff[i] = Hpma115S0_Read_Particle_Measuring(sensor_x);
        HAL_Delay(5);
    }

    for(uint8_t i =0; i< sample; i++)
    {
        sum += arr_buff[i];
    }

    data = (float)sum / sample;

    for(uint8_t i =0; i < sample; i++)
    {
        if(abs(data - arr_buff[i]) < data)
        {
        	copy_buff[index] = arr_buff[i];
        	index++;
        }
    }

    sum =0;
    data = 0;

    for(uint8_t i =0; i < index; i++)
    {
        sum += copy_buff[i];
    }

    data = (float)sum / index ;

    if(data >= 1000)
    {
    	data = 1000;
    }

    if(data <= 0)
    {
    	data = 0;
    }
    return  data;
}



