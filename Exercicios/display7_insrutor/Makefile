FILENAME   = main
PORT       = COM10
DEVICE     = atmega328p
PROGRAMMER = arduino
BAUD       = 115200
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)

default: linker upload clean

linker: main.o io_ctr.o display_ctr.o
	$(COMPILE) -o project.elf main.o io_ctr.o display_ctr.o
	avr-objcopy -j .text -j .data -O ihex project.elf project.hex 
	avr-size --format=avr --mcu=$(DEVICE) project.elf

main.o:
	$(COMPILE) -c main.c -o main.o

io_ctr.o: io_ctr.h
	$(COMPILE) -c io_ctr.c -o io_ctr.o

display_ctr.o: display_ctr.h
	$(COMPILE) -c display_ctr.c -o display_ctr.o

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:project.hex

clean:
	rm main.o
	rm project.elf
	rm project.hex

size:
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf