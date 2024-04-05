/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sketch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:20:28 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/05 16:43:21 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

//we get that position from map (where is NO etc.)
//in cub struct double	pos[2]; /* position vector of player: pos[0] = pos_x, pos[1] = pos_y*/

// we get that from map: which direction: N, O, S etc
//in cub struct double	dir[2]; /* direction of player: dir[0] = dir_x, dir[1] = dir_y*/

/* FOV is determined by ratio between length of direction and camera plane */
//in cub struct double	camplane[2]; /* camera plane of player, needs to be perpendicular to dir*/
//camplane[0] = 0;
//camplane[1] = 0.66; /* creates an FOV of 66° */

//frames: time difference can determine speed (how much move when key is pressed)
double	time = 0;
double	old_time = 0;

//gameloop/ raycasting loop
/* the raycasting loop goes through every vertical line (every x)
	and not every pixel, which makes it fast */
while (1)
{
	/* 1. calculate ray position and direction
			starts at position of player (pos)
			calculates for every x of the screen*/

	double	cam_x; /* x-coordinate of camera plane, current x-coordinate of screen*/
	//double	raydir[2];
	int	x;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		/* calculate ray position and direction */
		cam_x = 2 * x / SCREEN_WIDTH - 1;
		cub->raydir[0] = cub->dir[0] + cub->camplane[0] * cam_x;
		cub->raydir[1] = cub->dir[1] + cub->camplane[1] * cam_x;


	/* calculate where ray hits wall */	
	int	map[2]; // in which square on the map the ray is currently in
	map[0] = (int)cub->pos[0]; // it starts at the players position
	map[1] = (int)cub->pos[1];
	
	double	sidedist[2]; /* length of ray from current pos to next x- or y-side*/
	double	deltadist[2]; /* length of ray from one x- or y-side to next x- or y-side*/

	/* calculate length of ray from one x- or y-side to next
		to avoid undefined behaviour if ray_dir 0 (division through 0),
		it is divided in that case by infinity*/

	if (cub->raydir[0] != 0)
		deltadist[0] = abs(1 / cub->raydir[0]);
	else
		deltadist[0] = abs(1 / INFINITY);
	if (cub->raydir[1] != 0)
		deltadist[1] = abs(1 / cub->raydir[1]);
	else
		deltadist[1] = abs(1 / INFINITY);

	/* calculate step and initial sidedist*/

	int	step[2]; /* into what direction to step: either -1 or 1 */
	int	hit;	/* hit = 0; if a wall was hit, hit = 1 */
	int	side;	/* which wall was hit? x (NS) or y (EW)*/

	/* if raydir is negative, step is -1 (left for x (i = 0) or up for y (i = 1))
		otherwise step is 1 (right for x, down for y)*/
	int	i;
	i = 0;
	while (i < 2)
	{
		if (cub->raydir[i] < 0)
		{
			step[i] = -1;
			sidedist[i] = (cub->pos[i] - map[i]) * deltadist[i];
		}
		else
		{
			step[i] = 1;
			sidedist[i] = (map[i] + 1.0 - cub->pos[i]) * deltadist[i];
		}
		i++;
	}

		