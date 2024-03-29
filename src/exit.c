/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:02:48 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/20 17:12:38 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void	error_exit(t_cub *cub, char *message)
{
	printf("Error: %s\n", message);
	close_window(cub);
	exit(1);
}