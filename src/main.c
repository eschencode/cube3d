/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:16 by tstahlhu          #+#    #+#             */
/*   Updated: 2024/03/21 11:32:49 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


int main(int argc, char **argv)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if(cub == NULL)
		return(-1);
	initmap(argv[1], cub);
	//open_window(&cub);
	free_map_data(cub);
	free(cub);
}
