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

int main(void)
{
	t_sdl_sequence sdl_sq;
	t_ocl_sequence ocl_sq;

	init_sdl_sequence(&sdl_sq);
	init_ocl_sequence(&ocl_sq);
	prepare_kernel(&ocl_sq);
	execute_rt(ocl_sq, sdl_sq);
	SDL_RenderCopy(sdl_sq.renderer, sdl_sq.win_tex, NULL, NULL);
	while (!(SDL_PollEvent(&(sdl_sq.event)) && sdl_sq.event.type == SDL_QUIT))
    {
		SDL_RenderCopy(sdl_sq.renderer, sdl_sq.win_tex, NULL, NULL);
        SDL_RenderPresent(sdl_sq.renderer);
    }
	end_sdl(sdl_sq);
}