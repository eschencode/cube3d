/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:25:49 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/04 14:14:42 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


/* only works properly if SCREEN_WIDTH is a multiple of MAP_WIDTH * SQUARE_SIZE*/

int	set_right()
{
	return (SCREEN_WIDTH / SQUARE_SIZE - MAP_WIDTH);
}

int	set_down()
{
	return (SCREEN_HEIGHT / SQUARE_SIZE - MAP_HEIGHT);
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

/* render_map: 
	The size of the map is set by defining the SQUARE_SIZE in the header file. Feel free to change it,
		but be aware that the total size of the map needs to fit into the screen, otherwise the program will segfault.
	By setting start_x and start_y, you define where to display the map.
	If start_x = 0, the map will be displayed at the left side of the screen.
	If start_y = 0, the map will be displayed at the top of the screen.
	For displaying it at the right side of the screen, call the function set_right() instead of start_x.
	For displaying it at the bottom of the screen, call the function set_down() instead of start_x.*/

void	render_map(t_cub *cub, t_img *img, int start_x, int start_y)
{
	int	x;
	int	y;
	//printf("sy %dsx %d\n",start_y,start_x);
	y = start_y;
	while (y < (start_y + cub->map->nlines))
	{
		x = start_x;
		while (x < (start_x + cub->map->max_line_len))
		{
			if (cub->map->layout[y - start_y][x - start_x] == '1')
				render_square(cub, x, y, WHITE);
			else if (cub->map->layout[y - start_y][x - start_x] == '0')
				render_square(cub, x, y, BLACK);
			x++;
		}
		y++;
	}
	//render_player(cub, (cub->pos[0] + start_x), (cub->pos[1] + start_y));
	//printf("x: %f %f y: %f\n", cub->pos[0], (cub->pos[0] + start_x), (cub->pos[1] + start_y));
	render_square(cub, (cub->pos[0] + start_x), (cub->pos[1] + start_y), YELLOW);
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
}
