#include <stdio.h>
#include <stdlib.h>

#define num_cols 4
#define num_rows 3

typedef struct matrix {
	float vals[num_rows][num_cols];
} matrix;

int step = 0;

void print_matrix(matrix *A) {
	printf("\nSTEP %d\n", ++step);
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			printf("%.1f\t", A->vals[i][j]);
		}
		printf("\n\n");
	}
}

void add_row(matrix *A, int r1, int r2, float scale) {
	for (int i = 0; i < num_cols; i++) {
		A->vals[r2-1][i] += A->vals[r1-1][i] * scale;
	}
}

int main() {
	matrix A;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			A.vals[i][j] = 0;
		}
	}
	A.vals[0][0] = 2;
	A.vals[1][0] = 4;
	A.vals[2][0] = -2;

	A.vals[0][1] = 4;
	A.vals[1][1] = 9;
	A.vals[2][1] = -3;

	A.vals[0][2] = -2;
	A.vals[1][2] = -3;
	A.vals[2][2] = 7;

	A.vals[0][3] = 2;
	A.vals[1][3] = 8;
	A.vals[2][3] = 10;
	
	print_matrix(&A);
	add_row(&A, 1, 2, -2);
	print_matrix(&A);
	add_row(&A, 1, 3, 1);
	print_matrix(&A);
	add_row(&A, 2, 3, -1);
	print_matrix(&A);
	float z = A.vals[2][3] / A.vals[2][2];
	printf("solution\n");
	float y = (A.vals[1][3] - z*A.vals[1][2]) / A.vals[1][1];
	float x = (A.vals[0][3] - y*A.vals[0][1] - z*A.vals[0][2]) / A.vals[0][0];
	printf("x = %0.2f\n", x);
	printf("y = %0.2f\n", y);
	printf("z = %0.2f\n", z);
}
