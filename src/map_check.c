#include "../inc/cub.h"


int checkcolor(t_cub *cube)
{
	if(cube->map->C_color->b > 255 || cube->map->C_color->b < 0	 || cube->map->C_color->r > 255 || cube->map->C_color->r < 0 || cube->map->C_color->g > 255 || cube->map->C_color->g < 0)
	{
		cube->map->map_valid_flag = -1;
		return(-1);
	}
	if(cube->map->F_color->b > 255 || cube->map->F_color->b < 0	 || cube->map->F_color->r > 255 || cube->map->F_color->r < 0 || cube->map->F_color->g > 255 || cube->map->F_color->g < 0)
	{
		cube->map->map_valid_flag = -1;
		return(-1);
	}
	else 
		return(0);
	
}

int check_borders(t_cub *cube)
{
	int x = 0;
	while(cube->map->layout[0][x] == ' ' && x < cube->map->max_line_len)//skip posible spaces on start
			x++;
	while (cube->map->layout[0][x] != '\0' && x < cube->map->max_line_len)//check top border
	{
		if(cube->map->layout[0][x] != '1')
		{
			cube->map->map_valid_flag = -1;
			return(-1);
		}
		x++;
	}
	return (0);
	
}

int map_check(t_cub *cube)
{
	checkcolor(cube);
	//check_borders(cube);
	//check textures (missing can not open or dubbles)
	// printf("\ntxtEA :%s:\n",cube->map->EA);
	// printf("txtNO :%s:\n",cube->map->NO);
	// printf("txtWE :%s:\n",cube->map->WE);
	// printf("txtSO :%s:\n",cube->map->SO);
	if(cube->map->map_valid_flag == -1)
	{
		printf("map invalid\n");
	}

	return(0);
}