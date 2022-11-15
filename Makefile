NAME = cub3D

SRC_PATH = srcs/
OBJ_PATH = obj/

SRC_NAME =	main.c 			\
			data.c 			\
			map.c			\
			move.c			\
			loop.c			\
			seg.c

MLX = mlx/libmlx.a
LIBFT = ./libft/libft.a

PROGRESS = 🔁
CHECK = ✅

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX) $(LIBFT) -lXext -lX11
	@echo "\033[1;32mBuild $(NAME)\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\e[2K\r- $< [${PROGRESS}]"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(SRC_PATH) -o $@ -c $<
	@printf "\e[2K\r- $< [${CHECK}]\n"

$(MLX):
	@printf "\e[2K\r- MLX [${PROGRESS}]"
	@make --no-print-directory -C ./mlx  > /dev/null
	@printf "\e[2K\r- MLX [${CHECK}]\n"

$(LIBFT):
	@printf "\e[2K\r- Libft [${PROGRESS}]"
	@$(MAKE) --no-print-directory -C ./libft
	@printf "\e[2K\r- Libft [${CHECK}]\n"

clean:
	@rm -rf $(OBJ_PATH)
	@make clean --no-print-directory -C ./mlx
	@$(MAKE) clean --no-print-directory -C ./libft
	@echo "\033[0;36mClean des objs\033[0m"

fclean:	clean
	@rm -f $(NAME)
	@$(MAKE) fclean --no-print-directory -C ./libft
	@echo "\033[0;34mClean de l'executable\033[0m"

re:	fclean
	@make all

.PHONY: all clean fclean re