#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int fuel = 0;
int capacity = 40;
int cars_filled = 0;
int num_cars = 4;
pthread_mutex_t fuel_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fuel_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t station_cond = PTHREAD_COND_INITIALIZER;

void* car(void* ptr) {
	for(;;) {
		pthread_mutex_lock(&fuel_mutex);
		while (fuel < 40) {
			printf("Waiting...\n");
			pthread_cond_wait(&fuel_cond, &fuel_mutex);
		}
		fuel -= 40;
		printf("Done.\n");
		cars_filled++;
		pthread_cond_signal(&station_cond);
		pthread_mutex_unlock(&fuel_mutex);
		break;
	}
	return NULL;
}

void* station(void* ptr) {
	for(;;) {
		pthread_mutex_lock(&fuel_mutex);
		if (cars_filled == num_cars) {
			pthread_mutex_unlock(&fuel_mutex);
			break;
		}
		while (fuel > capacity) {
			printf("Nothing more to fill.\n");
			pthread_cond_wait(&station_cond, &fuel_mutex);
		}
		if (fuel < capacity) {
			fuel += 15;
		}
		pthread_cond_signal(&fuel_cond);
		pthread_mutex_unlock(&fuel_mutex);
	}
	return NULL;
}

int main() {
	pthread_t car_thread;
	pthread_t station_thread;
	
	int rtnval;
	for (int i = 0; i < num_cars; i++) {
		if ((rtnval = pthread_create(&car_thread, NULL, car, NULL)) != 0) {
			fprintf(stderr, "Error: pthread_create() failed. %s.\n", strerror(rtnval));
		}
	}
	if ((rtnval = pthread_create(&station_thread, NULL, station, NULL)) != 0) {
		fprintf(stderr, "Error: pthread_create() failed. %s.\n", strerror(rtnval));
	}

	if ((rtnval = pthread_join(station_thread, NULL)) != 0) {
		fprintf(stderr, "Error: pthread_join() failed. %s.\n", strerror(rtnval));
	}
	if ((rtnval = pthread_join(car_thread, NULL)) != 0) {
		fprintf(stderr, "Error: pthread_join() failed. %s.\n", strerror(rtnval));
	}
}
