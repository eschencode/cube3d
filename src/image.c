/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:20 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/22 11:48:46 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* render_square: renders one square of the map pixel by pixel
	px = pixel on x-axis of screen
	py = pixel on y-axis of screen
	x = square coordinate on x-axis of map
	y = square coordinate on y-axis of map
	px_end and py_end are the last pixel on the screen of the next square*/
	
/* fills in whole screen
void	render_square(t_cub *cub, int x, int y, unsigned int color)
{
	int	px_start;
	int py_start;
	int	px_end;
	int	py_end;
	int	px;
	int	py;

	px_start = x * (SCREEN_WIDTH / MAP_WIDTH);
	py_start = y * (SCREEN_HEIGHT / MAP_HEIGHT);
	px_end = (x + 1) * (SCREEN_WIDTH / MAP_WIDTH);
	py_end = (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT);
	py = py_start;
	while (py <= py_end)
	{
		px = px_start;
		while (px <= px_end)
		{
			if (px == px_start || px == px_end || py == py_start || py == py_end)
			{
				if (color == WHITE)
					my_pixel_put(cub->img, px, py, BLACK);
				else if (color == BLACK)
					my_pixel_put(cub->img, px, py, WHITE);
			}
			else
				my_pixel_put(cub->img, px, py, color);
			px++;
		}
		py++;
	}
}*/

void	render_square(t_cub *cub, int x, int y, unsigned int color)
{
	int	px_start;
	int py_start;
	int	px_end;
	int	py_end;
	int	px;
	int	py;

	px_start = x * SQUARE_SIZE;
	py_start = y * SQUARE_SIZE;
	px_end = (x + 1) * SQUARE_SIZE;
	py_end = (y + 1) * SQUARE_SIZE;
	py = py_start;
	while (py <= py_end)
	{
		px = px_start;
		while (px <= px_end)
		{
			if (px == px_start || px == px_end || py == py_start || py == py_end)
			{
				if (color == WHITE)
					my_pixel_put(cub->img, px, py, BLACK);
				else if (color == BLACK)
					my_pixel_put(cub->img, px, py, WHITE);
			}
			else
				my_pixel_put(cub->img, px, py, color);
			px++;
		}
		py++;
	}
}

void	render_image(t_cub *cub, t_img *img)
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

void	render_map(t_cub *cub, t_img *img)
{
	int	x;
	int	y;
	
	y = -1;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			if (test_map[x][y] == 1)
				render_square(cub, x, y, WHITE);
			else if (test_map[x][y] == 0)
				render_square(cub, x, y, BLACK);
		}
	}	
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
}

void	render_player(t_cub *cub)
{
	printf("player's position is: %i, %i\n", cub->pos[0], cub->pos[1]);
	mlx_clear_window(cub->mlx, cub->win);
	render_map(cub, cub->img);
	render_square(cub, cub->pos[0], cub->pos[1], YELLOW);
}