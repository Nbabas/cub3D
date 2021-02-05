SHELL		= /bin/sh

CURRENTOS	:= $(shell uname -s)

ifeq ($(CURRENTOS), Linux)
    MLX_DIR = ./minilibx-linux
	MLX = -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
endif
ifeq ($(CURRENTOS), Darwin)
	MLX_DIR = ./mlxopengl
    MLX = -L $(MLX_DIR) -lmlx -lm -framework OpenGL -framework AppKit
endif

NAME = cub3D

CC = clang -g3 -Wall -Wextra -Werror

INC= -I./inc

SRC = 	cub3d \
		init \
		player/init_player \
		player/movements \
		player/keys \
		config/checks \
		config/parsing \
		config/parse_config \
		config/process_map \
		raycast/draw_col \
		raycast/raycasting \
		raycast/trace_horizontal \
		raycast/trace_vertical \
		raycast/sprites \
		raycast/sprites_tools \
		raycast/images_textures \
		raycast/minimap \
		tools/free_all \
		tools/ft_error \
		tools/utils \
		tools/bmpsaver \

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.c.o:
	${CC} ${INC} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling libft..."
	@make -C ./libft
	@make -C $(MLX_DIR)
	@echo "\n\x1b[34mCompiling program..."
	$(CC)  $(INC) $(OBJ) -Llibft -lft $(MLX) -o $(NAME) -fsanitize=address
	@echo "\033[0m"

clean:
	@echo "\033[0;31mClean..."
	@make clean -C ./libft
	@make clean -C $(MLX_DIR)
	rm -rf $(OBJ)
	rm -f img_saved.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mDelete program..."
	@make fclean -C ./libft
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re