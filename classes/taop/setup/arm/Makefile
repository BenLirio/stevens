CROSS_COMPILE ?= arm-none-linux-gnueabi

AOPS = --warn --fatal-warnings
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

hello_world.bin	: startiup.s memmap
    $(CROSS_COMPILE)-as $(AOPS) startup.s -o startup.o
    $(CROSS_COMPILE)-ld startup.o -T memmap -o hello_world.elf
    $(CROSS_COMPILE)-objdump -D hello_world.elf > hello_world.list
    $(CROSS_COMPILE)-objcopy hello_world.elf -O binary hello_world.bin

