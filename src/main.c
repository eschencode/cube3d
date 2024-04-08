/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:16 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/08 17:01:16 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"



int render_frame(void *param)
{
	t_cub *cub = (t_cub *)param;
	if(cub->m_flag->move_up == 1)
	{
		move_up(cub);
	}
	if(cub->m_flag->move_down == 1)
	{
		move_down(cub);
	}
	if(cub->m_flag->move_left == 1)
	{
		move_left(cub);
	}
	if(cub->m_flag->move_right == 1)
	{
		move_right(cub);
	}
	//add render raytracing here later
	render_map(cub, cub->img, set_right(), set_down());
	return(0);
}

void game_loop(t_cub *cub)
{
	printf("ADADA");
	mlx_hook(cub->win, 2, 1L<<0, key_press, cub); // key press events
    mlx_hook(cub->win, 3, 1L<<1, key_release, cub); // key release events
	mlx_hook(cub->win, 17, 0L, x_close, cub); //to close window by clicking cross
	mlx_loop_hook(cub->mlx, render_frame, cub); // render a frame
	mlx_loop(cub->mlx);
}


int main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if (argc > 1)
		initmap(argv[1], &cub);
	open_window(&cub);
	printf("adada");
	game_loop(&cub);
	free_map_data(&cub);
}
