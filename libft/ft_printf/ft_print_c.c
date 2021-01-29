/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:07:29 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:24:26 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*put_width(t_inf *inf, char *strfill)
{
	inf->width--;
	if (inf->width < 1)
		return ("");
	if (inf->zeros == 1 && inf->left_align == -1)
		strfill = fill_stroptions(inf->width, '0');
	else
		strfill = fill_stroptions(inf->width, ' ');
	if (!strfill)
		return (NULL);
	return (strfill);
}

int				ft_print_c(t_inf *inf, va_list ap, char c, int fd)
{
	char		*res;
	t_strfill	*stroptions;

	(void) ap;
	if (inf->precision > 0)
		return (-1);
	stroptions = get_stroptions();
	res = put_width(inf, stroptions->width);
	if (!res)
	{
		free_stroptions(stroptions);
		return (-1);
	}
	if (inf->left_align == 1)
		inf->printed += ft_putchar_return(c, fd) + ft_putstr_return(res, fd);
	else
		inf->printed += ft_putstr_return(res, fd) + ft_putchar_return(c, fd);
	free(stroptions);
	return (0);
}
