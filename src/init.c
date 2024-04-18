/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:17:05 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/18 17:46:38 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void init_movement(t_cub *cub)
{
	cub->m_flag.move_down = 0;
	cub->m_flag.move_left = 0;
	cub->m_flag.move_right = 0;
	cub->m_flag.move_up = 0;
	cub->m_flag.look_left = 0;
	cub->m_flag.look_right = 0;
	cub->m_flag.map_flag = 1;
}


/* init_var: The variables of struct cub are initialized.
	The initial values of dir and cam are taken from lodev's guide.*/
void	init_cub(t_cub *cub)
{
	init_movement(cub);
	cub->exit_flag = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
}

/* Variables shortly explained:
	1. dir[2]; direction player is facing: dir[0] = dir_x, dir[1] = dir_y
		We get pos and dir from map (N, E, W, S).
	2. camplane[2]; camera plane of player, needs to be perpendicular to dir
		The FOV (Field of View) is determined by ratio between length of 
			direction and camera plane; camplane is set to [0, 0.66] 
			which creates perfect FOV of 66°*/

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


void	init_img(t_cub *cub, int width, int height)
{
	t_img	*img;
	
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		error_exit(cub, "malloc image failed");
	img = cub->img;
	img->img = mlx_new_image(cub->mlx, width, height);
	if (!img->img)
		error_exit(cub, "image could not be initialized");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	if (!img->addr)
		error_exit(cub, "image information could not be retrieved");
}

void	init_img_xpm(t_cub *cub, t_map *map, int tex)
{
	int			*addr;
	char		*texture_path;

	if (tex == TEX_N)
		texture_path = map->NO;
	else if (tex == TEX_S)
		texture_path = map->SO;
	else if (tex == TEX_W)
		texture_path = map->WE;
	else
		texture_path = map->EA;
	printf("tex: %i tex_path: %s", tex, texture_path);
	cub->img_tex.img = mlx_xpm_file_to_image(cub->mlx, texture_path, &map->tex_width[tex], &map->tex_height[tex]);
	if (!cub->img_tex.img)
		error_exit(cub, "image could not be initialized");
	if (map->tex_width[tex] < 1 || map->tex_width[tex] > 6000)
		error_exit(cub, "at least 1 texture image is too big or small");
	if (map->tex_height[tex] < 1 || map->tex_height[tex] > 6000)
		error_exit(cub, "at least 1 texture image is too big or small");	
	addr = (int *) mlx_get_data_addr(cub->img_tex.img, &cub->img_tex.bpp, &cub->img_tex.line_length, &cub->img_tex.endian);
	cub->img_tex.addr = addr;
	if (!cub->img_tex.addr)
		error_exit(cub, "image information could not be retrieved");
}