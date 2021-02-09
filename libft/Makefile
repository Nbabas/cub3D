# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 16:09:34 by nbascaul          #+#    #+#              #
#    Updated: 2021/02/09 09:20:24 by nbascaul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC =	ft_printf/ft_printf.c \
		ft_printf/ft_init.c \
		ft_printf/ft_prefill.c \
		ft_printf/ft_print_c.c \
		ft_printf/ft_print_d.c \
		ft_printf/ft_print_pourcent.c \
		ft_printf/ft_print_s.c \
		ft_printf/ft_print_sign.c \
		ft_printf/ft_print_x.c\
		ft_printf/ft_utils.c \
		ft_printf/ft_check_flags.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_islower.c \
		ft_isupper.c \
		ft_isspace.c \
		ft_strlen.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_strndup.c \
		ft_strepur.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_split_whitespaces.c \
		ft_split_charset.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_itoa.c \
		ft_itoa_base.c \
		ft_lltoa.c \
		ft_lltoa_base.c \
		ft_uitoa.c \
		ft_lstnew.c		\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstdelone.c	\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c		\
		get_next_line.c \

OBJ		= $(SRC:.c=.o)
CC		= gcc
FLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	-@$(CC) -I. -o $@ -c $? $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
