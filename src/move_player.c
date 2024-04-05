/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:59 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/05 15:17:46 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void	move_left(t_cub *cub)
{
	if (cub->map->layout[(int)cub->pos[1]][(int)cub->pos[0] - 1] == '0')
		cub->pos[0] -= 1;
}

void	move_right(t_cub *cub)
{
	if (cub->map->layout[(int)cub->pos[1]][(int)cub->pos[0] + 1] == '0')
		cub->pos[0] += 1;
}

void	move_down(t_cub *cub)
{
	//printf("strat %d %d",cub->pos[0],cub->pos[1]);
	//printf("pos %c\n",cub->map->layout[cub->pos[0]][cub->pos[1] + 1]);
	if (cub->map->layout[(int)cub->pos[1] + 1][(int)cub->pos[0]] == '0')
		cub->pos[1] += 1;
}

void	move_up(t_cub *cub)
{
	if (cub->map->layout[(int)cub->pos[1] - 1][(int)cub->pos[0]] == '0')//0 = x 1 = y
		cub->pos[1] -= 1;
}

/*void	render_player(t_cub *cub, float x, float y)
{
	int i;
	int	j;

	j = y;
	while (i <= y + 8)
	{

	}
	
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
}*/