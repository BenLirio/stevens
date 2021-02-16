#include <stdio.h>

#define START 0
#define STOP 100
#define STEP 20
#define FACTOR 5.0/9.0

void main() {
	float celcius, fahr;

	for(fahr = STOP; fahr >= START; fahr = fahr - STEP) {
		printf("%6.0f\t%6.1f\n", fahr, FACTOR * (fahr-32));
	}
}
