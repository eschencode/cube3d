

#include "../inc/cub.h"

void start_timer(t_cub *cube)
{
	cube->timer = time(NULL);
}

long ft_get_time(t_cub *cube)
{
	static long elapsed_time;
	
	if(cube->exit_flag != -1)
	{
		time_t current_time = time(NULL);
		elapsed_time = current_time - cube->timer;
	}
	return(elapsed_time);
}


