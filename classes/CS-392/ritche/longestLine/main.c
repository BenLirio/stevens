#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int myGetline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int len;	/* current line length */
	int max;	/* maxline length seen so far */
	char* line;	/* current input line */
	char longest[MAXLINE];	/* longest line save here */

	max = 0;
	while ((len = myGetline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) /* there was a line */
		printf("%s", longest);
	return 0;
}

/* getline:	read a line into s, return length */
int myGetline(char s[], int lim)
{
	int c, i;

	for (i=0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}
