#ifndef BIG_H
#define BIG_H
enum Errors {NIL, TOO_SMALL};
enum Comparison {LESS_THAN=-1, EQUAL_TO=0, GREATER_THAN=1};
enum bool {false, true};
typedef enum bool bool;
typedef enum Comparison comparison;
typedef enum Errors error;
struct big {
	bool sign;
	int offset;
	int n_bytes;
	unsigned char* bytes;
};
typedef struct big big_t;
big_t big_new();
void big_set(big_t *N, bool sign, int offset, unsigned long int val);
void big_delete(big_t N); 
char* big_to_string(big_t N);
long double big_to_double(big_t N);
void big_add(big_t *C, big_t A, big_t B);
void big_multiply(big_t *C, big_t A, big_t B);
void big_flip_sign(big_t *N);
#endif
