/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:36:01 by leschenb          #+#    #+#             */
/*   Updated: 2024/04/23 14:33:11 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	check_textures(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i + 4] != '\0')
		i++;
	if (str[i] != '.' || str[i + 1] != 'x' || str[i + 2] != 'p' || \
	str[i + 3] != 'm')
		return (-1);

	if (open(str, O_RDONLY) == -1)
		return (-1);
	return (0);
}

int	checkcolor(t_cub *cube)
{
	if (cube->map->C_color == NULL || cube->map->F_color == NULL)
		return (-1);
	if (cube->map->C_color->b > 255 || cube->map->C_color->b < 0
		|| cube->map->C_color->r > 255 || cube->map->C_color->r < 0
		|| cube->map->C_color->g > 255 || cube->map->C_color->g < 0)
	{
		cube->map->map_valid_flag = -1;
		return (-1);
	}
	if (cube->map->F_color->b > 255 || cube->map->F_color->b < 0
		|| cube->map->F_color->r > 255 || cube->map->F_color->r < 0
		|| cube->map->F_color->g > 255 || cube->map->F_color->g < 0)
	{
		cube->map->map_valid_flag = -1;
		return (-1);
	}
	else
		return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}
