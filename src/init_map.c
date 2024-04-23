
#include "../inc/cub.h"

#include <stdbool.h>

/*allocate space for layout
	in case malloc fails, all allocated pointers are set to NULL*/

void	allocate_layout(t_cub *cube)
{
	int	i;

	cube->map->layout = malloc(cube->map->nlines * sizeof(char *));
	i = -1;
	while (++i < cube->map->nlines)
		cube->map->layout[i] = NULL;
	if (!cube->map->layout)
		error_exit(cube, "malloc failed", NULL);
	i = 0;
	while (i < cube->map->nlines)
	{
		cube->map->layout[i] = malloc((cube->map->max_line_len +1) * sizeof(char));
		if(!cube->map->layout[i])
			error_exit(cube, "malloc failed", NULL);
		i++;
	}
}

void	count_lines(t_cub *cube ,char *path_to_map)
{
	int line_counter;
	char *line;
	int fd = open(path_to_map,O_RDONLY);
	line_counter = 0;
	int max_line_len = 0;
	int tab = 0;
	int i = 0;
	while((line = get_next_line(fd)) != NULL)
	{
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\n')
		{
			if(line[i] == '\t')
				tab += 3;
			i++;
		}
		if(line[i] == '1' || line[i] == '2')
		{
			while(line[i] != '\n' && line[i] != '\0')
				i++;
			line_counter++;
			if(i + tab > max_line_len)
				max_line_len = i + tab;
		}
		tab = 0;
		i = 0;
		free(line);
	}
	close(fd);
	//printf("max line len = %d  + 1 for nullbyte nlines %d\n",max_line_len,line_counter);
	cube->map->max_line_len = max_line_len;
	cube->map->nlines = line_counter;
}



void save_texture(t_cub *cube, char *line, int i)
{
	char *str;
	int j = i + 2;
	while (line[j] == ' ')
		j++;
	str = moded_strdup(line + j);
	if(line[i] == 'N')
		cube->map->NO = str;
	if(line[i] == 'S')
		cube->map->SO = str;
	if(line[i] == 'W')
		cube->map->WE = str;
	if(line[i] == 'E')
		cube->map->EA = str;
}

void ft_fill_layout(t_cub *cube,char *line, int current_line)
{
	int x = 0;
	if (cube == NULL || cube->map == NULL || cube->map->layout[current_line] == NULL) {
        printf("error");
        return;
    }
	while (line[x] != '\n' && line[x] != '\0' && cube->map->max_line_len > x)
	{
		cube->map->layout[current_line][x] = line[x];
		x++;
	}
    cube->map->layout[current_line][x] = '\0';
}


int check_valid_file(t_cub *cube, char *pf)
{
	int i;
	int	fd;

	i = 0;
	//check .cub at end 
	while (pf[i + 4] != '\0')
		i++;
	if (pf[i] != '.' || pf[i + 1] != 'c' || pf[i + 2] != 'u' || pf[i +3] != 'b')
		error_exit(cube, "wrong file format. Only '.cub' extension valid", pf);
	fd = open(pf, O_RDONLY);
	if (fd == -1)
		error_exit(cube, "could not open file", pf);
	return(0);
}

void	set_map_data_to_null(t_map *map)
{
	int	i;

	map->layout = NULL;
	map->C_color = NULL;
	map->F_color = NULL;
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	i = -1;
	while (++i < TEX_NUM)
		map->texture[i] = NULL;
}

/*allocate */
void	allocate_map_data(t_cub *cub)
{
	t_map	*map;

    cub->map = malloc(sizeof(t_map));
	set_map_data_to_null(cub->map);
    if (!cub->map)
       error_exit(cub, "malloc failed", NULL);
	map = cub->map;
	map->F_color = (t_rgb*)malloc(sizeof(t_rgb));
    if (!map->F_color)
		error_exit(cub, "malloc failed", NULL);
    map->C_color = (t_rgb*)malloc(sizeof(t_rgb));
    if (!map->C_color)
		error_exit(cub, "malloc failed", NULL);
}

int initmap(char *path_to_map,t_cub *cube)
{
	char *line;
	int i = 0;
	int current_line = 0;

	
	allocate_map_data(cube);	
	cube->map->map_valid_flag = 0;
	count_lines(cube,path_to_map);
	allocate_layout(cube);
	int fd = open(path_to_map,O_RDONLY);
	if(check_valid_file(cube, path_to_map) == -1)
		return(-1);
	line = get_next_line(fd);
	while(line != NULL)
	{
		if (ft_empty(line) == 1)//skips empty lines
		{
			//printf("%s",line);
			//skip sapces in line 
			while(line[i] == ' ')
				i++;
			if(line[i] == 'F' )
			{
				ft_setcolors(cube, line, i);
				//printf("color :%d: :%d: :%d: \n",cube->map->F_color->r,cube->map->F_color->g,cube->map->F_color->b);
			}
			if(line[i] == 'C')
			{
				ft_setcolors(cube, line, i);
				//printf("color :%d: :%d: :%d: \n",cube->map->C_color->r,cube->map->C_color->g,cube->map->C_color->b);
			}
			if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				save_texture(cube,line,i);
			}
			if((line[i] == '1' || line[i] == '2')&& current_line < cube->map->nlines)
			{
				
				//printf("current line = %d len of line = %d\n",current_line,ft_strlen(line));
				ft_fill_layout(cube,line,current_line);
			//	printf("lineinlayout[%d] :%s:\n",current_line ,cube->map->layout[current_line]);
				current_line++;
			}
			//printf("currentline %d\n",current_line);
		}
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
	if(map_check(cube) == -1)
		return(-1);
	return(0);
}