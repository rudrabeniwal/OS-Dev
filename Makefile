ASM = nasm
CC = gcc
BOOTSTRAP_FILE = bootstrap.asm
INIT_KERNEL_FILES = starter.asm
KERNEL_FILES = main.c
KERNEL_FLAGS = -Wall -m32 -c -ffreestanding -fno-asynchronous-unwind-tables -fno-pie
KERNEL_OBJECT = -o kernel.elf
build: $(BOOTSTRAP_FILE) $(KERNEL_FILES)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	$(ASM) -f elf32 $(INIT_KERNEL_FILES) -o starter.o
	$(CC) $(KERNEL_FLAGS) $(KERNEL_FILES) $(KERNEL_OBJECT)
	$(CC) $(KERNEL_FLAGS) screen.c -o screen.elf 
	$(CC) $(KERNEL_FLAGS) process.c -o process.elf 
	$(CC) $(KERNEL_FLAGS) scheduler.c -o scheduler.elf 
	ld -melf_i386 -Tlinker.ld starter.o kernel.elf screen.elf process.elf scheduler.elf -o myKernel.elf
	objcopy -O binary myKernel.elf myKernel.bin
	dd if=bootstrap.o of=kernel.img
	dd seek=1 conv=sync if=myKernel.bin of=kernel.img bs=512 count=5
	dd seek=6 conv=sync if=/dev/zero of=kernel.img bs=512 count=2046
	qemu-system-x86_64 -s kernel.img

# Clean target to remove build artifacts
clean:
	rm -f *.o *.elf *.bin myKernel.bin kernel.img
