#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define NORMALIZE(X) (X)/(float)(unsigned int)(~0)
#define MIN(X, Y) (X) < (Y) ? (X) : (Y)
#define PI 3.1415926535897932384626433832795028841972
#define E 2.7182818284590452353602874713526624977572
#define BUFSIZE 124

typedef struct rand_state_t {
	unsigned int a;
	unsigned int c;
	unsigned int cur;
	unsigned int start;
} rand_state_t;

rand_state_t new_rand_state(unsigned int seed) {
	rand_state_t rand_state;
	rand_state.a = 1664525;
	rand_state.c = 1013904223;
	rand_state.cur = seed;
	rand_state.start = seed;
	return rand_state;
}

unsigned int uniform_rand(rand_state_t* s) {
	s->cur = s->a * s->cur + s->c;
	return s->cur;
}

float small_sin_approx(float x) {
	if (x > 1) {
		fprintf(stderr, "Error: This function is only for values less than or equal to 1\n");
		exit(EXIT_FAILURE);
	}
	int degree = 5;
	float coeff[] = {
		0.007252,
		0.001613,
		-0.167616,
		0.000244,
		0.999978,
		0
	};
	float sum = 0;
	for (int i = 0; i <= degree; i++) {
		float poly = 1;
		for (int j = degree; j > i; j--) {
			poly *= x;
		}
		sum += coeff[i]*poly;
	}
	return sum;
}

float small_neg_natural_exp_approx(float power) {
	if (power < -1.0 || power > 0.0) {
		fprintf(stderr, "Error: Expected power to be in range [-1, 0]\n");
	}

	int degree = 5;
	float coeff[] = {
		-0.217251596861,
		-0.406386432184,
		-0.146323730534,
		0.410655519563,
		0.9914267988415,
		1
	};
	float sum = 0;
	for (int i = 0; i <= degree; i++) {
		float poly = 1.0;
		for (int j = degree; j > i; j--) {
			poly *= power;
		}
		sum += coeff[i]*poly;
	}
	return sum;
}

float pdf(float x, float y) {
	float exp = small_neg_natural_exp_approx(-x*y);
	float min_term_2 = x-y*y < 0 ? -(x-y*y) : (x-y*y);
	float sin_term = MIN(x, min_term_2);
	// sin will always be positive so no need to abs()
	return small_sin_approx(sin_term)*exp;
}

int main() {
	int seed = time(NULL);
	rand_state_t rand_state = new_rand_state(seed);
	unsigned int rand_bits;
	float x;
	float y;
	int sample_size = 50000;
	float** data = malloc(sizeof(float*)*sample_size);
	for (int i = 0; i < sample_size; i++) {
		data[i] = malloc(sizeof(float)*3); // Tuple (x, y, pdf(x, y))
	}
	for (int i = 0; i < sample_size; i++) {
		rand_bits = uniform_rand(&rand_state);
		x = NORMALIZE(rand_bits);
		rand_bits = uniform_rand(&rand_state);
		y = NORMALIZE(rand_bits);
		data[i][0] = x;
		data[i][1] = y;
		data[i][2] = pdf(x, y);
	}
	int fd;
	if ((fd = open("data.csv", O_CREAT|O_RDWR, 0644)) == -1) {
		fprintf(stderr, "Error: failed to create or open 'data.csv'. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	char buf[BUFSIZE];
	ssize_t n;
	char* header = "x,y,pdf\n";
	n = write(fd, header, strlen(header));
	if (n != strlen(header)) {
		fprintf(stderr, "Error: Failed to print %lu bytes. %s.\n", strlen(header), strerror(errno));
		return EXIT_FAILURE;
	}
	
	for (int i = 0; i < sample_size; i++) {
		sprintf(buf, "%f,%f,%f\n",data[i][0], data[i][1], data[i][2]);
		n = write(fd, buf, strlen(buf));
		if (n != strlen(buf)) {
			fprintf(stderr, "Error: Failed to print %lu bytes. %s.\n", strlen(buf), strerror(errno));
			return EXIT_FAILURE;
		}
	}

	if (close(fd) != 0) {
		fprintf(stderr, "Error: failed to close 'data.csv'. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	for (int i = 0; i < sample_size; i++) {
		free(data[i]);
	}
	free(data);
}
