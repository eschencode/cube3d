
#include "../inc/cub.h"

#include <stdbool.h>


int free_map_data(t_cub *cub)
{
	 if(cub == NULL) 
        return(-1);
	if(cub->map != NULL) 
	{
    	if(cub->map->NO != NULL)
		{
            free(cub->map->NO);
            cub->map->NO = NULL;
        }
		if(cub->map->EA != NULL)
		{
            free(cub->map->EA);
            cub->map->EA = NULL;
        }
		if(cub->map->WE != NULL)
		{
            free(cub->map->WE);
            cub->map->WE = NULL;
        }
        if(cub->map->SO != NULL)
		{
            free(cub->map->SO);
            cub->map->SO = NULL;
        }
		if(cub->map->C_color != NULL)
			free(cub->map->C_color);
		if(cub->map->F_color != NULL)
			free(cub->map->F_color);
		free(cub->map);
    	cub->map = NULL;
	}
	return(0);
}
int ft_empty(char *line)
{
	int i;
	i = 0;
	int len = ft_strlen(line);
	
	while(i < len)
	{
		if(line[i] != ' ' && line[i] != '\n')
			return(1);
			i++;
	}
	return(-1);
}


void ft_fill_layout(t_cub *cube,char *line)
{
	int x_len = ft_strlen(line);
	printf("\nxlen = %d\n",x_len);
	//cube->map->layout = malloc(sizeof(char) * x_len + 1);
	//cube->map->layout[0][0] = ft_strdup(line);
}

int count_lines(t_cub *cube ,char *path_to_map)
{
	int line_counter;
	char *line;
	int fd = open(path_to_map,O_RDONLY);
	line_counter = 0;
	while((line = get_next_line(fd)) != NULL)
	{
		if(line[0] == '1')
			line_counter++;
		free(line);
	}
	close(fd);
	return(line_counter);
}

void ft_setcolors(t_cub *cube, char *line, int i)//need to add check if rgb value higer 255 or lower 0
{
	char *newline;
	char **ar;
	if(line[i] == 'F')
	{
		cube->map->F_color = (t_rgb*)malloc(sizeof(t_rgb));
		while(line[i] == 'F' || line[i] == ' ')
			i++;
		newline = ft_strdup(line + i);
		ar = ft_split(newline, ',');
		cube->map->F_color->r = ft_atoi(ar[0]);
		cube->map->F_color->g = ft_atoi(ar[1]);
		cube->map->F_color->b = ft_atoi(ar[2]);
	}
	if(line[i] == 'C')
	{
		cube->map->C_color = (t_rgb*)malloc(sizeof(t_rgb));
		while(line[i] == 'C' || line[i] == ' ')
			i++;
		newline = ft_strdup(line + i);
		ar = ft_split(newline, ',');
		cube->map->C_color->r = ft_atoi(ar[0]);
		cube->map->C_color->g = ft_atoi(ar[1]);
		cube->map->C_color->b = ft_atoi(ar[2]);
		
	}
	if(ar != NULL)
	{
		free(ar[0]);
		free(ar[1]);
		free(ar[2]);
		free(ar);
	}
	if(newline != NULL)
		free(newline);
}



char	*moded_strdup(const char *s)
{
	int		i;
	int		len = 0;
	char	*nstr;

	i = 0;
	while(s[len] != '\0' && s[len] != '\n')
		len++;
	nstr = malloc ( 1 + len * sizeof(char));
	if (nstr == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		nstr[i] = s[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
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

void initmap(char *path_to_map,t_cub *cube)
{
	char **map;
	char *line;
	int i = 0;
	int lines = count_lines(cube,path_to_map);
	printf("nlines %d\n",lines);
	cube->map = malloc(sizeof(t_map));
	
	int fd = open(path_to_map,O_RDONLY);
	printf("path to map %s fd = %d\n",path_to_map,fd);
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
	
		}
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
	
	map_check(cube);
	
}