#include <stdio.h>

#define OUT 0
#define IN 1
#define MAX_WORD_LEN 16

int main() {
	int c;
	int wordLen;
	int state;
	int wordLens[MAX_WORD_LEN];
	for (int i = 0; i < MAX_WORD_LEN; i++)
		wordLens[i] = 0;

	state = OUT;
	wordLen = 0;
	while((c = getchar()) != EOF) {
		if (!(c == ' ') && !(c == '\t') && !(c == '\n')) {
			state = IN;
			wordLen += 1;
		}
		else if (state == IN) {
			state = OUT;
			if (wordLen > MAX_WORD_LEN)
				wordLen = MAX_WORD_LEN;
			wordLens[wordLen-1] += 1;

			wordLen = 0;
		}
	}
	for (int i = MAX_WORD_LEN; i > 0; i--) {
		for (int j = 0; j < MAX_WORD_LEN; j++) {
			if (wordLens[j] >= i) {
				printf("  *");
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}
	for (int i = 0; i < MAX_WORD_LEN; i++) {
		if ((i+1) >= 10) {
			printf(" %d", i+1);
		} else {
			printf("  %d", i+1);
		}
	}
	printf("\n");
	return 0;
}
