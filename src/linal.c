/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:16:48 by ppepperm          #+#    #+#             */
/*   Updated: 2020/06/21 21:16:50 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

t_p3	lin_comb(t_p3 a, real_t k1, t_p3 b, real_t k2)
{
    t_p3 ret;

    ret.x = k1 * a.x + k2 * b.x;
    ret.y = k1 * a.y + k2 * b.y;
    ret.z = k1 * a.z + k2 * b.z;
    return (ret);
}

real_t	sc_mult(t_p3 a, t_p3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

real_t	min(real_t a, real_t b)
{
    if (a > b)
        return (b);
    return (a);
}

void	normalize(t_p3 *vec)
{
    real_t abs;

    abs = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    vec->x /= abs;
    vec->y /= abs;
    vec->z /= abs;
}

t_p3	return_norm_cone(t_cone cone, t_p3 inter)
{
    t_p3	ret;
    real_t y;

    ret = inter;
    y = sqrt(ret.x * ret.x + ret.z * ret.z);
    y = y * cone.r / cone.c;
    if (ret.y < 0)
        ret.y = y;
    else
        ret.y = -y;
    return (ret);
}