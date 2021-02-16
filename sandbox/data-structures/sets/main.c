#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SET_SIZE 16
#define MAX_LINE 1024
#define MAX_WORD 64
#define MAX_ARGS 16

void* Search(void* S[], void* k);
void Insert(void* S[], void* x);
void Delete(void* S[], void* x);
void* Minimum(void* S[]);
void* Maximum(void* S[]);
void* Successor(void* S[], void* x);
void* Predecessor(void* S[], void* x);
void HandleCmds(int cmdc, char** cmds);

int main() {
	int n;
	char b[MAX_LINE];
	while(1) {
		n = read(STDIN_FILENO, b, MAX_LINE);
		if (n == 0) {
			exit(0);
		}
		char** cmds = malloc(MAX_ARGS*sizeof(char*));
		for (int i = 0; i < MAX_ARGS; i++) {
			cmds[i] = malloc(MAX_WORD);
		}
		int cmdc = 0;
		int wordlen = 0;
		for (int i = 0; i < n; i++) {
			if ((b[i] == ' ' || b[i] == '\n') && wordlen != 0) {
				cmdc += 1;
				wordlen = 0;
			} else {
				cmds[cmdc][wordlen] = b[i];
				wordlen += 1;
			}
		}
		HandleCmds(cmdc, cmds);
	}
}

void HandleCmds(int cmdc, char** cmds) {
	if (cmdc < 1) {
		printf("Display Help\n");
	}
}

void* Search(void* S[], void* k) {
	void *s;
	return s;
}

void Insert(void* S[], void* x) {
	printf("INSERT\n");
}

void Delete(void* S[], void* x) {
}
void* Minimum(void* S[]) {
	void *s;
	return s;
}
void* Maximum(void* S[]) {
	void *s;
	return s;
}
void* Successor(void* S[], void* x) {
	void *s;
	return s;
}
void* Predecessor(void* S[], void* x) {
	void *s;
	return s;
}
