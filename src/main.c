/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:16 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/22 17:32:08 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"



int render_frame(void *param)
{
	t_cub *cub = (t_cub *)param;
	if (cub->exit_found > 0)
	{
		exit_screen(cub);
		return (0);
	}
	if(cub->m_flag.move_up == 1)
		move_up(cub);
	if(cub->m_flag.move_down == 1)
		move_down(cub);
	if(cub->m_flag.move_left == 1)
		move_left(cub);
	if(cub->m_flag.move_right == 1)
		move_right(cub);
	if(cub->m_flag.look_left == 1)
		look_left(cub);
	if(cub->m_flag.look_right == 1)
		look_right(cub);
	render_3d_view(cub);
	if(cub->m_flag.map_flag == 1) 
		render_minimap(cub, cub->img, set_right(cub), set_down(cub));
	//printf("timer %ld\n",ft_get_time(cub));
	print_timer(cub);
	mlx_clear_window(cub->mlx, cub->win);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	return(0);
}

void game_loop(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L<<0, key_press, cub); // key press events
    mlx_hook(cub->win, 3, 1L<<1, key_release, cub); // key release events
	mlx_hook(cub->win, 17, 0L, x_close, cub); //to close window by clicking cross
	mlx_loop_hook(cub->mlx, render_frame, cub); // render a frame
	mlx_loop(cub->mlx);
}


int main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (printf("No map given. Choose one from ./maps/ \n"), 0);
	if (argc > 2)
		return (printf("Too many arguments. 1 argument required.\n"), 0);
	init_cub(&cub);
	if (initmap(argv[1], &cub) == -1)
		error_exit(&cub, "could not initialize map", NULL);
	open_window(&cub);
	start_timer(&cub);
	game_loop(&cub);
}
