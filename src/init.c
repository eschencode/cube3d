/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:17:05 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/15 16:32:34 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void init_movment(t_cub *cub)
{
	cub->m_flag = malloc(sizeof(t_flag));
	cub->m_flag->move_down = 0;
	cub->m_flag->look_left = 0;
	cub->m_flag->look_right = 0;
	cub->m_flag->move_up = 0;
	cub->m_flag->look_left = 0;
	cub->m_flag->look_right = 0;
	cub->m_flag->map_flag = 1;
}


/* init_var: The variables of struct cub are initialized.
	The initial values of dir and cam are taken from lodev's guide.*/
void	init_cub(t_cub *cub)
{
	init_movment(cub);
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
}

void	init_dir(t_cub *cub, char c)
{	
	//printf("direction facing: %c\n", c);
	/*this is the right code, but I had to change it, as in map->layout x and y are swapped
	if(c == 'N' || c == 'S')
	{
		cub->dir[0] = 1;
		if (c == 'N')
			cub->dir[0] = -1;
		cub->dir[1] = 0;
		cub->camplane[0] = 0;
		cub->camplane[1] = 0.66 * cub->dir[0];
	}
	if(c == 'E' || c == 'W')
	{
		cub->dir[0] = 0;
		cub->dir[1] = 1;
		if (c == 'W')
			cub->dir[1] = -1;
		cub->camplane[0] = -0.66 * cub->dir[1];
		cub->camplane[1] = 0;
	}*/
		if(c == 'N' || c == 'S')
	{
		cub->dir[1] = 1;
		if (c == 'N')
			cub->dir[1] = -1;
		cub->dir[0] = 0;
		cub->camplane[1] = 0;
		cub->camplane[0] = -0.66 * cub->dir[1];
	}
	if(c == 'E' || c == 'W')
	{
		cub->dir[1] = 0;
		cub->dir[0] = 1;
		if (c == 'W')
			cub->dir[0] = -1;
		cub->camplane[1] = -0.66 * cub->dir[0];
		cub->camplane[0] = 0;
	}
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