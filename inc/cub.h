#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include <stdio.h>
# include <math.h>

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480
# define NAME	"cub3d"




typedef struct cub
{
	void	*mlx;
	void	*win;
	int		map_width; /* is calculated in map parsing*/
	int		map_height;
	double	pos[2];	/* players position (N) found in map: pos[0] = x, pos[1] = y*/
	double	dir[2]; /* direction player faces: dir[0] = x, dir[1] = y*/
	double	cam[2]; /* camera plane: part you see on the screen */
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