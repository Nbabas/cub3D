/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:59:26 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:30:15 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define FLAGS "-0+ #"
# define TYPE "cspdiuxX%"
# define BASE "0123456789abcdef"

typedef struct	s_inf
{
	int		width;
	int		precision;
	int		zeros;
	int		plus;
	int		space;
	int		hexa;
	char	signe;
	int		left_align;
	char	type;
	int		len_modif;
	int		printed;
}				t_inf;

typedef struct	s_strfill
{
	char	*width;
	char	*precision;
}				t_strfill;

/*
**      MAIN FUNCTIONS
*/

int				ft_printf(int fd, const char *input, ...);
int				add_to_print(t_inf *inf, const char *strinput,
				 va_list ap, int fd);

/*
**      FUNCTION WRITE WITH RETURN INT + UTILS
*/
int				ft_putchar_return(char c, int fd);
int				c_is_in_s(char c, char *s);
int				ft_putstr_return(char *str, int fd);

int				check_all(t_inf *inf, const char **input, va_list ap);
void			reset_infos(t_inf *inf);
void			flag_to_zero(t_inf *inf);

void			ft_print_types(char *ptr, t_inf *inf, int len);
void			ft_printf_typed(t_inf *inf, char *src);

void			free_stroptions(t_strfill *strfill);
char			*fill_stroptions(int size, char tofill);
t_strfill		*get_stroptions(void);

char			*get_sign(t_inf *inf, char *str);
char			*print_sign(t_inf *inf, char *strfilled, int str_len);

int				ft_print_c(t_inf *inf, va_list ap, char c, int fd);
int				ft_print_s(t_inf *inf, va_list ap, int fd);
int				ft_print_d(t_inf *inf, va_list ap, char *str, int fd);
int				ft_print_x(t_inf *inf, va_list ap, char conv, char *str, int fd);
int				ft_print_pourcent(t_inf *inf, va_list ap, char c, int fd);

#endif
