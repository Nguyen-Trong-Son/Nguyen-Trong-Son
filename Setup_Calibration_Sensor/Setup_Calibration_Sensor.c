/**
 * @file Setup_Calibration_Sensor.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Setup_Calibration_Sensor.h"
#include "flash.h"
#include "main.h"
#include "Hpma115S0_Dust_Sensor.h"
#include "Mh_Z19B_Co2_Sensor.h"
#include "Sharp_G2y10_Dust_Sensor.h"
#include "BMP180_Air_Pressure_Sensor.h"
#include "Delay_Timer.h"
#include "DHTxx_Humidity_Sensor.h"
#include "Driver_74HC595.h"
#include "Transmit_Data_Lora.h"
#include "So2_Sensor_Hx711.h"
#include "LM335A_Sensor.h"
#include "CLCD_I2C.h"
#include "Display_LCD_Parameter.h"
#include "Driver_74HC595.h"



/*time wating wake up sensor*/
#define TIME_WAITTING_START_CALIBRATION         			 300000

/*Flash page 127 start address 0x0801FC00 -> 0x0801 FFFF from MCU*/
#define START_BASE_ADDRESS_PM2_5_SENSOR 					(BaseAdreesMCU)0x0801FC00
#define START_BASE_ADDRESS_SUM_PM_SENSOR 					(BaseAdreesMCU)0x0801FC96
#define START_BASE_ADDRESS_CO2_SENSOR           			(BaseAdreesMCU)0x0801FD2C
#define START_BASE_ADDRESS_SO2_PM_VALUE         			(BaseAdreesMCU)0x0801FDC2
#define START_BASE_ADDRESS_TEMPERATURE          			(BaseAdreesMCU)0x0801FE58
#define START_BASE_ADDRESS_HUMIDITY		       				(BaseAdreesMCU)0x0801FEEE


/*Flash page 126 start address 0x0801F800  ->  0x0801FFFF from MCU*/
#define START_BASE_ADDRESS_PARAMETER_PM2_5    				(BaseAdreesMCU)0x0801F800
#define START_BASE_ADDRESS_PARAMETER_SUM_PM   				(BaseAdreesMCU)0x0801F896
#define START_BASE_ADDRESS_PARAMETER_CO2      				(BaseAdreesMCU)0x0801F92C
#define START_BASE_ADDRESS_PARAMETER_SO2      				(BaseAdreesMCU)0x0801F9C2
#define START_BASE_ADDRESS_PARAMETER_TEMPERATURE      		(BaseAdreesMCU)0x0801FA58
#define START_BASE_ADDRESS_PARAMETER_HUMIDITY      			(BaseAdreesMCU)0x0801FAEE

/*Max array langnge interpolation*/
#define MAX_ARR_X_Y_LAGRANGE 								3

/*Max Prameter setup calibrartion group sensor*/
#define MODE_MAX_CALIBRATION_GROUP_SENSOR      				6
#define MODE_MIN_CALIBRATION_GROUP_SENSOR     				0

/*Max - Min prameter group sensor*/
/*PM2.5 sensor*/
#define PM2_5_MAX       									1000U          /*1000 ug/m3		*/
#define PM2_5_MIN											0U             /*0 ug/m3*/
/*Sum pm sensor*/
#define SUM_PM_MAX          							    500U           /*500 ug/m3		*/
#define SUM_PM_MIN          							    0U             /*0 ug/m3*/
/*co2 sensor*/
#define CO2_MAX          							    	1000U          /*1000 ppm		*/
#define CO2_MIN          							   		0U             /*0 ppm*/
/*SO2 sensor*/
#define SO2_MAX          							    	1000U          /*1000 ppm		*/
#define SO2_MIN          							    	0U             /*0 ppm			*/
/*Humidity sensor*/
#define HUMIDITY_MAX          							    95U            /*95 %			*/
#define HUMIDITY_MIN          							    0U             /*0 ppm			*/
/*Temperature sensor*/
#define TEMPERATURE_MAX          							60U            /*60 °C			*/
#define TEMPERATURE_MIN          							0U             /*0 °C			*/

/*Mode setup*/
#define MAX_MODE_SETUP										6
#define MIN_MODE_SETUP               						0

/*Mode monitor setup*/
#define MAX_MODE_MONITOR                 					5
#define MIN_MODE_MONITOR 									0


/*Max array funtion pointer initialization group sensor*/
#define MAX_ARRAY_FUN_PTR_INIT_SENSOR                      8



typedef uint32_t BaseAdreesMCU;

/*option setup prameter group sensor*/
typedef enum 
{
//    OPTION_01_PM2_5_SENSOR         = 1,
    OPTION_02_SUM_PM_SENSOR         = 1,
	OPTION_03_CO2_SENSOR            = 2,
	OPTION_04_SO2_SENSOR            = 3,
    OPTION_05_TEMPERATURE_SENSOR    = 4,
	OPTION_06_HUMIDITY_SENSOR       = 5,
	OPTION_07_MONITOR_GROUP_SENSOR  = 6,
}Selec_Option_Sensor;

/*option monitor parameter before setup prameter group sensor*/
typedef enum
{
	// PM2_5_MONITOR 		= 1,
	SUM_PM_MONITOR 		= 1,
	CO2_MONITOR 		= 2,
	SO2_MONITOR 	    = 3,
	HUMIDITY_MONITOR    = 4, 
	TEMPERATURE         = 5
}Option_monitor_group_sensor;

typedef struct
{
    float(*Result_Calib_Sensor);
}SensorCalibraion_t;

typedef struct
{
    void(*gInit_Sensor)(void);
}Init_Handle_Sensor;

typedef struct
{
    uint8_t index;
    Init_Handle_Sensor gSensor;
    SensorCalibraion_t gSesnor_calibration;
}gSensor;


/*Group sensor initialization*/
Hpma115S0_Dust_Sensor_Name          hpma115s0_sensor_01;
Mh_Z19B_Co2_Sensor_Name             mh_z19b_sensor_01;
DHTxx_Humidity_Sensor_Name          DHT22_Sensor_1;
BMP180_Air_Pressure_Sensor_Name     bmp180_sensor_01;
SharpG2y10DustSensor_Name           sharpg2y_sensor01;
hx711_t                             so2_sensor;
LM335A_HandleTypeDef                lm335a_sensor;


/**
 * Init sensor 
*/
static void Init_Hpma115S0_Dust_Sensor(void);

static void Init_Mh_Z19B_Co2_Sensor(void);

static void Init_DHT22(void);

static void Init_So2_Sensor(void);

static void Init_BMP18_Air_Pressure(void);

static void Init_Sharp_G2y10_Sum_Dust_Sensor(void);

static void Init_Lm335A_Temperature_Sensor(void);

static void Int_Read_Data_Parameter_Group_Sensor_To_Flash_MCU(void);


/**
 *
 */
static uint8_t Output_Value_Sum_Pm_Sensor(void);

static uint8_t Output_Value_Co2_Sensor(void);

static uint8_t Output_Value_So2_Sensor(void);

static uint8_t Output_Value_Humidity_Sensor(void);

static uint8_t Output_Value_Temperature_Sensor(void);



/*variable x input lagrange interpolation */
static  float x_input_pm2_5_value[MAX_ARR_X_Y_LAGRANGE] 	  		= 			{0};

static  float x_input_sum_pm_value[MAX_ARR_X_Y_LAGRANGE] 	  		= 			{0};

static  float x_input_co2_value[MAX_ARR_X_Y_LAGRANGE]         		= 			{0};

static  float x_input_so2_pm_value[MAX_ARR_X_Y_LAGRANGE]      		= 			{0};

static float x_input_temperature_value[MAX_ARR_X_Y_LAGRANGE]  		=		    {0};

static  float x_input_humidity_value[MAX_ARR_X_Y_LAGRANGE]   		= 			{0};

/*variable y input lagrange interpolation */
static float y_static_input_pm2_5_value[MAX_ARR_X_Y_LAGRANGE]   	=			{225, 555, 865};

static float y_static_input_sum_pm_value[MAX_ARR_X_Y_LAGRANGE] 		=			{235, 345, 455};

static float y_static_input_co2_value[MAX_ARR_X_Y_LAGRANGE]         =			{225, 525, 845};

static float y_static_input_so2_value[MAX_ARR_X_Y_LAGRANGE]			=			{235, 565, 855};

static float y_static_input_temperature_value[MAX_ARR_X_Y_LAGRANGE] =			{25, 45, 55};

static float y_static_input_humidity_value[MAX_ARR_X_Y_LAGRANGE]	=			{25, 55, 85};

/*system local protype funtion*/
static uint8_t Save_Value_Float_Flash(uint32_t address, float *array, uint8_t lenght_array);
static uint8_t Read_Value_Float_Flash(uint32_t address, float *array, uint8_t lenght_array);

