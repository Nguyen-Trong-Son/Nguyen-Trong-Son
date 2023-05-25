######################################
# Makefile by Nguyen Trong Son LOH Co...LTD
# Makefile (based gcc and g++)
# The user must edit libray freeRTOS the message when using g++
# Runs on both windows or linux platforms
# when using on the operating system, you have to edit the path GCC_PATH
# Use Openocd to load the code and debug program
######################################

######################################
# Config Blank 
######################################
DBANK = 1

######################################
# Config start address 
######################################
ifeq ($(DBANK), 1)
#	Default
	START_ADDRESS_BLANK_1  = 0x08000000
	START_ADDRESS_BLANK_2  = 0x08100000 
endif  

ifeq ($(DBANK), 0)
#	Default
	START_ADDRESS_BLANK_1  = 0x08000000
endif  


######################################
# Config Flashing use Openocd
######################################
OPENOCD_CMD             = openocd
OPENOCD_TARGET          = stm32f1x.cfg
OPENOCD_INTERFACE       = stlink.cfg
HEX_FILE_PATH           = $(BUILD_DIR)/$(TARGET).hex
BIN_FILE_PATH           = $(BUILD_DIR)/$(TARGET).bin
OPENOCD_INTERFACE_PATH 	= /usr/share/openocd/scripts/interface/$(OPENOCD_INTERFACE)
OPENCD_TARGET_PATH   	= /usr/share/openocd/scripts/target/$(OPENOCD_TARGET)


######################################
# Flashing File.Hex use Openocd
######################################
FLASHING_MODE_HEXFILE 		= $(OPENOCD_CMD) -f $(OPENOCD_INTERFACE_PATH) -f $(OPENCD_TARGET_PATH) -c "init" -c "reset halt" -c "flash write_image erase $(HEX_FILE_PATH)" -c "reset" -c "shutdown" 

######################################
# Flashing File.bin use Openocd
######################################
FLASHING_MODE_BINFILE 	    = $(OPENOCD_CMD) -f $(OPENOCD_INTERFACE_PATH) -f $(OPENCD_TARGET_PATH) -c "init" -c "reset halt" -c "flash write_image erase $(BIN_FILE_PATH) $(START_ADDRESS_BLANK_1)" -c "reset" -c "shutdown"

######################################
# Debugging use Openocd
######################################
ELF_FILE_PATH            = ./$(BUILD_DIR)/$(TARGET).elf
OPENOCD_CONFIG_DEBUGGING = $(OPENOCD_CMD) -f $(OPENOCD_INTERFACE_PATH) -f $(OPENCD_TARGET_PATH)
GDB_RUNNING              = gdb-multiarch $(ELF_FILE_PATH)


######################################
# Tittle
######################################
FLAG_CLEAN_FILE 		        = CLEAN SUCCESS!
FLAG_BUILD_FILE 		        = BUILD SUCCESS!
FLAG_CREATE_OBJ_FILE 			= Creating object File...
FLAG_CREATE_ELF_FILE			= Creating elf File...
FLAG_CREATE_HEX_FILE 			= Creating hex File...
FLAG_CREATE_BIN_FILE 			= Creating bin File...
FALG_BUILD_SUCSSEFULL           = "(.)---(.)"...CHUC MUNG BRO DA BUILD THANH CONG PROJECT!BRO DEP TRAI VCL..."(.)---(.)"


######################################
# target
######################################
TARGET = Quan_Trac_Moi_Truong_MK


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/stm32f1xx_it.c \
Core/Src/stm32f1xx_hal_msp.c \
Debug_Program/Debug_Program.c \
HPMA115S_Dust_Sensor/Hpma115S0_Dust_Sensor.c \
MHZ19B_Co2_Sensor/Mh_Z19B_Co2_Sensor.c \
Sharp_G2Y10_Dust_Sensor/Sharp_G2y10_Dust_Sensor.c \
BMP180_Air_Pressure_Sensor/BMP180_Air_Pressure_Sensor.c \
Delay_Timer/Delay_Timer.c \
Driver_HC595/Driver_74HC595.c \
DHTxx_Humidity_Sensor/DHTxx_Humidity_Sensor.c \
Protocol_Lora/Transmit_Data_Lora.c \
So2_Hx711/So2_Sensor_Hx711.c \
LM335A_Sensor/LM335A_Sensor.c \
I2C_LCD/CLCD_I2C.c \
Display_Prameter/Display_LCD_Parameter.c \
Flash_System/flash.c \
Setup_Calibration_Sensor/Setup_Calibration_Sensor.c\
Machine_Routine/Machine_Routine.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
Core/Src/system_stm32f1xx.c \
Core/Src/stm32f1xx_hal_timebase_tim.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c \
Core/Src/freertos.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c \


# ASM sources
ASM_SOURCES =  \
startup_stm32f103xb.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
GCC_PATH = /media/son/Data/Embedded_Systems/Document/Tool/Arm_GNU_Toolchain/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
# either it can be added to the PATH environment variable.

ifdef GCC_PATH
	CPP = $(GCC_PATH)/$(PREFIX)g++
	CC = $(GCC_PATH)/$(PREFIX)gcc
	AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
	CP = $(GCC_PATH)/$(PREFIX)objcopy
	SZ = $(GCC_PATH)/$(PREFIX)size
else
	CC = $(PREFIX)gcc
	AS = $(PREFIX)gcc -x assembler-with-cpp
	CP = $(PREFIX)objcopy
	SZ = $(PREFIX)size
endif

	HEX = $(CP) -O ihex
	BIN = $(CP) -O binary -S

 
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi
FLOAT_ABI = -mfloat-abi=soft

#use funtion printf
PRINTF_FUTION = -u _printf_float

#user funtion scanf
SCANF_FUTION = -u _scanf_float 

# mcu
# MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
MCU = $(CPU) -mthumb $(FPU) $(FLOAT_ABI) $(PRINTF_FUTION)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F103xB


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32F1xx_HAL_Driver/Inc \
-IDrivers/STM32F1xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F1xx/Include \
-IDrivers/CMSIS/Include \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 \
-IDebug_Program \
-IHPMA115S_Dust_Sensor \
-IMHZ19B_Co2_Sensor \
-ISharp_G2Y10_Dust_Sensor \
-IBMP180_Air_Pressure_Sensor \
-IDelay_Timer \
-IDriver_HC595 \
-IDHTxx_Humidity_Sensor \
-IProtocol_Lora \
-ISo2_Hx711 \
-ILM335A_Sensor \
-II2C_LCD \
-IDisplay_Prameter \
-ISetup_Calibration_Sensor \
-IFlash_System \
-IMachine_Routine 

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -std=gnu11

# CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -std=gnu11


ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F103VBTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) --specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo $(FLAG_CREATE_ELF_FILE)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo $(FLAG_CREATE_HEX_FILE)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo $(FLAG_CREATE_BIN_FILE)
	$(BIN) $< $@	
	@echo $(FALG_BUILD_SUCSSEFULL)

$(BUILD_DIR):
	mkdir $@		

#######################################
# GBD Load Flash hex file
#######################################
load_fash_hexfile:
	$(FLASHING_MODE_HEXFILE)

#######################################
# GBD Load Flash bin file
#######################################
load_fash_binfile:
	$(FLASHING_MODE_BINFILE)

#######################################
# GBD Config GDB
#######################################
config_gdb:
	$(OPENOCD_CONFIG_DEBUGGING)

#######################################
# GBD runnning
#######################################
gdb_running:
	$(GDB_RUNNING)

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
