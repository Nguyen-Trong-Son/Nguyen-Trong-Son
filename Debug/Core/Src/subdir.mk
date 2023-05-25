################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_hal_timebase_tim.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_hal_timebase_tim.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_hal_timebase_tim.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/BMP180_Air_Pressure_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Debug_Program" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Delay_Timer" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/DHTxx_Humidity_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Display_Prameter" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Driver_HC595" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/HPMA115S_Dust_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/I2C_LCD" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/LM335A_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/MHZ19B_Co2_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Protocol_Lora" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Sharp_G2Y10_Dust_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/So2_Hx711" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Machine_Routine" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Flash_System" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Setup_Calibration_Sensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_hal_timebase_tim.d ./Core/Src/stm32f1xx_hal_timebase_tim.o ./Core/Src/stm32f1xx_hal_timebase_tim.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

