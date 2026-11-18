compile: main.c GPIO.c
	gcc -c main.c -o main.o
	gcc -c GPIO.c -o GPIO.o

link: main.o GPIO.o
	gcc main.o GPIO.o -o a.out # gpio_test

clean:
	rm main.o gpio.o a.out
