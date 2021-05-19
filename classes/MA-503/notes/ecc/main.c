#include <stdlib.h>
#include <stdio.h>

typedef enum ERROR {
	NIL,
	UNDEF
} ERROR;
char* err_to_string(ERROR err) {
	switch(err) {
	case UNDEF:
		return "Undefined";
	default:
		return "Default err";
	}
}
typedef struct rtn_t {
	void* v;
	ERROR err;
} rtn_t;
rtn_t new_rtn() {
	rtn_t rtn;
	rtn.v = NULL;
	rtn.err = NIL;
	return rtn;
}
void clear_rtn(rtn_t rtn) {
	free(rtn.v);
}


typedef struct eliptic_curve_t {
	int a;
	int b;
} eliptic_curve_t;

typedef struct solution_t {
	int x;
	int y;
} solution_t;

/*
 * Returns a *solution_t
 */
rtn_t add(eliptic_curve_t E, solution_t a, solution_t b) {
	rtn_t rtn = new_rtn();
	
	solution_t* c = malloc(sizeof(solution_t));
	rtn.v = c;
	if (a.x != b.x) {
		c->x = 1;
	} else {
		rtn.err = UNDEF;
	}
	
	return rtn;
}

void check(ERROR err, char* msg) {
	if (err != NIL) {
		printf("Error: %s. %s.\n", msg, err_to_string(err));
		exit(EXIT_FAILURE);
	}
}

int main() {
	rtn_t rtn = new_rtn();
	eliptic_curve_t E;
	E.a = 2;
	E.b = 3;
	solution_t a;
	a.x = 1;
	a.y = 2;
	solution_t b;
	b.x = 2;
	b.y = 8;
	rtn = add(E, a, b);
	check(rtn.err, "Add failed");
	solution_t c = *(solution_t*)rtn.v;
	clear_rtn(rtn);

	printf("x: %d, y: %d\n", c.x, c.y);

}
