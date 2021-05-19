#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	char* str = malloc(sizeof(char)*10);
	for (int i = 0; i < 10; i++) {
		str[i] = i + '0';
	}
	str[9] = '\0';
	printf("%s\n", str);
	str = realloc(str, sizeof(char)*5);
	str[4] = '\0';
	printf("%s\n", str);
	free(str);
	return 0;
}
