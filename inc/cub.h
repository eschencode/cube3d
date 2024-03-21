#ifndef CUBE_H
#define CUBE_H

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include "color_codes.h"
# include <stdio.h>
# include <math.h>

# define SCREEN_WIDTH	1024 
# define SCREEN_HEIGHT	512	//dimension taken from Video by 3D Sage
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
	int		map_width; /* is calculated in map parsing*/
	int		map_height;
	double	pos[2];	/* players position (N) found in map: pos[0] = x, pos[1] = y*/
	double	dir[2]; /* direction player faces: dir[0] = x, dir[1] = y*/
	double	plane[2]; /* camera plane: part you see on the screen */
}			t_cub;

/* init.c: variables are initialized*/
void	init_cub(t_cub *cub);

/*	window.c: window management */
void	open_window(t_cub *cub);
void	close_window(t_cub *cub);

/* image.c: creates the image displayed */
void	init_img(t_cub *cub);
void	draw_image(t_cub *cub, t_img *img);
void	my_pixel_put(t_img *img, int x, int y, unsigned int color);

/* event_handlings.c: management of key and mouse events */
int	deal_key(int key, t_cub *cub);
int	x_close(t_cub *cub);

/* exit.c: handles clean exit */
void	error_exit(t_cub *cub, char *message);

#endif