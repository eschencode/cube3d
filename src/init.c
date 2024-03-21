/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:17:05 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/21 11:34:52 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* init_var: The variables of struct cub are initialized.
	The initial values of dir and cam are taken from lodev's guide.*/
void	init_cub(t_cub *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
	cub->dir[0] = -1;
	cub->dir[1] = 0;
	cub->plane[0] = 0;
	cub->plane[1] = 0.66;
}