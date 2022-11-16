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
	@printf "\e[2K\r- Build \033[1;33m${NAME}\033[0m [${PROGRESS}]"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX) $(LIBFT) -lXext -lX11
	@printf "\e[2K\r- Build \033[1;32m${NAME}\033[0m [${CHECK}]\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\e[2K\r- \033[1;34m$<\033[0m [${PROGRESS}]"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(SRC_PATH) -o $@ -c $<
	@printf "\e[2K\r- \033[1;32m$<\033[0m [${CHECK}]\n"

$(MLX):
	@printf "\e[2K\r-[\033[1mLIB\033[0m] \033[1;33mMLX\033[0m [${PROGRESS}]"
	@make --no-print-directory -C ./mlx  > /dev/null
	@printf "\e[2K\r-[\033[1mLIB\033[0m] \033[1;32mMLX\033[0m [${CHECK}]\n"

$(LIBFT):
	@printf "\e[2K\r-[\033[1mLIB\033[0m] \033[1;33mLibft\033[0m [${PROGRESS}]"
	@$(MAKE) --no-print-directory -C ./libft
	@printf "\e[2K\r-[\033[1mLIB\033[0m] \033[1;32mLibft\033[0m [${CHECK}]\n"

clean:
	@printf "\e[2K\r- \033[36mClean des objs\033[0m [${PROGRESS}]"
	@rm -rf $(OBJ_PATH)
	@make clean --no-print-directory -C ./mlx
	@$(MAKE) clean --no-print-directory -C ./libft
	@printf "\e[2K\r- \033[31mClean des objs\033[0m [${CHECK}]\n"

fclean:	clean
	@printf "\e[2K\r- \033[36mClean de lexecutable\033[0m [${PROGRESS}]"
	@rm -f $(NAME)
	@$(MAKE) fclean --no-print-directory -C ./libft
	@printf "\e[2K\r- \033[31mClean de lexecutable\033[0m [${CHECK}]\n"

re:	fclean
	@make all

.PHONY: all clean fclean re