/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:20:28 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:36 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../inc/cub.h"

/* the raycasting loop goes through every vertical line (every x)
	and not every pixel, which makes it fast */

	/* 1. calculate ray position and direction
			starts at position of player (pos)
			calculates for every x of the screen*/

	int x;
	double	cam_x; /* x-coordinate of camera plane, current x-coordinate of screen*/
	double	w;// was soll w sein?
	double	ray_dir[2];

	x = 0;
	
		/* calculate ray position and direction */
		cam_x = 2 * x / w - 1;
		ray_dir[0] = cub->dir[0] + cub->plane[0] * cam_x;
		ray_dir[1] = cub->dir[1] + cub->plane[1] * cam_x;
	
	int	map[2]; // in which square on the map the ray is currently in

//	map[0] = cub->player[0]; // it starts at the players position
//	map[1] = cub->player[1];
	
	double	side_dist[2]; /* length of ray from current pos to next x- or y-side*/
	double	delta_dist[2]; /* length of ray from one x- or y-side to next x- or y-side*/

	/* calculate length of ray from one x- or y-side to next
		to avoid undefined behaviour if ray_dir 0 (division through 0),
		it is divided in that case by infinity*/

	if (ray_dir[0] != 0)
		delta_dist[0] = abs(1 / ray_dir[0]);
	else
		delta_dist[0] = abs(1 / __DBL_HAS_INFINITY__);
	if (ray_dir[1] != 0)
		delta_dist[1] = abs(1 / ray_dir[1]);
	else
		delta_dist[1] = abs(1 / __DBL_HAS_INFINITY__);
		