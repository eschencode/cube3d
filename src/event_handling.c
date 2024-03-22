/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:11:00 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/22 16:48:58 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int test_map[MAP_WIDTH][MAP_HEIGHT] = {{1,1,1,1,1,1,1,1,1,1}, 
			{1,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,1},
			{1,0,1,1,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,1,0,0,1},
			{1,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1}};

/* x_close: This function closes the window with a MLX function. */

int	x_close(t_cub *cub)
{
	close_window(cub);
	return (0);
}

/* deal_key: This function handles key events (when the keyboard is pressed).
	If ESC (0xff1b) is pressed, the window is closed.
	 */

int	deal_key(int key, t_cub *cub)
{
	if (key == KEY_ESC)
	{
		close_window(cub);
		return (0);
	}
	if (key == KEY_DOWN)
	{
		mlx_clear_window(cub->mlx, cub->win);
		render_image(cub, cub->img);
	}
	if (key == KEY_UP)
	{
	}
	printf("test_map[%i][%i] = %i\n", cub->pos[0], cub->pos[1], test_map[cub->pos[0]][cub->pos[1]]);
	if (key == KEY_A)
		move_left(cub);
	else if (key == KEY_D)
		move_right(cub);
	else if (key == KEY_W)
		move_up(cub);
	else if (key == KEY_S)
		move_down(cub);
	else
		printf("key code: %i\n", key);
	render_map(cub, cub->img, set_right(), set_down());
	return (0);
}