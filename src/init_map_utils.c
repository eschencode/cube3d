/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:58:41 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:47 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	allocate_map_data(t_cub *cub)
{
	t_map	*map;

	cub->map = malloc(sizeof(t_map));
	set_map_data_to_null(cub->map);
	if (!cub->map)
		error_exit(cub, "malloc failed", NULL);
	map = cub->map;
	map->max_line_len = 0;
	map->nlines = 0;
	map->F_color = (t_rgb *)malloc(sizeof(t_rgb));
	if (!map->F_color)
		error_exit(cub, "malloc failed", NULL);
	map->C_color = (t_rgb *)malloc(sizeof(t_rgb));
	if (!map->C_color)
		error_exit(cub, "malloc failed", NULL);
}

int	ft_empty(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (1);
		i++;
	}
	return (-1);
}

char	*moded_strdup(const char *s)
{
	int		i;
	int		len;
	char	*nstr;

	i = 0;
	len = 0;
	while (s[len] != '\0' && s[len] != '\n')
		len++;
	nstr = malloc(1 + len * sizeof(char));
	if (nstr == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		nstr[i] = s[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

void	ft_setcolor_f(t_cub *cube, char *line, int i)
{
	char	*newline;
	char	**ar;

	while (line[i] == 'F' || line[i] == ' ')
		i++;
	newline = ft_strdup(line + i);
	ar = ft_split(newline, ',');
	if (ar[0] && ar[1] && ar[2])
	{
		cube->map->F_color->r = ft_atoi(ar[0]);
		cube->map->F_color->g = ft_atoi(ar[1]);
		cube->map->F_color->b = ft_atoi(ar[2]);
	}
	if (ar != NULL)
	{
		free(ar[0]);
		free(ar[1]);
		free(ar[2]);
		free(ar);
	}
	if (newline != NULL)
		free(newline);
}

void	ft_setcolor_c(t_cub *cube, char *line, int i)
{
	char	*newline;
	char	**ar;

	while (line[i] == 'C' || line[i] == ' ')
		i++;
	newline = ft_strdup(line + i);
	ar = ft_split(newline, ',');
	if (ar[0] && ar[1] && ar[2])
	{
		cube->map->C_color->r = ft_atoi(ar[0]);
		cube->map->C_color->g = ft_atoi(ar[1]);
		cube->map->C_color->b = ft_atoi(ar[2]);
	}
	if (ar != NULL)
	{
		free(ar[0]);
		free(ar[1]);
		free(ar[2]);
		free(ar);
	}
	if (newline != NULL)
		free(newline);
}
