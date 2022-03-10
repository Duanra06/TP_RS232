all: main

main: hellow.o
	avr-gcc -mmcu=atmega32u4 -Os -Wall -o main hellow.o

hellow.o: hellow.c
	avr-gcc -mmcu=atmega32u4 -Os -Wall -c hellow.c

clean:
	rm *.o main

flash: main
	avrdude -c avr109 -b57600 -D -p atmega32u4 -P /dev/ttyACM0 -e -U flash:w:main.out
