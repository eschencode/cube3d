#include "../inc/cub.h"


int ft_empty(char *line)
{
	int i;
	i = 0;
	int len = ft_strlen(line);
	
	while (i < len)
	{
		if (line[i] != ' ' && line[i] != '\n')
			return(1);
		i++;
	}
	return (-1);
}

int free_map_data(t_cub *cub)
{
	int i = 0;
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
		if(cub->map->layout != NULL)
		{
			while(cub->map->nlines > i)
			{
				if(cub->map->layout[i] != NULL)
				{
					free(cub->map->layout[i]);
					cub->map->layout[i] = NULL;
				}
				i++;
			}
			free(cub->map->layout);
			cub->map->layout = NULL;
		}
		free(cub->map);
    	cub->map = NULL;
		
	}
	return(0);
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

void ft_setcolors(t_cub *cube, char *line, int i)//need to add check if rgb value higer 255 or lower 0
{
	char *newline;
	char **ar;
	if(line[i] == 'F')
	{
		while(line[i] == 'F' || line[i] == ' ')
			i++;
		newline = ft_strdup(line + i);
		ar = ft_split(newline, ',');
		if(ar[0] && ar[1] && ar[2])
		{
			cube->map->F_color->r = ft_atoi(ar[0]);
			cube->map->F_color->g = ft_atoi(ar[1]);
			cube->map->F_color->b = ft_atoi(ar[2]);
		}
		
	}
	if(line[i] == 'C')
	{
		while(line[i] == 'C' || line[i] == ' ')
			i++;
		newline = ft_strdup(line + i);
		ar = ft_split(newline, ',');
		if(ar[0] && ar[1] && ar[2])
		{
			cube->map->C_color->r = ft_atoi(ar[0]);
			cube->map->C_color->g = ft_atoi(ar[1]);
			cube->map->C_color->b = ft_atoi(ar[2]);
		}
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
