SRCS := \
	$(wildcard src/*.c)\
	vendor/ch32fun/ch32fun/ch32fun.c
INCLUDES := \
	$(wildcard src)\
	vendor/ch32fun/ch32fun

#preprocess variables
INCLUDES := $(addprefix -I,$(INCLUDES))
OBJS := $(SRCS:%=build/%.o)
DEPS := $(OBJS:.o=.d)

#compiler variables
CC := riscv64-unknown-elf-gcc
CXX := riscv64-unknown-elf-g++
CFLAGS := -g -O0 -ffunction-sections \
          -march=rv32ec_zicsr -mabi=ilp32e \
          -nostdlib -Wall -MMD -MP

LDFLAGS := \
          	-march=rv32ec_zicsr -mabi=ilp32e \
			-nostdlib \
			-Wl,--gc-sections \
			-T build/generated_ch32v003.ld \

build/firmware.bin: build/firmware.elf
	@riscv64-unknown-elf-size build/firmware.elf
	@riscv64-unknown-elf-objdump -S build/firmware.elf > build/firmware.lst
	@riscv64-unknown-elf-objdump -t build/firmware.elf > build/firmware.map
	@riscv64-unknown-elf-objcopy -O binary build/firmware.elf build/firmware.bin
	@riscv64-unknown-elf-objcopy -O ihex build/firmware.elf build/firmware.hex
	@cd build && xxd -i firmware.bin > firmware.h

build/firmware.elf: $(OBJS) build/generated_ch32v003.ld
	@echo "Linking OBJ"
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) -lgcc

build/%.c.o : %.c
	@echo "Compiling sourcefiles"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/generated_ch32v003.ld:
	@echo "Generating flash preset"
	@$(CC) -E -P -x c \
		-DTARGET_MCU=ch32v003 \
		-DMCU_PACKAGE=1 \
		-DTARGET_MCU_LD=0 \
		vendor/ch32fun/ch32fun/ch32fun.ld \
		-o $@

.PHONY: flash
flash : build/firmware.bin
	gdb -x gdbinit -ex 'load' -ex 'detach' -ex 'quit' build/firmware.elf

.PHONY: clang
clang :
	bear -- make

.PHONY: clean
clean:
	rm -rf build

-include $(DEPS)
