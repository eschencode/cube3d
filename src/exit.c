/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:02:48 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/10 17:43:24 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	free_textures(t_map *map)
{
	int	i;

	i = -1;
	while (++i < TEX_NUM)
	{
		if (map->texture_buf[i])
			free(map->texture_buf[i]);
	}
}

void	error_exit(t_cub *cub, char *message)
{
	printf("Error: %s\n", message);
	free_textures(cub->map);
	close_window(cub);
	exit(1);
}