static uint8_t Selec_Option_Sensor_Name(void);
static uint8_t Setup_Parameter_Pm2_5_Sensor(void);
static uint8_t Setup_Parameter_Sum_Pm_Sensor(void);
static uint8_t Setup_Parameter_Co2_Sensor(void);
static uint8_t Setup_Parameter_So2_Sensor(void);
static uint8_t Setup_Parameter_Humidity_Sensor(void);
static uint8_t Setup_Parameter_Temperature_Sensor(void);
static void Save_Parameter_Sensor(void);
static void Monitor_Group_Sensor(void);
static float Lagrange_Interpolation(float *x, float *y, uint8_t lenght ,float find_value);

static float temperature = 0, humidity = 0;

/*Extern variable globale from the file name main.c*/
extern hadc1;
extern hdma_adc1;
extern hi2c2;
extern htim2;
extern htim3;
extern huart1;
extern huart2;
extern lcd1;
extern moudle_lora_01;


/*Global group sensor funtion initialization*/
gSensor gSensor_Init_System[] ={

    {	.index = 0,
    	Init_Hpma115S0_Dust_Sensor
    },
	{	.index = 1,
		Init_Mh_Z19B_Co2_Sensor
	},

	{	.index = 2,
		Init_DHT22
	},
	{	.index = 3,
		Init_So2_Sensor
	},
	{	.index = 4,
		Init_BMP18_Air_Pressure
	},
	{	.index = 5,
		Init_Sharp_G2y10_Sum_Dust_Sensor
	},
	{	.index = 6,
		Init_Lm335A_Temperature_Sensor
	},
	{	.index = 7,
		Int_Read_Data_Parameter_Group_Sensor_To_Flash_MCU
	}

};
/*Initialization globale flag system*/
 GLOBAL_FLAG flag_system ={.flag_01 = 0, .flag_02 = 0, .check_start_mesurment_sensor = 0};

/**
 * @brief Save_Value_Float_Flash
 * 
 * @param address 
 * @param value_reload 
 * @return uint8_t 
 */
static uint8_t Save_Value_Float_Flash(uint32_t address, float *array, uint8_t lenght_array)
{
	float value = 0;
	for(uint8_t i =0; i < lenght_array; i++)
	{
		value = Flash_Read_Float(address + 4*i);
		if(value == *(array + i))
			continue;
		else
		Flash_Write_Float(address + 4*i, *(array+i));
	}
	return 0;
}


/**
 * Read_Value_Float_Flash
*/
static uint8_t Read_Value_Float_Flash(uint32_t address, float *array, uint8_t lenght_array)
{
	for(uint8_t i =0; i < lenght_array; i++)
	{
		*(array+i) = Flash_Read_Float(address + 4 * i);
	}
	return 0;
}



/**
 * @brief Init_Hpma115S0_Dust_Sensor
 * 
 */
static void Init_Hpma115S0_Dust_Sensor(void)
{
	 Hpma115S0_Dust_Sensor_Init(&hpma115s0_sensor_01, &huart2);
	 Hpma115S0_Start_Particle_Measure(&hpma115s0_sensor_01);
	 Hpma115S0_Enable_Auto_Send(&hpma115s0_sensor_01);
}

/**
 * @brief Init_Mh_Z19B_Co2_Sensor
 * 
 */
static void Init_Mh_Z19B_Co2_Sensor(void)
{
	  Mh_Z19B_Co2_Sensor_Init(&mh_z19b_sensor_01, &huart1);
	  Sensor_Set_Auto_Calibration(&mh_z19b_sensor_01);
}


/**
 * @brief Init_DHT22
 * 
 */
static void Init_DHT22(void)
{
	  DHT_Init(&DHT22_Sensor_1, &htim2, DHT22_Sensor_GPIO_Port, DHT22_Sensor_Pin);
}

/**
 * @brief Init_So2_Sensor
 * 
 */
static void Init_So2_Sensor(void)
{
	  hx711_init(&so2_sensor, So2_Hx711_Clk_GPIO_Port, So2_Hx711_Clk_Pin, So2_Hx711_Data_GPIO_Port, So2_Hx711_Data_Pin);
	  hx711_coef_set(&so2_sensor, 8368841.00); // read afer calibration
	  hx711_tare(&so2_sensor, 10);
	  hx711_coef_set(&so2_sensor, 1.0f);
	  hx711_set_gain(&so2_sensor, 64);
}

/**
 * @brief Init_BMP18_Air_Pressure
 * 
 */
static void Init_BMP18_Air_Pressure(void)
{
	  BMP_180_Air_Pressure_Sensor_Init(&bmp180_sensor_01, &hi2c2, 0);
	  BMP180_Start_Read_Calliberation_Data(&bmp180_sensor_01);
}

/**
 * @brief Init_Sharp_G2y10_Sum_Dust_Sensor
 * 
 */
static void Init_Sharp_G2y10_Sum_Dust_Sensor(void)
{
	   HAL_GPIO_WritePin(Ctl_AI_Dust_Sensor_GPIO_Port, Ctl_AI_Dust_Sensor_Pin, GPIO_PIN_RESET);
	   Sharp_G2y10_Dust_Sensor_Init(&sharpg2y_sensor01, &hadc1, &htim2, Ctl_AI_Dust_Sensor_GPIO_Port, Ctl_AI_Dust_Sensor_Pin);
}

/**
 * @brief Init_Lm335A_Temperature_Sensor
 * 
 */
static void Init_Lm335A_Temperature_Sensor(void)
{
	   LM335A_Init(&lm335a_sensor, &hadc1);
}


/**
 * @brief Selec_Option_Sensor_Name
 * 
 * @return uint8_t 
 */
static uint8_t Selec_Option_Sensor_Name(void)
{
	static __IO uint8_t mode_option_selec_sensor = 0;
	static __IO uint8_t check_option_mode = 0;
	/*check status input pin mode selec sensor. Before for each setup prameter*/
    if(HAL_GPIO_ReadPin(BUTTON_01_OPTION_GPIO_Port, BUTTON_01_OPTION_Pin) == GPIO_PIN_SET)
    {
    	HAL_Delay(100);
        if(HAL_GPIO_ReadPin(BUTTON_01_OPTION_GPIO_Port, BUTTON_01_OPTION_Pin) == GPIO_PIN_SET)
        {
        	CLCD_I2C_Clear(&lcd1);
            mode_option_selec_sensor++;
            flag_system.flag_02 = 1;
            if(mode_option_selec_sensor > MAX_MODE_SETUP)
            {
            	mode_option_selec_sensor = MIN_MODE_SETUP;
            	flag_system.flag_02 = 0;
            }
        }
    }
    switch (mode_option_selec_sensor)
    {
//        case OPTION_01_PM2_5_SENSOR:
//			CLCD_I2C_SetCursor(&lcd1, 0, 3);
//			CLCD_I2C_WriteString(&lcd1, "Tab_1");
//            Setup_Parameter_Pm2_5_Sensor();
//            HAL_Delay(50);
//            break;
		/*Setup prameter sum pm sensor*/
        case OPTION_02_SUM_PM_SENSOR:
			if(check_option_mode == 1)
			{
        		HAL_TIM_Base_Stop_IT(&htim3);
				check_option_mode = 2;
			}
        	Send_Data_74HC595(0xFF);
			CLCD_I2C_SetCursor(&lcd1, 0, 3);
			CLCD_I2C_WriteString(&lcd1, "Tab_1");
            Setup_Parameter_Sum_Pm_Sensor();
            break;

		/*Setup prameter co2 sensor*/
        case OPTION_03_CO2_SENSOR:
			if(check_option_mode == 2)
			{
        		HAL_TIM_Base_Stop_IT(&htim3);
				check_option_mode = 3;
			}
        	Send_Data_74HC595(0xFF);
			CLCD_I2C_SetCursor(&lcd1, 0, 3);
			CLCD_I2C_WriteString(&lcd1, "Tab_2");
			Setup_Parameter_Co2_Sensor();
            break;
        
		/*Setup prameter so2 sensor*/
        case OPTION_04_SO2_SENSOR:
        	if(check_option_mode == 3)
			{
        		HAL_TIM_Base_Stop_IT(&htim3);
				check_option_mode = 4;
			}
        	Send_Data_74HC595(0xFF);
			CLCD_I2C_SetCursor(&lcd1, 0, 3);
			CLCD_I2C_WriteString(&lcd1, "Tab_3");
            Setup_Parameter_So2_Sensor();
            break;

		/*Setup prameter temperature sensor*/
        case OPTION_05_TEMPERATURE_SENSOR:
        	if(check_option_mode == 5)
			{
        		HAL_TIM_Base_Stop_IT(&htim3);
				check_option_mode = 6;
			}
        	Send_Data_74HC595(0xFF);
			CLCD_I2C_SetCursor(&lcd1, 0, 3);
			CLCD_I2C_WriteString(&lcd1, "Tab_4");
            Setup_Parameter_Temperature_Sensor();
             break;

		/*Setup prameter humidity sensor*/
		case OPTION_06_HUMIDITY_SENSOR:
			if(check_option_mode == 7)
			{
        		HAL_TIM_Base_Stop_IT(&htim3);
				check_option_mode = 8;
			}
			Send_Data_74HC595(0xFF);
			CLCD_I2C_SetCursor(&lcd1, 0, 3);
			CLCD_I2C_WriteString(&lcd1, "Tab_5");
            Setup_Parameter_Humidity_Sensor();
            break;

		/*Setup monitor group sensor*/
		case OPTION_07_MONITOR_GROUP_SENSOR:
            if(check_option_mode == 9)
			{
        		HAL_TIM_Base_Stop_IT(&htim3);
				check_option_mode = 0;
			}
        	Send_Data_74HC595(0xFF);
			CLCD_I2C_SetCursor(&lcd1, 0, 3);
			CLCD_I2C_WriteString(&lcd1, "Tab_6");
			Monitor_Group_Sensor();
			break;
        
		/*default mode */
        default:
			/*Start timer timer sensor*/
			if(check_option_mode == 0)
			{
				HAL_TIM_Base_Start_IT(&htim3);
				check_option_mode = 1;
			}
        	Run_Normal();
			/*setup variable: mode_option_selec_sensor = 0*/
			mode_option_selec_sensor = 0;
            break;
    }
    return 0;
}

