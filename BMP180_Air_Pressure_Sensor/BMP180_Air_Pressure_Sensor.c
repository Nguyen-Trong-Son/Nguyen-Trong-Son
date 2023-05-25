/**
 * @file BMP180_Air_Pressure_Sensor.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-08-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "BMP180_Air_Pressure_Sensor.h"
#include "stdint.h"
#include "math.h"


// Defines according to the datsheet
// int16_t AC1 = 0;
// int16_t AC2 = 0;
// int16_t AC3 = 0;
// uint16_t AC4 = 0;
// uint16_t AC5 = 0;
// uint16_t AC6 = 0;
// int16_t B1 = 0;
// int16_t B2 = 0;
// int16_t MB = 0;
// int16_t MC = 0;
// int16_t MD = 0;

// /********************/
// int32_t UT = 0;
// int16_t oss = 0;
// int32_t UP = 0;
// int32_t X1 = 0;
// int32_t X2 = 0;
// int32_t X3 = 0;
// int32_t B3 = 0;
// int32_t B5 = 0;
// uint32_t B4 = 0;
// int32_t B6 = 0;
// uint32_t B7 = 0;

// /*******************/
// int32_t Press = 0;
// int32_t Temp = 0;

/**
 * @brief BMP_180_Air_Pressure_Sensor_Init
 * 
 * @param sensor_x 
 */
void BMP_180_Air_Pressure_Sensor_Init(BMP180_Air_Pressure_Sensor_Name *sensor_x, I2C_HandleTypeDef *hi2c_x, uint16_t oversmapling_setting)
{
	sensor_x->hi2c_bmp180_air_pressure_sensor = hi2c_x;
	sensor_x->AC1 = 0;
	sensor_x->AC2 = 0;
	sensor_x->AC3 = 0;
	sensor_x->AC4 = 0;
	sensor_x->AC5 = 0;
	sensor_x->B1 = 0;
	sensor_x->B2 = 0;
	sensor_x->B3 = 0;
	sensor_x->B4 = 0;
	sensor_x->B5 = 0;
	sensor_x->B6 = 0;
	sensor_x->B7 = 0;
	sensor_x->MB = 0;
	sensor_x->MC = 0;
	sensor_x->MD = 0;
	sensor_x->oss = oversmapling_setting;
	sensor_x->Press = 0;
	sensor_x->Temp = 0;
	sensor_x->UT = 0;
	sensor_x->UP = 0;
	sensor_x->X1 = 0;
	sensor_x->X2 = 0;
	sensor_x->X3 = 0;
}

/**
 * @brief Start_Read_Calliberation_Data
 * 
 * @param hi2c 
 * @return uint8_t 
 */
uint8_t BMP180_Start_Read_Calliberation_Data(BMP180_Air_Pressure_Sensor_Name *sensor_x)
{
	uint8_t Callib_Data[22] = {0};
	uint16_t Callib_Start = 0xAA;
	HAL_I2C_Mem_Read(sensor_x->hi2c_bmp180_air_pressure_sensor, BMP180_ADDRESS, Callib_Start, 1, Callib_Data, 22, 1000);

	sensor_x->AC1 = ((Callib_Data[0] << 8) | Callib_Data[1]);
	sensor_x->AC2 = ((Callib_Data[2] << 8) | Callib_Data[3]);
	sensor_x->AC3 = ((Callib_Data[4] << 8) | Callib_Data[5]);
	sensor_x->AC4 = ((Callib_Data[6] << 8) | Callib_Data[7]);
	sensor_x->AC5 = ((Callib_Data[8] << 8) | Callib_Data[9]);
	sensor_x->AC6 = ((Callib_Data[10] << 8) | Callib_Data[11]);
	sensor_x->B1 = ((Callib_Data[12] << 8) | Callib_Data[13]);
	sensor_x->B2 = ((Callib_Data[14] << 8) | Callib_Data[15]);
	sensor_x->MB = ((Callib_Data[16] << 8) | Callib_Data[17]);
	sensor_x->MC = ((Callib_Data[18] << 8) | Callib_Data[19]);
	sensor_x->MD = ((Callib_Data[20] << 8) | Callib_Data[21]);
    return 0;
}

