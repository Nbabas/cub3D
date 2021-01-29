/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:58:32 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:29:36 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	add_to_print(t_inf *inf, const char *strinput, va_list ap, int fd)
{
	if (*strinput == 'c')
		return (ft_print_c(inf, ap, va_arg(ap, int), fd));
	else if (*strinput == 's')
		return (ft_print_s(inf, ap, fd));
	else if (*strinput == 'd' || *strinput == 'i')
		return (ft_print_d(inf, ap, ft_itoa(va_arg(ap, int)), fd));
	else if (*strinput == 'u')
		return (ft_print_d(inf, ap, ft_uitoa(va_arg(ap, unsigned int)), fd));
	else if (*strinput == 'x')
		return (ft_print_x(inf, ap, 'x',
				ft_itoa_base((int)va_arg(ap, int), BASE), fd));
	else if (*strinput == 'X')
		return (ft_print_x(inf, ap, 'X',
				ft_itoa_base((int)va_arg(ap, int), BASE), fd));
	else if (*strinput == 'p')
	{
		inf->hexa = 2;
		return (ft_print_x(inf, ap, 'x',
			ft_lltoa_base(va_arg(ap, unsigned long long), BASE), fd));
	}
	else if (*strinput == '%')
		return (ft_print_pourcent(inf, ap, '%', fd));
	else
		return (-1);
}

/*
**	printf("Width = %d || Preci = %d || Plus = %d || Space = %d || Zeros = %d ||
**	LeftAlign = %d || Signe = %c || Hexa = %d || len_modif = %d ||
**	Printed = %d\n", inf->width, inf->precision, inf->plus, inf->space,
**	inf->zeros, inf->left_align, inf->signe, inf->hexa, inf->len_modif,
**	inf->printed);
*/

int	print_strinput(t_inf *inf, const char *strinput, va_list ap, int fd)
{
	if (!strinput)
		return (-1);
	while (*strinput)
	{
		while (*strinput && *strinput != '%')
			inf->printed += ft_putchar_return(*strinput++, fd);
		if (*strinput == '%')
		{
			strinput++;
			reset_infos(inf);
			if (check_all(inf, &strinput, ap) == -1)
				return (-2);
			inf->type = *strinput;
			if (add_to_print(inf, strinput, ap, fd) == -1)
				return (-3);
			strinput++;
		}
	}
	return (0);
}

int	ft_printf(int fd, const char *strinput, ...)
{
	t_inf	inf;
	va_list	ap;
	int		ret;

	inf.printed = 0;
	va_start(ap, strinput);
	ret = print_strinput(&inf, strinput, ap, fd);
	if (ret < 0)
		return (ret);
	va_end(ap);
	return (inf.printed);
}
