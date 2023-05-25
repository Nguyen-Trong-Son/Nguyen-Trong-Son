#include "Transmit_Data_Lora.h"
#include "string.h"
#include "stdio.h"


/**
 * @brief Slect mode data transmit from master to the salve
 * Mode I2C: I2C1                   #define  PROTOCOL_BYTE  
 * Mode USART: USART3               #define  PROTOCOL_TEXT  
 * 
 */


#if LORA_TRANSMIT_MODE_UART

#define  LORA_AT_SEND      "AT+SEND=2:"
// #define  PROTOCOL_BYTE          
#define  PROTOCOL_TEXT          


static char Buffer_Size_Frame[15];
static char Buffer_Nun_Error[10];
static char Buffer_Number_Sensor[10];
static char Buffer_Data[128];
static char Buffer_Temp[15];
static char Buffer_Hum[15];
static char Buffer_Co2[15];
static char Buffer_So2[20];
static char Buffer_Sum_Pm[15];
static char Buffer_Pm2_5[15];
static char Buffer_Bat_Vol[15];
static char Buffer_Vdc_Input[15];
static char Buffer_Solar_Vol[15];
static char Buffer_Check_Sum[15];



#endif


#if LORA_TRANSMIT_MODE_I2C

void I2C_Lora_Init(Frame_Transmit_Data *frame_data_x, I2C_HandleTypeDef *I2C, uint16_t address_slave, uint16_t time_out)
{
    frame_data_x->I2C_Lora = I2C;
    frame_data_x->index = 0;
    frame_data_x->Time_Out_I2C = time_out;
    frame_data_x->Address_Slave = address_slave;
    memset(frame_data_x->Fame_Transimt_Data, 0, ARRAY_MAX);
}

