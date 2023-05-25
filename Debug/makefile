################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include So2_Hx711/subdir.mk
-include Sharp_G2Y10_Dust_Sensor/subdir.mk
-include Setup_Calibration_Sensor/subdir.mk
-include Protocol_Lora/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Machine_Routine/subdir.mk
-include MHZ19B_Co2_Sensor/subdir.mk
-include LM335A_Sensor/subdir.mk
-include I2C_LCD/subdir.mk
-include HPMA115S_Dust_Sensor/subdir.mk
-include Flash_System/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Driver_HC595/subdir.mk
-include Display_Prameter/subdir.mk
-include Delay_Timer/subdir.mk
-include Debug_Program/subdir.mk
-include DHTxx_Humidity_Sensor/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include BMP180_Air_Pressure_Sensor/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Quan_Trac_Moi_Truong_MK
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Quan_Trac_Moi_Truong_MK.elf \

MAP_FILES += \
Quan_Trac_Moi_Truong_MK.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Quan_Trac_Moi_Truong_MK.list \


# All Target
all: main-build

# Main-build Target
main-build: Quan_Trac_Moi_Truong_MK.elf secondary-outputs

# Tool invocations
Quan_Trac_Moi_Truong_MK.elf Quan_Trac_Moi_Truong_MK.map: $(OBJS) $(USER_OBJS) /media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/STM32F103VBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Quan_Trac_Moi_Truong_MK.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/media/son/Data/LoH_Tech/Firmware/Quan_Trac_Moi_Truong_MK/STM32F103VBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Quan_Trac_Moi_Truong_MK.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Quan_Trac_Moi_Truong_MK.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Quan_Trac_Moi_Truong_MK.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Quan_Trac_Moi_Truong_MK.elf Quan_Trac_Moi_Truong_MK.list Quan_Trac_Moi_Truong_MK.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
