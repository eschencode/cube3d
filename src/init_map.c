/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:43:07 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/23 13:29:09 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub.h"
#include <stdbool.h>

void	process_line(t_cub *cube, char *line, int *line_counter,
		int *max_line_len)
{
	int	i;

	i = 0;
	while ((line[i] == ' ') && line[i] != '\n')
	{
		i++;
	}
	if (line[i] == '1' || line[i] == '2')
	{
		while (line[i] != '\n' && line[i] != '\0')
			i++;
		(*line_counter)++;
		if (i > *max_line_len)
			*max_line_len = i;
	}
}

void	count_lines(t_cub *cube, char *path_to_map, int fd)
{
	int		line_counter;
	int		max_line_len;
	char	*line;

	line_counter = 0;
	max_line_len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(cube, line, &line_counter, &max_line_len);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	cube->map->max_line_len = max_line_len;
	cube->map->nlines = line_counter;
}


void	set_map_values(t_cub *cube, int i, char *line)
{
	if (line[i] == 'F')
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
	int	fd;

	allocate_map_data(cube);
	cube->map->map_valid_flag = 0;
	fd = open(path_to_map, O_RDONLY);
	count_lines(cube, path_to_map, fd);
	allocate_layout(cube);
	if (check_valid_file(cube, path_to_map) == -1)
		return (-1);
	init_map_contents(path_to_map, cube, fd);
	if (map_check(cube) == -1)
		return (-1);
	return (0);
}