/**
 * @brief Get_UTemp
 * 
 * @param hi2c 
 * @return uint16_t 
 */
static uint16_t BMP180_Get_UTemp (BMP180_Air_Pressure_Sensor_Name *sensor_x)
{
	uint8_t datatowrite = 0x2E;
	uint8_t Temp_RAW[2] = {0};
	HAL_I2C_Mem_Write(sensor_x->hi2c_bmp180_air_pressure_sensor, BMP180_ADDRESS, 0xF4, 1, &datatowrite, 1, 1000);
	HAL_Delay (5);  // wait 4.5 ms
	HAL_I2C_Mem_Read(sensor_x->hi2c_bmp180_air_pressure_sensor, BMP180_ADDRESS, 0xF6, 1, Temp_RAW, 2, 1000);
	return ((Temp_RAW[0]<<8) + Temp_RAW[1]);
}

/**
 * @brief BMP180_GetTemp
 * 
 * @param hi2c 
 * @return float 
 */
float BMP180_GetTemp(BMP180_Air_Pressure_Sensor_Name *sensor_x)
{
	sensor_x->UT = BMP180_Get_UTemp(sensor_x);
	sensor_x->X1 = ((sensor_x->UT - sensor_x->AC6) * (sensor_x->AC5/(pow(2,15))));
	sensor_x->X2 = ((sensor_x->MC*(pow(2,11))) / (sensor_x->X1 + sensor_x->MD));
	sensor_x->B5 = sensor_x->X1 + sensor_x->X2;
	sensor_x->Temp = (sensor_x->B5 + 8)/(pow(2,4));
	return sensor_x->Temp / 10.0;
}

/**
 * @brief Get_UPress
 * 
 * @param oss 
 * @param hi2c 
 * @return uint32_t 
 */
static uint32_t BMP180_Get_UPress(BMP180_Air_Pressure_Sensor_Name *sensor_x)   // oversampling setting 0,1,2,3
{
	uint8_t datatowrite = 0x34+(sensor_x->oss<<6);
	uint8_t Press_RAW[3] = {0};
	HAL_I2C_Mem_Write(sensor_x->hi2c_bmp180_air_pressure_sensor, BMP180_ADDRESS, 0xF4, 1, &datatowrite, 1, 1000);
	switch (sensor_x->oss)
	{
		case (0):
			HAL_Delay (5);
			break;
		case (1):
			HAL_Delay (8);
			break;
		case (2):
			HAL_Delay (14);
			break;
		case (3):
			HAL_Delay (26);
			break;
	}
	HAL_I2C_Mem_Read(sensor_x->hi2c_bmp180_air_pressure_sensor, BMP180_ADDRESS, 0xF6, 1, Press_RAW, 3, 1000);
	return (((Press_RAW[0]<<16)+(Press_RAW[1]<<8)+Press_RAW[2]) >> (8-sensor_x->oss));
}

/**
 * @brief BMP180_GetPress
 * 
 * @param oss 
 * @param hi2c 
 * @return float 
 */
