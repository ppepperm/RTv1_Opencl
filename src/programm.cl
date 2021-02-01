#include "../includes/cl_header.h"

__kernel void vector_add(__global unsigned char *buffer)
{
// Get the index of the current element to be processed
	int coll = get_global_id(0);
	int row = 0;
	int pitch = (int)(W_W* sizeof(unsigned int));

	while (row < W_H)
	{
		buffer[coll * 4 + 0 + row * pitch] = 255;
		buffer[coll * 4 + 1 + row * pitch] = 200;
		buffer[coll * 4 + 2 + row * pitch] = 255;
		buffer[coll * 4 + 3 + row * pitch] = 0;
		row++;
	}


}
