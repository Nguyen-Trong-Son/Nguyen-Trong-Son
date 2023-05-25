################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Quan_Trac_Moi_Truong_MK/Driver_HC595/Driver_74HC595.c 

OBJS += \
./Quan_Trac_Moi_Truong_MK/Driver_HC595/Driver_74HC595.o 

C_DEPS += \
./Quan_Trac_Moi_Truong_MK/Driver_HC595/Driver_74HC595.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/Driver_HC595/%.o Quan_Trac_Moi_Truong_MK/Driver_HC595/%.su: ../Quan_Trac_Moi_Truong_MK/Driver_HC595/%.c Quan_Trac_Moi_Truong_MK/Driver_HC595/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Quan_Trac_Moi_Truong_MK-2f-Driver_HC595

clean-Quan_Trac_Moi_Truong_MK-2f-Driver_HC595:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/Driver_HC595/Driver_74HC595.d ./Quan_Trac_Moi_Truong_MK/Driver_HC595/Driver_74HC595.o ./Quan_Trac_Moi_Truong_MK/Driver_HC595/Driver_74HC595.su

.PHONY: clean-Quan_Trac_Moi_Truong_MK-2f-Driver_HC595

