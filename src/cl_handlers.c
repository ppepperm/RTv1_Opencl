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
	t_ocl_sequence	sq_r;
	cl_int			ret;

	sq_r.p_id = NULL;
	sq_r.d_id = NULL;
	ret = clGetPlatformIDs(1, &(sq_r.p_id), &(sq_r.num_pl));
	ret = clGetDeviceIDs(sq_r.p_id, CL_DEVICE_TYPE_GPU, 1, &(sq_r.d_id), &(sq_r.num_dv));
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
	cl_program header;
	cl_program srcs[2];
	cl_program kernel_program;
	char *h_str;

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