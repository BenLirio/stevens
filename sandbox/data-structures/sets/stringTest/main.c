#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int wordLen = 5;
	int numWords = 3;
	char** word = malloc(numWords * sizeof(void*));
	for (int i = 0; i < numWords; i++) {
		word[i] = malloc(wordLen);
	}
	for (int i = 0; i < numWords; i++) {
		for (int j = 0; j < wordLen; j++) {
			printf("%d", word[i][j]);
		}
		printf("\n");
	}
}
