#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
#include <stdio.h>
#include <fcntl.h>      // for open
#include <unistd.h>     // for close, read, write
#include <stdlib.h>     // for malloc, free, exit
#include <string.h>     // for strerror
#include <errno.h>      // for perror
#include <math.h>       // for math library functions

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480
# define NAME	"cub3d"


typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_point
{
	int x;
	int y;
}t_point;

typedef struct s_map
{
	char **layout;
	int x_len;
	int y_len;
	int map_valid_flag;
	t_rgb *F_color;
	t_rgb *C_color;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
}t_map;


typedef struct cub
{
	t_map *map;
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


//map parsing
void initmap(char *path_to_map, t_cub *cube);
int map_check(t_cub *cube);
int free_map_data(t_cub *cub);

#endif