/**
 * @brief Save_Parameter_Sensor
 * 
 */
static void Save_Parameter_Sensor(void)
{
	static __IO uint8_t mode_save_parameter_sensor = 0;
	static __IO uint8_t check = 0;
	/*Check button save prameter into flash*/
	if(HAL_GPIO_ReadPin(BUTTON_02_SAVE_GPIO_Port, BUTTON_02_SAVE_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*Check button save prameter into flash*/
		if(HAL_GPIO_ReadPin(BUTTON_02_SAVE_GPIO_Port, BUTTON_02_SAVE_Pin) == GPIO_PIN_SET)
		{
			/*Clear LCD*/
			CLCD_I2C_Clear(&lcd1);
			/*variable up*/
			mode_save_parameter_sensor++;
			/*set up flag global*/
			flag_system.flag_01  = 1;
			if(mode_save_parameter_sensor > 1)
			{
				/*variable down*/
				mode_save_parameter_sensor = 0;
				/*set up flag global*/
				flag_system.flag_01  = 0;
			}
		}
	}
	/**
	 * check mode
	*/
	switch (mode_save_parameter_sensor)
	{
		case 1:
				if(check == 1)
				{
					/*Lcd setup cursor*/
					CLCD_I2C_SetCursor(&lcd1, 0, 0);
					/*Lcd send string*/
					CLCD_I2C_WriteString(&lcd1, "SaveParameter");

					/*Erase flash page*/
					Flash_Erase(START_BASE_ADDRESS_PM2_5_SENSOR);
					/*Erase flash page*/
					Flash_Erase(START_BASE_ADDRESS_PARAMETER_PM2_5);

					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PM2_5_SENSOR, x_input_pm2_5_value, sizeof(x_input_pm2_5_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_SUM_PM_SENSOR, x_input_sum_pm_value,  sizeof(x_input_sum_pm_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_CO2_SENSOR, x_input_co2_value,  sizeof(x_input_co2_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_SO2_PM_VALUE, x_input_so2_pm_value,  sizeof(x_input_so2_pm_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_TEMPERATURE, x_input_temperature_value,  sizeof(x_input_temperature_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_HUMIDITY, x_input_humidity_value,  sizeof(x_input_humidity_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_PM2_5, y_static_input_pm2_5_value,  sizeof(y_static_input_pm2_5_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_SUM_PM, y_static_input_sum_pm_value,  sizeof(y_static_input_sum_pm_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_CO2, y_static_input_co2_value,  sizeof(y_static_input_co2_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_SO2, y_static_input_so2_value,  sizeof(y_static_input_so2_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_TEMPERATURE, y_static_input_temperature_value,  sizeof(y_static_input_temperature_value)/sizeof(float));
					/*Save Parameter data type float*/
					Save_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_HUMIDITY, y_static_input_humidity_value,  sizeof(y_static_input_humidity_value)/sizeof(float));

					/*Lcd setup cursor*/
					CLCD_I2C_SetCursor(&lcd1, 0, 1);
					/*Lcd send string*/
					CLCD_I2C_WriteString(&lcd1,"Done");
					check = 2;
				}
				break;

		default:
			check = 1;
			break;
	}
}

/**
 * @brief Monitor_Group_Sensor
 * 
 */
static void Monitor_Group_Sensor(void)
{
	static __IO uint8_t mode_monitor_Gruop_Sensor = 0;
//	static float value = 0;
	/*Check button monitor prameter sensor display to LCD*/
	if(HAL_GPIO_ReadPin(BUTTON_03_MONITOR_GPIO_Port, BUTTON_03_MONITOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*Check button monitor prameter sensor display to LCD*/
		if(HAL_GPIO_ReadPin(BUTTON_03_MONITOR_GPIO_Port, BUTTON_03_MONITOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd Clear*/
			CLCD_I2C_Clear(&lcd1);
			/*Variable up*/
			mode_monitor_Gruop_Sensor++;
			if(mode_monitor_Gruop_Sensor > MAX_MODE_MONITOR)
			{
				/*Variable mode_monitor_Gruop_Sensor = 0*/
				mode_monitor_Gruop_Sensor = MIN_MODE_MONITOR;
			}
		}
	}
	switch (mode_monitor_Gruop_Sensor)
	{
//		case PM2_5_MONITOR:
//			/* monior pm2_5 sensor */
//			value = Pm2_5_Result_Calibration();
//			Display_Pm2_5(&lcd1, value);
//			HAL_Delay(500);
//			break;

		/* monitor sum pm sensor*/
		case SUM_PM_MONITOR:
			Output_Value_Sum_Pm_Sensor();
			break;

		/* monitor co2 sensor*/
		case CO2_MONITOR:
			Output_Value_Co2_Sensor();
			break;

		/* monitor so2 sensor*/
		case SO2_MONITOR:
			Output_Value_So2_Sensor();
			break;

		/* monitor humidity sensor*/
		case HUMIDITY_MONITOR:
			Output_Value_Humidity_Sensor();
			break;

		/* monitor humidity sensor*/
		case TEMPERATURE:
			Output_Value_Temperature_Sensor();
			break;

	/*Defaulr mode*/
	default:
		/*LCD set cursor*/
		CLCD_I2C_SetCursor(&lcd1, 0, 0);
		/*LCd Send string*/
		CLCD_I2C_WriteString(&lcd1,"Monitor_Sensor");
		HAL_Delay(50);
		break;
	}
}

/**
 * @brief Setup_Parameter_Pm2_5_Sensor
 * 
 * @return uint8_t 
 */
static uint8_t Setup_Parameter_Pm2_5_Sensor(void)
{
	static __IO uint8_t mode_setup_parameter_pm2_5_sensor = 0;
	static __IO uint8_t check_01 = 0;
	uint32_t time_wake_up_01 = HAL_GetTick();
	/*check button set parameter*/
    if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
    {
    	HAL_Delay(100);
        if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
        {
			CLCD_I2C_Clear(&lcd1);
            mode_setup_parameter_pm2_5_sensor++;
            if(mode_setup_parameter_pm2_5_sensor > MODE_MAX_CALIBRATION_GROUP_SENSOR)
                mode_setup_parameter_pm2_5_sensor = MODE_MIN_CALIBRATION_GROUP_SENSOR;
        }
    }

   /*
    *setting measurement condition pm2_5 sensor
    *
    * */

    switch (mode_setup_parameter_pm2_5_sensor)
    {
    	/*Set up input value ppm 0 - 255*/
        case 1:
		    /*lcd display option*/
			Display_Setup_Parameter_Pm2_5(&lcd1,y_static_input_pm2_5_value[0]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_pm2_5_value[0]++;
				if(y_static_input_pm2_5_value[0] >= PM2_5_MAX)
				{
					y_static_input_pm2_5_value[0] = PM2_5_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_pm2_5_value[0]--;
				if(y_static_input_pm2_5_value[0] <= PM2_5_MIN)
				{
					y_static_input_pm2_5_value[0] = PM2_5_MIN;
				}
			}
			break;

        case 2:
        	Display_Setup_Parameter_Pm2_5(&lcd1,y_static_input_pm2_5_value[0]);
			/*input value*/
			if(check_01 == 1)
			{
				while(HAL_GetTick() - time_wake_up_01 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*Turn on pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				x_input_pm2_5_value[0] = Hpma115S0_Caclulator_Average(&hpma115s0_sensor_01, 10);
				for(uint8_t i =0; i < 10; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				check_01 ++;
			}
			if(check_01 == 2)
			{
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				Display_Done(&lcd1, x_input_pm2_5_value[0]);
			}
            break;

          	/*Set up input value ppm 0 - 555*/
			case 3:
				/*lcd display option*/
				Display_Setup_Parameter_Pm2_5(&lcd1,y_static_input_pm2_5_value[1]);
				/*check the button press then perform the increment of the variable's value*/
				if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
				{
					HAL_Delay(50);
					y_static_input_pm2_5_value[1]++;
					if(y_static_input_pm2_5_value[1] >= PM2_5_MAX)
					{
						y_static_input_pm2_5_value[1] = PM2_5_MAX;
					}

				}
				/*check the button press then do the decrement of the variable*/
				if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
				{
					HAL_Delay(50);
					y_static_input_pm2_5_value[1]--;
					if(y_static_input_pm2_5_value[1] <= PM2_5_MIN)
					{
						y_static_input_pm2_5_value[1] = PM2_5_MIN;
					}
				}
				break;

			case 4:
				Display_Setup_Parameter_Pm2_5(&lcd1,y_static_input_pm2_5_value[1]);
				/*input value*/
				if(check_01 == 1)
				{
					while(HAL_GetTick() - time_wake_up_01 <= TIME_WAITTING_START_CALIBRATION)
					{
						/*Turn on pump*/
						Send_Data_74HC595(0xAF);
					}
					/*Turn off pump*/
					Send_Data_74HC595(0xFF);
					x_input_pm2_5_value[1] = Hpma115S0_Caclulator_Average(&hpma115s0_sensor_01, 10);
					for(uint8_t i =0; i < 10; i++)
					{
						HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
						HAL_Delay(1000);
					}
					check_01 ++;
				}
				if(check_01 == 2)
				{
					HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
					Display_Done(&lcd1, x_input_pm2_5_value[1]);
				}
				break;

			   /*Set up input value ppm 555 - 855*/
				case 5:
					/*lcd display option*/
					Display_Setup_Parameter_Pm2_5(&lcd1,y_static_input_pm2_5_value[2]);
					/*check the button press then perform the increment of the variable's value*/
					if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
					{
						HAL_Delay(50);
						y_static_input_pm2_5_value[2]++;
						if(y_static_input_pm2_5_value[2] >= PM2_5_MAX)
						{
							y_static_input_pm2_5_value[2] = PM2_5_MAX;
						}

					}
					/*check the button press then do the decrement of the variable*/
					if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
					{
						HAL_Delay(50);
						y_static_input_pm2_5_value[2]--;
						if(y_static_input_pm2_5_value[2] <= PM2_5_MIN)
						{
							y_static_input_pm2_5_value[2] = PM2_5_MIN;
						}
					}
					break;

				case 6:
					Display_Setup_Parameter_Pm2_5(&lcd1,y_static_input_pm2_5_value[2]);
					/*input value*/
					if(check_01 == 3)
					{
						while(HAL_GetTick() - time_wake_up_01 <= TIME_WAITTING_START_CALIBRATION)
						{
							/*Turn on pump*/
							Send_Data_74HC595(0xAF);
						}
						/*Turn off pump*/
						Send_Data_74HC595(0xFF);
						x_input_pm2_5_value[2] = Hpma115S0_Caclulator_Average(&hpma115s0_sensor_01, 10);
						for(uint8_t i =0; i < 10; i++)
						{
							HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
							HAL_Delay(1000);
						}
						check_01 ++;
					}
					if(check_01 == 4)
					{
						HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
						Display_Done(&lcd1, x_input_pm2_5_value[2]);
					}
					break;

        default:
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			CLCD_I2C_WriteString(&lcd1, "Pm2_5 Sensor");
			check_01 = 1;
            break;
    }
    return 0;
}

/**
 * @brief Setup_Parameter_Sum_Pm_Sensor
 * 
 * @return uint8_t 
 */
static uint8_t Setup_Parameter_Sum_Pm_Sensor(void)
{
	static __IO uint8_t mode_setup_parameter_sum_pm_sensor = 0;
	static __IO uint8_t check_02 = 0;
	uint32_t time_wake_up_02 = HAL_GetTick();
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Display clear*/
			CLCD_I2C_Clear(&lcd1);
			/*variable up */
			mode_setup_parameter_sum_pm_sensor++;
			if(mode_setup_parameter_sum_pm_sensor > MODE_MAX_CALIBRATION_GROUP_SENSOR)
				/*variable up  mode_setup_parameter_sum_pm_sensor = 0*/
				mode_setup_parameter_sum_pm_sensor = MODE_MIN_CALIBRATION_GROUP_SENSOR;
		}
	}

   /*
	*setting measurement condition sum pm sensor
	*
	* */

	switch (mode_setup_parameter_sum_pm_sensor)
	{
		/*set up value sum pm 0 - 235*/
		case 1:

			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[0]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_sum_pm_value[0]++;
				if(y_static_input_sum_pm_value[0] >= SUM_PM_MAX)
				{
					y_static_input_sum_pm_value[0] = SUM_PM_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_sum_pm_value[0]--;
				if(y_static_input_sum_pm_value[0] <= SUM_PM_MIN)
				{
					y_static_input_sum_pm_value[0] = SUM_PM_MIN;
				}
			}
			break;

		case 2:
			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[0]);
			/*check condition for execution the data reading from sum pm sensor*/
			if(check_02 == 1)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_02 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*Turn on pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_sum_pm_value[0] = Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
				/*Tonggle buzz after having read data from sum pm sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_02 ++;
			}
			/*check condition when finished reading data from sum pm sensor*/
			if(check_02 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_sum_pm_value[0]);
			}
			break;

		/*set up value sum pm 235 - 345*/
		case 3:
			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[1]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_sum_pm_value[1]++;
				if(y_static_input_sum_pm_value[1] >= SUM_PM_MAX)
				{
					y_static_input_sum_pm_value[1] = SUM_PM_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_sum_pm_value[1]--;
				if(y_static_input_sum_pm_value[1] <= SUM_PM_MIN)
				{
					y_static_input_sum_pm_value[1] = SUM_PM_MIN;
				}
			}
			break;
		case 4:
			/*Lcd display*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[1]);
			/*check condition for execution the data reading from sum pm sensor*/
			if(check_02 == 2)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_02 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_sum_pm_value[1] = Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
				/*Tonggle buzz after having read data from sum pm sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_02 ++;
			}
			/*check condition when finished reading data from sum pm sensor*/
			if(check_02 == 3)
			{	
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_sum_pm_value[1]);
			}
			break;

		/*set up value sum pm 345 - 455*/
		case 5:
			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[2]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_sum_pm_value[2]++;
				if(y_static_input_sum_pm_value[2] >= SUM_PM_MAX)
				{
					y_static_input_sum_pm_value[2] = SUM_PM_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_sum_pm_value[2]--;
				if(y_static_input_sum_pm_value[2] <= SUM_PM_MIN)
				{
					y_static_input_sum_pm_value[2] = SUM_PM_MIN;
				}
			}
			break;
		case 6:
			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[2]);
			/*check condition for execution the data reading from sum pm sensor*/
			if(check_02 == 3)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_02 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_sum_pm_value[2] = Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
				/*Tonggle buzz after having read data from sum pm sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_02 ++;
			}
			/*check condition when finished reading data from sum pm sensor*/
			if(check_02 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_sum_pm_value[2]);
			}
			break;

		/*Default mode*/
		default:
			/*Lcd set cursor*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			/*Lcd display*/
			CLCD_I2C_WriteString(&lcd1, "Sum Pm Sensor");
			/*reassign variable check_02 = 1*/
			check_02 = 1;
			break;
	}

	return 0;
}

/**
 * @brief Setup_Parameter_Co2_Sensor
 *
 * @return uint8_t
 */
static uint8_t Setup_Parameter_Co2_Sensor(void)
{
	static __IO uint8_t mode_setup_parameter_co2_pm_sensor = 0;
	static __IO uint8_t check_03 = 0;
	uint32_t time_wake_up_03 = HAL_GetTick();
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*lcd display */
			CLCD_I2C_Clear(&lcd1);
			/*variable up*/
			mode_setup_parameter_co2_pm_sensor++;
			if(mode_setup_parameter_co2_pm_sensor > MODE_MAX_CALIBRATION_GROUP_SENSOR)
				mode_setup_parameter_co2_pm_sensor = MODE_MIN_CALIBRATION_GROUP_SENSOR;
		}
	}

   /*
	*setting measurement condition co2 pm sensor
	*
	* */
	switch (mode_setup_parameter_co2_pm_sensor)
	{

		/*set up value co2 pm 0 - 225*/
		case 1:
			/*lcd display option*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[0]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_co2_value[0]++;
				if(y_static_input_co2_value[0] >= CO2_MAX)
				{
					y_static_input_co2_value[0] = CO2_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_co2_value[0]--;
				if(y_static_input_co2_value[0] <= CO2_MIN)
				{
					y_static_input_co2_value[0] = CO2_MIN;
				}
			}
			break;
		case 2 :
			/*Lcd display*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[0]);
			/*check condition for execution the data reading from co2 sensor*/
			if(check_03 == 1)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_03 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_co2_value[0] =  Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
				/*Tonggle buzz after having read data from co2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_03++;
			}
			/*check condition when finished reading data from co2 sensor*/
			if(check_03 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_co2_value[0]);
			}
			break;

		/*set up value co2 pm 225 - 525*/
		case 3:
			/*lcd display option*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[1]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_co2_value[1]++;
				if(y_static_input_co2_value[1] >= CO2_MAX)
				{
					y_static_input_co2_value[1] = CO2_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_co2_value[1]--;
				if(y_static_input_co2_value[1] <= CO2_MIN)
				{
					y_static_input_co2_value[1] = CO2_MIN;
				}
			}
			break;
		case 4:
			/*Lcd display*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[1]);
			/*check condition for execution the data reading from co2 sensor*/
			if(check_03 == 2)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_03 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_co2_value[1] =  Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
				/*Tonggle buzz after having read data from co2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_03 ++;
			}
			/*check condition when finished reading data from co2 sensor*/
			if(check_03 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_co2_value[1]);
			}
			break;

		/*set up value co2 pm 525 - 845*/
		case 5:
			/*lcd display option*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[2]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_co2_value[2]++;
				if(y_static_input_co2_value[2] >= CO2_MAX)
				{
					y_static_input_co2_value[2] = CO2_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_co2_value[2]--;
				if(y_static_input_co2_value[2] <= CO2_MIN)
				{
					y_static_input_co2_value[2] = CO2_MIN;
				}
			}
			break;
		case 6:
			/*Lcd display*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[2]);
			/*check condition for execution the data reading from co2 sensor*/
			if(check_03 == 3)
			{
				while (HAL_GetTick() - time_wake_up_03 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_co2_value[2] =  Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
				/*Tonggle buzz after having read data from co2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_03 ++;
			}
			/*check condition when finished reading data from co2 sensor*/
			if(check_03 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_co2_value[2]);
			}
			break;


		/*Default mode*/
		default:
			/*Lcd set cursor*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			/*Lcd send string*/
			CLCD_I2C_WriteString(&lcd1, "Co2 Sensor");
			check_03 = 1;
			break;
	}

	    return 0;
}


/**
 * @brief Setup_Parameter_So2_Sensor
 *
 * @return uint8_t
 */
static uint8_t Setup_Parameter_So2_Sensor(void)
{
	static __IO uint8_t mode_setup_parameter_so2_sensor = 0;
	static __IO uint8_t check_04 = 0;
	uint32_t time_wake_up_04 = HAL_GetTick();
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd clear*/
			CLCD_I2C_Clear(&lcd1);
			mode_setup_parameter_so2_sensor++;
			if(mode_setup_parameter_so2_sensor > MODE_MAX_CALIBRATION_GROUP_SENSOR)
				mode_setup_parameter_so2_sensor = MODE_MIN_CALIBRATION_GROUP_SENSOR;
		}
	}

   /*
	*setting measurement condition so2 pm sensor
	*
	* */

	switch (mode_setup_parameter_so2_sensor)
	{
		/*set up value so2 pm 0 - 235*/
		case 1:
			/*lcd display option*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[0]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_so2_value[0]++;
				if(y_static_input_so2_value[0] >= SO2_MAX)
				{
					y_static_input_so2_value[0]= SO2_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_so2_value[0]--;
				if(y_static_input_so2_value[0] <= SO2_MIN)
				{
					y_static_input_so2_value[0]= SO2_MIN;
				}
			}
			break;
		case 2:
			/*lcd display option*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[0]);
			/*check condition for execution the data reading from So2 sensor*/
			if(check_04 == 1)
			{
				while (HAL_GetTick() - time_wake_up_04 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_so2_pm_value[0] =  hx711_so2_result(&so2_sensor, 10);
				/*Tonggle buzz after having read data from so2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_04 ++;
			}
		     /*check condition when finished reading data from so2 sensor*/
			if(check_04 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_so2_pm_value[0] );
			}
			break;

		/*set up value so2 pm 235 - 565*/
		case 3:
			/*lcd display option*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[1]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_so2_value[1]++;
				if(y_static_input_so2_value[1] >= SO2_MAX)
				{
					y_static_input_so2_value[1]= SO2_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_so2_value[1]--;
				if(y_static_input_so2_value[1] <= SO2_MIN)
				{
					y_static_input_so2_value[1]= SO2_MIN;
				}
			}
			break;
		case 4:
			/*Lcd display*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[1]);
			/*check condition for execution the data reading from So2 sensor*/
			if(check_04 == 2)
			{
				while (HAL_GetTick() - time_wake_up_04 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_so2_pm_value[1] =  hx711_so2_result(&so2_sensor, 10);
				/*Tonggle buzz after having read data from so2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_04++;
			}
			/*check condition when finished reading data from so2 sensor*/
			if(check_04 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1,x_input_so2_pm_value[1] );
			}
			break;

		/*set up value so2 pm 535 - 855*/
		case 5:
			/*lcd display option*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[2]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_so2_value[2]++;
				if(y_static_input_so2_value[2] >= SO2_MAX)
				{
					y_static_input_so2_value[2]= SO2_MAX;
				}

			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_so2_value[2]--;
				if(y_static_input_so2_value[2] <= SO2_MIN)
				{
					y_static_input_so2_value[2]= SO2_MIN;
				}
			}
			break;
		case 6:
			/*Lcd display*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[2]);
			/*check condition for execution the data reading from So2 sensor*/
			if(check_04 == 3)
			{
				while (HAL_GetTick() - time_wake_up_04 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				x_input_so2_pm_value[2] =  hx711_so2_result(&so2_sensor, 10);
				/*Tonggle buzz after having read data from so2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_04++;
			}
			/*check condition when finished reading data from so2 sensor*/
			if(check_04 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Done(&lcd1, x_input_so2_pm_value[2]);
			}
			break;

		/*Default mode*/
		default:
			/*lcd set cursor*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			/*Lcd send string*/
			CLCD_I2C_WriteString(&lcd1, "So2 Sensor");
			/*reassign variable check_04 = 1*/
			check_04 = 1;
			break;
	}
	    return 0;
}


/**
 * @brief Setup_Parameter_Humidity_Sensor
 *
 * @return uint8_t
 */
static uint8_t Setup_Parameter_Humidity_Sensor(void)
{
	static __IO uint8_t mode_setup_parameter_humidity_sensor = 0;
	static __IO uint8_t check_05 = 0;
	uint32_t time_wake_up_05 = HAL_GetTick();
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd clear*/
			CLCD_I2C_Clear(&lcd1);
			mode_setup_parameter_humidity_sensor++;
			if(mode_setup_parameter_humidity_sensor > MODE_MAX_CALIBRATION_GROUP_SENSOR)
				mode_setup_parameter_humidity_sensor = MODE_MIN_CALIBRATION_GROUP_SENSOR;
		}
	}

   /*
	*setting measurement condition humidity sensor
	*
	* */

	switch (mode_setup_parameter_humidity_sensor)
	{
	
		/*set up value humidity 0 - 25*/
		case 1:
			/*lcd display*/
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[0]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_humidity_value[0]++;
				if(y_static_input_humidity_value[0] >= HUMIDITY_MAX)
				{
					y_static_input_humidity_value[0] = HUMIDITY_MAX;
				}
			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_humidity_value[0]--;
				if(y_static_input_humidity_value[0] <= HUMIDITY_MIN)
				{
					y_static_input_humidity_value[0] = HUMIDITY_MIN;
				}
			}
			break;
		case 2:
			/*lcd display*/
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[0]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_05 == 1)
			{
				while (HAL_GetTick() - time_wake_up_05 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				x_input_humidity_value[0] = humidity;
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_05 ++;
			}
			/*check condition when finished reading data from humidity sensor*/
			if(check_05 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Done(&lcd1, x_input_humidity_value[0]);
			}
			break;

		/*set up value humidity 20 - 55*/
		case 3:
			/*lcd display*/
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[1]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_humidity_value[1]++;
				if(y_static_input_humidity_value[1] >= HUMIDITY_MAX)
				{
					y_static_input_humidity_value[1] = HUMIDITY_MAX;
				}
			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_humidity_value[1]--;
				if(y_static_input_humidity_value[1] <= HUMIDITY_MIN)
				{
					y_static_input_humidity_value[1] = HUMIDITY_MIN;
				}
			}
			break;
		case 4:
			/*lcd display*/
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[1]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_05 == 2)
			{
				while (HAL_GetTick() - time_wake_up_05 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				//DHT_Read_Temperature_Humidity(&DHT22_Sensor_1, &temperature, &humidity);
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				x_input_humidity_value[1] = humidity;
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_05 ++;
			}
			/*check condition when finished reading data from humidity sensor*/
			if(check_05 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Done(&lcd1, x_input_humidity_value[1]);
			}
			break;


		/*set up value humidity 55 - 85*/
		case 5:
			/*lcd display */
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[2]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_humidity_value[2]++;
				if(y_static_input_humidity_value[2] >= HUMIDITY_MAX)
				{
					y_static_input_humidity_value[2] = HUMIDITY_MAX;
				}
			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_humidity_value[2]--;
				if(y_static_input_humidity_value[2] <= HUMIDITY_MIN)
				{
					y_static_input_humidity_value[2] = HUMIDITY_MIN;
				}
			}
			break;
		case 6:
			/*lcd display */
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[2]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_05 == 3)
			{
				while (HAL_GetTick() - time_wake_up_05 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				x_input_humidity_value[2] = humidity;
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_05 ++;
			}
			/*check condition when finished reading data from humidity sensor*/
			if(check_05 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Done(&lcd1, x_input_humidity_value[2]);
			}
			break;

		/*Default mode*/
		default:
			/*Lcd cursor*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			/*Lcd send string*/
			CLCD_I2C_WriteString(&lcd1, "Humidity Sensor");
			/*reassign variable*/
			check_05 = 1;
			break;
	}

	    return 0;
}

/**
 * @brief Setup_Parameter_Humidity_Sensor
 *
 * @return uint8_t
 */
static uint8_t Setup_Parameter_Temperature_Sensor(void)
{
	static __IO uint8_t mode_setup_parameter_temperature_sensor = 0;
	static __IO uint8_t check_06 = 0;
	uint32_t time_wake_up_06 = HAL_GetTick();
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd clear*/
			CLCD_I2C_Clear(&lcd1);
			mode_setup_parameter_temperature_sensor++;
			if(mode_setup_parameter_temperature_sensor > MODE_MAX_CALIBRATION_GROUP_SENSOR)
				mode_setup_parameter_temperature_sensor = MODE_MIN_CALIBRATION_GROUP_SENSOR;
		}
	}

   /*
	*setting measurement condition temperature sensor
	*
	* */

	switch (mode_setup_parameter_temperature_sensor)
	{

		/*set up value temperature pm 0 - 25*/
		case 1:
			/*lcd display*/
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[0]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_temperature_value[0]++;
				if(y_static_input_temperature_value[0] >= TEMPERATURE_MAX)
				{
					y_static_input_temperature_value[0] = TEMPERATURE_MAX;
				}
			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_temperature_value[0]--;
				if(y_static_input_temperature_value[0] <= TEMPERATURE_MIN)
				{
					y_static_input_temperature_value[0] = TEMPERATURE_MIN;
				}
			}
			break;
		case 2:
			/*lcd display*/
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[0]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_06 == 1)
			{
				while (HAL_GetTick() - time_wake_up_06 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
//				DHT_Read_Temperature_Humidity(&DHT22_Sensor_1, &temperature, &humidity);
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				x_input_temperature_value[0] = temperature;
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_06 ++;
			}
			/*check condition when finished reading data from temperature sensor*/
			if(check_06 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Done(&lcd1, x_input_temperature_value[0] );
			}
			break;


		/*set up value temperature pm 20 - 45*/
		case 3:
			/*lcd display*/
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[1]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_temperature_value[1]++;
				if(y_static_input_temperature_value[1] >= TEMPERATURE_MAX)
				{
					y_static_input_temperature_value[1] = TEMPERATURE_MAX;
				}
			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				HAL_Delay(50);
				y_static_input_temperature_value[1]--;
				if(y_static_input_temperature_value[1] <= TEMPERATURE_MIN)
				{
					y_static_input_temperature_value[1] = TEMPERATURE_MIN;
				}
			}
			break;
		case 4:
			/*lcd display*/
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[1]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_06 == 2)
			{
				while (HAL_GetTick() - time_wake_up_06 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				x_input_temperature_value[1] = temperature;
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_06 ++;
			}
			/*check condition when finished reading data from temperature sensor*/
			if(check_06 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Done(&lcd1, x_input_temperature_value[1]);
			}
			break;

		/*set up value temperature pm 45 - 55*/
		case 5:
			/*lcd display */
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[2]);
			/*check the button press then perform the increment of the variable's value*/
			if(HAL_GPIO_ReadPin(BUTTON_05_UP_GPIO_Port, BUTTON_05_UP_Pin) == GPIO_PIN_RESET)
			{
				y_static_input_temperature_value[2]++;
				if(y_static_input_temperature_value[2] >= TEMPERATURE_MAX)
				{
					HAL_Delay(50);
					y_static_input_temperature_value[2] = TEMPERATURE_MAX;
				}
			}
			/*check the button press then do the decrement of the variable*/
			if(HAL_GPIO_ReadPin(BUTTON_06_DOWN_GPIO_Port, BUTTON_06_DOWN_Pin) == GPIO_PIN_RESET)
			{
				y_static_input_temperature_value[2]--;
				if(y_static_input_temperature_value[2] <= TEMPERATURE_MIN)
				{
					HAL_Delay(50);
					y_static_input_temperature_value[2] = TEMPERATURE_MIN;
				}
			}
			break;
		case 6:
			/*lcd display */
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[2]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_06 == 3)
			{
				while (HAL_GetTick() - time_wake_up_06 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				x_input_temperature_value[2] = temperature;
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_06++;
			}
			/*check condition when finished reading data from temperature sensor*/
			if(check_06 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Done(&lcd1, x_input_temperature_value[2]);
			}
			break;
		
		/*Default mode*/
		default:
			/*Lcd set cursor*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			/*Lcd send string*/
			CLCD_I2C_WriteString(&lcd1, "TemperatureSensor");
			/*reassign variable check_06 = 1*/
			check_06 = 1;
			break;
	}

	    return 0;
}





