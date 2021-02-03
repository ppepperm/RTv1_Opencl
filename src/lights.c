/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:13:03 by ppepperm          #+#    #+#             */
/*   Updated: 2020/07/23 17:13:05 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

void		inc_i(real_t cosa, t_light *lights, real_t *i, real_t pw)
{
    if (cosa < 0)
        cosa = 0;
    cosa = pow(cosa, pw);
    *i += cosa * lights->i;
}

t_rgb		colour_mult(t_rgb base, real_t k)
{
    real_t r;
    real_t g;
    real_t b;

    r = base.r * k;
    if (r > 255)
        r = 255;
    g = base.g * k;
    if (g > 255)
        g = 255;
    b = base.b * k;
    if (b > 255)
        b = 255;
    return (init_rgb((unsigned char)r,\
	(unsigned char)g, (unsigned char)b, 255));
}

void		prep_light(t_light *lights, t_p3 *light, t_light_arg arg)
{
    if (lights->type == L_DIR)
        *light = lights->data;
    else if (lights->type == L_DOT)
        *light = lin_comb(arg.inter, 1, lights->data, -1);
    normalize(light);
}

int			push_dot(t_scene *scene, char **nums)
{
    t_light *light;

    if (!(light = (t_light*)malloc(sizeof(t_light))))
        return (0);
    light->type = L_DOT;
    light->data = init_p3(ft_atoi(nums[1]),\
	ft_atoi(nums[2]), ft_atoi(nums[3]));
    light->i = ft_atoi(nums[4]) / 10.0;
    light->next = scene->lights;
    scene->lights = light;
    return (1);
}

int			push_dir(t_scene *scene, char **nums)
{
    t_light *light;

    if (!(light = (t_light*)malloc(sizeof(t_light))))
        return (0);
    light->type = L_DIR;
    light->data = init_p3(ft_atoi(nums[1]),\
	ft_atoi(nums[2]), ft_atoi(nums[3]));
    light->i = ft_atoi(nums[4]) / 10.0;
    light->next = scene->lights;
    scene->lights = light;
    return (1);
}
