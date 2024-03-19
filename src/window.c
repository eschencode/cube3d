/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:54:13 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/19 13:21:12 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	open_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit(cub, "connection to X-Server failed to establish");
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, NAME);
	if (!cub->win)
		error_exit(cub, "new window failed to open");
	/*here insert image*/
	mlx_key_hook(cub->win, deal_key, cub);
	mlx_hook(cub->win, 17, 0L, x_close, cub);
	mlx_loop(cub->mlx);
}