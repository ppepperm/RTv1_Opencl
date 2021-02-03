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

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


#define CONFIG_USE_real_t 1

#if CONFIG_USE_real_t

#if defined(cl_khr_fp64)  // Khronos extension available?
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define real_t_SUPPORT_AVAILABLE
#elif defined(cl_amd_fp64)  // AMD extension available?
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#define real_t_SUPPORT_AVAILABLE
#endif

#endif // CONFIG_USE_real_t

#if defined(real_t_SUPPORT_AVAILABLE)

// real_t
typedef real_t real_t;
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
    real_t			r;
}					t_sphere;

typedef struct		s_plane
{
    t_p3			dir;
    real_t			d;
}					t_plane;

typedef struct		s_cone
{
    t_p3			pos;
    real_t			r;
    real_t			c;
}					t_cone;

typedef struct		s_cylinder
{
    t_p3			pos;
    real_t			r;
}					t_cylinder;

typedef struct		s_camera
{
    t_p3			pos;
    t_p3			x_dir;
    t_p3			y_dir;
    t_p3			z_dir;
}					t_camera;

typedef struct		s_light
{
    unsigned char	type;
    t_p3			data;
    real_t 			i;
    struct s_light	*next;
}					t_light;

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

typedef struct		s_object
{
    unsigned char	type;
    void			*data;
    real_t 			reflect;
    t_rgb			colour;
    t_transform		t;
    t_transform		i_t;
    t_p3			pos;
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


int				init_sdl_sequence(t_sdl_sequence *sq);
void			end_sdl(t_sdl_sequence sq);
void			init_ocl_sequence(t_ocl_sequence *sq);
cl_program		program_from_file(char *fname, t_ocl_sequence sq);
void			get_build_info(cl_program program, t_ocl_sequence sq, char* name);
void			prepare_kernel(t_ocl_sequence *sq);
void			execute_rt(t_ocl_sequence ocl_sq, t_sdl_sequence sdl_sq);

real_t          abs_p3(t_p3 vect);
t_p2		    init_p2(real_t x, real_t y);
t_p3		    init_p3(real_t x, real_t y, real_t z);
t_camera	    init_camera(t_p3 pos, t_p3 x, t_p3 y, t_p3 z);
t_transform	    init_transform(t_p3 x_dir, t_p3 y_dir, t_p3 z_dir);
t_rgb		    init_rgb(unsigned char r, unsigned char g,
                      unsigned char b, unsigned char a);

void		    ft_error(char *l);
void		    *return_sphere(char **nums);
void		    *return_plane(char **nums);
void		    *return_cone(char **nums);
void		    *return_cylinder(char **nums);

void	        free_nums(char **nums);
void	        free_scene(t_scene *scene);
void	        read_malloc_exit(t_scene *scene);
void	        draw_exit(t_scene *scene, t_sdl_sequence sq);

int             push_sphere(t_scene *scene, char **nums);
int             push_plane(t_scene *scene, char **nums);
int             push_cone(t_scene *scene, char **nums);
int             push_cylinder(t_scene *scene, char **nums);

t_transform	    i_transform(t_transform t);
t_p3		    transform_pos(t_p3 pos, t_transform t, t_p3 t_pos);
t_p3		    transform_dir(t_p3 dir, t_transform t);
t_ray		    ray_transform(t_ray ray, t_transform t, t_p3 pos);

t_p3	        lin_comb(t_p3 a, real_t k1, t_p3 b, real_t k2);
real_t 	        sc_mult(t_p3 a, t_p3 b);
real_t 	        min(real_t a, real_t b);
void	        normalize(t_p3 *vec);
t_p3	        return_norm_cone(t_cone cone, t_p3 inter);

void			inc_i(real_t cosa, t_light *lights, real_t *i, real_t pw);
t_rgb			colour_mult(t_rgb base, real_t k);
void			prep_light(t_light *lights, t_p3 *light, t_light_arg arg);
int				push_dot(t_scene *scene, char **nums);
int				push_dir(t_scene *scene, char **nums);

t_scene		    read_scene(char *fname);

#endif
