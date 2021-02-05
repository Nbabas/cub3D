/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:07:39 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:25:38 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*put_precision(t_inf *inf, char *strfilled, char *str)
{
	if ((inf->precision == -1) ||
		(inf->precision != 0 && inf->precision > (int)ft_strlen(str)))
		return (str);
	strfilled = malloc(sizeof(char) * (inf->precision + 1));
	if (!strfilled)
		return (NULL);
	ft_strncpy(strfilled, str, inf->precision);
	strfilled[inf->precision] = 0;
	return (strfilled);
}

static char	*put_width(t_inf *inf, char *strfilled, char *str)
{
	int			str_len;

	str_len = ft_strlen(str);
	if (inf->width <= str_len)
		return (str);
	if (inf->zeros == 1 && inf->left_align == -1)
		strfilled = fill_stroptions(inf->width, '0');
	else
		strfilled = fill_stroptions(inf->width, ' ');
	if (!strfilled)
		return (NULL);
	if (inf->left_align == 1)
		ft_strncpy(strfilled, str, str_len);
	else
		ft_strncpy(&strfilled[inf->width - str_len], str, str_len);
	return (strfilled);
}

int			ft_print_s(t_inf *inf, va_list ap, int fd)
{
	t_strfill	*stroptions;
	int			didmalloc;
	char		*str;

	str = va_arg(ap, char *);
	didmalloc = 0;
	if (!str)
	{
		str = strndup("(null)", 6);
		didmalloc = 1;
	}
	stroptions = get_stroptions();
	str = put_precision(inf, stroptions->precision, str);
	str = put_width(inf, stroptions->width, str);
	if (!str)
	{
		free_stroptions(stroptions);
		return (-1);
	}
	inf->printed += ft_putstr_return(str, fd);
	free_stroptions(stroptions);
	if (didmalloc)
		free(str);
	return (0);
}
