/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:29:54 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/25 16:44:33 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**  First check if char is in flag's charset and update the struct.
**  Put hexa to 2 is to use the number to print '0x' later.
*/

static void	check_flags(t_inf *inf, const char **strinput)
{
	while (c_is_in_s(**strinput, FLAGS))
	{
		if (**strinput == '-')
			inf->left_align = 1;
		else if (**strinput == '0')
			inf->zeros = 1;
		else if (**strinput == '+')
			inf->plus = 1;
		else if (**strinput == ' ')
			inf->space = 1;
		else if (**strinput == '#')
			inf->hexa = 2;
		(*strinput)++;
	}
}

/*
**  Update struct for the width. With arg (*) or digits (atoi)
**  If digits is < 0. Minus is present so alig left
*/

static void	check_width(t_inf *inf, const char **strinput, va_list ap)
{
	if (ft_isdigit(**strinput) || **strinput == '*')
	{
		if (**strinput == '*')
		{
			inf->width = va_arg(ap, int);
			(*strinput)++;
		}
		else
		{
			inf->width = ft_atoi(*strinput);
			while (ft_isdigit(**strinput))
				(*strinput)++;
		}
		if (inf->width < 0)
		{
			inf->left_align = 1;
			inf->zeros = -1;
			inf->width *= -1;
		}
	}
}

/*
**  Update struct for the precision (.) With digits : atoi OR with (*) : Arg
**  Precision = 0 if no digits and no (*). precision cant be negative.
**  Precision = -1 if negative for some checks later
*/

static void	check_precision(t_inf *inf, const char **strinput, va_list ap)
{
	if (**strinput != '.')
		return ;
	(*strinput)++;
	if (ft_isdigit(**strinput))
	{
		inf->precision = ft_atoi(*strinput);
		while (ft_isdigit(**strinput))
			(*strinput)++;
	}
	else if (**strinput == '*')
	{
		inf->precision = va_arg(ap, int);
		(*strinput)++;
	}
	else
		inf->precision = 0;
	if (inf->precision < 0)
		inf->precision = -1;
}

/*
**  Process to check all parameters before some TYPE symbol
**  Probably here to add check_len_modif (l ll h hh)
*/

int			check_all(t_inf *inf, const char **strinput, va_list ap)
{
	check_flags(inf, strinput);
	check_width(inf, strinput, ap);
	check_precision(inf, strinput, ap);
	if (!c_is_in_s(**strinput, TYPE))
		return (-1);
	return (0);
}
