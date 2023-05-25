################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Quan_Trac_Moi_Truong_MK/Core/Src/freertos.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/main.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_msp.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_timebase_tim.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_it.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/syscalls.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/sysmem.c \
../Quan_Trac_Moi_Truong_MK/Core/Src/system_stm32f1xx.c 

OBJS += \
./Quan_Trac_Moi_Truong_MK/Core/Src/freertos.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/main.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_msp.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_timebase_tim.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_it.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/syscalls.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/sysmem.o \
./Quan_Trac_Moi_Truong_MK/Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Quan_Trac_Moi_Truong_MK/Core/Src/freertos.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/main.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_msp.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_timebase_tim.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_it.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/syscalls.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/sysmem.d \
./Quan_Trac_Moi_Truong_MK/Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/Core/Src/%.o Quan_Trac_Moi_Truong_MK/Core/Src/%.su: ../Quan_Trac_Moi_Truong_MK/Core/Src/%.c Quan_Trac_Moi_Truong_MK/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Quan_Trac_Moi_Truong_MK-2f-Core-2f-Src

clean-Quan_Trac_Moi_Truong_MK-2f-Core-2f-Src:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/Core/Src/freertos.d ./Quan_Trac_Moi_Truong_MK/Core/Src/freertos.o ./Quan_Trac_Moi_Truong_MK/Core/Src/freertos.su ./Quan_Trac_Moi_Truong_MK/Core/Src/main.d ./Quan_Trac_Moi_Truong_MK/Core/Src/main.o ./Quan_Trac_Moi_Truong_MK/Core/Src/main.su ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_msp.d ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_msp.o ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_msp.su ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_timebase_tim.d ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_timebase_tim.o ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_hal_timebase_tim.su ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_it.d ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_it.o ./Quan_Trac_Moi_Truong_MK/Core/Src/stm32f1xx_it.su ./Quan_Trac_Moi_Truong_MK/Core/Src/syscalls.d ./Quan_Trac_Moi_Truong_MK/Core/Src/syscalls.o ./Quan_Trac_Moi_Truong_MK/Core/Src/syscalls.su ./Quan_Trac_Moi_Truong_MK/Core/Src/sysmem.d ./Quan_Trac_Moi_Truong_MK/Core/Src/sysmem.o ./Quan_Trac_Moi_Truong_MK/Core/Src/sysmem.su ./Quan_Trac_Moi_Truong_MK/Core/Src/system_stm32f1xx.d ./Quan_Trac_Moi_Truong_MK/Core/Src/system_stm32f1xx.o ./Quan_Trac_Moi_Truong_MK/Core/Src/system_stm32f1xx.su

.PHONY: clean-Quan_Trac_Moi_Truong_MK-2f-Core-2f-Src

