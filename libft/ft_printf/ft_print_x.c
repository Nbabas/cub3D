/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:09:05 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:25:56 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_precision(t_inf *inf, char *strfilled, char *str)
{
	int			str_len;

	str_len = ft_strlen(str);
	if (inf->precision >= 0)
		inf->zeros = -1;
	if (str[0] == '0' && inf->type != 'p')
	{
		inf->hexa = 0;
		if (inf->precision == 0)
			return (str = "");
	}
	if (str[0] == '0' && inf->type == 'p')
	{
		if (inf->precision == 0)
			return (str = "");
	}
	if (inf->precision <= str_len)
		return (str);
	strfilled = fill_stroptions(inf->precision, '0');
	if (!strfilled)
		return (NULL);
	ft_strcpy(&strfilled[inf->precision - str_len], str);
	return (strfilled);
}

static void	get_prefixhexa(t_inf *inf, char *strfilled, int str_len, char conv)
{
	char		prefix[3];

	if (inf->hexa == 0)
		return ;
	prefix[0] = '0';
	prefix[1] = conv;
	prefix[2] = '\0';
	if (inf->left_align == 1 || inf->zeros == 1)
		ft_strncpy(strfilled, prefix, 2);
	else
		ft_strncpy(&strfilled[inf->width - str_len - 2], prefix, 2);
}

static char	*get_width(t_inf *inf, char *strfilled, char *str, char conv)
{
	int			str_len;

	str_len = ft_strlen(str);
	if (!inf->hexa && str_len > inf->width)
		return (str);
	else if (str_len + inf->hexa > inf->width)
		inf->width = str_len + inf->hexa;
	if (inf->zeros == 1 && inf->precision == -1)
		strfilled = fill_stroptions(inf->width, '0');
	else
		strfilled = fill_stroptions(inf->width, ' ');
	if (!strfilled)
		return (NULL);
	get_prefixhexa(inf, strfilled, str_len, conv);
	if (inf->left_align == 1)
		ft_strncpy(&strfilled[inf->hexa], str, str_len);
	else
		ft_strncpy(&strfilled[inf->width - str_len], str, str_len);
	return (strfilled);
}

int			ft_print_x(t_inf *inf, va_list ap, char conv, char *str, int fd)
{
	t_strfill	*stroptions;
	int			i;

	(void) ap;
	i = 0;
	stroptions = get_stroptions();
	str = get_precision(inf, stroptions->precision, str);
	str = get_width(inf, stroptions->width, str, conv);
	if (!str)
		return (0);
	if (conv == 'X')
	{
		while (str[i])
		{
			str[i] = ft_toupper(str[i]);
			i++;
		}
	}
	inf->printed += ft_putstr_return(str, fd);
	free_stroptions(stroptions);
	return (0);
}
