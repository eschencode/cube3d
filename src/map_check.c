#include "../inc/cub.h"

/* Wenn man sich bei der map eingabe vertippt, segfaulted die Funktion*/
int checkcolor(t_cub *cube)
{
	if(cube->map->C_color == NULL || cube->map->F_color == NULL)
		return(-1);
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
		if((!ft_isspace(cube->map->layout[0][x])) && (cube->map->layout[0][x] != '1' && cube->map->layout[0][x] != '2'))
			return(-1);
		x++;
	}
	return(0);
}


void set_angle(t_cub *cube, char c)
{
	cube->map->initial_dir = c;
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
}


int check_all_rows(t_cub *cube)//probelm dosent check the dimesnion right :()
{
	char c;
	int x = 0;
	int y = 0;
	int playerCount = 0;

	if (cube == NULL || cube->map == NULL || cube->map->layout == NULL || cube->map->nlines < 3) {
		printf("222\n");
        return -1;
    }
	if(check_first_row(cube) == -1)
		printf("11111\n");//return(-1);
	y++;
	//printf("n lines %d",cube->map->nlines);
	while (y < cube->map->nlines - 1 )
	{
		while(cube->map->layout[y][x] != '\0' )
		{
			//printf("c = %c x %d y %d\n",c,x,y);
			c = cube->map->layout[y][x];
			 // Check if the character is valid
            if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ') 
            {
				printf("invalid char on map\n");
				return (-1);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                playerCount++;
				cube->pos[0] = x + 0.5; // + 12,5 so he starts in middle of the grid thingi
				cube->pos[1] = y + 0.5;
				set_angle(cube, c);
				init_dir(cube, c);
				cube->map->layout[y][x] = '0';
			}
			if(c == '2')
			{
				printf("F2");
				cube->exit_pos[0] = x;
				cube->exit_pos[1] = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
	/*while (cube->map->layout[y][x] != '\0')
	{
		if(cube->map->layout[y][x] != '1')
		{
			printf("last row error\n");
			return(-1);
		}
		x++;
	*/
	if(playerCount != 1){
		printf("TO MANY PLAYERS ON MAP");
		return(-1);
	}
	return(0);
}

int check_textures(char *str)//can open and xmp at the end 
{
	int i;
	i = 0;
	if(!str)
		return(-1);
	while(str[i+4] != '\0')
		i++;
	if(str[i] != '.' || str[i+1] != 'x' || str[i+2] != 'p' || str[i+3] != 'm')
		return(-1);
	
	if(open(str,O_RDONLY) == -1)
		return(-1);
	return(0);
}

int flood_fill_check(char **layout,int x,int y, int xmax,int ymax)
{
	// Check if x and y are within the map's boundaries
    if (x < 0 || y < 0 || x >= xmax || y >= ymax) 
	{
        // If not, return -1
        return -1;
    }
	//printf("layout[%d][%d]:%c:\n", y, x, layout[y][x]);
	if(layout[y][x] == 'x' ||layout[y][x] == '1' || layout[y][x] == '2')
		return(0);
	layout[y][x] = 'x';
	 // Recursively check the neighboring cells
    // If any of them return -1, return -1
    if (flood_fill_check(layout, x + 1, y,xmax,ymax) == -1 ||
        flood_fill_check(layout, x - 1, y,xmax,ymax) == -1 ||
        flood_fill_check(layout, x, y + 1,xmax,ymax) == -1 ||
        flood_fill_check(layout, x, y - 1,xmax,ymax) == -1) {
        return (-1);
    }
	return(0);
}

int ft_flood_fill(t_cub *cube)
{
	printf("dadad");
	char **layout_copy;
	int i = 0;
	int rounded_x  = cube->pos[0] -0.5;
	int rounded_y = cube->pos[1] -0.5;
	layout_copy = malloc(sizeof(char*)*cube->map->nlines);
	while (i < cube->map->nlines)
	{
		layout_copy[i] = malloc(sizeof(char)*(cube->map->max_line_len + 1));
		ft_strcpy(layout_copy[i],cube->map->layout[i]);
		i++;
	}
	if(flood_fill_check(layout_copy,rounded_x,rounded_y,cube->map->max_line_len,cube->map->nlines) == -1)
		return(-1);
	i = 0;
	while(i < cube->map->nlines)
	{
		free(layout_copy[i]);
		i++;
	}	
	free(layout_copy);
	return(0);
}

int map_check(t_cub *cube)
{
	
	checkcolor(cube);
	if(cube->map->map_valid_flag == -1)
		printf("COLOR ERROR\n");
	if (check_textures(cube->map->NO) == -1 || check_textures(cube->map->SO) == -1 || check_textures(cube->map->WE) == -1 || check_textures(cube->map->EA) == -1)
	{
		printf("TEXTURE ERROR\n");
		cube->map->map_valid_flag = -1;
	}	
	
	if(check_all_rows(cube) == -1)
	{
		printf("DAASDA");
		cube->map->map_valid_flag = -1;
	}
	if(ft_flood_fill(cube) == -1)
	{
		printf("ADADADA");
		cube->map->map_valid_flag = -1;
	}
	if(cube->map->map_valid_flag == -1)
	{
		printf("map invalid\n");
		
		return(-1);
	}
	else{
		printf("MAP VALIDDDD\n");
	}

	return(0);
}