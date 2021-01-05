/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 13:11:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/07/26 13:16:06 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../SDL2/SDL.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>

#define CONFIG_USE_DOUBLE 1

#if CONFIG_USE_DOUBLE

#if defined(cl_khr_fp64)  // Khronos extension available?
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#elif defined(cl_amd_fp64)  // AMD extension available?
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#endif

#endif // CONFIG_USE_DOUBLE

#if defined(DOUBLE_SUPPORT_AVAILABLE)

// double
typedef double real_t;
#define PI 3.14159265358979323846

#else

// float
typedef float real_t;
#define PI 3.14159265359f

#endif


# define MAX_SOURCE_SIZE (0x100000)
# define W_H		720.0
# define W_W		1080.0
# define C_Z		1.0
# define T_SPHERE	1
# define T_PLANE	2
# define T_CONE		3
# define T_CYLINDER	4
# define L_DOT	  1
# define L_DIR	  2

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

typedef struct		s_i2
{
	int				x;
	int				y;
}					t_i2;

typedef struct		s_p2
{
	real_t			x;
	real_t			y;
}					t_p2;

typedef struct		s_p3
{
	real_t			x;
	real_t			y;
	real_t			z;
}					t_p3;

typedef struct		s_q
{
	real_t			s;
	real_t			i;
	real_t			j;
	real_t			k;
}					t_q;

typedef struct		s_sdl_sequence
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Texture		*win_tex;
}					t_sdl_sequence;

typedef struct			s_ocl_sequence
{
	cl_platform_id		p_id;
	cl_device_id		d_id;
	cl_uint				num_dv;
	cl_uint				num_pl;
	cl_context			context;
	cl_command_queue	queue;
	cl_kernel			kernel;
}					t_ocl_sequence;

int				init_sdl_sequence(t_sdl_sequence *sq);
void			end_sdl(t_sdl_sequence sq);
void			init_ocl_sequence(t_ocl_sequence *sq);
cl_program		program_from_file(char *fname, t_ocl_sequence sq);
void			get_build_info(cl_program program, t_ocl_sequence sq, char* name);
void			prepare_kernel(t_ocl_sequence *sq);
void			execute_rt(t_ocl_sequence ocl_sq, t_sdl_sequence sdl_sq);

#endif
