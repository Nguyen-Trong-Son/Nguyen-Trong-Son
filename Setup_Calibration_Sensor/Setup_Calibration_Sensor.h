/**
 * @file Setup_Calibration_Sensor.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SETUP_CALIBRATION_SENSOR_H
#define __SETUP_CALIBRATION_SENSOR_H

#include "stdint.h"

/*Flag check global system */

typedef struct
{
	uint8_t flag_01, flag_02, check_start_mesurment_sensor;
}GLOBAL_FLAG;


/*Initialization globale flag system*/
extern GLOBAL_FLAG flag_system;

void Init_Sensor(void);
void Funtion_Routine_Hightlevel(void);
void Run_Normal(void);
#endif