/**
 *
 */
static uint8_t Output_Value_Sum_Pm_Sensor(void)
{
	static __IO uint8_t mode_output_value_sum_pm_sensor = 0;
	static __IO uint8_t check_07 = 0;
	uint32_t time_wake_up_07 = HAL_GetTick();
	float out_put_01 = 0;
	float value_01 = 0;
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Display clear*/
			CLCD_I2C_Clear(&lcd1);
			/*variable up */
			mode_output_value_sum_pm_sensor++;
			if(mode_output_value_sum_pm_sensor > 3)
				/*variable up  mode_setup_parameter_sum_pm_sensor = 0*/
				mode_output_value_sum_pm_sensor = 0;
		}
	}

   /*
	*setting measurement condition sum pm sensor
	*
	* */

	switch (mode_output_value_sum_pm_sensor)
	{

		case 1:
			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[0]);
			/*check condition for execution the data reading from sum pm sensor*/
			if(check_07 == 1)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_07 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*Turn on pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_01 = Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
				out_put_01 = Lagrange_Interpolation(x_input_sum_pm_value, y_static_input_sum_pm_value, MAX_ARR_X_Y_LAGRANGE, value_01);
				/*Tonggle buzz after having read data from sum pm sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_07 ++;
			}
			/*check condition when finished reading data from sum pm sensor*/
			if(check_07 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_01);
			}
			break;

		case 2:
			/*Lcd display*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[1]);
			/*check condition for execution the data reading from sum pm sensor*/
			if(check_07 == 2)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_07 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_01 = Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
				out_put_01 = Lagrange_Interpolation(x_input_sum_pm_value, y_static_input_sum_pm_value, MAX_ARR_X_Y_LAGRANGE, value_01);
				/*Tonggle buzz after having read data from sum pm sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_07 ++;
			}
			/*check condition when finished reading data from sum pm sensor*/
			if(check_07 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_01);
			}
			break;

		case 3:
			/*lcd display option*/
			Display_Setup_Parameter_Sum_pm(&lcd1,y_static_input_sum_pm_value[2]);
			/*check condition for execution the data reading from sum pm sensor*/
			if(check_07 == 3)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_07 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_01 = Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
				out_put_01 = Lagrange_Interpolation(x_input_sum_pm_value, y_static_input_sum_pm_value, MAX_ARR_X_Y_LAGRANGE,value_01);
				/*Tonggle buzz after having read data from sum pm sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_07 ++;
			}
			/*check condition when finished reading data from sum pm sensor*/
			if(check_07 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_01);
			}
			break;

		/*Default mode*/
		default:
			/*reassign variable check_02 = 1*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			CLCD_I2C_WriteString(&lcd1, "Sum_Pm_Monitor");
			check_07 = 1;
			break;
	}

	return 0;
}

/**
 *
 */
