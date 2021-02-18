#include "big.h"


int main() {
	int n_bytes = 2;
	big_t N = big_new();
	big_t LN = big_new();
	max_val(&N, n_bytes);
	ln(&LN, N);
	big_print(LN);
	big_delete(N);
	big_delete(LN);
	return 0;
}
