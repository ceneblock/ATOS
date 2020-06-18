# Default CFLAGS:
CFLAGS?=-O2 -g
 
# Add mandatory options to CFLAGS:
CFLAGS:=$(CFLAGS) -Wall -Wextra

all: myos.bin

myos.bin: boot.o kernel.o
	${TARGET}-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

kernel.o: kernel.c
	${TARGET}-gcc -c kernel.c -o kernel.o -ffreestanding ${CFLAGS}

boot.o: boot.s
	${TARGET}-as $< -o $@

clean:
	-rm myos.bin kernel.o boot.o


.PHONY: clean
