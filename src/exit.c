/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:02:48 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/17 16:11:32 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	free_textures(t_map *map)
{
	int	i;

	i = -1;
	while (++i < TEX_NUM)
	{
		if (map->texture[i])
			free(map->texture[i]);
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		free_textures(map);
		if (map->F_color)
			free(map->F_color);
		if (map->C_color)
			free(map->C_color);
		free(map);
	}
	
	
}

void	error_exit(t_cub *cub, char *message)
{
	printf("Error: %s\n", message);
	free_map(cub->map);
	close_window(cub);
	exit(1);
}