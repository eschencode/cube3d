NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -lXext -lX11 
DEPS = libs/minilibx-linux/mlx.h libs/libft/libft.a


SRC = src/main.c src/exit.c src/window.c src/event_handling.c
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
	$(MAKE) $@ -C ./libs/minilibx-linux
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)

re: fclean all
	$(MAKE) re -C ./libs/libft
	$(MAKE) re -C ./libs/minilibx-linux

.PHONY: all clean fclean re