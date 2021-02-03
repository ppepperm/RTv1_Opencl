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

unsigned char *serialize_objects(t_object *objects, unsigned char *serialization_map);

unsigned char *serialize_ligts(t_light *lights, unsigned char *serialization_map);