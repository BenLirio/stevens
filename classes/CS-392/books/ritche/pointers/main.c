#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 50

char buf[BUFSIZE];
int bufp = 0;


int getch(void);
int getfloat(float *);
void ungetch(int);

int main()
{
	float a = 0;
	printf("return: %d\n", getfloat(&a));
	printf("float: %f\n", a);
	return 0;
}

/* getch: return the next availabe spot on the buffer, otherwise getchar */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getfloat: get next integer from input into *pn */
int getfloat(float *pn)
{
	char c;
	*pn = 0;
	while(isspace(c = getch()))
		;
	if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	int sign = c == '-' ? -1 : 1;
	if (c == '+'|| c == '-')
		c = getch();
	if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	int factor = 1;
	int pastdecimal = 0;
	for (;isdigit(c) || c == '.';c = getch()) {
		if (isdigit(c) && !pastdecimal) {
			*pn = (*pn * 10) + (c - '0');
		} else if(isdigit(c)) {
			*pn += (float)(c - '0')/(float)(factor *= 10);
		} else if (!pastdecimal) {
			pastdecimal = 1;
		} else {
			return 0;
		}

	}
	return 1;
}
