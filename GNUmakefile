# $@ = target file
# $< = first dependency
# $^ = all dependencies

CPP_SOURCES = $(wildcard kernel/*.cc libk/*.cc)
HEADERS = $(wildcard kernel/*.hh libk/*.hh)
OBJ = ${CPP_SOURCES:.cc=.o}

CC = i686-elf-g++
CFLAGS = -g -std=c++20 -ffreestanding -nostdlib -lgcc -Wall -O2 -flto -ffat-lto-objects \
		 -fno-threadsafe-statics -fno-stack-protector -fno-rtti -fno-exceptions
SFLAGS = -mgeneral-regs-only
GDB = x86_64-elf-gdb

CRTI_OBJ = boot/crti.o
CRTN_OBJ = boot/crtn.o
CRT0_OBJ = boot/crt0.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
OBJ_LINK_LIST:=$(CRT0_OBJ) $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJ) $(CRTEND_OBJ) $(CRTN_OBJ)

all: run

goosyos.bin: boot/boot.bin kernel.bin
	cat $^ > $@

kernel.bin: ${OBJ_LINK_LIST}
	i686-elf-ld -flto -use-linker-plugin  -o $@ --script=linker.ld $^ --oformat binary

kernel.elf: ${OBJ_LINK_LIST}
	i686-elf-ld -flto -use-linker-plugin -o $@ --script=linker.ld $^ 

dump: kernel.elf
	objdump -d kernel.elf > dump.txt

run: goosyos.bin
	qemu-system-i386 -hda $<

run-debug: goosyos.bin
	qemu-system-i386 -hda $< -d int -no-reboot -no-shutdown

gdb: goosyos.bin kernel.elf
	qemu-system-i386 -hda $< -S -s -d int -no-reboot -no-shutdown & ${GDB}

%.o: %.cc ${HEADERS}
	${CC} ${CFLAGS} ${SFLAGS} -c $< -o $@

%.o: %.s
	nasm $< -f elf -o $@

%.bin: %.s
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o goosyos.bin *.elf
	rm -rf *.o boot/*.bin boot/*.o libk/*.o libk/*/*.o kernel/*.o obj/*

summary:
	find . -name '*.s'   | xargs wc -l && \
	find . -name '*.cc'  | xargs wc -l && \
	find . -name '*.hh'  | xargs wc -l
