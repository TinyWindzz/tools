CC = arm-tiny4412-linux-gnueabi-

obj = start.o main.o

asm.bin : $(obj)
	$(CC)ld -Tasm.lds -N -o asm.elf $^
	$(CC)objcopy -O binary -S asm.elf $@
	$(CC)objdump -D -m arm asm.elf > asm.dis
	./run.sh

%.o:%.c
	$(CC)gcc -Wall -marm -c -O2 -o $@ $< -fno-builtin

%.o:%.S
	$(CC)gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f *.dis *.bin *.elf *.o
