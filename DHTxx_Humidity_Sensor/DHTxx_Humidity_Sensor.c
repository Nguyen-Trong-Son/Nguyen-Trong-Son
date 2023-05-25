/**
 * @file DHTxx_Humidity_Sensor.c
 * @author Nguyen Trong Son LoH Tech ...Ldt
 * 
*/
#include "DHTxx_Humidity_Sensor.h"
#include "Delay_Timer.h"
#include "stdlib.h"

/**
 * @brief DHT_DelayInit
 * 
*/
static void DHT_DelayInit(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x)
{
	Delay_Tim_Init(DHTxx_sensor_x->Timer_DHTxx);
}

/**
 * @brief DHT_DelayUs
*/
static void DHT_DelayUs(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, uint16_t Time)
{
	Delay_Timer_Us(DHTxx_sensor_x->Timer_DHTxx, Time);
}

/**
 * @brief DHT_Set_Pin_Output
*/
static void  DHT_Set_Pin_Output(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHTxx_sensor_x->Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHTxx_sensor_x->Port_DHTxx, &GPIO_InitStruct);
}

/**
 * @brief DHT_Set_Pin_Input
*/
static void DHT_Set_Pin_Input(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHTxx_sensor_x->Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(DHTxx_sensor_x->Port_DHTxx, &GPIO_InitStruct);
}

/**
 * @brief DHT_WritePin
*/
static void DHT_WritePin(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, uint8_t Value)
{
	HAL_GPIO_WritePin(DHTxx_sensor_x->Port_DHTxx, DHTxx_sensor_x->Pin, Value);
}

/**
 * @brief DHT_ReadPin
*/
static uint8_t DHT_ReadPin(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x)
{
	uint8_t value;
	value = HAL_GPIO_ReadPin(DHTxx_sensor_x->Port_DHTxx, DHTxx_sensor_x->Pin);
	return value;
}

/**
 * @brief DHT22_Start
*/
static uint8_t DHT22_Start (DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x)
{
	uint8_t Response = 0;
	DHT_Set_Pin_Output(DHTxx_sensor_x); 			// set the pin as output
	DHT_WritePin(DHTxx_sensor_x,0);  		 		// pull the pin low
	DHT_DelayUs(DHTxx_sensor_x, 1200);   			// wait for > 1ms

	DHT_Set_Pin_Input(DHTxx_sensor_x);   			// set as input
	DHT_DelayUs(DHTxx_sensor_x, 40);  				// wait for 40us
	if (!(DHT_ReadPin(DHTxx_sensor_x))) 			// if the pin is low
	{
	  	DHT_DelayUs(DHTxx_sensor_x, 80);   					// wait for 80us
		if ((DHT_ReadPin(DHTxx_sensor_x))) Response = 1;  	// if the pin is high, response is ok
		else Response = 0;
	}
	while ((DHT_ReadPin(DHTxx_sensor_x)));   				// wait for the pin to go low
	return Response;
}

/**
 * @brief DHT22_Read
*/
static uint8_t DHT22_Read (DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x)
{
	uint8_t value = 0;
	DHT_Set_Pin_Input(DHTxx_sensor_x);
	for (uint8_t i=0 ; i<8; i++)
	{
		while (!(DHT_ReadPin(DHTxx_sensor_x)));   			// wait for the pin to go high
	    DHT_DelayUs(DHTxx_sensor_x, 40);  					// wait for 40 us

		if (!(DHT_ReadPin(DHTxx_sensor_x)))   				// if the pin is low
		{
			value &= ~(1<<(7-i));  							// write 0
		}
		else value |= 1<<(7-i);  							// if the pin is high, write 1
		while ((DHT_ReadPin(DHTxx_sensor_x)));  			// wait for the pin to go low
	}
	return value;
}

/**
 * @brief DHT_Init
*/
void DHT_Init(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, TIM_HandleTypeDef* Timer, GPIO_TypeDef *DHTxx_PORT, uint16_t DHTxx_Pin)
{
	DHTxx_sensor_x->Port_DHTxx = DHTxx_PORT;
	DHTxx_sensor_x->Pin = DHTxx_Pin;
	DHTxx_sensor_x->Timer_DHTxx = Timer;
	DHTxx_sensor_x->Temperature = 0;
	DHTxx_sensor_x->Humidity = 0;
	DHT_DelayInit(DHTxx_sensor_x);
}

/**
 * @brief DHT_Read_Temperature_Humidity
*/
uint8_t DHT_Read_Temperature_Humidity(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, float *temperature, float *humidity)
{
	uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
	uint16_t SUM, RH, TEMP;

	DHT22_Start(DHTxx_sensor_x);
	Rh_byte1 = DHT22_Read(DHTxx_sensor_x);
	Rh_byte2 = DHT22_Read(DHTxx_sensor_x);
	Temp_byte1 = DHT22_Read(DHTxx_sensor_x);
	Temp_byte2 = DHT22_Read(DHTxx_sensor_x);
	SUM = DHT22_Read(DHTxx_sensor_x);

	TEMP = ((Temp_byte1<<8)|Temp_byte2);
	RH = ((Rh_byte1<<8)|Rh_byte2);

	DHTxx_sensor_x->Temperature = (float)(TEMP/10.0f);
	DHTxx_sensor_x->Humidity = (float)(RH/10.0f);

	*temperature = DHTxx_sensor_x->Temperature;
	*humidity = DHTxx_sensor_x->Humidity;

	return SUM;
}

/**
 * @brief DHT_Read_Temperature_Humidity_Average
*/
void DHT_Read_Temperature_Humidity_Average(DHTxx_Humidity_Sensor_Name *DHTxx_sensor_x, float *temperature, float *humidity, uint8_t sample)
{
	float arr1_buff_temp[sample];
	float arr2_buff_humi[sample];
	uint8_t index = 0;
	float sum = 0;
	float data  = 0;
	for(uint8_t i =0; i < sample; i++)
	{
		DHT_Read_Temperature_Humidity(DHTxx_sensor_x, temperature, humidity);
		arr1_buff_temp[i] = *temperature;
		arr2_buff_humi[i] = *humidity;
		HAL_Delay(1000);
	}

    for(uint8_t i = 0; i < sample; i++)
    {
    	sum += arr1_buff_temp[i];
    }
     data = sum /sample;
     *temperature = data;

     sum = 0;
     data = 0;
     for(uint8_t i =0; i< sample; i++)
     {
    	 sum += arr2_buff_humi[i];
     }
     data = sum /sample;
     *humidity = data;
}





























