NAME = cub3D

CC = clang

CFLAGS =  -Wall -Wextra -Werror

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit -lm


SRC = cub3d\
		/player/init_player \
		/player/movements \
		/player/keys \
		/config/checks \
		/config/parsing \
		/config/parse_config \
		/config/process_map \
		/raycast/draw_col \
		/raycast/raycasting \
		/raycast/trace_horizontal \
		/raycast/trace_vertical \
		/raycast/sprites \
		/raycast/sprites_tools \
		/raycast/images_textures \
		init \
		minimap \
		free_all \
		ft_error \
		utils \
		bmpsaver \

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling libft..."
	@make -C ./libft
	@make -C ./mlxopengl
	@echo "\n\x1b[34mCompiling program..."
	$(CC) -o $(NAME) ./libft/libft.a -L $(MLX) $(LXFLAGS) $(OBJ) -fsanitize=address
	@echo "\033[0m"

clean:
	@echo "\033[0;31mClean..."
	@make clean -C ./libft
	@make clean -C ./mlxopengl
	rm -rf $(OBJ) $(B_OBJ)
	rm -f img_saved.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mDelete program..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all