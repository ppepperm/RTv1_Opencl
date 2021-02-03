/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:39:29 by ppepperm          #+#    #+#             */
/*   Updated: 2020/07/23 13:39:31 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

t_transform	i_transform(t_transform t)
{
    t_transform	inv;
    real_t 		det;

    det = t.x_dir.x * (t.y_dir.y * t.z_dir.z - t.y_dir.z * t.z_dir.y) -\
	t.y_dir.x * (t.x_dir.y * t.z_dir.z - t.x_dir.z * t.z_dir.y) +\
	t.z_dir.x * (t.x_dir.y * t.y_dir.z - t.x_dir.z * t.y_dir.y);
    inv.x_dir = init_p3((t.y_dir.y * t.z_dir.z - t.y_dir.z * t.z_dir.y),\
	-(t.x_dir.y * t.z_dir.z - t.x_dir.z * t.z_dir.y),\
	(t.x_dir.y * t.y_dir.z - t.x_dir.z * t.y_dir.y));
    inv.x_dir = lin_comb(inv.x_dir, 1 / det, init_p3(0, 0, 0), 0);
    inv.y_dir = init_p3(-(t.y_dir.x * t.z_dir.z - t.y_dir.z * t.z_dir.x),\
	(t.x_dir.x * t.z_dir.z - t.x_dir.z * t.z_dir.x),\
	-(t.x_dir.x * t.y_dir.z - t.x_dir.z * t.y_dir.x));
    inv.y_dir = lin_comb(inv.y_dir, 1 / det, init_p3(0, 0, 0), 0);
    inv.z_dir = init_p3((t.y_dir.x * t.z_dir.y - t.y_dir.y * t.z_dir.x),\
	-(t.x_dir.x * t.z_dir.y - t.x_dir.y * t.z_dir.x),\
	(t.x_dir.x * t.y_dir.y - t.x_dir.y * t.y_dir.x));
    inv.z_dir = lin_comb(inv.z_dir, 1 / det, init_p3(0, 0, 0), 0);
    return (inv);
}

t_p3		transform_pos(t_p3 pos, t_transform t, t_p3 t_pos)
{
    t_p3 new_pos;

    pos = lin_comb(pos, 1, t_pos, -1);
    new_pos = lin_comb(t.x_dir, pos.x, t.y_dir, pos.y);
    new_pos = lin_comb(new_pos, 1, t.z_dir, pos.z);
    return (new_pos);
}

t_p3		transform_dir(t_p3 dir, t_transform t)
{
    t_p3 new_dir;

    new_dir = lin_comb(t.x_dir, dir.x, t.y_dir, dir.y);
    new_dir = lin_comb(new_dir, 1, t.z_dir, dir.z);
    return (new_dir);
}

t_ray		ray_transform(t_ray ray, t_transform t, t_p3 pos)
{
    t_ray new_ray;

    new_ray.pos = transform_pos(ray.pos, t, pos);
    new_ray.dir = transform_dir(ray.dir, t);
    return (new_ray);
}