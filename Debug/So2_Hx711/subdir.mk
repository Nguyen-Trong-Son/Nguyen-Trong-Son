################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../So2_Hx711/So2_Sensor_Hx711.c 

OBJS += \
./So2_Hx711/So2_Sensor_Hx711.o 

C_DEPS += \
./So2_Hx711/So2_Sensor_Hx711.d 


# Each subdirectory must supply rules for building sources it contributes
So2_Hx711/%.o So2_Hx711/%.su: ../So2_Hx711/%.c So2_Hx711/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/BMP180_Air_Pressure_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Debug_Program" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Delay_Timer" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/DHTxx_Humidity_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Display_Prameter" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Driver_HC595" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/HPMA115S_Dust_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/I2C_LCD" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/LM335A_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/MHZ19B_Co2_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Protocol_Lora" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Sharp_G2Y10_Dust_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/So2_Hx711" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Machine_Routine" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Flash_System" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Setup_Calibration_Sensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-So2_Hx711

clean-So2_Hx711:
	-$(RM) ./So2_Hx711/So2_Sensor_Hx711.d ./So2_Hx711/So2_Sensor_Hx711.o ./So2_Hx711/So2_Sensor_Hx711.su

.PHONY: clean-So2_Hx711

