#include <stdio.h>
#include "GPIO.h"

int main(void) {

    GPIO_Status status;

    // Initialize pin 2 as an output
    status = GPIO_init(2, GPIO_OUTPUT);
    printf("GPIO_init status: %u\n", (unsigned int)status);

    // Write GPIO_HIGH to pin 2
    status = GPIO_write(2, GPIO_HIGH);

    // Print the returned statuses
    printf("GPIO_write status: %u\n", (unsigned int)status);

    return 0;
}
