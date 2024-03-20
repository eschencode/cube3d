#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
#include "../libs/libft/libft.h"
#include <stdio.h>
#include <fcntl.h>      // for open
#include <unistd.h>     // for close, read, write
#include <stdlib.h>     // for malloc, free, exit
#include <string.h>     // for strerror
#include <errno.h>      // for perror
#include <math.h>       // for math library functions



struct t_cub;

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

typedef struct s_cub
{
	t_map *map;

} t_cub;

void initmap(char *path_to_map, t_cub *cube);
int map_check(t_cub *cube);

#endif