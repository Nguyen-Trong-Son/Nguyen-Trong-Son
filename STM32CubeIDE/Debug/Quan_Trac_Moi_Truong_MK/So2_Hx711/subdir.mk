################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Quan_Trac_Moi_Truong_MK/So2_Hx711/So2_Sensor_Hx711.c 

OBJS += \
./Quan_Trac_Moi_Truong_MK/So2_Hx711/So2_Sensor_Hx711.o 

C_DEPS += \
./Quan_Trac_Moi_Truong_MK/So2_Hx711/So2_Sensor_Hx711.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/So2_Hx711/%.o Quan_Trac_Moi_Truong_MK/So2_Hx711/%.su: ../Quan_Trac_Moi_Truong_MK/So2_Hx711/%.c Quan_Trac_Moi_Truong_MK/So2_Hx711/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Quan_Trac_Moi_Truong_MK-2f-So2_Hx711

clean-Quan_Trac_Moi_Truong_MK-2f-So2_Hx711:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/So2_Hx711/So2_Sensor_Hx711.d ./Quan_Trac_Moi_Truong_MK/So2_Hx711/So2_Sensor_Hx711.o ./Quan_Trac_Moi_Truong_MK/So2_Hx711/So2_Sensor_Hx711.su

.PHONY: clean-Quan_Trac_Moi_Truong_MK-2f-So2_Hx711

