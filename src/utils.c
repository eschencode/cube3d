/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:20:42 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/24 11:38:39 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/* conv_rgb_hex: converts rgb color to the unsigned int equivalent 
	of the color in hexadecimal */

unsigned int	conv_rgb_hex(t_rgb *rgb)
{
	return (rgb->r << 16 | rgb->g << 8 | rgb->b);
}

/*
	line_length = amount of bytes taken by one row of image
			= image_width * (bpp / 8)*/

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}
