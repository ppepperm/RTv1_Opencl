#include "../includes/cl_header.h"

t_p2		init_p2(real_t x, real_t y)
{
    t_p2 ret;

    ret.x = x;
    ret.y = y;
    return (ret);
}

t_p3		init_p3(real_t x, real_t y, real_t z)
{
    t_p3 ret;

    ret.x = x;
    ret.y = y;
    ret.z = z;
    return (ret);
}

t_camera	init_camera(t_p3 pos, t_p3 x, t_p3 y, t_p3 z)
{
    t_camera camera;

    camera.pos = pos;
    camera.x_dir = x;
    camera.y_dir = y;
    camera.z_dir = z;
    return (camera);
}

t_transform	init_transform(t_p3 x_dir, t_p3 y_dir, t_p3 z_dir)
{
    t_transform ret;

    ret.x_dir = x_dir;
    ret.y_dir = y_dir;
    ret.z_dir = z_dir;
    return (ret);
}

t_rgb		init_rgb(unsigned char r, unsigned char g,\
unsigned char b, unsigned char a)
{
    t_rgb ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;
    ret.a = a;
    return (ret);
}
