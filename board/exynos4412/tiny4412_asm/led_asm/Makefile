CC=arm-tiny4412-linux-gnueabi-

led.bin : led.S
	$(CC)gcc -c -o led.o led.S
	$(CC)ld -Tled.lds -N led.o -o led.elf
	$(CC)objcopy -O binary -S led.elf led.bin
	$(CC)objdump -D -m arm led.elf > led.dis
clean:
	rm -f *.dis *.bin *.elf *.o
