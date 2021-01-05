/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:34:02 by ppepperm          #+#    #+#             */
/*   Updated: 2020/08/04 14:34:06 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

void			init_ocl_sequence(t_ocl_sequence *sq)
{
	t_ocl_sequence		sq_r;
	cl_device_fp_config double_check;
	cl_int				ret;

	sq_r.p_id = NULL;
	sq_r.d_id = NULL;
	ret = clGetPlatformIDs(1, &(sq_r.p_id), &(sq_r.num_pl));
	ret = clGetDeviceIDs(sq_r.p_id, CL_DEVICE_TYPE_GPU, 1, &(sq_r.d_id), &(sq_r.num_dv));
	//printf("device num %d\n", sq_r.num_dv);
	/*
	ret = clGetDeviceInfo(sq_r.d_id, CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(cl_device_fp_config),&double_check,NULL);
	ft_putstr("CL_FP_DENORM : ");
	printf("%d \n", double_check);
	*/

	sq_r.context = clCreateContext(NULL, 1, &(sq_r.d_id), NULL, NULL, &ret);
	sq_r.queue = clCreateCommandQueue(sq_r.context, sq_r.d_id, 0, &ret);
	*sq = sq_r;
}

cl_program		program_from_file(char *fname, t_ocl_sequence sq)
{
	int fd;
	char *source_str;
	size_t source_size;
	cl_program program;

	fd = open(fname, O_RDWR);
	if (fd < 0) {
		ft_putstr("failed to load prog\n");
		exit(1);
	}
	source_str = (char*) malloc(MAX_SOURCE_SIZE);
	source_size = read(fd, source_str, MAX_SOURCE_SIZE);
	close(fd);
	program = clCreateProgramWithSource(sq.context, 1,
			(const char**)&source_str, (const size_t*)&source_size, NULL);
	free(source_str);
	return (program);
}

void			get_build_info(cl_program program, t_ocl_sequence sq, char* name)
{
	char *ret;

	ret = (char*)malloc(sizeof(char)*MAX_SOURCE_SIZE);
	clGetProgramBuildInfo(program, sq.d_id, CL_PROGRAM_BUILD_LOG, MAX_SOURCE_SIZE, ret, NULL);
	ft_putstr(name);
	ft_putstr(" BUILD INFO: ");
	ft_putstr(ret);
	ft_putchar('\n');
	free(ret);
}

void			prepare_kernel(t_ocl_sequence *sq)
{
	cl_program	header;
	cl_program	srcs[2];
	cl_program	kernel_program;
	char 		*h_str;

	h_str = "../includes/cl_header.h";
	header = program_from_file("includes/cl_header.h", *sq);
	srcs[0] = program_from_file("src/programm.cl", *sq);
	srcs[1] = program_from_file("src/abs.cl", *sq);
	clCompileProgram(srcs[0], sq->num_dv, &(sq->d_id), NULL, 1, &header, (const char**)&h_str, NULL, NULL);
	clCompileProgram(srcs[1], sq->num_dv, &(sq->d_id), NULL, 1, &header, (const char**)&h_str, NULL, NULL);
	get_build_info(srcs[0], *sq, "main");
	get_build_info(srcs[1], *sq, "funk");
	kernel_program = clLinkProgram(sq->context, sq->num_dv, &(sq->d_id), NULL, 2, srcs, NULL, NULL, NULL);
	get_build_info(kernel_program, *sq, "all");
	sq->kernel = clCreateKernel(kernel_program, "vector_add", NULL);
}

void			execute_rt(t_ocl_sequence ocl_sq, t_sdl_sequence sdl_sq)
{
	unsigned char	*tex_buff;
	void			*tmp;
	int 			pitch;
	cl_mem			buff_obj;
	cl_int				ret;

	SDL_LockTexture(sdl_sq.win_tex, NULL, &tmp, &pitch);
	tex_buff = (unsigned char *)tmp;
	/*for (int i = 0; i < W_W; i++)
	{
		for(int j = 0; j < W_H; j++)
		{
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 0 + j * pitch]);
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 1 + j * pitch]);
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 2 + j * pitch]);
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 3 + j * pitch]);
		}
		ft_putchar('\n');
	}*/
	buff_obj = clCreateBuffer(ocl_sq.context, CL_MEM_WRITE_ONLY,
			(unsigned int)(W_H*W_W)* sizeof(unsigned int), NULL, &ret);
	ft_putnbr(ret);
	ft_putchar('\n');
	ret = clSetKernelArg(ocl_sq.kernel, 0, sizeof(cl_mem), (void *)&buff_obj);
	ft_putnbr(ret);
	ft_putchar('\n');
	size_t global_item_size = (size_t)(W_W);
	size_t local_item_size = 1;
	ret = clEnqueueNDRangeKernel(ocl_sq.queue, ocl_sq.kernel, 1,
			NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ft_putnbr(ret);
	ft_putchar('\n');
	ret = clEnqueueReadBuffer(ocl_sq.queue, buff_obj, CL_TRUE, 0,
			(unsigned int)(W_H*W_W)* sizeof(unsigned int), tex_buff, 0, NULL, NULL);
	ft_putnbr(ret);
	ft_putchar('\n');
	/*for (int i = 0; i < W_W; i++)
	{
		for(int j = 0; j < W_H; j++)
		{
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 0 + j * pitch]);
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 1 + j * pitch]);
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 2 + j * pitch]);
			ft_putchar(' ');
			ft_putnbr(tex_buff[i * 4 + 3 + j * pitch]);
		}
		ft_putchar('\n');
	}*/
	SDL_UnlockTexture(sdl_sq.win_tex);
}