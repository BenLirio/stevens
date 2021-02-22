#include <stdio.h>
#include <stdlib.h>

typedef unsigned short int dim_t;

void print_dim(int* a, int num_dims, dim_t* dims, dim_t cur_dim, dim_t offset) {
	if (cur_dim == num_dims -1) {
		for (int i = 0; i < dims[cur_dim]; i++) {
			printf("%d", a[offset + i]);
		}
		printf("\n");
	} else {
		int offset_factor = 1;
		for (int i = num_dims-1; i > cur_dim; i--) {
			offset_factor *= dims[i];
		}
		for (int i = 0; i < dims[cur_dim]; i++) {
			print_dim(a, num_dims, dims, cur_dim + 1, offset + offset_factor*i);
		}
	}
}

int main() {	
	dim_t* a_dims;
	int a_num_dims = 3;
	a_dims = malloc(sizeof(dim_t) * a_num_dims);
	a_dims[0] = 3; // height
	int height = 3;
	a_dims[1] = 2; // width
	int width = 2;
	a_dims[2] = 4; // depth
	int depth = 4;
	int a_num_elements = 1;
	for (int i = 0; i < a_num_dims; i++) {
		a_num_elements *= a_dims[i];
	}
	int *a = malloc(sizeof(int) * a_num_elements);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < depth; k++) {
				a[i*width*depth + j*depth + k] = i + j + k;
			}
		}
	}
	print_dim(a, a_num_dims, a_dims, (dim_t) 0, 0);
}
