/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:20:28 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/08 15:46:43 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* 1. calculate ray position and direction
		starts at position of player (pos)
		calculates for every x of the screen
	2. calculate length of ray from one x- or y-side to next
		to avoid undefined behaviour if ray_dir 0 (division through 0),
		it is divided in that case by infinity*/

void	calculate_rays(t_cub *cub, int x)
{
	double	cam_x; /* x-coordinate of camera plane, current x-coordinate of screen*/
	int		i;

	i = 0;
	while (i < 2) // One time for x [0], one time for y [1]
	{
		//1.
		cam_x = 2 * x / (double)SCREEN_WIDTH - 1;
		//cam_x = -cam_x; //Robin fragen
		cub->raydir[i] = cub->dir[i] + cub->camplane[i] * cam_x;
		//2.
		if (cub->raydir[i] != 0)
			cub->deltadist[i] = fabs(1 / cub->raydir[i]);
		else
			cub->deltadist[i] = 1e30; //Robin fragen
			//cub->deltadist[i] = fabs(1 / INFINITY);
		i++;
	}
}

/* calculates where ray hits wall */	
int	calculate_wall_hit(t_cub *cub)
{	
	int	step[2]; /* into what direction to step: either -1 or 1 */
	int	hit;	/* hit = 0; if a wall was hit, hit = 1 */
	int	side;	/* which wall was hit? x (NS) or y (EW)*/
	int	map[2]; // in which square on the map the ray is currently in

	map[0] = (int)cub->pos[0]; // it starts at the players position
	map[1] = (int)cub->pos[1];
	
	/* calculate step and initial sidedist*/
	/* if raydir is negative, step is -1 (left for x (i = 0) or up for y (i = 1))
		otherwise step is 1 (right for x, down for y)*/
	int	i;
	i = 0;
	while (i < 2)
	{
		if (cub->raydir[i] < 0)
		{
			step[i] = -1;
			cub->sidedist[i] = (cub->pos[i] - map[i]) * cub->deltadist[i];
		}
		else
		{
			step[i] = 1;
			cub->sidedist[i] = (map[i] + 1.0 - cub->pos[i]) * cub->deltadist[i];
		}
		i++;
	}
	hit = 0;
	while (hit == 0)
	{
		if (cub->sidedist[0] < cub->sidedist[1])
			i = 0;
		else
			i = 1;
		cub->sidedist[i] += cub->deltadist[i];
		map[i] += step[i];
		side = i;
		if (cub->map->layout[map[1]][map[0]] != 48)
			hit = 1;
	}
	return (side);
}

/* draw vertical line on screen */
void	render_vline(t_cub *cub, int wallheight, int side, int x)
{
	int		startwall;
	int		endwall;
	int		color;
	int		y;

	startwall = -wallheight / 2 + SCREEN_HEIGHT / 2;
	if (startwall < 0)
		startwall = 0;
	endwall = wallheight / 2 + SCREEN_HEIGHT / 2;
	if (endwall >= SCREEN_HEIGHT || endwall < 0)
		endwall = SCREEN_HEIGHT - 1;
	color = LAVENDER;
	if (side == 1)
		color = color / 2; //gives x and y side different brightness
	y = startwall;
	while (y < endwall)
	{
		my_pixel_put(cub->img, x, y, color);
		y++;
	}
}

/* raycasting: this function calculates the representation of the 2D in 3D
	This calculation is based on https://lodev.org/cgtutor/raycasting.html
	Lodev's calculation relies solely on vectors and triangles (no pi or 
		fisheye correction needed)
	Variables used, shortly explained:
		- pos[2]; position vector of player: pos[0] = pos_x, pos[1] = pos_y
		- dir[2]; direction player is facing: dir[0] = dir_x, dir[1] = dir_y
		We get pos and dir from map (N, E, W, S).
		The FOV (Field of View) is determined by ratio between length of 
			direction and camera plane
		- camplane[2]; camera plane of player, needs to be perpendicular to dir
			it is set to [0, 0.66] which creates perfect FOV of 66°
		- deltadist[2]; length of ray from one square x- or y-side to next x- or y-side
	The raycasting loop goes through every vertical line (every x) and 
		not every pixel, which makes it fast.
			*/

int	raycasting(t_cub *cub)
{
	int	x;
	int	side;
	double	walldist; /* perpendicular distance from camera plane to wall */
	int		wallheight; /* height of line drawn on screen, i.e. height of wall*/

	x = 0;
	printf("dir: %f, %f\n", cub->dir[0], cub->dir[1]);
	while (x < SCREEN_WIDTH)
	{
		calculate_rays(cub, x);/* calculate ray position and direction */
		side = calculate_wall_hit(cub);
		if (side != 0 && side != 1)
			printf("ERROR: side value wrong, see raycasting\n");
		walldist = (cub->sidedist[side] - cub->deltadist[side]);
		wallheight = (int) (SCREEN_HEIGHT / walldist); //calculate height of walls
		render_vline(cub, wallheight, side, x);
		// time frame
		// speed: move speed and rotation speed
		x++;
	}
	return (0);
}