uint8_t Lora_Uart_Master_Send_Data_To_Salve(Frame_Transmit_Data *frame_data_x, float *Temperature, float *Humidity, uint16_t *Average_PPM_Co2, int32_t *Average_PPM_So2,
                                                     float *Average_Sum_PM, uint16_t *Average_PM2_5, uint16_t *Battery_Voltage, uint16_t *VDC_Input_Voltage, uint16_t *Solar_Panel_Voltage)
{
    uint16_t checksum = 0;

    frame_data_x->Fame_Transimt_Data[0] = ARRAY_MAX;
    frame_data_x->Fame_Transimt_Data[1] = ERRORR_STATUS_FRAME;
    frame_data_x->Fame_Transimt_Data[2] = NUMBER_SENSOR;

    frame_data_x->Fame_Transimt_Data[3] = (uint16_t)(Temperature * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[4] = (uint16_t)(Temperature * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[5] = (uint16_t)(Humidity * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[6] = (uint16_t)(Humidity * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[7] = (uint16_t)(Average_PPM_Co2) >> 8;
    frame_data_x->Fame_Transimt_Data[8] = (uint16_t)(Average_PPM_Co2) & 0xFF; 

    frame_data_x->Fame_Transimt_Data[9] = (uint16_t)(Average_PPM_So2 * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[10] =(uint16_t)(Average_PPM_So2 * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[11] = (uint16_t)(Average_Sum_PM * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[12] = (uint16_t)(Average_Sum_PM * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[13] = (uint16_t)(Average_PM2_5) >> 8;
    frame_data_x->Fame_Transimt_Data[14] = (uint16_t)(Average_PM2_5) & 0xFF;

    frame_data_x->Fame_Transimt_Data[15] = (uint16_t)(Battery_Voltage) >> 8;
    frame_data_x->Fame_Transimt_Data[16] = (uint16_t)(Battery_Voltage) & 0xFF;

    frame_data_x->Fame_Transimt_Data[17] = (uint16_t)(VDC_Input_Voltage) >> 8;
    frame_data_x->Fame_Transimt_Data[18] = (uint16_t)(VDC_Input_Voltage) & 0xFF;

    frame_data_x->Fame_Transimt_Data[19] = (uint16_t)(Solar_Panel_Voltage) >> 8;
    frame_data_x->Fame_Transimt_Data[20] = (uint16_t)(Solar_Panel_Voltage) & 0xFF;

    for(uint8_t i = 0; i < ARRAY_MAX ; i++)
    {
        checksum += frame_data_x->Fame_Transimt_Data[i];
    }

    frame_data_x->Fame_Transimt_Data[21] = (0xFFFF - checksum) >> 8;
    frame_data_x->Fame_Transimt_Data[22] = (0xFFFF - checksum) & 0xFF;

    HAL_I2C_Master_Transmit(frame_data_x->I2C_Lora, frame_data_x->Address_Slave, (uint8_t*)&frame_data_x->Fame_Transimt_Data, 
                                sizeof(frame_data_x->Fame_Transimt_Data)/sizeof(uint8_t), frame_data_x->Time_Out_I2C);

    return 0;
}

#endif

#if LORA_TRANSMIT_MODE_UART

void Uart_Lora_Init(Frame_Transmit_Data *frame_data_x, UART_HandleTypeDef *UART, uint16_t time_out)
{
    frame_data_x->UART_LORA = UART;
    frame_data_x->index = 0;
    frame_data_x->time_out_uart = time_out;
    memset(frame_data_x->Fame_Transimt_Data, 0, ARRAY_MAX);
}

uint8_t Lora_Uart_Master_Send_Data_To_Salve(Frame_Transmit_Data *frame_data_x, float Temperature, uint16_t Humidity, uint16_t Average_PPM_Co2, uint16_t Average_PPM_So2,
                                                     uint16_t Average_Sum_PM, uint16_t Average_PM2_5, uint16_t Battery_Voltage, uint16_t VDC_Input_Voltage, uint16_t Solar_Panel_Voltage)
{
    uint16_t lengh_string = 0;


    #if !defined(PROTOCOL_BYTE)
        // #error Not Define USE
    #else
    uint16_t checksum = 0;

    frame_data_x->Fame_Transimt_Data[0] = ARRAY_MAX;
    frame_data_x->Fame_Transimt_Data[1] = ERRORR_STATUS_FRAME;
    frame_data_x->Fame_Transimt_Data[2] = NUMBER_SENSOR;

    frame_data_x->Fame_Transimt_Data[3] = (uint16_t)(Temperature * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[4] = (uint16_t)(Temperature * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[5] = (uint16_t)(Humidity * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[6] = (uint16_t)(Humidity * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[7] = (uint16_t)(Average_PPM_Co2) >> 8;
    frame_data_x->Fame_Transimt_Data[8] = (uint16_t)(Average_PPM_Co2) & 0xFF; 

    frame_data_x->Fame_Transimt_Data[9] = (uint16_t)(Average_PPM_So2 * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[10] =(uint16_t)(Average_PPM_So2 * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[11] = (uint16_t)(Average_Sum_PM * 10) >> 8;
    frame_data_x->Fame_Transimt_Data[12] = (uint16_t)(Average_Sum_PM * 10) & 0xFF;

    frame_data_x->Fame_Transimt_Data[13] = (uint16_t)(Average_PM2_5) >> 8;
    frame_data_x->Fame_Transimt_Data[14] = (uint16_t)(Average_PM2_5) & 0xFF;

    frame_data_x->Fame_Transimt_Data[15] = (uint16_t)(Battery_Voltage) >> 8;
    frame_data_x->Fame_Transimt_Data[16] = (uint16_t)(Battery_Voltage) & 0xFF;

    frame_data_x->Fame_Transimt_Data[17] = (uint16_t)(VDC_Input_Voltage) >> 8;
    frame_data_x->Fame_Transimt_Data[18] = (uint16_t)(VDC_Input_Voltage) & 0xFF;

    frame_data_x->Fame_Transimt_Data[19] = (uint16_t)(Solar_Panel_Voltage) >> 8;
    frame_data_x->Fame_Transimt_Data[20] = (uint16_t)(Solar_Panel_Voltage) & 0xFF;


    for(uint8_t i = 0; i < ARRAY_MAX ; i++)
    {
        checksum += frame_data_x->Fame_Transimt_Data[i];
    }

    frame_data_x->Fame_Transimt_Data[21] = (0xFFFF - checksum) >> 8;
    frame_data_x->Fame_Transimt_Data[22] = (0xFFFF - checksum) & 0xFF;

    #endif

    #if !defined(PROTOCOL_TEXT)
        // #error Not Define USE
    #else
    sprintf(Buffer_Nun_Error, "%d", ERRORR_STATUS_FRAME);
    sprintf(Buffer_Number_Sensor, "%d", NUMBER_SENSOR);
    sprintf(Buffer_Temp, "%.1f", Temperature);
    sprintf(Buffer_Hum, "%d", Humidity);
    sprintf(Buffer_Co2, "%d", Average_PPM_Co2);
    sprintf(Buffer_So2, "%d", Average_PPM_So2);
    sprintf(Buffer_Sum_Pm, "%d", Average_Sum_PM);
    sprintf(Buffer_Pm2_5, "%d", Average_PM2_5);
    sprintf(Buffer_Bat_Vol, "%d", Battery_Voltage);
    sprintf(Buffer_Vdc_Input, "%d", VDC_Input_Voltage);
    sprintf(Buffer_Solar_Vol, "%d", Solar_Panel_Voltage);

    memset(Buffer_Data, '\0', sizeof(Buffer_Data));
    strcpy(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Nun_Error);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Number_Sensor);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Temp);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Hum);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Co2);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_So2);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Sum_Pm);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Pm2_5);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Bat_Vol);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Vdc_Input);
    strcat(Buffer_Data, ",");
    strcat(Buffer_Data, Buffer_Solar_Vol);
    strcat(Buffer_Data, ",");

    lengh_string = strlen(Buffer_Data);

    sprintf(Buffer_Size_Frame, "%d", lengh_string);

    sprintf(Buffer_Check_Sum, "%d\r", 0XFFFF-lengh_string);

    HAL_UART_Transmit(frame_data_x->UART_LORA, (uint8_t*)LORA_AT_SEND, strlen(LORA_AT_SEND), frame_data_x->time_out_uart);
    HAL_UART_Transmit(frame_data_x->UART_LORA, (uint8_t*)Buffer_Size_Frame, strlen(Buffer_Size_Frame), frame_data_x->time_out_uart);
    HAL_UART_Transmit(frame_data_x->UART_LORA, (uint8_t*)Buffer_Data, strlen(Buffer_Data), frame_data_x->time_out_uart);
    HAL_UART_Transmit(frame_data_x->UART_LORA, (uint8_t*)Buffer_Check_Sum, strlen(Buffer_Check_Sum), frame_data_x->time_out_uart);

    return 0;

    #endif
}

#endif
