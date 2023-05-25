#ifndef __TRANSMIT_DATA_LORA_H__
#define __TRANSMIT_DATA_LORA_H__


#include "stm32f1xx_hal.h"
#include <stdint.h>
 
#define LORA_TRANSMIT_MODE_I2C       0
#define LORA_TRANSMIT_MODE_UART      1

#if LORA_TRANSMIT_MODE_I2C

#define ARRAY_MAX                23
#define ERRORR_STATUS_FRAME      0xAA
#define NUMBER_SENSOR            6

typedef struct 
{
    I2C_HandleTypeDef *I2C_Lora;
    uint8_t Fame_Transimt_Data[ARRAY_MAX];
    uint8_t index;
    uint16_t Time_Out_I2C, Address_Slave;
}Frame_Transmit_Data;

void I2C_Lora_Init(Frame_Transmit_Data *frame_data_x, I2C_HandleTypeDef *I2C, uint16_t address_slave, uint16_t time_out);

uint8_t Lora_Uart_Master_Send_Data_To_Salve(Frame_Transmit_Data *frame_data_x, float Temperature, float Humidity, uint16_t Average_PPM_Co2, uint16_t Average_PPM_So2,
                                                     uint16_t Average_Sum_PM, uint16_t Average_PM2_5, uint16_t Battery_Voltage, uint16_t VDC_Input_Voltage, uint16_t Solar_Panel_Voltage);

#endif

#if LORA_TRANSMIT_MODE_UART

#define ARRAY_MAX                23
#define ERRORR_STATUS_FRAME      0xAA
#define NUMBER_SENSOR            6

typedef struct Transmit_Data_Lora
{
    UART_HandleTypeDef *UART_LORA;
    uint8_t Fame_Transimt_Data[ARRAY_MAX];
    uint8_t index;
    uint16_t time_out_uart;
}Frame_Transmit_Data;

void Uart_Lora_Init(Frame_Transmit_Data *frame_data_x, UART_HandleTypeDef *UART, uint16_t time_out);

uint8_t Lora_Uart_Master_Send_Data_To_Salve(Frame_Transmit_Data *frame_data_x, float Temperature, uint16_t Humidity, uint16_t Average_PPM_Co2, uint16_t Average_PPM_So2,
                                                     uint16_t Average_Sum_PM, uint16_t Average_PM2_5, uint16_t Battery_Voltage, uint16_t VDC_Input_Voltage, uint16_t Solar_Panel_Voltage);
#endif


#endif
