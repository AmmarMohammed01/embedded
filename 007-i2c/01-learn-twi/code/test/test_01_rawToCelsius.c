#include <stdio.h>

#include "helper.h"

int main() {
	//6272 around 24'C
	//float celsius = tmp1075_raw_to_celsius(6272); //24
	float celsius = tmp1075_raw_to_celsius(65520); //-0.0625
	//float celsius = tmp1075_raw_to_celsius(52736); //-50

	printf("Celsius: %.4f\n", celsius);
	printf("Celsius: %g\n", celsius);
	return 0;
}
