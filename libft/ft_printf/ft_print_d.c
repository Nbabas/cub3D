/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:09:07 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:30:34 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_precision(t_inf *inf, char *strfilled, char *str)
{
	int			str_len;

	str_len = ft_strlen(str);
	if (str[0] == '0' && inf->precision == 0)
		str = "";
	if (inf->precision <= str_len)
		return (str);
	strfilled = fill_stroptions(inf->precision, '0');
	if (!strfilled)
		return (NULL);
	ft_strncpy(&strfilled[inf->precision - str_len], str, str_len);
	return (strfilled);
}

static char		*get_width(t_inf *inf, char *strfilled, char *str)
{
	int			str_len;

	str_len = ft_strlen(str);
	if (!inf->signe && inf->width < str_len)
		return (str);
	if (inf->width < str_len)
		inf->width = str_len;
	if (inf->signe && inf->width == str_len)
		inf->width++;
	if (inf->zeros == 1 && inf->precision == -1 && inf->left_align == -1)
		strfilled = fill_stroptions(inf->width, '0');
	else
		strfilled = fill_stroptions(inf->width, ' ');
	if (!strfilled)
		return (NULL);
	if (inf->left_align == 1 && inf->signe)
		ft_strncpy(strfilled + 1, str, str_len);
	else if (inf->left_align == 1)
		ft_strncpy(strfilled, str, str_len);
	else
		ft_strncpy(&strfilled[inf->width - str_len], str, str_len);
	return (print_sign(inf, strfilled, str_len));
}

int				ft_print_d(t_inf *inf, va_list ap, char *str, int fd)
{
	t_strfill	*stroptions;

	(void) ap;
	stroptions = get_stroptions();
	str = get_sign(inf, str);
	str = get_precision(inf, stroptions->precision, str);
	str = get_width(inf, stroptions->width, str);
	if (!str)
	{
		free_stroptions(stroptions);
		return (-1);
	}
	inf->printed += ft_putstr_return(str, fd);
	free_stroptions(stroptions);
	return (0);
}
