#ifndef CUBE_H
# define CUBE_H

# include "../../../minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "key_codes.h"
# include "color_codes.h"
# include <stdio.h>
# include <fcntl.h>      // for open
# include <unistd.h>     // for close, read, write
# include <stdlib.h>     // for malloc, free, exit
# include <string.h>     // for strerror
# include <errno.h>      // for perror
# include <math.h>       // for math library functions
# include <sys/time.h>	// for calculating frames (get_time)
# include <time.h>

# define SCREEN_WIDTH	1500 //1024 
# define SCREEN_HEIGHT	1000	//dimension taken from Video by 3D Sage
# define MAP_WIDTH 10 // should later be deleted and ...
# define MAP_HEIGHT 10 // ... calculated from given map
# define SQUARE_SIZE 25 //side length of 1 square in the map in pixel
# define NAME	"cub3d"
# define MAP_CHARS "012NSEW"
# define MAP_INSIDE "02NSEW"
# define PLAYER "NSEW"
# define TEX_NUM 5 // number of textures
# define TEX_N 0	//texture for NO side
# define TEX_S 1	//texture for SO side
# define TEX_W 2	//texture for WE side
# define TEX_E 3	//texture for EA side
# define TEX_EXIT 4 //texture for exit
// To DO: either delete defined tex width & height and retrieve from xpm file
// or include check in map parsing that xpm not bigger or smaller than 64x64
# define TEX_WIDTH 64 // size of pixels for texture (x)
# define TEX_HEIGHT 64 // size of pixels for texture (y)
# define TEX_EXIT_PATH "./textures/exit_blue.xpm"
# define EXIT_IMAGE "./textures/win.xpm"

typedef struct	s_img
{
	void	*img;
	char	*addr;			/*needed by mlx to create image*/
	int		bpp;			/*bits_per_pixel:needed by mlx to create image*/
	int		line_length;	/*needed by mlx to create image*/
	int		endian;			/*needed by mlx to create image*/
}		t_img;

typedef struct	s_img_tex
{
	void	*img;
	int		*addr;			/*needed by mlx to create image*/
	int		bpp;			/*bits_per_pixel:needed by mlx to create image*/
	int		line_length;	/*needed by mlx to create image*/
	int		endian;			/*needed by mlx to create image*/
}		t_img_tex;

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
	int move_left;
	int move_right;
	int look_right;
	int look_left;
	int map_flag;
} t_flag;

typedef struct s_map
{
	char 	**layout; /*l[0] = y l[1] = x*/
	int		nlines;
	int		max_line_len;
	int		map_valid_flag;
	t_rgb	*F_color;
	t_rgb	*C_color;
	char	*NO; // dir = -1, 0
	char	*SO; // dir = 1, 0
	char	*WE; // dir = 0, -1
	char	*EA; // dir = 0, 1
	char 	initial_dir;
	int		*texture[TEX_NUM]; // stores the colour of each pixel of the 4 textures
	int		tex_width[TEX_NUM]; //width of all loaded textures
	int		tex_height[TEX_NUM]; //height of all loaded textures
}t_map;


typedef struct s_cub
{
	t_map 	*map;
	void	*mlx;
	void	*win;
	t_img	*img;	/* pointer to image struct, can hold several images*/	
	t_img_tex	img_tex;
	t_img	img_exit;
	double 	pos[2];/* position vector of player: pos[0] = pos_x, pos[1] = pos_y*/
	int		exit_pos[2];/*0 =x 1=y pos of exit */
	int		exit_found; /* 1 if player touched exit, otherwise 0*/
	int		exit_flag;	/* 1 if map has an exit door (a "2" on the map), 0 if it doesn't */
	double	dir[2]; /* direction player faces: dir[0] = dir_x, dir[1] = dir_y*/
	double	camplane[2]; /* camera plane (part you see on screen)*/
	double	raydir[2]; /* ray direction */
	double	deltadist[2]; /* length of ray from one x- or y-side to next x- or y-side*/
	double	sidedist[2]; /* length of ray from current pos to next x- or y-side*/
	int		side;		/* which wall was hit? x (NS) or y (EW)*/
	int		step[2]; /* into what direction to step: either -1 or 1, maybe if SW or NE*/
	double	walldist;
	int		wallheight;
	int		startwall;
	int		endwall;
	double	speedmove;	/* speed of movement */
	double	speedrot;	/* speed of rotation */
	t_flag	m_flag;
	time_t timer;
}			t_cub;

//extern int	test_map[MAP_WIDTH][MAP_HEIGHT];

/* init.c: variables are initialized*/
void		init_cub(t_cub *cub);
void		init_img(t_cub *cub, int width, int height);
void		init_img_xpm(t_cub *cub, t_map *map, int tex);
void 		init_movement(t_cub *cub);
void		init_dir(t_cub *cub, char c);
void		init_map(t_map *map);

/* textures.c: init textures (save them so that they are usable)*/
void		malloc_textures(t_cub *cub, t_map *map, int tex);
void		read_in_textures(t_cub *cub, t_map *map);
int			choose_texture(t_cub *cub, int wall_type);

/*	window.c: window management */
void		open_window(t_cub *cub);
void		close_window(t_cub *cub);


/* render_map.c: rendering of 2D map*/
void		render_square(t_cub *cub, int x, int y, unsigned int color);
void		render_minimap(t_cub *cub, int start_x, int start_y);
int			set_right();
int			set_down();

/* event_handlings.c: management of key and mouse events */
int			deal_key(int key, t_cub *cub);
int			x_close(t_cub *cub);

/* raycasting_calc.c */
void		calculate_ray(t_cub *cub, int x);
void		calculate_step_sidedist(t_cub *cub, int map[2]);
int			calculate_wall_hit(t_cub *cub);
void		calculate_wall_dimensions(t_cub *cub);
int			calculate_tex_x(t_cub *cub, double walldist, int tex);

/* raycasting.c */
void		render_wall_texture(t_cub *cub, int x, int tex);
int			render_3d_view(t_cub *cub);


//timer
void start_timer(t_cub *cube);
long ft_get_time(t_cub *cube);
void	print_timer(t_cub *cub);

/* move_player.c: calculates and renders movements of player on 2D map*/

void	look_left(t_cub *cub);
void	look_right(t_cub *cub);
void	move_up(t_cub *cub);
void	move_down(t_cub *cub);
void move_left(t_cub *cub);
void move_right(t_cub *cub);
void check_next_pos(t_cub *cub,int new_x,int new_y);

int key_press(int key, t_cub *cub);
int key_release(int key, t_cub *cub);

/* exit.c: handles clean exit */
void 		free_map_data(t_map *map);
void		error_exit(t_cub *cub, char *message, char *file);
void		exit_screen(t_cub *cub);


/*map parsing*/
int			initmap(char *path_to_map, t_cub *cube);
int 		map_check(t_cub *cube);

/* init_map.c */
void		allocate_map_data(t_cub *cub);

/*initmap utils*/
char		*moded_strdup(const char *s);
int 		ft_empty(char *line);
void 		ft_setcolors(t_cub *cube, char *line, int i);

/* utils.c*/
unsigned int	conv_rgb_hex(t_rgb *rgb);
void			my_pixel_put(t_img *img, int x, int y, unsigned int color);

#endif
