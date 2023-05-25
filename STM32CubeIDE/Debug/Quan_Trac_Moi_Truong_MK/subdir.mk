################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Quan_Trac_Moi_Truong_MK/startup_stm32f103xb.s 

OBJS += \
./Quan_Trac_Moi_Truong_MK/startup_stm32f103xb.o 

S_DEPS += \
./Quan_Trac_Moi_Truong_MK/startup_stm32f103xb.d 


# Each subdirectory must supply rules for building sources it contributes
Quan_Trac_Moi_Truong_MK/%.o: ../Quan_Trac_Moi_Truong_MK/%.s Quan_Trac_Moi_Truong_MK/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Quan_Trac_Moi_Truong_MK

clean-Quan_Trac_Moi_Truong_MK:
	-$(RM) ./Quan_Trac_Moi_Truong_MK/startup_stm32f103xb.d ./Quan_Trac_Moi_Truong_MK/startup_stm32f103xb.o

.PHONY: clean-Quan_Trac_Moi_Truong_MK

