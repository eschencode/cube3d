/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:53:02 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/19 16:02:08 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* to know which wall was hit:
	side distinguishes between NS and EW wall
	step[side] could distinguish between NE and SW*/

void	malloc_textures(t_cub *cub, t_map *map, int tex)
{
	map->texture[tex] = malloc(sizeof(int) * map->tex_width[tex] * map->tex_height[tex]);
	if (!map->texture[tex])
		error_exit(cub, "malloc texture failed", NULL);
//	map->texture[tex] = NULL;
}


void	init_img_xpm(t_cub *cub, t_map *map, int tex)
{
	int			*addr;
	char		*texture_path;

	if (tex == (TEX_NUM - 1))
		texture_path = TEX_EXIT_PATH;
	else if (tex == TEX_N)
		texture_path = map->NO;
	else if (tex == TEX_S)
		texture_path = map->SO;
	else if (tex == TEX_W)
		texture_path = map->WE;
	else
		texture_path = map->EA;
	cub->img_tex.img = mlx_xpm_file_to_image(cub->mlx, texture_path, &map->tex_width[tex], &map->tex_height[tex]);
	if (!cub->img_tex.img)
		error_exit(cub, "image could not be initialized", texture_path);
	if (map->tex_width[tex] < 1 || map->tex_width[tex] > 6000)
		error_exit(cub, "at least 1 texture image is too big or small", texture_path);
	if (map->tex_height[tex] < 1 || map->tex_height[tex] > 6000)
		error_exit(cub, "at least 1 texture image is too big or small", texture_path);	
	addr = (int *) mlx_get_data_addr(cub->img_tex.img, &cub->img_tex.bpp, &cub->img_tex.line_length, &cub->img_tex.endian);
	cub->img_tex.addr = addr;
	if (!cub->img_tex.addr)
		error_exit(cub, "image information could not be retrieved", texture_path);
}

/* the number of textures varies depending on whether there is an 
	exit door in the map ('2') or not. TEX_NUM is the max nb of 
	textures available. It is 5 (4 wall textures + 1 exit texture).
	All texture pointers are set to NULL (see init.c).
	We start at the end of the textures array with the copying.
	If there is a exit texture, we start at position 4
	(5 - 1 + 1 & -1 at the start of the loop), 
	if not at position 3 (5 - 1 + 0 & -1)*/

void	read_in_textures(t_cub *cub, t_map *map)
{
	int	x;
	int	y;
	void	*temp;
	int		*address;
	int		tex;

	tex = TEX_NUM -1 + cub->exit_flag;
	while (--tex >= 0)
	{
		init_img_xpm(cub, map, tex);
		malloc_textures(cub, map, tex);
		y = -1;
		while(++y < map->tex_height[tex])
		{
			x = -1;
			while (++x < map->tex_width[tex])
			{
				map->texture[tex][map->tex_height[tex] * y + x] = cub->img_tex.addr[map->tex_height[tex] * y + x];
			}
		}
		mlx_destroy_image(cub->mlx, cub->img_tex.img);
	}
}

/* choose_texture: returns the texture for wall which was hit
	side = 0 -> South or North side
	side = 1 -> East or West side
	step = -1 -> North or West
	step = 1 -> South or East
	(imagine a coordinate system)
	if no texture matches (which should not be the case)
		it returns 0 which corresponds to the north texture */

int	choose_texture(t_cub *cub, int wall_type)
{
	int	tex;

	tex = 0;
	if (wall_type == '2')
		tex = TEX_EXIT;
	else if (cub->side == 1 && cub->step[cub->side] == -1)
		tex = TEX_N;
	else if (cub->side == 1 && cub->step[cub->side] == 1)
		tex = TEX_S;
	else if (cub->side == 0 && cub->step[cub->side] == 1)
		tex = TEX_E;
	else if (cub->side == 0 && cub->step[cub->side] == -1)
		tex = TEX_W;
	return (tex);
}