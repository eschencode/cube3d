/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:20:42 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/09 12:19:04 by tstahlhu         ###   ########.fr       */
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