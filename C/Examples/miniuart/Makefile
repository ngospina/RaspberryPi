
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

muterm.o : muterm.c
	$(ARMGNU)-gcc $(COPS) -c muterm.c -o muterm.o

kernel.o : kernel.c
	$(ARMGNU)-gcc $(COPS) -c kernel.c -o kernel.o

kernel.elf : memmap start.o muterm.o kernel.o 
	$(ARMGNU)-ld start.o muterm.o kernel.o -T memmap -o kernel.elf

kernel.img : kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary kernel.img
