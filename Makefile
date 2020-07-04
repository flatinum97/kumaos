OBJECTS = loader.o \
asm_interrupts.o \
assembly_interface.o \
drivers/frame_buffer.o \
drivers/keyboard.o \
drivers/pic.o \
drivers/serial_port.o \
interrupts.o \
kmain.o \
stdio.o \
global_descriptor_table.o \
interrupt_descriptor_table.o \
page_table.o

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
QEMU = qemu-system-i386
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	mkdir -p iso/boot/grub              # create the folder structure
	cp stage2_eltorito iso/boot/grub/   # copy the bootloader
	cp kernel.elf iso/boot/             # copy the kernel
	cp menu.lst iso/boot/grub           # copy the configuration file
	mkisofs -R                              \
          -b boot/grub/stage2_eltorito    \
          -no-emul-boot                   \
          -boot-load-size 4               \
          -A os                           \
          -input-charset utf8             \
          -quiet                          \
          -boot-info-table                \
          -o os.iso                       \
          iso

run: os.iso
	$(QEMU) -monitor stdio -cdrom $< -serial file:log/log.txt

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o drivers/*.o kernel.elf os.iso