int32_t BMP180_GetPress(BMP180_Air_Pressure_Sensor_Name *sensor_x)
{
	sensor_x->UP = BMP180_Get_UPress(sensor_x);
	sensor_x->X1 = ((sensor_x->UT - sensor_x->AC6) * (sensor_x->AC5/(pow(2,15))));
	sensor_x->X2 = ((sensor_x->MC * (pow(2,11))) / (sensor_x->X1 + sensor_x->MD));
	sensor_x->B5 = sensor_x->X1 + sensor_x->X2;
	sensor_x->B6 = sensor_x->B5 - 4000;
	sensor_x->X1 = (sensor_x->B2 * (sensor_x->B6 *sensor_x->B6/(pow(2,12))))/(pow(2,11));
	sensor_x->X2 = sensor_x->AC2 * sensor_x->B6/(pow(2,11));
	sensor_x->X3 = sensor_x->X1 + sensor_x->X2;
	sensor_x->B3 = (((sensor_x->AC1 * 4 + sensor_x->X3) << sensor_x->oss)+2)/4;
	sensor_x->X1 = sensor_x->AC3 * sensor_x->B6/pow(2,13);
	sensor_x->X2 = (sensor_x->B1 * (sensor_x->B6 * sensor_x->B6/(pow(2,12))))/(pow(2,16));
	sensor_x->X3 = ((sensor_x->X1 + sensor_x->X2)+2)/pow(2,2);
	sensor_x->B4 = sensor_x->AC4*(uint32_t)(sensor_x->X3 + 32768)/(pow(2,15));
	sensor_x->B7 = ((uint32_t)(sensor_x->UP - sensor_x->B3))*(50000>>sensor_x->oss);
	if (sensor_x->B7<0x80000000) 
	{
		sensor_x->Press = (sensor_x->B7*2)/sensor_x->B4;
	}
	else
	{
		sensor_x->Press = (sensor_x->B7/sensor_x->B4)*2;
	} 
	sensor_x->X1 = (sensor_x->Press/(pow(2,8)))*(sensor_x->Press/(pow(2,8)));
	sensor_x->X1 = (sensor_x->X1*3038)/(pow(2,16));
	sensor_x->X2 = (-7357 * sensor_x->Press)/(pow(2,16));
	sensor_x->Press = sensor_x->Press + (sensor_x->X1 + sensor_x->X2+3791)/(pow(2,4));
	return 	sensor_x->Press;
}


/**
 * @brief BMP180_GetAlt
 * 
 * @param oss 
 * @param hi2c 
 * @return float 
 */
float BMP180_GetAlt (BMP180_Air_Pressure_Sensor_Name *sensor_x)
{
	BMP180_GetPress(sensor_x);
	// return 44330*(1-(pow((sensor_x->Press/(float)atmPress), 0.19029495718)));
	return (1-(pow(((float)sensor_x->Press/(float)atmPress), 0.19029495718)));
}


// extern I2C_HandleTypeDef hi2c2;
// #define BMP180_I2C &hi2c2

// #define BMP180_ADDRESS 0xEE 


// // Defines according to the datsheet
// short AC1 = 0;
// short AC2 = 0;
// short AC3 = 0;
// unsigned short AC4 = 0;
// unsigned short AC5 = 0;
// unsigned short AC6 = 0;
// short B1 = 0;
// short B2 = 0;
// short MB = 0;
// short MC = 0;
// short MD = 0;

// /********************/
// long UT = 0;
// short oss = 0;
// long UP = 0;
// long X1 = 0;
// long X2 = 0;
// long X3 = 0;
// long B3 = 0;
// long B5 = 0;
// unsigned long B4 = 0;
// long B6 = 0;
// unsigned long B7 = 0;

// /*******************/
// long Press = 0;
// long Temp = 0;

// #define atmPress 101325 //Pa



// void read_calliberation_data (void)
// {
// 	uint8_t Callib_Data[22] = {0};
// 	uint16_t Callib_Start = 0xAA;
// 	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, Callib_Start, 1, Callib_Data,22, HAL_MAX_DELAY);

// 	AC1 = ((Callib_Data[0] << 8) | Callib_Data[1]);
// 	AC2 = ((Callib_Data[2] << 8) | Callib_Data[3]);
// 	AC3 = ((Callib_Data[4] << 8) | Callib_Data[5]);
// 	AC4 = ((Callib_Data[6] << 8) | Callib_Data[7]);
// 	AC5 = ((Callib_Data[8] << 8) | Callib_Data[9]);
// 	AC6 = ((Callib_Data[10] << 8) | Callib_Data[11]);
// 	B1 = ((Callib_Data[12] << 8) | Callib_Data[13]);
// 	B2 = ((Callib_Data[14] << 8) | Callib_Data[15]);
// 	MB = ((Callib_Data[16] << 8) | Callib_Data[17]);
// 	MC = ((Callib_Data[18] << 8) | Callib_Data[19]);
// 	MD = ((Callib_Data[20] << 8) | Callib_Data[21]);

