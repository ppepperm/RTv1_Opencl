#include "cl_header.h"

__kernel void vector_add(__global const real_t *A, __global const t_data *B, __global double *C)
{
// Get the index of the current element to be processed
int i = get_global_id(0);
real_t kek = 0;
// Do the operation
C[i] = abs_p3(B[i].pos);
}
