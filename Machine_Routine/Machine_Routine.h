/*
 * Machine_Routine.h
 *
 *  Created on: Oct 28, 2022
 *      Author: son
 */

#ifndef MACHINE_ROUTINE_H_
#define MACHINE_ROUTINE_H_

#define USE_RTOS_MACHINE_SYSTEM 1

#include "Driver_74HC595.h"
#include "Setup_Calibration_Sensor.h"

void Init_Cmd_Transmit_Lora(void);
void Init_System_Funtion_Project(void);
void Init_RTOS_System_Project(void);
uint8_t Routine_Machine_NotUseRTOS(void);


#endif /* MACHINE_ROUTINE_H_ */
