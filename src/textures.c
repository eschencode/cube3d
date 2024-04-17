/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:53:02 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/17 16:29:19 by tstahlhu         ###   ########.fr       */
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
		error_exit(cub, "malloc texture failed");
//	map->texture[tex] = NULL;
}

void	read_in_textures(t_cub *cub, t_map *map)
{
	int	x;
	int	y;
	void	*temp;
	int		*address;
	int		tex;

	tex = -1;
	while (++tex < TEX_NUM)
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
		printf("texture %i read in\n", tex);
	}
}

int	choose_texture(t_cub *cub)
{
	int	tex;

	tex = 0;
	if (cub->side == 1 && cub->step[cub->side] == -1)
		tex = TEX_N;
	if (cub->side == 1 && cub->step[cub->side] == 1)
		tex = TEX_S;
	if (cub->side == 0 && cub->step[cub->side] == -1)
		tex = TEX_E;
	if (cub->side == 0 && cub->step[cub->side] == 1)
		tex = TEX_W;
	return (tex);
}