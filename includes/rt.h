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
	double			x;
	double			y;
}					t_p2;

typedef struct		s_p3
{
	double			x;
	double			y;
	double			z;
}					t_p3;

typedef struct		s_q
{
	double			s;
	double			i;
	double			j;
	double			k;
}					t_q;

typedef struct		s_sdl_sequence
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Texture		*win_tex;
}					t_sdl_sequence;

typedef				s_ocl_sequence
{
	cl_platform_id		p_id;
	cl_device_id		d_id;
	cl_uint				num_dv;
	cl_uint				num_pl;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_kernel			kernel;
}					t_ocl_sequence;

int			init_sdl_sequence(t_sdl_sequence *sq);
void		end_sdl(t_sdl_sequence sq);

#endif
