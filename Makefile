ASM = nasm                   
BOOTSTRAP_FILE = bootstrap.asm 
KERNEL_FILE = simple_kernel.asm 

build: $(BOOTSTRAP_FILE) $(KERNEL_FILE)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	$(ASM) -f bin $(KERNEL_FILE) -o kernel.o
	dd if=bootstrap.o of=kernel.img bs=512 count=1
	dd if=kernel.o of=kernel.img bs=512 seek=1 conv=notrunc
	qemu-system-x86_64 -hda kernel.img -nographic    

clean:
	rm -f *.o               
