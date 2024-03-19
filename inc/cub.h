#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include <stdio.h>
# include <math.h>

# define WIDTH	1024
# define HEIGHT	640
# define NAME	"cub3d"




typedef struct cub
{
	void	*mlx;
	void	*win;
	
}			t_cub;

/* init.c: variables are initialized*/
void	init_cub(t_cub *cub);

/*	window.c: window management */
void	open_window(t_cub *cub);

/* event_handlings.c: management of key and mouse events */
int	deal_key(int key, t_cub *cub);
int	x_close(t_cub *cub);

/* exit.c: handles clean exit */
void	error_exit(t_cub *cub, char *message);
void	close_window(t_cub *cub);

#endif