static uint8_t Output_Value_Co2_Sensor(void)
{
	static __IO uint8_t mode_output_value_co2_pm_sensor = 0;
	static __IO uint8_t check_08 = 0;
	uint32_t time_wake_up_08 = HAL_GetTick();
	float out_put_02 = 0;
	float value_02 = 0;
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*lcd display */
			CLCD_I2C_Clear(&lcd1);
			/*variable up*/
			mode_output_value_co2_pm_sensor++;
			if(mode_output_value_co2_pm_sensor > 3)
				mode_output_value_co2_pm_sensor = 0;
		}
	}

   /*
	*setting measurement condition co2 pm sensor
	*
	* */
	switch (mode_output_value_co2_pm_sensor)
	{
		case 1:
			/*Lcd display*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[0]);
			/*check condition for execution the data reading from co2 sensor*/
			if(check_08 == 1)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_08 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_02 =  Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
				out_put_02 = Lagrange_Interpolation(x_input_co2_value, y_static_input_co2_value, MAX_ARR_X_Y_LAGRANGE, value_02);
				/*Tonggle buzz after having read data from co2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_08++;
			}
			/*check condition when finished reading data from co2 sensor*/
			if(check_08 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_02);
			}
			break;

		case 2:
			/*Lcd display*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[1]);
			/*check condition for execution the data reading from co2 sensor*/
			if(check_08 == 2)
			{
				/*Waitting sensor initialization*/
				while (HAL_GetTick() - time_wake_up_08 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_02 =  Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
				out_put_02 = Lagrange_Interpolation(x_input_co2_value, y_static_input_co2_value, MAX_ARR_X_Y_LAGRANGE, value_02);
				/*Tonggle buzz after having read data from co2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_08 ++;
			}
			/*check condition when finished reading data from co2 sensor*/
			if(check_08 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_02);
			}
			break;

		case 3:
			/*Lcd display*/
			Display_Setup_Parameter_Co2(&lcd1, y_static_input_co2_value[2]);
			/*check condition for execution the data reading from co2 sensor*/
			if(check_08 == 3)
			{
				while (HAL_GetTick() - time_wake_up_08 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_02 =  Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
				out_put_02 = Lagrange_Interpolation(x_input_co2_value, y_static_input_co2_value, MAX_ARR_X_Y_LAGRANGE, value_02);
				/*Tonggle buzz after having read data from co2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_08 ++;
			}
			/*check condition when finished reading data from co2 sensor*/
			if(check_08 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_02);
			}
			break;

		/*Default mode*/
		default:
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			CLCD_I2C_WriteString(&lcd1, "Co2_Monitor");
			check_08 = 1;
			break;
	}

	    return 0;
}

