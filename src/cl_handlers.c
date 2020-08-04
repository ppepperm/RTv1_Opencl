/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:34:02 by ppepperm          #+#    #+#             */
/*   Updated: 2020/08/04 14:34:06 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_ocl_sequence	init_ocl_sequence(void)
{
	t_ocl_squence	sq;
	cl_int			ret;

	sq.p_id = NULL;
	sq.d_id = NULL;
	ret = clGetPlatformsIDs(1, &(sq.p_id), &(sq.num_pl));
	ret = clGetDeviceIDs(sq.p_id, CL_DEVICE_TYPE_GPU, 1, &(sq.d_id), &(sq.num_dv));
	sq.context = clCreateContext(NULL, 1, &(sq.))


}