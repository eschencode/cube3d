/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:25:49 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/04 16:19:50 by leschenb         ###   ########.fr       */
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



void render_line(t_cub *cub, int x1, int y1, int x2, int y2, unsigned int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        my_pixel_put(cub->img, x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}
#define TRIANGLE_SIZE 6
//#define M_PI 3,1415926
void fill_triangle(t_cub *cub, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color)
{
    float invslope1 = (x2 - x1) / (float)(y2 - y1);
    float invslope2 = (x3 - x1) / (float)(y3 - y1);

    float curx1 = x1;
    float curx2 = x1;

    int scanlineY = y1;
    while (scanlineY <= y2)
    {
        render_line(cub, (int)curx1, scanlineY, (int)curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
        scanlineY++;
    }
}

void render_player(t_cub *cub, int x, int y, unsigned int color)
{
    // Calculate the center of the player's position
    int center_x = x * SQUARE_SIZE + SQUARE_SIZE / 2;
    int center_y = y * SQUARE_SIZE + SQUARE_SIZE / 2;
 // Convert the direction from degrees to radians
    double dir_rad = cub->dir[0] * M_PI / 180.0;

    // Calculate the points of the triangle
    int point1_x = center_x + (int)(TRIANGLE_SIZE * cos(dir_rad));
    int point1_y = center_y + (int)(TRIANGLE_SIZE * sin(dir_rad));
    int point2_x = center_x + (int)(TRIANGLE_SIZE * cos(dir_rad + 2 * M_PI / 3));
    int point2_y = center_y + (int)(TRIANGLE_SIZE * sin(dir_rad + 2 * M_PI / 3));
    int point3_x = center_x + (int)(TRIANGLE_SIZE * cos(dir_rad - 2 * M_PI / 3));
    int point3_y = center_y + (int)(TRIANGLE_SIZE * sin(dir_rad - 2 * M_PI / 3));
	// Render the triangle
	fill_triangle(cub, point1_x, point1_y, point2_x, point2_y, point3_x, point3_y, color);
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
	printf("\n %d \n ",cub->dir[0]);

	render_player(cub, (cub->pos[0] + start_x), (cub->pos[1] + start_y), YELLOW);
	//printf("x: %f %f y: %f\n", cub->pos[0], (cub->pos[0] + start_x), (cub->pos[1] + start_y));
	//render_square(cub, (cub->pos[0] + start_x), (cub->pos[1] + start_y), YELLOW);
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
}
