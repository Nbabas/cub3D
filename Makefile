NAME = cub3D

CC = clang

CFLAGS =  -Wall -Wextra -Werror

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit -lm

HEADER = cub3d.h

B_HEADER = cub3d_bonus.h

SRC = cub3d\
		utils \
		parsing \
		get_next_line \
		ft_error \
		parse_config \
		process_map \
		init \
		raycasting \
		sprites \
		minimap \
		free_all \
		checks \
		keys \
		movements \
		trace_horizontal \
		trace_vertical \

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

B_HEADER = cub3d_bonus.h

B_SRC = cub3d.c \
		utils.c \
		parsing.c \
		get_next_line.c \
		ft_error.c \
		parse_config.c \
		parse_map.c \
		init.c \

B_FIL = $(addsuffix _bonus.c, $(addprefix bonus/, $(SRC) $(B_SRC)))

B_OBJ = $(B_FIL:.c=.o)

B_BIN = $(addsuffix _bonus.o, $(SRC) $(B_SRC))

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) ./libft/libft.a -L $(MLX) $(LXFLAGS) $(OBJ) -fsanitize=address
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ) $(B_OBJ)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all