// }


// // Get uncompensated Temp
// uint16_t Get_UTemp (void)
// {
// 	uint8_t datatowrite = 0x2E;
// 	uint8_t Temp_RAW[2] = {0};
// 	HAL_I2C_Mem_Write(BMP180_I2C, BMP180_ADDRESS, 0xF4, 1, &datatowrite, 1, 1000);
// 	HAL_Delay (5);  // wait 4.5 ms
// 	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, 0xF6, 1, Temp_RAW, 2, 1000);
// 	return ((Temp_RAW[0]<<8) + Temp_RAW[1]);
// }

// float BMP180_GetTemp (void)
// {
// 	UT = Get_UTemp();
// 	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
// 	X2 = ((MC*(pow(2,11))) / (X1+MD));
// 	B5 = X1+X2;
// 	Temp = (B5+8)/(pow(2,4));
// 	return Temp/10.0;
// }

// // Get uncompensated Pressure
// uint32_t Get_UPress (int oss)   // oversampling setting 0,1,2,3
// {
// 	uint8_t datatowrite = 0x34+(oss<<6);
// 	uint8_t Press_RAW[3] = {0};
// 	HAL_I2C_Mem_Write(BMP180_I2C, BMP180_ADDRESS, 0xF4, 1, &datatowrite, 1, 1000);
// 	switch (oss)
// 	{
// 		case (0):
// 			HAL_Delay (5);
// 			break;
// 		case (1):
// 			HAL_Delay (8);
// 			break;
// 		case (2):
// 			HAL_Delay (14);
// 			break;
// 		case (3):
// 			HAL_Delay (26);
// 			break;
// 	}
// 	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, 0xF6, 1, Press_RAW, 3, 1000);
// 	return (((Press_RAW[0]<<16)+(Press_RAW[1]<<8)+Press_RAW[2]) >> (8-oss));
// }


// float BMP180_GetPress (int oss)
// {
// 	UP = Get_UPress(oss);
// 	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
// 	X2 = ((MC*(pow(2,11))) / (X1+MD));
// 	B5 = X1+X2;
// 	B6 = B5-4000;
// 	X1 = (B2 * (B6*B6/(pow(2,12))))/(pow(2,11));
// 	X2 = AC2*B6/(pow(2,11));
// 	X3 = X1+X2;
// 	B3 = (((AC1*4+X3)<<oss)+2)/4;
// 	X1 = AC3*B6/pow(2,13);
// 	X2 = (B1 * (B6*B6/(pow(2,12))))/(pow(2,16));
// 	X3 = ((X1+X2)+2)/pow(2,2);
// 	B4 = AC4*(unsigned long)(X3+32768)/(pow(2,15));
// 	B7 = ((unsigned long)UP-B3)*(50000>>oss);
// 	if (B7<0x80000000) Press = (B7*2)/B4;
// 	else Press = (B7/B4)*2;
// 	X1 = (Press/(pow(2,8)))*(Press/(pow(2,8)));
// 	X1 = (X1*3038)/(pow(2,16));
// 	X2 = (-7357*Press)/(pow(2,16));
// 	Press = Press + (X1+X2+3791)/(pow(2,4));

// 	return Press;
// }


// float BMP180_GetAlt (int oss)
// {
// 	BMP180_GetPress (oss);
// 	return 44330*(1-(pow((Press/(float)atmPress), 0.19029495718)));
// }

// void BMP180_Start (void)
// {
// 	read_calliberation_data();
// }
