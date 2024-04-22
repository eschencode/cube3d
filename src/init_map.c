/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:43:07 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/22 18:25:20 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






#include "../inc/cub.h"

#include <stdbool.h>

void	count_lines(t_cub *cube, char *path_to_map)
{
	int		line_counter;
	char	*line;
	int		fd;
	int		i;

	line_counter = 0;
	i = 0;
	fd = open(path_to_map, O_RDONLY);
	while (line != NULL)
	{
		while ((line[i] == ' ') && line[i] != '\n')
			i++;
		if (line[i] == '1' || line[i] == '2')
		{
			while (line[i] != '\n' && line[i] != '\0')
				i++;
			line_counter++;
			if (i > cube->map->max_line_len)
				cube->map->max_line_len = i;
		}
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	cube->map->nlines = line_counter;
}


void	set_map_values(t_cub *cube, int i, char *line)
{
	if (line[i] == 'F' )
		ft_setcolor_f(cube, line, i);
	if (line[i] == 'C')
		ft_setcolor_c(cube, line, i);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		save_texture(cube, line, i);
}


int	init_map_contents(char *path_to_map, t_cub *cube, int fd)
{
	char	*line;
	int		i;
	int		c_l;

	i = 0;
	c_l = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_empty(line) == 1)
		{
			while (line[i] == ' ')
				i++;
			set_map_values(cube, i, line);
			if ((line[i] == '1' || line[i] == '2') && c_l < cube->map->nlines)
			{
				ft_fill_layout(cube, line, c_l);
				c_l++;
			}
		}
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
}

int	initmap(char *path_to_map, t_cub *cube)
{
	int		fd;

	allocate_map_data(cube);
	cube->map->map_valid_flag = 0;
	count_lines(cube, path_to_map);
	allocate_layout(cube);
	fd = open(path_to_map, O_RDONLY);
	if (check_valid_file(cube, path_to_map) == -1)
		return (-1);
	init_map_contents(path_to_map, cube, fd);
	if (map_check(cube) == -1)
		return (-1);
	return (0);
}

