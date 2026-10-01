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
CC := riscv64-elf-gcc
CFLAGS := -g -O0 -ffunction-sections -static-libgcc\
		  -lgcc -march=rv32ec_zicsr -mabi=ilp32e\
		  -nostdlib -I. -Wall -MMD -MP

build/firmware.elf: $(OBJS) build/generated_ch32v003.ld
	@echo "Linking OBJ"
	@$(CC) $(CFLAGS) -T build/generated_ch32v003.ld -Wl,--gc-sections -L. -o $@ $(OBJS) $(LDFLAGS)

#build obj
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

.PHONY: clean
clean:
	rm -rf build

-include $(DEPS)
