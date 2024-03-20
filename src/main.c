#include "../inc/cube.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int main(int argc, char** argv)
{
	t_cub *main;
	
	
	main = malloc(sizeof(t_cub));
	if(main == NULL)
		return(-1);
	initmap(argv[1], main);
	/*void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 1000, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	int x = 0;
	while(x < 500)
		mlx_pixel_put(mlx ,mlx_win , x++, 100, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	*/
}