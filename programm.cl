#include "cl_header.h"

__kernel void vector_add(__global const real_t *A, __global const t_data *B, __global double *C)
{
	// Get the index of the current element to be processed
	int i = get_global_id(0);
	// Do the operation
	C[i] = B[i].pos.x*B[i].pos.x + B[i].pos.y*B[i].pos.y + B[i].pos.z*B[i].pos.z;
}