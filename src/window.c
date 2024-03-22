/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:54:13 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/22 16:13:48 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	open_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit(cub, "connection to X-Server failed to establish");
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, NAME);
	if (!cub->win)
		error_exit(cub, "new window failed to open");
	init_img(cub);
	render_map(cub, cub->img, set_right(), set_down());
	//render_player(cub);
	mlx_key_hook(cub->win, deal_key, cub); // key events
	mlx_hook(cub->win, 17, 0L, x_close, cub); //to close window by clicking cross
	mlx_loop(cub->mlx);
}

void	close_window(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->img)
	{
		mlx_destroy_image(cub->mlx, cub->img->img);
		free(cub->img);
	}
	if (cub->win && cub->mlx)
	{
		mlx_clear_window(cub->mlx, cub->win);
		mlx_destroy_window(cub->mlx, cub->win);
	}
	if (cub->mlx)
	{
		mlx_loop_end(cub->mlx);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	exit (0);
}