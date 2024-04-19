/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:02:48 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/19 13:32:45 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	free_textures(t_map *map)
{
	int	i;

	i = -1;
	while (++i < (TEX_NUM))
	{
		if (map->texture[i])
			free(map->texture[i]);
	}
}

/*void	free_layout(t_map *map)
{
	
}*/

void free_map_data(t_map *map, t_cub *cub)
{
	int i = 0;
	if(map)
	{
		free_textures(map);
    	if(map->NO != NULL)
		{
            free(map->NO);
            map->NO = NULL;
        }
		if(map->EA != NULL)
		{
            free(map->EA);
            map->EA = NULL;
        }
		if(map->WE != NULL)
		{
            free(map->WE);
            map->WE = NULL;
        }
        if(map->SO != NULL)
		{
            free(map->SO);
            map->SO = NULL;
        }
		if(map->C_color != NULL)
			free(map->C_color);
		if(map->F_color != NULL)
			free(map->F_color);
		if(map->layout)
		{
			while(map->nlines > i)
			{
				if(map->layout[i] != NULL)
				{
					free(map->layout[i]);
					map->layout[i] = NULL;
				}
				i++;
			}
			free(map->layout);
			map->layout = NULL;
		}
		free(map);
    	map = NULL;
		
	}
}

void	error_exit(t_cub *cub, char *message)
{
	printf("Error: %s\n", message);
	free_map_data(cub->map, cub);
	close_window(cub);
	exit(1);
}