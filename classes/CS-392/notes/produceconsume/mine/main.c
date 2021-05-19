#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFLEN 100
#define TOP 10000000

struct ctx {
	char buffer[BUFLEN];
	pthread_mutex_t mutex;
	int i;
	int a;
	int b;
};
typedef struct ctx* ctx_t;
void ctx_init(ctx_t ctx) {
	pthread_mutex_init(&(ctx->mutex), NULL);
	ctx->i = 0;
	ctx->a = 0;
	ctx->b = 0;
}

void* produce(void* ptr) {
	ctx_t ctx = (ctx_t)ptr;
	pthread_mutex_lock(&(ctx->mutex));
	for(;;) {
		if (ctx->i >= TOP) {
			pthread_mutex_unlock(&(ctx->mutex));
			goto DONE;
		}
		ctx->a++;
		ctx->i++;
		pthread_mutex_unlock(&(ctx->mutex));
	}
	DONE:
	return NULL;
}

void* consume(void* ptr) {
	ctx_t ctx = (ctx_t)ptr;
	for (;;) {
		pthread_mutex_lock(&(ctx->mutex));
		if (ctx->i >= TOP) {
			pthread_mutex_unlock(&(ctx->mutex));
			goto DONE;
		}
		ctx->b++;
		ctx->i++;
		pthread_mutex_unlock(&(ctx->mutex));
	}
	DONE:
	return NULL;
}

int main() {
	pthread_t producer_thread;
	pthread_t consumer_thread;
	ctx_t ctx = malloc(sizeof(struct ctx));
	ctx_init(ctx);
	pthread_create(&producer_thread, NULL, produce, ctx);
	pthread_create(&consumer_thread, NULL, consume, ctx);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);
	printf("A: %d, B: %d\n", ctx->a, ctx->b);
	printf("Total: %d\n", ctx->a + ctx->b);
	printf("I: %d\n", ctx->i);
	pthread_mutex_destroy(&(ctx->mutex));
	free(ctx);
}
