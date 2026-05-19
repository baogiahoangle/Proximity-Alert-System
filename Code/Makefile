GCC_DIR   :=  C:/Toolchain/Arm_Toolchain
OBJ_COPY  := $(GCC_DIR)/bin/arm-none-eabi-objcopy
CC  	  := $(GCC_DIR)/bin/arm-none-eabi-gcc
OUTPUT_DIR	:= ./Output
LINKER_DIR	:= ./Linker
INC_DIRS 	:= ./App/Inc ./BSP/Inc ./DeviceDrivers/Inc ./HardwareAbstraction ./SystemService/Inc ./RTE/Device/STM32F103C8
INC_FILES   := $(foreach INC_DIR, $(INC_DIRS), $(wildcard $(INC_DIR)/*))
SRC_DIRS	:= ./App/Src ./BSP/Src ./DeviceDrivers/Src ./HardwareAbstraction ./SystemService/Src ./HardwareAbstraction ./RTE/Device/STM32F103C8
SRC_FILES   := $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*.c)) ./stm32_startup.c
OBJ_FILES	:= $(patsubst %.c, %.o, $(notdir $(SRC_FILES)))
OBJ_PATHS	:= $(foreach OBJ_FILE, $(OBJ_FILES), $(OUTPUT_DIR)/$(OBJ_FILE))
INC_DIRS_OPT:= $(foreach INC_DIR, $(INC_DIRS), -I$(INC_DIR))
CHIP 		:= cortex-m3
CCFLAGS		:= -c -mcpu=$(CHIP) -mthumb -std=gnu11 -O0 $(INC_DIRS_OPT)
LDFLAGS		:= -nostdlib -T $(LINKER_DIR)/stm_ls.ld -Wl,-Map=Output/makefile.map

vpath %.c $(SRC_DIRS)

build: makefile.hex

print-%:
	@echo $($(subst print-,,$@))

clean:
	rm -f Output/*

%.o:%.c
	$(CC) $(CCFLAGS) -o $(OUTPUT_DIR)/$@ $<

makefile.elf:$(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(OUTPUT_DIR)/$@ $(OBJ_PATHS)

makefile.hex:makefile.elf
	$(OBJ_COPY) -O ihex $(OUTPUT_DIR)/$^ $(OUTPUT_DIR)/$@