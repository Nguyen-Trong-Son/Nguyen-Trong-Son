/**
 * @file Machine_Routine.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "stm32f1xx_hal.h"
#include "main.h"
#include "Machine_Routine.h"
#include "stdint.h"
#include "Transmit_Data_Lora.h"
#include "CLCD_I2C.h"
#include "stdio.h"
#include "Debug_Program.h"
#include "Setup_Calibration_Sensor.h"

#define TIME_WAKE_UP_SENSOR     180000

#if USE_RTOS_MACHINE_SYSTEM
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#define STACK_SIZE_TASK01_ROUTINE_SYSTEM         512
#define STACK_SIZE_TASK02_STATUS_MACHINE         64

/**
 * @brief Prority task
 *
 */
#define PRORITY_TASK01_ROUTINE_SYSTEM     3
#define PRORITY_TASK02_STATUS_MACHINE     2

/**
 * @brief Name task
 *
 */
#define NAME_TASK01_ROUTINE_SYSTEM          "task01_routine_system"
#define NAME_TASK02_STATUS_MACHINE          "task02_status_machine"

/**
 * @brief Status Connect to the Sensor
 *
 */
#define CONNECTED                       "CONNECTED SUSSESFULL\r\n"
#define UNCONNECTED_DUST_SENSOR         "UNCONNECTED_DUST_SENSOR\r\n"
#define UNCONNECTED_CO2_SENSOR           "UNCONNECTED_CO2_SENSOR\r\n"
#define NO_RESULT                       "NO_RESULT\r\n"
#define RESULT                          "RESULT\r\n"
#define DATA_MASTER_TRASMIT             "MASTER TRASMIT DATA OK\n"
#define MCU_RESET                       "RESET MCU...\n\n"

static TaskHandle_t my_task01_routine_system;
static TaskHandle_t my_task02_status_machine;
static SemaphoreHandle_t countingsem = 0;

static uint8_t Routine01_Task_01_Routine_System(void);
static uint8_t Routine02_Task_02_Status_Machine(void);


static void Task01_Routine_System(void *parameter);

static void Task02_Status_Machine(void *parameter);

#endif

#define ADDRESS_SLAVE 0x1A

extern hi2c2;
extern htim3;
extern huart3;
extern hadc1;


Debug_Program_Name                  pgm_1;
Frame_Transmit_Data                 moudle_lora_01;
CLCD_I2C_Name                       lcd1;


static void Init_Debug_Program(void);

static void Init_LCD_Display(void);
static void Init_Transimir_Lora_Mode_Uart(void);
static void Init_HC595(void);

#if USE_RTOS_MACHINE_SYSTEM
uint16_t test =0;

/**
 * @brief Application StackOver Flow Hook
 *
 * @param xTask
 * @param pcTaskName
 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   __disable_irq();
  while(1)
  {
	HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_SET);
	Transmit_Data_To_Computer(&pgm_1, (uint8_t*)"memory overflow applications\r\n", strlen("memory overflow applications\r\n"));
	vTaskDelay(100);
	HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
	vTaskDelay(100);
  }
}

/**
 * @brief Application Malloc Failed Hook
 *
 */
void vApplicationMallocFailedHook(void)
{
	/* Force an assert. */
  // configASSERT( ( volatile void * ) NULL );
  __disable_irq();
  while (1)
  {
    HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_SET);
    Transmit_Data_To_Computer(&pgm_1, (uint8_t*)("lack of memory allocation for applications\r\n"), strlen("lack of memory allocation for applications\r\n"));
	vTaskDelay(1000);
	HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
	vTaskDelay(1000);
  }
}

#endif


/**
 * @brief Init_Debug_Program
 * 
 */
static void Init_Debug_Program(void)
{
	  Debug_Program_Config(&pgm_1, &huart3, Led_MCH_GPIO_Port, Led_MCH_Pin, 1000);
}


/**
 * @brief Init_LCD_Display
 * 
 */
static void Init_LCD_Display(void)
{
	  CLCD_I2C_Init(&lcd1, &hi2c2, 0x4e, 20, 4);
	  CLCD_I2C_SetCursor(&lcd1, 0, 1);
	  CLCD_I2C_WriteString(&lcd1, "**WELLCOME AQI**");
	  CLCD_I2C_SetCursor(&lcd1, 0, 2);
	  CLCD_I2C_WriteString(&lcd1, "AQI CALIBRATION");
	  HAL_Delay(5000);
	  CLCD_I2C_Clear(&lcd1);
}

#if 0
static void Init_Transimit_Lora_Mode_I2C(void)
{
	 I2C_Lora_Init(&moudle_lora_01, &hi2c1, ADDRESS_SLAVE, 1000);
}
#endif

/**
 * @brief Init_Transimir_Lora_Mode_Uart
 * 
 */
static void Init_Transimir_Lora_Mode_Uart(void)
{
    Uart_Lora_Init(&moudle_lora_01, &huart3, 1000);
}

/**
 * @brief Init_Cmd_Transmit_Lora
 * 
 */
void Init_Cmd_Transmit_Lora(void)
{
	Transmit_Data_To_Computer(&pgm_1, (uint8_t*)"ATZ\r\n", (uint16_t)strlen("ATZ\r\n"));
}

/**
 * @brief Init_HC595
 * 
 */
static void Init_HC595(void)
{
	Send_Data_74HC595(0xFF);
}

/**
 * @brief Init_RTOS_System_Project
 * 
 */
