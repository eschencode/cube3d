#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include "color_codes.h"
# include <stdio.h>
# include <math.h>

# define SCREEN_WIDTH	512 //1024 
# define SCREEN_HEIGHT	512	//dimension taken from Video by 3D Sage
# define MAP_WIDTH 10 // should later be deleted and ...
# define MAP_HEIGHT 10 // ... calculated from given map
# define SQUARE_SIZE 50 //side length of 1 square in the map in pixel
# define NAME	"cub3d"

typedef struct	s_img
{
	void	*img;
	char	*addr;			/*needed by mlx to create image*/
	int		bpp;			/*bits_per_pixel:needed by mlx to create image*/
	int		line_length;	/*needed by mlx to create image*/
	int		endian;			/*needed by mlx to create image*/
}		t_img;


typedef struct s_cub
{
	void	*mlx;
	void	*win;
	t_img	*img;	/* pointer to image struct, can hold several images*/	
	int	pos[2];	/* players position (N) found in map: pos[0] = x, pos[1] = y*/
	//player pos should be changed to double for raytracing
	double	dir[2]; /* direction player faces: dir[0] = x, dir[1] = y*/
	double	plane[2]; /* camera plane: part you see on the screen */
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
void	render_square(t_cub *cub, int x, int y, unsigned int color);
void	render_map(t_cub *cub, t_img *img);
void	render_player(t_cub *cub);

/* event_handlings.c: management of key and mouse events */
int	deal_key(int key, t_cub *cub);
int	x_close(t_cub *cub);

/* exit.c: handles clean exit */
void	error_exit(t_cub *cub, char *message);

#endif