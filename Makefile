NAME = cub3d
CC = cc
CFLAGS = -g #-Wall -Wextra -Werror 
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -lXext -lX11 
DEPS = libs/minilibx-linux/mlx.h libs/libft/libft.a

DIRSRC = ./src/

C_FILES = main init exit window event_handling image \
			init_map init_map_utils map_check textures \
			render_map move_player raycasting raycasting_calc \
			utils

SRC = ${addprefix ${DIRSRC}, $(addsuffix .c, $(C_FILES))}
OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: libs $(NAME)

$(LIBFT):
	$(MAKE) -C ./libs/libft

libs:
	$(MAKE) -C ./libs/minilibx-linux
	
$(NAME): $(OBJ) $(libs) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)



clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)

re: fclean all
	$(MAKE) re -C ./libs/libft
	

r: fclean all
	./$(NAME) "maps/map.cub"

gdb: fclean all
	gdb $(NAME) "maps/map.cub"
v: fclean all
	 valgrind --leak-check=full ./$(NAME) "maps/map.cub" 
vv:fclean all
	valgrind --leak-check=full ./$(NAME) "maps/bad/wall_none.cub"
.PHONY: all clean fclean re