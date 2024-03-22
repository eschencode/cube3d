
#include "../inc/cub.h"

#include <stdbool.h>


int count_lines(t_cub *cube ,char *path_to_map)
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
		if(line[i] == '1')
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
	printf("max line len = %d  + 1 for nullbyte nlines %d\n",max_line_len,line_counter);
	cube->map->max_line_len = max_line_len;
	cube->map->nlines = line_counter;
	//allocate space for layout
	cube->map->layout = malloc(line_counter * sizeof(char *));
	if(cube->map->layout == NULL)
		printf("error");//add error handelibg here later
	i = 0;
	while (i < line_counter)
	{
		cube->map->layout[i] = malloc((max_line_len +1) * sizeof(char));
		if(cube->map->layout[i] == NULL)
			printf("error");//add error handelibg here later
		i++;
	}
	
	return(line_counter);
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
	int startposcount = 0;
	int x = 0;
	if (cube == NULL || cube->map == NULL || cube->map->layout[current_line] == NULL) {
        printf("error");
        return;
    }
	while (line[x] != '\n' && line[x] != '\0' && cube->map->max_line_len > x)
	{
		if(line[x] == '\t' && x + 3 < cube->map->max_line_len)
		{
			cube->map->layout[current_line][x] = ' ';
			cube->map->layout[current_line][x + 1] = ' ';
			cube->map->layout[current_line][x+ 2] = ' ';
			cube->map->layout[current_line][x + 3] = ' ';
		}
		if(line[x] == '1' || line[x] == '0')
		{
			cube->map->layout[current_line][x] = line[x];
		}
		if(line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
		{
			cube->map->layout[current_line][x] = line[x];
			startposcount++;
		}
		x++;
	}
	if(x < cube->map->max_line_len)
    {	cube->map->layout[current_line][x] = '\0';}
}

void initmap(char *path_to_map,t_cub *cube)
{
	char *line;
	int i = 0;
	int current_line = 0;
	
	cube->map = malloc(sizeof(t_map));
	count_lines(cube,path_to_map);
	int fd = open(path_to_map,O_RDONLY);
	line = get_next_line(fd);
	while(line != NULL)
	{
		if (ft_empty(line) == 1)//skips empty lines
		{
			printf("%s",line);
			//skip sapces in line 
			while(line[i] == ' ' || line[i] == '\t')
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
			if(line[i] == '1' && current_line < cube->map->nlines)
			{
				
				//printf("current line = %d len of line = %d\n",current_line,ft_strlen(line));
				ft_fill_layout(cube,line,current_line);
				printf("lineinlayout[%d] :%s:\n",current_line ,cube->map->layout[current_line]);
				current_line++;
			}
			printf("currentline %d\n",current_line);
		}
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
	
	//map_check(cube);
	
}