NAME = cube3d
CC = cc
CFLAGS = #-Wall -Wextra -Werror
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11 
DEPS = libs/minilibx-linux/mlx.h libs/libft/libft.a


SRC = src/main.c src/init_map.c
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
	./$(NAME) "maps/map.cub"
