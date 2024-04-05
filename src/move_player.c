/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:59 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/05 17:06:56 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void rotateDirection(t_cub *cub, double Dangle)//Dangle = angleindegrees
{
	double angleInRadians;
	double newDirX;
	double newDirY;
	
	angleInRadians = Dangle * M_PI / 180;// Convert the angle from degrees to radians
	newDirX = cub->dir[0] * cos(angleInRadians) - cub->dir[1] * sin(angleInRadians);
	newDirY = cub->dir[0] * sin(angleInRadians) + cub->dir[1] * cos(angleInRadians);
	cub->dir[0] = newDirX;
	cub->dir[1] = newDirY;
}

void move(t_cub *cub,double distance)
{
	// Calculate new position
    double new_x = cub->pos[0] + distance * cub->dir[0];
    double new_y = cub->pos[1] + distance * cub->dir[1];
	//add checks here 
	cub->pos[0] = new_x;
    cub->pos[1] = new_y;
}

void	move_left(t_cub *cub)//more kinda look left 
{
	rotateDirection(cub, 10);
	printf("new looking x = %f, y = %f\n",cub->dir[0],cub->dir[1]);
}

void move_right(t_cub *cub) // more like look right
{
    rotateDirection(cub, -10);
    printf("new looking x = %f, y = %f\n",cub->dir[0],cub->dir[1]);
}

void	move_down(t_cub *cub)
{
	move(cub,-1);
	printf("npos x%f,y%f\n",cub->pos[0],cub->pos[1]);
}

void	move_up(t_cub *cub)
{
	move(cub,1);
	printf("npos x%f,y%f\n",cub->pos[0],cub->pos[1]);
}

