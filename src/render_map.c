/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:25:49 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/09 12:15:49 by tstahlhu         ###   ########.fr       */
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


void ft_draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_pixel_put(img, x0, y0, color);  // Assuming you have a function to put a pixel on the image
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
void render_player(t_cub *cub, int start_x ,int start_y)
{
	int i = 0;
	int x_pixel = (start_x * 25) + (25 * cub->pos[0]) + 12.5;//layout pos to pixel pos 
	int y_pixel = (start_y * 25) + (25 * cub->pos[1]) + 12.5;
	//printf("ppixle %d y %d\n",x_pixel, y_pixel);
	int end_x_pixel = x_pixel + (cub->dir[0] * 10);
	int end_y_pixel = y_pixel + (cub->dir[1] * 10);
	my_pixel_put(cub->img, x_pixel + i, y_pixel + i, YELLOW);
	ft_draw_line(cub->img,x_pixel,y_pixel,end_x_pixel,end_y_pixel,YELLOW);
		
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
			else if (cub->map->layout[y - start_y][x - start_x] != '1')
				render_square(cub, x, y, BLACK);
			x++;
		}
		y++;
	}
	render_player(cub, start_x, start_y);
	//printf("strtpos x%f y%f\n",cub->pos[0],cub->pos[1]);
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
}
