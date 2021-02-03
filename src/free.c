/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:09:20 by ppepperm          #+#    #+#             */
/*   Updated: 2020/06/27 17:09:22 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

void	free_nums(char **nums)
{
    int i;

    i = 0;
    while (nums[i])
    {
        free(nums[i]);
        i++;
    }
    free(nums);
}

void	free_scene(t_scene *scene)
{
    t_object	*o_ptr;
    t_light		*l_ptr;

    scene->chosen = NULL;
    while (scene->objects)
    {
        free(scene->objects->data);
        o_ptr = scene->objects->next;
        free(scene->objects);
        scene->objects = o_ptr;
    }
    while (scene->lights)
    {
        l_ptr = scene->lights->next;
        free(scene->lights);
        scene->lights = l_ptr;
    }
}

void	read_malloc_exit(t_scene *scene)
{
    free_scene(scene);
    ft_putstr("malloc error while reading\n");
    exit(EXIT_FAILURE);
}

void	draw_exit(t_scene *scene, t_sdl_sequence sq)
{
    free_scene(scene);
    end_sdl(sq);
    ft_putstr("malloc error while drawing\n");
    exit(EXIT_FAILURE);
}