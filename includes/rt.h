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

typedef struct		s_ray
{
	t_p3			pos;
	t_p3			dir;
}					t_ray;

typedef struct		s_light_arg
{
	t_p3			norm;
	t_p3			inter;
}					t_light_arg;

typedef struct		s_sphere
{
	t_p3			pos;
	double			r;
}					t_sphere;

typedef struct		s_plane
{
	t_p3			dir;
	double			d;
}					t_plane;

typedef struct		s_cone
{
	t_p3			pos;
	double			r;
	double			c;
}					t_cone;

typedef struct		s_cylinder
{
	t_p3			pos;
	double			r;
}					t_cylinder;

typedef struct		s_camera
{
	t_p3			pos;
	t_p3			x_dir;
	t_p3			y_dir;
	t_p3			z_dir;
}					t_camera;

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_rgb;

typedef struct		s_transform
{
	t_p3			x_dir;
	t_p3			y_dir;
	t_p3			z_dir;
}					t_transform;

typedef struct		s_light
{
	unsigned char	type;
	t_p3			data;
	double			i;
	struct s_light	*next;
}					t_light;

typedef struct		s_object
{
	void			*data;
	unsigned char	type;
	double			reflect;
	t_rgb			colour;
	t_transform		t;
	t_transform		i_t;
	t_p3			pos;
	t_p2			(*intersect) (t_ray, struct s_object);
	double			(*light_funk) (t_light*, struct s_object, t_ray, double);
	struct s_object	*head;
	struct s_object	*next;
}					t_object;

typedef struct		s_scene
{
	t_camera		camera;
	t_object		*objects;
	t_light			*lights;
	t_object		*chosen;
}					t_scene;

typedef struct		s_sdl_sequence
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Texture		*win_tex;
}					t_sdl_sequence;

typedef struct		s_p_data
{
	t_scene			scene;
	unsigned char	*win_buff;
	int				pitch;
	int				coll;
}					t_p_data;

int			init_sdl_sequence(t_sdl_sequence *sq);
void		end_sdl(t_sdl_sequence sq);

#endif
