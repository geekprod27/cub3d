NAME = cub3D

SRC_PATH = srcs/
OBJ_PATH = obj/

SRC_NAME =	main.c \
			tex.c

MLX = mlx/libmlx.a

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX) -lXext -lX11
	@echo "\033[1;32mBuild $(NAME)\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(SRC_PATH) -o $@ -c $<
	@echo "\033[0;32mCompilation de $<\033[0m"

$(MLX):
	@echo "\033[1;32mCompilation mlx\033[0m"
	@make --no-print-directory -C ./mlx  > /dev/null
	@echo "\033[1;32mBuild $(MLX)\033[0m"


clean:
	@rm -rf $(OBJ_PATH)
	@make clean --no-print-directory -C ./mlx
	@echo "\033[0;36mClean des objs\033[0m"

fclean:	clean
	@rm -f $(NAME)
	@echo "\033[0;34mClean de l'executable\033[0m"

re:	fclean
	@make all

.PHONY: all clean fclean re