################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/startup_stm32f103vbtx.s 

OBJS += \
./Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/startup_stm32f103vbtx.o 

S_DEPS += \
./Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/startup_stm32f103vbtx.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/%.o: ../Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/%.s Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Quan_Trac_Moi_Truong_MK-2f-STM32CubeIDE-2f-Application-2f-User-2f-Startup

clean-Quan_Trac_Moi_Truong_MK-2f-STM32CubeIDE-2f-Application-2f-User-2f-Startup:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/startup_stm32f103vbtx.d ./Quan_Trac_Moi_Truong_MK/STM32CubeIDE/Application/User/Startup/startup_stm32f103vbtx.o

.PHONY: clean-Quan_Trac_Moi_Truong_MK-2f-STM32CubeIDE-2f-Application-2f-User-2f-Startup

