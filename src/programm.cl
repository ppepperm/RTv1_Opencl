#include "../includes/cl_header.h"

__kernel void vector_add(__global unsigned char *buffer)
{
// Get the index of the current element to be processed
	int coll = get_global_id(0);
	int row = 0;
	int pitch = (int)(W_H* sizeof(unsigned int));


	//printf("kernel num: %d\n", coll);
	while (row < W_H)
	{
		/*ray = get_ray(data->scene.camera, data->coll - W_W / 2, W_H / 2 - row);
		colour = trace_ray(ray, data->scene);
		data->win_buff[data->coll * 4 + 0 + row * data->pitch] = colour.b;
		data->win_buff[data->coll * 4 + 1 + row * data->pitch] = colour.g;
		data->win_buff[data->coll * 4 + 2 + row * data->pitch] = colour.r;
		data->win_buff[data->coll * 4 + 3 + row * data->pitch] = colour.a;*/
		buffer[coll * 4 + 0 + row * pitch] = 255;
		buffer[coll * 4 + 0 + row * pitch] = 0;
		buffer[coll * 4 + 0 + row * pitch] = 255;
		buffer[coll * 4 + 0 + row * pitch] = 0;
		row++;
	}


}
