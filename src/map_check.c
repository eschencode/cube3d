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
int		ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}
int sides_check(t_cub *cube, int y , int x)
{
	
	if(cube->map->layout[y][x + 1] != '1')
		return(-1);
	if(cube->map->layout[y - 1][x -1] != '1')
		return(-1);
	if(cube->map->layout[y - 1][x] != '1')
		return(-1);
	if(cube->map->layout[y - 1][x + 1] != '1')
		return(-1);
	if(cube->map->layout[y + 1][x -1] != '1')
		return(-1);
	if(cube->map->layout[y + 1][x] != '1')
		return(-1);
	if(cube->map->layout[y + 1][x + 1] != '1')
		return(-1);
	return (1);
}

/*
int		check_closed(char **ar)
{
	int i;

	i = 0;
	while (ar[0][i])
	{
		if (ft_strchr(MAP_INSIDE, ar[0][i]))
		{
			if (!sides_check(ar, i))
				return (0);
		}
		i++;
	}
	return (1);
}
*/
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
/*returns -1 if contaions diff char*/
int check_wall(char *str)
{
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i] != '1' && str[i] != ' ')
			return(-1);
		i++;
	}
	return(0);
}

int		is_map(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isspace(*str) && !ft_strchr(MAP_CHARS, *str))
			return (0);
		str++;
	}
	return (1);
}

int check_first_row(t_cub *cube)
{
	int x = 0;
	while(x < cube->map->max_line_len && cube->map->layout[0][x] != '\0')
	{
		if(!ft_isspace(cube->map->layout[0][x]) && cube->map->layout[0][x] != '1')
			return(-1);
		x++;
	}
	//printf("passed first row check\n");
	return(0);
}


void set_angle(t_cub *cube, char c)
{
	if(c == 'N')
	{
		cube->dir[0] = 0;
		cube->dir[1] = -1;
	}
	if(c == 'E')
	{
		cube->dir[0] = 1;
		cube->dir[1] = 0;
	}
	if(c == 'S')
	{
		cube->dir[0] = 0;
		cube->dir[1] = 1;
	}
	if(c == 'W')
	{
		cube->dir[0] = -1;
		cube->dir[1] = 0;
	}
	printf("\nstrtd 0= %f 1= %f\n\n",cube->dir[0] , cube->dir[1]);
}

int check_all_rows(t_cub *cube)//probelm dosent check the dimesnion right :()
{
	char c;
	int x = 0;
	int y = 0;
	int playerCount = 0;
	if(check_first_row(cube) == -1)
		return(-1);
	y++;
	//printf("n lines %d",cube->map->nlines);
	while (y < cube->map->nlines - 1 )
	{
		while(cube->map->layout[y][x] != '\0')
		{
			//printf("c = %c x %d y %d\n",c,x,y);
			c = cube->map->layout[y][x];
			 // Check if the character is valid
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W') 
            {
				return (-1);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                playerCount++;
				cube->pos[0] = x;
				cube->pos[1] = y;
				printf("\n YYY = %f",y);
				set_angle(cube, c);
			}
			if((x == 0 || cube->map->layout[y][x + 1] == '\0') && c != '1'){
				return(-1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	while (cube->map->layout[y][x] != '\0')
	{
		if(cube->map->layout[y][x] != '1')
		{
			printf("last row error\n");
			return(-1);
		}
		x++;
	}
	if(playerCount != 1){
		printf("4");
		return(-1);
	}
	//printf("passed all row check\n");
	return(0);
}


int map_check(t_cub *cube)
{
	checkcolor(cube);
	//check_borders(cube);
	//printf("valid flag %d\n",cube->map->map_valid_flag);
	if(check_all_rows(cube) == -1)
	{
		cube->map->map_valid_flag = -1;
	}
	if(cube->map->map_valid_flag == -1)
	{
		printf("map invalid\n");
	}
	else{
		printf("MAP VALIDDDD\n");
	}

	return(0);
}