/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:49:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/07/15 15:57:19 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

static void	remember_head(t_scene scene)
{
    t_object *head;

    head = scene.objects;
    while (scene.objects)
    {
        scene.objects->head = head;
        scene.objects = scene.objects->next;
    }
}

static void	read_obj(int fd, t_scene *scene)
{
    int			error;
    char		*str;
    char		**nums;

    error = 1;
    while (get_next_line(fd, &str))
    {
        nums = ft_strsplit(str, ';');
        if (!ft_strcmp(nums[0], "sphere"))
            error &= push_sphere(scene, nums);
        else if (!ft_strcmp(nums[0], "plane"))
            error &= push_plane(scene, nums);
        else if (!ft_strcmp(nums[0], "cone"))
            error &= push_cone(scene, nums);
        else if (!ft_strcmp(nums[0], "cylinder"))
            error &= push_cylinder(scene, nums);
        else if (!ft_strcmp(nums[0], "dot_source"))
            error &= push_dot(scene, nums);
        else if (!ft_strcmp(nums[0], "dir_source"))
            error &= push_dir(scene, nums);
        free_nums(nums);
        free(str);
        if (!error)
            read_malloc_exit(scene);
    }
}

static void get_size(t_scene *scene)
{
    t_object    *o_ptr;
    t_light     *l_ptr;

    scene->o_count = 0;
    scene->l_count = 0;
    scene->o_size = 0;
    o_ptr = scene->objects;
    l_ptr = scene->lights;
    while (o_ptr)
    {
        scene->o_count += 1;
        scene->o_size += sizeof(t_s_object);
        if (o_ptr->type == T_SPHERE)
            scene->o_size += sizeof(t_sphere);
        else if (o_ptr->type == T_CONE)
            scene->o_size += sizeof(t_cone);
        else if (o_ptr->type == T_CYLINDER)
            scene->o_size += sizeof(t_cylinder);
        else if (o_ptr->type == T_PLANE)
            scene->o_size += sizeof(t_plane);
        o_ptr = o_ptr->next;
    }
    while (l_ptr)
    {
        scene->l_count += 1;
        l_ptr = l_ptr->next;
    }
}

t_scene		read_scene(char *fname)
{
    t_scene	scene;
    int		fd;

    fd = open(fname, O_RDWR);
    scene.camera = init_camera(init_p3(0, 0, 0),\
	init_p3(1, 0, 0), init_p3(0, 1, 0), init_p3(0, 0, 1));
    scene.objects = NULL;
    scene.lights = NULL;
    scene.chosen = NULL;
    scene.s_obj = NULL;
    scene.s_lht = NULL;
    scene.obj_map = NULL;
    read_obj(fd, &scene);
    remember_head(scene);
    get_size(&scene);
    return (scene);
}