/**
 *
 */
static uint8_t Output_Value_So2_Sensor(void)
{
	static __IO uint8_t mode_output_value_so2_sensor = 0;
	static __IO uint8_t check_09 = 0;
	uint32_t time_wake_up_09 = HAL_GetTick();
	float out_put_03 = 0;
	float value_03 = 0;
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd clear*/
			CLCD_I2C_Clear(&lcd1);
			mode_output_value_so2_sensor++;
			if(mode_output_value_so2_sensor > 3)
				mode_output_value_so2_sensor = 0;
		}
	}

   /*
	*setting measurement condition so2 pm sensor
	*
	* */

	switch (mode_output_value_so2_sensor)
	{

		case 1:
			/*lcd display option*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[0]);
			/*check condition for execution the data reading from So2 sensor*/
			if(check_09 == 1)
			{
				while (HAL_GetTick() - time_wake_up_09 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_03 =  hx711_so2_result(&so2_sensor, 10);
				out_put_03 = Lagrange_Interpolation(x_input_so2_pm_value, y_static_input_so2_value, MAX_ARR_X_Y_LAGRANGE, value_03);
				/*Tonggle buzz after having read data from so2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_09 ++;
			}
		     /*check condition when finished reading data from so2 sensor*/
			if(check_09 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_03);
			}
			break;

		case 2:
			/*Lcd display*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[1]);
			/*check condition for execution the data reading from So2 sensor*/
			if(check_09 == 2)
			{
				while (HAL_GetTick() - time_wake_up_09 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_03 =  hx711_so2_result(&so2_sensor, 10);
				out_put_03 = Lagrange_Interpolation(x_input_so2_pm_value, y_static_input_so2_value, MAX_ARR_X_Y_LAGRANGE, value_03);
				/*Tonggle buzz after having read data from so2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_09++;
			}
			/*check condition when finished reading data from so2 sensor*/
			if(check_09 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_03);
			}
			break;

		case 3:
			/*Lcd display*/
			Display_Setup_Parameter_So2(&lcd1, y_static_input_so2_value[2]);
			/*check condition for execution the data reading from So2 sensor*/
			if(check_09 == 3)
			{
				while (HAL_GetTick() - time_wake_up_09 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				value_03 =  hx711_so2_result(&so2_sensor, 10);
				out_put_03 = Lagrange_Interpolation(x_input_so2_pm_value, y_static_input_so2_value, MAX_ARR_X_Y_LAGRANGE, value_03);
				/*Tonggle buzz after having read data from so2 sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_09++;
			}
			/*check condition when finished reading data from so2 sensor*/
			if(check_09 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*Lcd display*/
				Display_Monitor(&lcd1, out_put_03);
			}
			break;

		/*Default mode*/
		default:
			/*reassign variable check_04 = 1*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			CLCD_I2C_WriteString(&lcd1, "So2_Monitor");
			check_09 = 1;
			break;
	}
	    return 0;
}

/**
 *
 */
static uint8_t Output_Value_Humidity_Sensor(void)
{
	static __IO uint8_t mode_output_value_humidity_sensor = 0;
	static __IO uint8_t check_10 = 0;
	uint32_t time_wake_up_10 = HAL_GetTick();
	float out_put_4 = 0;
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd clear*/
			CLCD_I2C_Clear(&lcd1);
			mode_output_value_humidity_sensor++;
			if(mode_output_value_humidity_sensor > 3)
				mode_output_value_humidity_sensor = 0;
		}
	}

   /*
	*setting measurement condition humidity sensor
	*
	* */

	switch (mode_output_value_humidity_sensor)
	{


		case 1:
			/*lcd display*/
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[0]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_10 == 1)
			{
				while (HAL_GetTick() - time_wake_up_10 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				out_put_4 =  Lagrange_Interpolation(x_input_humidity_value, y_static_input_humidity_value, MAX_ARR_X_Y_LAGRANGE, humidity);
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_10 ++;
			}
			/*check condition when finished reading data from humidity sensor*/
			if(check_10 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Monitor(&lcd1, out_put_4);
			}
			break;


		case 2:
			/*lcd display*/
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[1]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_10 == 2)
			{
				while (HAL_GetTick() - time_wake_up_10 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				//DHT_Read_Temperature_Humidity(&DHT22_Sensor_1, &temperature, &humidity);
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				out_put_4 =  Lagrange_Interpolation(x_input_humidity_value, y_static_input_humidity_value, MAX_ARR_X_Y_LAGRANGE, humidity);
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_10 ++;
			}
			/*check condition when finished reading data from humidity sensor*/
			if(check_10 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Monitor(&lcd1, out_put_4);
			}
			break;



		case 3:
			/*lcd display */
			Display_Setup_Parameter_Humidity(&lcd1, y_static_input_humidity_value[2]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_10 == 3)
			{
				while (HAL_GetTick() - time_wake_up_10 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				out_put_4 =  Lagrange_Interpolation(x_input_humidity_value, y_static_input_humidity_value, MAX_ARR_X_Y_LAGRANGE, humidity);
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_10 ++;
			}
			/*check condition when finished reading data from humidity sensor*/
			if(check_10 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Monitor(&lcd1, out_put_4);
			}
			break;

		/*Default mode*/
		default:
			/*reassign variable*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			CLCD_I2C_WriteString(&lcd1, "Humidity_Monitor");
			check_10 = 1;
			break;
	}

	    return 0;
}


/**
 *
 */
static uint8_t Output_Value_Temperature_Sensor(void)
{
	static __IO uint8_t mode_output_value_temperature_sensor = 0;
	static __IO uint8_t check_11 = 0;
	uint32_t time_wake_up_11 = HAL_GetTick();
	float out_put_05 = 0;
	/*check button04 set parameter*/
	if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(100);
		/*check button04 set parameter*/
		if(HAL_GPIO_ReadPin(BUTTON_04_SET_GROUP_SENOR_GPIO_Port, BUTTON_04_SET_GROUP_SENOR_Pin) == GPIO_PIN_SET)
		{
			/*Lcd clear*/
			CLCD_I2C_Clear(&lcd1);
			mode_output_value_temperature_sensor++;
			if(mode_output_value_temperature_sensor > 3)
				mode_output_value_temperature_sensor = 0;
		}
	}

   /*
	*setting measurement condition temperature sensor
	*
	* */

	switch (mode_output_value_temperature_sensor)
	{


		case 1:
			/*lcd display*/
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[0]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_11 == 1)
			{
				while (HAL_GetTick() - time_wake_up_11 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
//				DHT_Read_Temperature_Humidity(&DHT22_Sensor_1, &temperature, &humidity);
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				out_put_05 = Lagrange_Interpolation(x_input_temperature_value, y_static_input_temperature_value, MAX_ARR_X_Y_LAGRANGE, temperature);
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_11 ++;
			}
			/*check condition when finished reading data from temperature sensor*/
			if(check_11 == 2)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Monitor(&lcd1, out_put_05 );
			}
			break;


		case 2:
			/*lcd display*/
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[1]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_11 == 2)
			{
				while (HAL_GetTick() - time_wake_up_11 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				out_put_05 = Lagrange_Interpolation(x_input_temperature_value, y_static_input_temperature_value, MAX_ARR_X_Y_LAGRANGE, temperature);
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_11 ++;
			}
			/*check condition when finished reading data from temperature sensor*/
			if(check_11 == 3)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Monitor(&lcd1, out_put_05);
			}
			break;


		case 3:
			/*lcd display */
			Display_Setup_Parameter_Temperature(&lcd1, y_static_input_temperature_value[2]);
			/*check condition for execution the data reading from humidity sensor*/
			if(check_11 == 3)
			{
				while (HAL_GetTick() - time_wake_up_11 <= TIME_WAITTING_START_CALIBRATION)
				{
					/*wake up pump*/
					Send_Data_74HC595(0xAF);
				}
				/*Turn off pump*/
				Send_Data_74HC595(0xFF);
				/*input value*/
				DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);
				out_put_05 = Lagrange_Interpolation(x_input_temperature_value, y_static_input_temperature_value, MAX_ARR_X_Y_LAGRANGE, temperature);
				/*Tonggle buzz after having read data from humidity sensor*/
				for(uint8_t i =0; i < 5; i++)
				{
					HAL_GPIO_TogglePin(Buzz_GPIO_Port, Buzz_Pin);
					HAL_Delay(1000);
				}
				/*increase variable by 1 unit*/
				check_11++;
			}
			/*check condition when finished reading data from temperature sensor*/
			if(check_11 == 4)
			{
				/*Buzz off*/
				HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
				/*lcd display*/
				Display_Monitor(&lcd1,out_put_05);
			}
			break;

		/*Default mode*/
		default:

			/*reassign variable check_06 = 1*/
			CLCD_I2C_SetCursor(&lcd1, 0, 0);
			CLCD_I2C_WriteString(&lcd1, "Temp_Monitor");
			check_11 = 1;
			break;
	}

	    return 0;
}


/**
 * Hight level funtion calibaration group sensor
 */


/**
 * @brief Lagrange_Interpolation
 * 
 * @param x 
 * @param y 
 * @param lenght 
 * @param find_value 
 * @return float 
 */
float Lagrange_Interpolation(float *x, float *y, uint8_t lenght ,float find_value)
{
	float s = 1, t = 1 , k = 0;
	for(uint8_t i =0; i< lenght; i++)
	{
		s = 1;
		t = 1;
		for(uint8_t j =0; j < lenght ; j++)
		{
			if(j!=i)
			{
				s = s*(find_value - *(x+j));
				t = t *(*(x + i) - *(x +j));
			}
		}
		k = k +((s/t) * (*(y+i)));
	}
	return k;
}


/** Read_Data_Parameter_Group_Sensor
 *
 */
void Int_Read_Data_Parameter_Group_Sensor_To_Flash_MCU(void)
{
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PM2_5_SENSOR, x_input_pm2_5_value, sizeof(x_input_pm2_5_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_SUM_PM_SENSOR, x_input_sum_pm_value, sizeof(x_input_sum_pm_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_CO2_SENSOR, x_input_co2_value, sizeof(x_input_co2_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_SO2_PM_VALUE, x_input_so2_pm_value, sizeof(x_input_so2_pm_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_TEMPERATURE, x_input_temperature_value, sizeof(x_input_temperature_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_HUMIDITY, x_input_humidity_value, sizeof(x_input_humidity_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_PM2_5, y_static_input_pm2_5_value,  sizeof(y_static_input_pm2_5_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_SUM_PM, y_static_input_sum_pm_value,  sizeof(y_static_input_sum_pm_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_CO2, y_static_input_co2_value,  sizeof(y_static_input_co2_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_SO2, y_static_input_so2_value,  sizeof(y_static_input_so2_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_TEMPERATURE, y_static_input_temperature_value,  sizeof(y_static_input_temperature_value)/sizeof(float));
	/*read Parameter data type float*/
	Read_Value_Float_Flash(START_BASE_ADDRESS_PARAMETER_HUMIDITY, y_static_input_humidity_value,  sizeof(y_static_input_humidity_value)/sizeof(float));
}


/**
 * Init_Sensor
*/
void Init_Sensor(void)
{
	/*
		{0, Init_Hpma115S0_Dust_Sensor},
		{1, Init_Mh_Z19B_Co2_Sensor},
		{2, Init_DHT22},
		{3, Init_So2_Sensor},
		{4, Init_BMP18_Air_Pressure},
		{5, Init_Sharp_G2y10_Sum_Dust_Sensor},
		{6, Init_Lm335A_Temperature_Sensor},
		{7, Int_Read_Data_Parameter_Group_Sensor_To_Flash_MCU}
	*/
	for(uint8_t i =0; i<sizeof(gSensor_Init_System)/sizeof(gSensor); i++)
	{
		gSensor_Init_System[i].gSensor.gInit_Sensor();
	}

}

/**
 * @brief Run_Normal
*/
void Run_Normal(void)
{
	static __IO float pm2_5, sum_pm, co2, so2, batery_voltage, vdc_input, solar_voltage;
	uint32_t Wake_Up_Send_Data_Lora = HAL_GetTick();
	batery_voltage = vdc_input = solar_voltage = 12000; /*Uinit: mV*/
	pm2_5 = sum_pm = co2 = so2 = 0;
	/*run nomarl */
	/* Lcd setup cursor */
	CLCD_I2C_SetCursor(&lcd1, 0, 0);
	/* Lcd send string*/
	CLCD_I2C_WriteString(&lcd1, "Run Normal");
	/* Lcd setup cursor */
	CLCD_I2C_SetCursor(&lcd1, 0, 3);
	/* Lcd send string*/
	CLCD_I2C_WriteString(&lcd1, "Tab_0");
	/*read value pm2_5 sensor*/
	//pm2_5 =  Hpma115S0_Caclulator_Average(&hpma115s0_sensor_01, 10);
	/*read value sum_pm sensor*/
//	if(flag_system.check_start_mesurment_sensor == 1)
//	{
		sum_pm  =  Sharp_G2y10_Dust_Sensor_Measuring_Average(&sharpg2y_sensor01, 10);
		/*read value co2 sensor*/
		co2 = Mh_Z19B_Co2_Sensor_Caclulator_Average(&mh_z19b_sensor_01, 10);
		/*read value so2 sensor*/
		so2 = hx711_so2_result(&so2_sensor, 10);
		/*read value temp, humi*/
		DHT_Read_Temperature_Humidity_Average(&DHT22_Sensor_1, &temperature,  &humidity, 10);

		if(HAL_GetTick() - Wake_Up_Send_Data_Lora >= 200)
		{
			Wake_Up_Send_Data_Lora = HAL_GetTick();
			Lora_Uart_Master_Send_Data_To_Salve(&moudle_lora_01, temperature, (uint16_t)humidity, (uint16_t)co2, (uint16_t)so2, (uint16_t)sum_pm, (uint16_t)pm2_5, (uint16_t)batery_voltage, (uint16_t)vdc_input, (uint16_t)solar_voltage);
		}
//		flag_system.check_start_mesurment_sensor = 0;
//	}
	//Lora_Uart_Master_Send_Data_To_Salve(&moudle_lora_01, temperature, (uint16_t)humidity, (uint16_t)co2, (uint16_t)so2, (uint16_t)sum_pm, (uint16_t)pm2_5, (uint16_t)batery_voltage, (uint16_t)vdc_input, (uint16_t)solar_voltage);

}


/**
 * @brief Funtion_Routine_Hightlevel
 * 
 */
void Funtion_Routine_Hightlevel(void)
{
	if(flag_system.flag_01==0)
	{
		Selec_Option_Sensor_Name();
	}
	Save_Parameter_Sensor();
}

