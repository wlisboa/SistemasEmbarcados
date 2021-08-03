
default: projeto gravar clean

projeto: main_io.o io_ctr.o
	avr-gcc -Wall -Os -mmcu=atmega328p -o projeto.elf main_io.o io_ctr.o
	avr-objcopy -j .text -j .data -O ihex projeto.elf projeto.hex 

main_io.o:
	avr-gcc -Wall -Os -mmcu=atmega328p -c main_io.c -o main_io.o

io_ctr.o: io_ctr.h
	avr-gcc -Wall -Os -mmcu=atmega328p -c io_ctr.c -o io_ctr.o

gravar:
	avrdude -v -p atmega328p -c arduino -P COM10 -b 115200 -U flash:w:projeto.hex

clean:
	rm main_io.o
	rm io_ctr.o
	rm projeto.elf
	rm projeto.hex