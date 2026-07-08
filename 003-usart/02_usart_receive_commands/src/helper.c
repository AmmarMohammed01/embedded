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
	char input[10];
	char current = ' ';
	while(current != '\r') {
		current = usart_receive();
		usart_transmit(current); //for debugging
		input[index] = current;
		index++;
	}

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
		printPhrase(input, 10);
	}
}
