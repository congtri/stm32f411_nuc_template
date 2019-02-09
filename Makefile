# -----------------------------------------------------------------------------
# Generic Makefile (based on gcc)
# -----------------------------------------------------------------------------

###############################################################################
# target
###############################################################################
TARGET = stm32f411re_nucleo


###############################################################################
# building variables
###############################################################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


###############################################################################
# paths
###############################################################################
# STM32 driver source path
STM32_DRIVER_SRC_DIR = mcu_platform/stm_driver/src
# Application source path
APP_SRC_DIR = app/src
# Board utilities source
BOARD_UTILS_SRC = board_utilities

# Output path
BUILD_DIR		= output

##Create Output folder
$(shell mkdir -p ${BUILD_DIR} 2>/dev/null)


###############################################################################
# source
###############################################################################
# C Stm32 driver source files
C_SOURCES +=		$(STM32_DRIVER_SRC_DIR)/misc.c						\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_adc.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_can.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_crc.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_cryp.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_cryp_aes.c		\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_cryp_des.c		\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_cryp_tdes.c		\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dac.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dbgmcu.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dcmi.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dfsdm.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dma.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dma2d.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_dsi.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_exti.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_flash.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_flash_ramfunc.c	\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_gpio.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_hash.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_hash_md5.c		\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_hash_sha1.c		\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_i2c.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_iwdg.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_lptim.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_ltdc.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_pwr.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_rcc.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_rng.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_rtc.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_sai.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_sdio.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_spi.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_syscfg.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_tim.c				\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_usart.c			\
					$(STM32_DRIVER_SRC_DIR)/stm32f4xx_wwdg.c

# FreeRTOS
C_SOURCES +=		$(BOARD_UTILS_SRC)/FreeRTOS/croutine.c				\
					$(BOARD_UTILS_SRC)/FreeRTOS/event_groups.c			\
					$(BOARD_UTILS_SRC)/FreeRTOS/list.c					\
					$(BOARD_UTILS_SRC)/FreeRTOS/queue.c					\
					$(BOARD_UTILS_SRC)/FreeRTOS/stream_buffer.c			\
					$(BOARD_UTILS_SRC)/FreeRTOS/tasks.c					\
					$(BOARD_UTILS_SRC)/FreeRTOS/timers.c				\
					$(BOARD_UTILS_SRC)/FreeRTOS/portable/GCC/ARM_CM4F/port.c	\
					$(BOARD_UTILS_SRC)/FreeRTOS/portable/MemMang/heap_4.c

# Thirdparty lib
C_SOURCES +=		$(BOARD_UTILS_SRC)/tinyprintf/tinyprintf.c			\
					$(BOARD_UTILS_SRC)/nucleo_io/nucleo_io.c			\
					$(BOARD_UTILS_SRC)/diag/trace_impl.c				\
					$(BOARD_UTILS_SRC)/diag/Trace.c

# C Application source
C_SOURCES += 		$(APP_SRC_DIR)/syscalls.c					\
					$(APP_SRC_DIR)/system_stm32f4xx.c			\
					$(APP_SRC_DIR)/timer_tick.c					\
					$(APP_SRC_DIR)/serial_debug.c

CPP_SOURCES = 		$(APP_SRC_DIR)/main.cpp

# ASM source
ASM_SOURCES = mcu_platform/startup/startup_stm32f411xe.s

# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
			-DTRACE						\
			-DUSE_FULL_ASSERT			\
			-DSTM32						\
			-DSTM32F4					\
			-DSTM32F411RETx				\
			-DNUCLEO_F411RE				\
			-DDEBUG						\
			-DSTM32F411xE				\
			-DUSE_STDPERIPH_DRIVER


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
				-I"app/inc"											\
				-I"mcu_platform/inc"								\
				-I"mcu_platform/cmsis/core"							\
				-I"mcu_platform/cmsis/device"						\
				-I"mcu_platform/stm_driver/inc"						\
				-I"board_utilities/tinyprintf"						\
				-I"board_utilities/diag"							\
				-I"board_utilities/nucleo_io"						\
				-I"board_utilities/FreeRTOS/include"				\
				-I"board_utilities/FreeRTOS/portable/GCC/ARM_CM4F"
