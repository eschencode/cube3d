/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:20:42 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/10 16:27:21 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* get_time: calculates elapsed time since time_zero in milliseconds
	gettimeofday() gets the system's clock time in elapsed seconds and 
		microseconds since 00:00:00, January 1, 1970 (Unix Epoch)
	to calculate milliseconds accurately, seconds and microseconds are added
		to receive milliseconds */

double	get_time(double time_zero)
{
	struct timeval	tv;
	double			time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mill - time_zero);
}

/* conv_rgb_hex: converts rgb color to the unsigned int equivalent 
	of the color in hexadecimal */

unsigned int	conv_rgb_hex(t_rgb *rgb)
{
	return (rgb->r << 16 | rgb->g << 8 | rgb->b);
	/*unsigned int	color;

	color = rgb->b;
	color += (rgb->g % 16) * pow(16, 2);
	if (rgb->g > 16)
		color += (rgb->g / 16) * pow(16, 3);
	color += (rgb->r % 16) * pow(16, 4);
	if (rgb->r > 16)
		color += (rgb->r / 16) * pow(16, 5);
	return (color);*/
}