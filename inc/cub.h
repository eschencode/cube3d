#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include "color_codes.h"
#include <stdio.h>
#include <fcntl.h>      // for open
#include <unistd.h>     // for close, read, write
#include <stdlib.h>     // for malloc, free, exit
#include <string.h>     // for strerror
#include <errno.h>      // for perror
#include <math.h>       // for math library functions

# define SCREEN_WIDTH	1500 //1024 
# define SCREEN_HEIGHT	1000	//dimension taken from Video by 3D Sage
# define MAP_WIDTH 10 // should later be deleted and ...
# define MAP_HEIGHT 10 // ... calculated from given map
# define SQUARE_SIZE 25 //side length of 1 square in the map in pixel
# define NAME	"cub3d"
# define MAP_CHARS "012NSEW"
# define MAP_INSIDE "02NSEW"
# define PLAYER "NSEW"

typedef struct	s_img
{
	void	*img;
	char	*addr;			/*needed by mlx to create image*/
	int		bpp;			/*bits_per_pixel:needed by mlx to create image*/
	int		line_length;	/*needed by mlx to create image*/
	int		endian;			/*needed by mlx to create image*/
}		t_img;

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

typedef struct m_flag
{
	int move_up;
	int move_down;
	int move_right;
	int move_left;
} t_flag;

typedef struct s_map
{
	char **layout; /*l[0] = y l[1] = x*/
	int nlines;
	int max_line_len;
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
	void	*mlx;
	void	*win;
	t_img	*img;	/* pointer to image struct, can hold several images*/	
	double pos[2];	/* players position (N) found in map: pos[0] = x, pos[1] = y*/
	double	dir[2]; /* direction player faces: dir[0] = x, dir[1] = y*/
	double	plane[2]; /* camera plane: part you see on the screen */
	t_flag *m_flag;
}			t_cub;

extern int	test_map[MAP_WIDTH][MAP_HEIGHT];

/* init.c: variables are initialized*/
void	init_cub(t_cub *cub);
void	init_img(t_cub *cub);

/*	window.c: window management */
void	open_window(t_cub *cub);
void	close_window(t_cub *cub);

/* image.c: creates the image displayed */
void	my_pixel_put(t_img *img, int x, int y, unsigned int color);
void	render_image(t_cub *cub, t_img *img);

/* render_map.c: rendering of 2D map*/
void	render_square(t_cub *cub, int x, int y, unsigned int color);
void	render_map(t_cub *cub, t_img *img, int start_x, int start_y);
int		set_right();
int		set_down();

/* event_handlings.c: management of key and mouse events */
int	deal_key(int key, t_cub *cub);
int	x_close(t_cub *cub);

/* move_player.c: calculates and renders movements of player on 2D map*/
void	move_left(t_cub *cub);
void	move_right(t_cub *cub);
void	move_up(t_cub *cub);
void	move_down(t_cub *cub);

int key_press(int key, t_cub *cub);
int key_release(int key, t_cub *cub);
/* exit.c: handles clean exit */
void	error_exit(t_cub *cub, char *message);


//map parsing
void initmap(char *path_to_map, t_cub *cube);
int map_check(t_cub *cube);
int free_map_data(t_cub *cub);
//initmap utils
char	*moded_strdup(const char *s);
int free_map_data(t_cub *cub);
int ft_empty(char *line);
void ft_setcolors(t_cub *cube, char *line, int i);
#endif
