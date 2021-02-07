/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:52:33 by ppepperm          #+#    #+#             */
/*   Updated: 2020/08/04 12:52:35 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cl_rt.h"

t_s_object init_s_object(t_object object)
{
    t_s_object ret;

    ret.type = object.type;
    ret.t = object.t;
    ret.pos = object.pos;
    ret.i_t = object.i_t;
    ret.colour = object.colour;
    ret.reflect = object.reflect;
    return ret;
}


void   serialize_scene(t_scene *scene)
{
    t_light         *l_ptr;
    t_object        *obj_ptr;
    void            *ptr;
    unsigned char   *map_ptr;
    t_types         types;

    if(!(scene->s_obj))
        scene->s_obj = (unsigned char*)malloc(scene->o_size);
    if(!(scene->s_lht))
        scene->s_lht = (t_light*)malloc(sizeof(t_light)*scene->l_count);
    if(!(scene->obj_map))
        scene->obj_map = (unsigned char*)malloc(scene->o_count);
    obj_ptr = scene->objects;
    ptr = (void*)scene->s_obj;
    map_ptr = scene->obj_map;
    while (obj_ptr)
    {
        types.s_object = (t_s_object*)ptr;
        *types.s_object = init_s_object(*obj_ptr);
        types.s_object++;
        if (obj_ptr->type == T_SPHERE)
        {
            types.sphere = (t_sphere*)types.s_object;
            *types.sphere = *((t_sphere*)obj_ptr->data);
            types.sphere++;
            ptr = (void*)types.sphere;
            *map_ptr = T_SPHERE;
            map_ptr++;
        }
        else if (obj_ptr->type == T_CYLINDER)
        {
            types.cylinder = (t_cylinder *)types.s_object;
            *types.cylinder = *((t_cylinder *)obj_ptr->data);
            types.cylinder++;
            ptr = (void*)types.cylinder;
            *map_ptr = T_CYLINDER;
            map_ptr++;
        }
        else if (obj_ptr->type == T_PLANE)
        {
            types.plane = (t_plane *)types.s_object;
            *types.plane = *((t_plane *)obj_ptr->data);
            types.plane++;
            ptr = (void*)types.plane;
            *map_ptr = T_PLANE;
            map_ptr++;
        }
        else if (obj_ptr->type == T_CONE)
        {
            types.cone = (t_cone*)types.s_object;
            *types.cone = *((t_cone*)obj_ptr->data);
            types.cone++;
            ptr = (void*)types.cone;
            *map_ptr = T_CONE;
            map_ptr++;
        }
        obj_ptr = obj_ptr->next;
    }
    ptr = (void*)scene->s_lht;
    l_ptr = scene->lights;
    while (l_ptr)
    {
        types.light = (t_light*)ptr;
        *types.light = *l_ptr;
        types.light++;
        ptr = (void*)types.light;
        l_ptr = l_ptr->next;
    }
}