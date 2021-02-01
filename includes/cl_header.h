#ifndef CL_HEADER
#define CL_HEADER 1
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
typedef double2 real2_t;
typedef double3 real3_t;
typedef double4 real4_t;
typedef double8 real8_t;
typedef double16 real16_t;
#define PI 3.14159265358979323846
#else
// float
typedef float real_t;
typedef float2 real2_t;
typedef float3 real3_t;
typedef float4 real4_t;
typedef float8 real8_t;
typedef float16 real16_t;
#define PI 3.14159265359f
#endif

# define W_H		720.0
# define W_W		1080.0
# define C_Z		1.0

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

real_t      abs_p3(t_p3 vect);
t_p2		init_p2(real_t x, real_t y);
t_p3		init_p3(real_t x, real_t y, real_t z);
t_camera	init_camera(t_p3 pos, t_p3 x, t_p3 y, t_p3 z);
t_transform	init_transform(t_p3 x_dir, t_p3 y_dir, t_p3 z_dir);
t_rgb		init_rgb(unsigned char r, unsigned char g,
                    unsigned char b, unsigned char a);

t_transform	i_transform(t_transform t);
t_p3		transform_pos(t_p3 pos, t_transform t, t_p3 t_pos);
t_p3		transform_dir(t_p3 dir, t_transform t);
t_ray		ray_transform(t_ray ray, t_transform t, t_p3 pos);

t_p3	lin_comb(t_p3 a, real_t k1, t_p3 b, real_t k2);
real_t 	sc_mult(t_p3 a, t_p3 b);
real_t 	ft_min(real_t a, real_t b);
void	ft_normalize(t_p3 *vec);
t_p3	return_norm_cone(t_cone cone, t_p3 inter);

t_p2	intersect_sphere(t_ray ray, t_object object);
t_p2	intersect_plane(t_ray ray, t_object object);
t_p2	intersect_cone(t_ray ray, t_object object);
t_p2	intersect_cylinder(t_ray ray, t_object object);

#endif