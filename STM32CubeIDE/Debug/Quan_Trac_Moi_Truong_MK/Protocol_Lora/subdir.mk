################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Quan_Trac_Moi_Truong_MK/Protocol_Lora/Transmit_Data_Lora.c 

OBJS += \
./Quan_Trac_Moi_Truong_MK/Protocol_Lora/Transmit_Data_Lora.o 

C_DEPS += \
./Quan_Trac_Moi_Truong_MK/Protocol_Lora/Transmit_Data_Lora.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/Protocol_Lora/%.o Quan_Trac_Moi_Truong_MK/Protocol_Lora/%.su: ../Quan_Trac_Moi_Truong_MK/Protocol_Lora/%.c Quan_Trac_Moi_Truong_MK/Protocol_Lora/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Quan_Trac_Moi_Truong_MK-2f-Protocol_Lora

clean-Quan_Trac_Moi_Truong_MK-2f-Protocol_Lora:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/Protocol_Lora/Transmit_Data_Lora.d ./Quan_Trac_Moi_Truong_MK/Protocol_Lora/Transmit_Data_Lora.o ./Quan_Trac_Moi_Truong_MK/Protocol_Lora/Transmit_Data_Lora.su

.PHONY: clean-Quan_Trac_Moi_Truong_MK-2f-Protocol_Lora

