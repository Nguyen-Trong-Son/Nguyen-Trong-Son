################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.su: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/BMP180_Air_Pressure_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Debug_Program" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Delay_Timer" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/DHTxx_Humidity_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Display_Prameter" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Driver_HC595" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/HPMA115S_Dust_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/I2C_LCD" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/LM335A_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/MHZ19B_Co2_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Protocol_Lora" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Sharp_G2Y10_Dust_Sensor" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/So2_Hx711" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Machine_Routine" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Flash_System" -I"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/Setup_Calibration_Sensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

