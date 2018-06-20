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
STM32_DRIVER_SRC_DIR = chip_platform/stm_driver/src
# Application source path
APP_SRC_DIR = application/src
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

# Thirdparty lib
C_SOURCES +=		$(BOARD_UTILS_SRC)/tinyprintf/tinyprintf.c			\
					$(BOARD_UTILS_SRC)/nucleo_io/nucleo_io.c

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
					
# C Application source
C_SOURCES += \
					$(APP_SRC_DIR)/syscalls.c					\
					$(APP_SRC_DIR)/system_stm32f4xx.c			\
					$(APP_SRC_DIR)/timer_tick.c					\
					$(APP_SRC_DIR)/serial_debug.c				\
					$(APP_SRC_DIR)/main.c

# ASM source
ASM_SOURCES = chip_platform/startup/startup_stm32f411xe.s

###############################################################################
# firmware library
###############################################################################
PERIFLIB_SOURCES = 


###############################################################################
# binaries
###############################################################################
BINPATH = 
TOOLCHAIN_PATH = /Applications/gcc-arm-none-eabi-5_4-2016q3/bin
PREFIX = $(TOOLCHAIN_PATH)/arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
###############################################################################
# CFLAGS
###############################################################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
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
				-Iapplication/inc									\
				-Ichip_platform/inc							\
				-Ichip_platform/cmsis/core					\
				-Ichip_platform/cmsis/device				\
				-Ichip_platform/stm_driver/inc				\
				-Iboard_utilities							\
				-Iboard_utilities/tinyprintf				\
				-Iboard_utilities/nucleo_io					\
				-Iboard_utilities/FreeRTOS/include			\
				-Iboard_utilities/FreeRTOS/portable/GCC/ARM_CM4F


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"


###############################################################################
# LDFLAGS
###############################################################################
# link script
LDSCRIPT = chip_platform/LinkerScript.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


###############################################################################
# build the applicationlication
###############################################################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo "[GCC]: $< --> $(BUILD_DIR)/$@"
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "[ASM]: $< --> $(BUILD_DIR)/$@"
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo "[GCC]: $^ --> $(BUILD_DIR)/$@"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) -A $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "Generate HEX file: $@"
	@$(HEX) $< $@
	
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
