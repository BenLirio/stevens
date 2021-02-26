#include <stdio.h>
#include <stdlib.h>

int main() {
  long unsigned int *a;
  void *p = a;
  p++;
  printf("%p\n", a);
  printf("%p\n", ++a);
	return 0;
}
