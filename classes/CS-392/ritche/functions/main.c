#include <stdio.h>

int fahrenheitToCelcius(int fahrenheit);

int main() {
	int i;
	for (i = 0; i < 100; ++i) {
		int fahrenheit = i;
		int celcius = fahrenheitToCelcius(fahrenheit);
		printf("Celcius: %d\tFahrenheit: %d\n", celcius, fahrenheit);
	}
}

int fahrenheitToCelcius(int fahrenheit) {
	return (fahrenheit * 9 - 32) / 5;
}
