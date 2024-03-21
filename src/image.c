/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:20 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/21 11:48:39 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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
}

void	draw_image(t_cub *cub, t_img *img)
{
	int	x;
	int y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			my_pixel_put(cub->img, x, y, GREY);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
}

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}