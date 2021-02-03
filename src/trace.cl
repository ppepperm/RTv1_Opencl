#include "../includes/cl_header.h"

t_ray			init_ray(t_p3 pos, t_p3 dir)
{
    t_ray ret;

    ret.dir = dir;
    ret.pos = pos;
    return (ret);
}

t_ray			get_ray(t_camera camera, real_t x, real_t y)
{
    t_ray	ray;
    t_p3	tmp;

    ray.pos = camera.pos;
    tmp = lin_comb(camera.x_dir, x / 1000, camera.y_dir, y / 1000);
    ray.dir = lin_comb(tmp, 1, camera.z_dir, C_Z);
    ft_normalize(&ray.dir);
    return (ray);
}

