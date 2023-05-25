################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/list.c \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/croutine.o \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/list.o \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/queue.o \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.o \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/tasks.o \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/timers.o 

C_DEPS += \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/croutine.d \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/list.d \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/queue.d \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.d \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/tasks.d \
./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/%.o Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/%.su: ../Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/%.c Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Quan_Trac_Moi_Truong_MK-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source

clean-Quan_Trac_Moi_Truong_MK-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/croutine.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/croutine.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/croutine.su ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/event_groups.su ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/list.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/list.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/list.su ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/queue.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/queue.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/queue.su ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.su ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/tasks.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/tasks.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/tasks.su ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/timers.d ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/timers.o ./Quan_Trac_Moi_Truong_MK/Middlewares/Third_Party/FreeRTOS/Source/timers.su

.PHONY: clean-Quan_Trac_Moi_Truong_MK-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source