#if USE_RTOS_MACHINE_SYSTEM
void Init_RTOS_System_Project(void)
{
	  /* USER CODE BEGIN RTOS_MUTEX */
	  /* add mutexes, ... */
	  /* USER CODE END RTOS_MUTEX */

	  /* USER CODE BEGIN RTOS_SEMAPHORES */
	  countingsem = xSemaphoreCreateCounting(2, 0);
	  /* USER CODE END RTOS_SEMAPHORES */

	  /* USER CODE BEGIN RTOS_TIMERS */
	  /* start timers, add new ones, ... */
	  /* USER CODE END RTOS_TIMERS */

	  /* USER CODE BEGIN RTOS_QUEUES */
	  /* add queues, ... */
	  /* USER CODE END RTOS_QUEUES */

	  /* Create the thread(s) */
	  /* USER CODE BEGIN RTOS_THREADS */
		xTaskCreate(Task01_Routine_System, NAME_TASK01_ROUTINE_SYSTEM,  STACK_SIZE_TASK01_ROUTINE_SYSTEM, NULL, PRORITY_TASK01_ROUTINE_SYSTEM,   &my_task01_routine_system);
		xTaskCreate(Task02_Status_Machine, NAME_TASK02_STATUS_MACHINE,  STACK_SIZE_TASK02_STATUS_MACHINE, NULL, PRORITY_TASK02_STATUS_MACHINE,   &my_task02_status_machine);
		vTaskStartScheduler();
	  /* USER CODE END RTOS_THREADS */

	  /* Start scheduler */

	  /* We should never get here as control is now taken by the scheduler */
	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
}
#endif
/**
 * @brief Init_System_Funtion_Project
 * 
 */
void Init_System_Funtion_Project(void)
{
	/* Init Program Sensor*/
	Init_Sensor();

	/*Init Program Process Bebug*/
	Init_Debug_Program();

	/*Init driver hc595*/
	Init_HC595();

	/*Init Display LCD*/
	Init_LCD_Display();

	/*Init Transmit data from MCU to Module lora*/
	Init_Transimir_Lora_Mode_Uart();

	/*Init command control module lora*/
	Init_Cmd_Transmit_Lora();

	/*Init timer start*/
	//HAL_TIM_Base_Start_IT(&htim3);
}

/**
 * @brief Routine01_Task_01_Request_Sensor
 * 
 * @return uint8_t 
 */
static uint8_t Routine01_Task_01_Routine_System(void)
{
	  Funtion_Routine_Hightlevel();
      return 0;
}

static uint8_t Routine02_Task_02_Status_Machine(void)
{
    Blink_Led01(&pgm_1);
    HAL_GPIO_TogglePin(LED_SST1_GPIO_Port, LED_SST1_Pin);
    return 0;
}

#if USE_RTOS_MACHINE_SYSTEM
/**
 * @brief Task01_Request_Sensor
 *
 * @param parameter
 */
static void Task01_Routine_System(void *parameter)
{
  uint32_t time_wakeup_sensor = xTaskGetTickCount();
  static __IO uint8_t check_sate_machine = 0;
  while(1)
  {
    // HAL_IWDG_Refresh(&hiwdg);
	xSemaphoreGive(countingsem);
    switch(check_sate_machine)
    {
    	case 0:
    		Init_Cmd_Transmit_Lora();
    		while(xTaskGetTickCount() - time_wakeup_sensor <= TIME_WAKE_UP_SENSOR)
    		{
	 			CLCD_I2C_SetCursor(&lcd1, 0, 0);
	 			CLCD_I2C_WriteString(&lcd1, "Waiting 3m...");
    		}
    		HAL_TIM_Base_Start_IT(&htim3);
    		check_sate_machine = 1;
    		break;
    	case 1:
    		CLCD_I2C_Clear(&lcd1);
    		check_sate_machine ++;
    		break;
    	case 2:
    		Routine01_Task_01_Routine_System();;
    	    check_sate_machine ++;
    	case 3:
    		//Routine02_Task_02_Status_Machine();
    		check_sate_machine = 2;
    	default:
    		break;
    }
    vTaskDelay(1);
  }
}


/**
 * @brief Task03_Status Machine
 *
 * @param parameter
 */
static void Task02_Status_Machine(void *parameter)
{
  while(1)
  {
	xSemaphoreTake(countingsem, portMAX_DELAY);
//    Routine02_Task_02_Status_Machine();
    vTaskDelay(1);
  }
}
#endif

/**
 * @brief Routine_Machine_NotUseRTOS
 * 
 * @return uint8_t 
 */
uint8_t Routine_Machine_NotUseRTOS(void)
{
    uint32_t tick_wake_up_sensor = HAL_GetTick();
    static __IO uint8_t check_sate_machine = 0;
    switch(check_sate_machine)
	{
		case 0:
			Init_Cmd_Transmit_Lora();
			while(HAL_GetTick() - tick_wake_up_sensor <= TIME_WAKE_UP_SENSOR)
			{
				CLCD_I2C_SetCursor(&lcd1, 0, 0);
				CLCD_I2C_WriteString(&lcd1, "Waitting 4m...");
			}
			HAL_TIM_Base_Start_IT(&htim3);
			check_sate_machine = 1;
			break;
		case 1:
			CLCD_I2C_Clear(&lcd1);
			check_sate_machine = 2;
			break;
		case 2:
			Routine01_Task_01_Routine_System();
		case 3:
			//Routine02_Task_02_Status_Machine();
			check_sate_machine = 2;
		default:
			break;
	}
    return 0;
}



