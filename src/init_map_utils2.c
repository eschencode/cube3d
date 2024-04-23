/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:42:46 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/23 16:44:39 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void	allocate_layout(t_cub *cube)
{
	int	i;

	cube->map->layout = malloc(cube->map->nlines * sizeof(char *));
	i = -1;
	while (++i < cube->map->nlines)
		cube->map->layout[i] = NULL;
	if (!cube->map->layout)
		error_exit(cube, "malloc failed", NULL);
	i = 0;
	while (i < cube->map->nlines)
	{
		cube->map->layout[i] = malloc((cube->map->max_line_len +1) \
		* sizeof(char));
		if (!cube->map->layout[i])
			error_exit(cube, "malloc failed", NULL);
		i++;
	}
}

void	save_texture(t_cub *cube, char *line, int i)
{
	int		j;

	j = i + 2;
	while (line[j] == ' ')
		j++;
	if (line[i] == 'N' && line[i + 1] == 'O' && !cube->map->NO)
		cube->map->NO = moded_strdup(line + j);
	if (line[i] == 'S' && line[i + 1] == 'O' && !cube->map->SO)
		cube->map->SO = moded_strdup(line + j);
	if (line[i] == 'W' && line[i + 1] == 'E' && !cube->map->WE)
		cube->map->WE = moded_strdup(line + j);
	if (line[i] == 'E' && line[i + 1] == 'A' && !cube->map->EA)
		cube->map->EA = moded_strdup(line + j);
}

void	ft_fill_layout(t_cub *cube, char *line, int current_line)
{
	int	startposcount;
	int	x;

	startposcount = 0;
	x = 0;

	if (cube == NULL || cube->map == NULL || \
	cube->map->layout[current_line] == NULL) 
	{
		printf("error");
		return ;
	}
	while (line[x] != '\n' && line[x] != '\0' && cube->map->max_line_len > x)
	{
		cube->map->layout[current_line][x] = line[x];
		x++;
	}
	cube->map->layout[current_line][x] = '\0';
}



int	check_valid_file(t_cub *cube, char *pf)
{
	int	i;
	int	fd;

	i = 0;

	while (pf[i + 4] != '\0')
		i++;
	if (pf[i] != '.' || pf[i + 1] != 'c' || pf[i + 2] != 'u' || pf[i +3] != 'b')
		error_exit(cube, "wrong file format. Only '.cub' extension valid", pf);
	fd = open(pf, O_RDONLY);
	if (fd == -1)
		error_exit(cube, "could not open file", pf);
	return (0);
}

void	set_map_data_to_null(t_map *map)
{
	int	i;

	map->layout = NULL;
	map->C_color = NULL;
	map->F_color = NULL;
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	i = -1;
	while (++i < TEX_NUM)
		map->texture[i] = NULL;
}
