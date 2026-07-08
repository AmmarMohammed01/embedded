#include "helper.h"

#include <string.h> //strcmp()

//Function that prints multiple characters at a time
void printPhrase(char* message, unsigned int msgLength) {
	for (int i = 0; i < msgLength; i++) {
		usart_transmit(message[i]);
	}
	usart_transmit('\n');
	usart_transmit('\r');
}

void interpret() {
	unsigned int index = 0;
	char input[8];
	memset(input, 0, sizeof(input));
	char current = ' ';
	while(current != '\r') {
		current = usart_receive();
		usart_transmit(current); //for debugging
		input[index] = current;
		index++;
	}
	input[index-1] = '\0';
	usart_transmit('\r');
	usart_transmit('\n');

	//if message == "LED ON", then ON LED
	if(strcmp("LED ON", input) == 0) {
		led_on();
	}

	//if message == "LED OFF", then OFF LED
	else if(strcmp("LED OFF", input) == 0) {
		led_off();
	}

	//else return an error message
	else {
		printPhrase("Invalid Input", 14);
	}

	for(int i = 0; i < 8; i++) {
		usart_transmit(i+48); //index
		usart_transmit(':');
		usart_transmit(' ');

		printMemory(&input[i]); //ascii code of character
		usart_transmit(' ');
		usart_transmit(input[i]); //character

		usart_transmit('\n');
		usart_transmit('\r');
	}
}

void printMemory(char * charByte) {
	//usart_transmit(*charByte); //this returns ASCII character instead of ASCII character code

	//Example: L is 76 or 01001100
	//If 01001100 is printed w/ transmit, it appears as letter
	//So I need to take the binary and convert the decimal number to a string form

	//
	unsigned int num = *charByte;
	usart_transmit((num / 10)+48);
	usart_transmit((num % 10)+48);
	//usart_transmit('\r');
	//usart_transmit('\n');
}
