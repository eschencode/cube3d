/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:16 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/04/05 15:52:17 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (printf("No map given. Choose one from ./maps/ \n"), 0);
	init_cub(&cub);
	if (argc > 1)
		initmap(argv[1], &cub);
	open_window(&cub);
	free_map_data(&cub);
}
