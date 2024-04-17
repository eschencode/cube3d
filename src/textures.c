/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:53:02 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/17 14:12:45 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* to know which wall was hit:
	side distinguishes between NS and EW wall
	step[side] could distinguish between NE and SW*/

void	malloc_textures(t_cub *cub, t_map *map)
{
	map->texture_buf[TEX_N] = malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
	if (!map->texture_buf[TEX_N])
		error_exit(cub, "malloc texture failed");
}

void	read_in_textures(t_cub *cub, t_map *map)
{
	int	img_width;
	int	img_height;
	int	x;
	int	y;
	void	*temp;
	int		*address;

	malloc_textures(cub, map);
	init_img_xpm(cub, &img_width, &img_height);
	//temp = mlx_xpm_file_to_image(cub->mlx, map->NO, &img_width, &img_height);
	//cub->img_tex.img = temp;
	//error handling
//	address = (int *) mlx_get_data_addr(cub->img_tex.img, &cub->img_tex.bpp, &cub->img_tex.line_length, &cub->img_tex.endian);
//	cub->img_tex.addr = address;
	//error handling
	y = -1;
	while(++y < img_height)
	{
		x = -1;
		while (++x < img_width)
		{
			map->texture_buf[TEX_N][img_height * y + x] = cub->img_tex.addr[img_height * y + x];
		}
	}
	mlx_destroy_image(cub->mlx, cub->img_tex.img);
	free(cub->img);
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