SHELL		= /bin/sh

CURRENTOS	:= $(shell uname -s)

ifeq ($(CURRENTOS), Linux)
MLX_DIR = ./minilibx-linux
MLX = -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
LISTPKG := "$(shell dpkg -l | grep -c "mpg123")"
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
		player/sprites_collisions \
		config/checks \
		config/parsing \
		config/parse_config \
		config/process_map \
		config/check_textures \
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
		tools/print_string \
		tools/handle_sound \
		tools/check_utils \
		tools/hud \

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.c.o:
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	-@${CC} ${INC} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33m Compiling libft..."
	@make -s -C ./libft
	@echo "\033[0;32m-->[OK] \033[0m"
	@echo "\n\033[0;33m Compiling MLX..."
	@make -s -C $(MLX_DIR) 2>/dev/null
	@echo "\033[0;32m-->[OK] \033[0m"
ifeq ($(CURRENTOS), Linux)
	@echo "\n\033[0;33m Checking for dependencies...\033[0m"
ifneq ($(LISTPKG),"2")
	@echo "\033[0;32m-->Installing MGP123 \033[0m"
	sudo apt-get install mpg123
	@echo "\033[0;32m-->MGP123 Installed\033[0m"
else
	@echo "\033[0;32m-->[OK] \033[0m"
endif
endif
	@echo "\n\033[0;34m Compiling $@..."
	-@$(CC) $(INC) $(OBJ) -Llibft -lft $(MLX) -o $(NAME) 
#-fsanitize=address
	@echo "\033[0;32m-->[OK] \033[0m"
	@echo "\033[0;36m\033[0;40mStart program with : ./cub3D [path_map] [--save]\033[0m"

clean:
	@echo "\033[0;31m__Clean__"
	@echo "\033[0;35mLibft"
	@make -s clean -C ./libft
	@echo "\033[0;35mMLX"
	@make -s clean -C $(MLX_DIR)
	@echo "\033[0;35mOBJ"
	@rm -rf $(OBJ)
	@echo "\033[0;35mImg saved"
	@rm -f img_saved.bmp
	@echo "\033[0;32mCleaned \033[0m"

fclean: clean
	@make -s fclean -C ./libft
	@echo
	@echo "\033[0;31m__Delete program__"
	@rm -f $(NAME)
	@echo "\033[0;32m$(NAME) removed\033[0m"

re: fclean all

.SILENT: clean

.PHONY: all clean fclean re packages