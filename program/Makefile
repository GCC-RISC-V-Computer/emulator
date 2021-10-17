# DEMO Makefile RISC-V
# wykys 2019

######################################
# project variables
######################################
# target name
TARGET = APP
# optimalization
OPT = -O0
# build dir
BUILD_DIR = build
# includes
INC = -IApp/inc -ILib/inc

######################################
# source
######################################
# C sources
C_SOURCES = $(wildcard App/src/*.c)
C_SOURCES += $(wildcard Lib/src/*.c)
# ASM sources
ASM_SOURCES = $(wildcard App/src/*.S)


#######################################
# toolchain
#######################################
TOOLCHAIN_PATH = ~/.local/xPacks/@xpack-dev-tools/riscv-none-embed-gcc/10.1.0-1.1.1/.content


BINPATH = $(TOOLCHAIN_PATH)/bin/
PREFIX = riscv-none-embed-
CC = $(BINPATH)$(PREFIX)gcc -fdiagnostics-color=always
AS = $(BINPATH)$(PREFIX)gcc -fdiagnostics-color=always -x assembler-with-cpp
CP = $(BINPATH)$(PREFIX)objcopy
DP = $(BINPATH)$(PREFIX)objdump
LD = $(BINPATH)$(PREFIX)ld
AR = $(BINPATH)$(PREFIX)ar
SZ = $(BINPATH)$(PREFIX)size -A
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
RM = rm -rf
HEXDUMP = ./Scripts/dump.py
CREATEROM = ./Scripts/create_logisim_rom.py
GENBIN = ./Scripts/bin.py
# UPLOAD = ./Scripts/upload.py

#######################################
# build the application
#######################################
# compile gcc flags
ARCH = -march=rv32i
#SPEC = --specs=nosys.specs
SPEC = -nostartfiles
AFLAGS = $(ARCH) $(SPEC) -Wall $(INC)
CFLAGS = $(ARCH) $(SPEC) -Wall -std=c99 $(INC) $(OPT)

# LDSCRIPT = linker-script-test.ld
LDSCRIPT = linker-script.ld
#LDSCRIPT = ld.ld
LDFLAGS = $(ARCH) $(SPEC) -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--cref -T$(LDSCRIPT)

# generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

# list of objects
# add ASM to objects BEFORE C so that start label is at beginning
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))
# add C
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# default action: build all
all: clean $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).lss $(BUILD_DIR)/$(TARGET).bin size hexdump
#all: clean $(BUILD_DIR)/$(TARGET).elf size
# create object files from C files
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
# create object files from ASM files
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@$(AS) -c $(AFLAGS) $< -o $@
# create aplication ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
# create bin file
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@$(BIN) $< $@
# disassembly EFL
$(BUILD_DIR)/$(TARGET).lss: $(BUILD_DIR)/$(TARGET).elf
	@$(DP) -h -S $< > $@
# create build directory
$(BUILD_DIR):
	@mkdir $@
# prints memory usage tables
size:
	@$(SZ) $(BUILD_DIR)/$(TARGET).elf
# clean up
clean:
	@$(RM) $(BUILD_DIR)
# hexdump
hexdump:
	@$(HEXDUMP) -i $(BUILD_DIR)/$(TARGET).elf -o $(BUILD_DIR)/$(TARGET).mhc
	@$(GENBIN)
	@$(CREATEROM)

# upload: clean $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).lss $(BUILD_DIR)/$(TARGET).bin size hexdump 
# 	@$(UPLOAD)

linker-script:
	$(LD) --verbose -arch=elf32lriscv
