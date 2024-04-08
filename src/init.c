/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:17:05 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/08 13:21:34 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void init_movment(t_cub *cub)
{
	cub->m_flag = malloc(sizeof(t_flag));
	cub->m_flag->move_down = 0;
	cub->m_flag->move_left = 0;
	cub->m_flag->move_right = 0;
	cub->m_flag->move_up = 0;
}


/* init_var: The variables of struct cub are initialized.
	The initial values of dir and cam are taken from lodev's guide.*/
void	init_cub(t_cub *cub)
{
	init_movment(cub);
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
	cub->pos[0] = 5.0;
	cub->pos[1] = 5.0;
	cub->dir[0] = -1;
	cub->dir[1] = 0;
	cub->plane[0] = 0;
	cub->plane[1] = 0.66;
	
}


void	init_img(t_cub *cub)
{
	t_img	*img;
	
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		error_exit(cub, "malloc image failed");
	img = cub->img;
	img->img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img->img)
		error_exit(cub, "image could not be initialized");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	if (!img->addr)
		error_exit(cub, "image information could not be retrieved");
	//draw_image(cub, cub->img);
}