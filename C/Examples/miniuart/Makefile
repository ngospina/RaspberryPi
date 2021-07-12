
ARMGNU ?= arm-none-eabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

gcc : kernel.img

all : gcc

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img

start.o : start.s
	$(ARMGNU)-as start.s -o start.o

miniuart.o : miniuart.c
	$(ARMGNU)-gcc $(COPS) -c miniuart.c -o miniuart.o

kernel.o : kernel.c
	$(ARMGNU)-gcc $(COPS) -c kernel.c -o kernel.o

kernel.elf : memmap start.o miniuart.o kernel.o 
	$(ARMGNU)-ld start.o miniuart.o kernel.o -T memmap -o kernel.elf

kernel.img : kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img