###############################################################################
# firmware library
###############################################################################
PERIFLIB_SOURCES = 


###############################################################################
# binaries
###############################################################################
BINPATH = 
TOOLCHAIN_PATH		= /Applications/gcc-arm-none-eabi/bin
PREFIX				= $(TOOLCHAIN_PATH)/arm-none-eabi-
CC					= $(PREFIX)gcc
CPP					= $(PREFIX)g++
AS					= $(PREFIX)gcc -x assembler-with-cpp
CP					= $(PREFIX)objcopy
AR					= $(PREFIX)ar
SZ					= $(PREFIX)size
HEX					= $(CP) -O ihex
BIN					= $(CP) -O binary -S
 
###############################################################################
# CFLAGS
###############################################################################
# cpu
CPU = -mcpu=cortex-m4

# instruction
INSTRUCTION = -mthumb

# fpu
FLOAT_ABI = -mfloat-abi=hard

# mcu flag
MCU = $(CPU) $(INSTRUCTION) $(FLOAT_ABI)

# compiler options
OPTIMIZE = -Og
WARNING  = -Wall
CPP_STD  = -std=gnu++11
DEPENDENCY_INFO = -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"

# c/c++ cross compiler flags
CC_FLAGS  = $(MCU) -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants
CC_FLAGS += $(OPTIMIZE) $(WARNING)
CC_FLAGS += $(C_DEFS) $(C_INCLUDES)

# Generate dependency information
CC_FLAGS += $(DEPENDENCY_INFO)

# asm flags
AS_FLAGS  = $(MCU) -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants
AS_FLAGS += $(OPTIMIZE) $(WARNING)
AS_FLAGS += $(AS_DEFS) $(AS_INCLUDES)

#ifeq ($(DEBUG), 1)
#CFLAGS += -g -gdwarf-2
#endif

###############################################################################
# LDFLAGS
###############################################################################
# link script
LDSCRIPT = mcu_platform/LinkerScript.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LD_FLAGS  = -g3 -Xlinker --gc-sections -T"$(LDSCRIPT)" $(LIBS) -Wl,-Map="$(BUILD_DIR)/$(TARGET).map" --specs=nano.specs

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


###############################################################################
# build the application
###############################################################################
# list of C objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of C++ objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))


#-------------------------------------------------------
# Generate Objiect files from C++ files
#-------------------------------------------------------
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo "[G++]: $< --> $@"
	@$(CPP) $(CC_FLAGS) -g3 -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics \
			-Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) -c -o "$@" "$<"

#-------------------------------------------------------
# Generate Objiect files from C files
#-------------------------------------------------------
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo "[GCC]: $< --> $@"
	@$(CC) $(CC_FLAGS) -g3 -std=gnu11 -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) -c -o "$@" "$<"
	

#-------------------------------------------------------
# Generate Objiect files from ASM files
#-------------------------------------------------------
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "[ASM]: $< --> $@"
	@$(AS) -c $(AS_FLAGS) $< -o $@

#-------------------------------------------------------
# Generate ELF files from object files
#-------------------------------------------------------
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) | Makefile
	@echo "Generate ELF file: $@"
	@$(CPP) $(CC_FLAGS) $(LD_FLAGS) -o $@ $(OBJECTS)
	@$(SZ) -A $@

#-------------------------------------------------------
# Generate HEX files from ELF files
#-------------------------------------------------------
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "Generate HEX file: $@"
	@$(HEX) $< $@

#-------------------------------------------------------
# Generate BIN files from ELF files
#-------------------------------------------------------
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "Generate BIN file: $@"
	@$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

###############################################################################
# clean up
###############################################################################
clean:
	-rm -fR $(BUILD_DIR)

# *** EOF ***
