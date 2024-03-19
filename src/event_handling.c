/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:11:00 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/19 13:21:41 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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
	mlx_clear_window(cub->mlx, cub->win);
	return (0);
}