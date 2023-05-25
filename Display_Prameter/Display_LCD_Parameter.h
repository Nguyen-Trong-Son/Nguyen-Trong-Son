/**
 * @file Display_LCD_Parameter.h
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _DISPLAY_LCD_PARAMETER_H_
#define _DISPLAY_LCD_PARAMETER_H_

#include "CLCD_I2C.h"

void Display_Setup_Parameter_Pm2_5(CLCD_I2C_Name *LCD, uint16_t satatic_data_pm2_5);

void Display_Setup_Parameter_Sum_pm(CLCD_I2C_Name *LCD, uint16_t satatic_data_sum_pm);

void Display_Setup_Parameter_Co2(CLCD_I2C_Name *LCD, uint16_t satatic_data_co2);

void Display_Setup_Parameter_So2(CLCD_I2C_Name *LCD, uint16_t satatic_data_so2);

void Display_Setup_Parameter_Humidity(CLCD_I2C_Name *LCD, uint8_t satatic_data_humididy);

void Display_Setup_Parameter_Temperature(CLCD_I2C_Name *LCD, uint8_t satatic_data_temperature);

void Display_Done(CLCD_I2C_Name *LCD, float value);

void Display_Monitor(CLCD_I2C_Name *LCD, float value);

#endif
