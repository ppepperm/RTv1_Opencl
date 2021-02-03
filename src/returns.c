/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:24:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/07/23 16:24:40 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

void		ft_error(char *l)
{
    if (l)
        free(l);
    write(1, "invalid file\n", 13);
    exit(EXIT_FAILURE);
}

void		*return_sphere(char **nums)
{
    t_sphere *sphere;

    if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
        return (NULL);
    sphere->pos = init_p3(ft_atoi(nums[1]), ft_atoi(nums[2]), ft_atoi(nums[3]));
    sphere->r = ft_atoi(nums[4]);
    return ((void*)sphere);
}

void		*return_plane(char **nums)
{
    t_plane *plane;

    if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
        return (NULL);
    plane->dir = init_p3(ft_atoi(nums[1]), ft_atoi(nums[2]), ft_atoi(nums[3]));
    plane->d = ft_atoi(nums[4]);
    return ((void*)plane);
}

void		*return_cone(char **nums)
{
    t_cone *cone;

    if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
        return (NULL);
    cone->pos = init_p3(ft_atoi(nums[1]), ft_atoi(nums[2]), ft_atoi(nums[3]));
    cone->r = ft_atoi(nums[4]);
    cone->c = ft_atoi(nums[5]);
    return ((void*)cone);
}

void		*return_cylinder(char **nums)
{
    t_cylinder *cylinder;

    if (!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
        return (NULL);
    cylinder->pos = init_p3(ft_atoi(nums[1]),\
	ft_atoi(nums[2]), ft_atoi(nums[3]));
    cylinder->r = ft_atoi(nums[4]);
    return ((void*)cylinder);
}
