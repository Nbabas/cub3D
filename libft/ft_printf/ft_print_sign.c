/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:34:32 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/25 16:46:06 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_sign(t_inf *inf, char *str)
{
	if (str[0] == '-')
	{
		inf->signe = '-';
		str++;
	}
	else if (inf->plus == 1)
		inf->signe = '+';
	else if (inf->space == 1)
		inf->signe = ' ';
	return (str);
}

char	*print_sign(t_inf *inf, char *strfilled, int str_len)
{
	if (!inf->signe)
		return (strfilled);
	if (inf->left_align == 1 || (inf->zeros == 1 && inf->precision == -1))
		strfilled[0] = inf->signe;
	else
		strfilled[inf->width - str_len - 1] = inf->signe;
	return (strfilled);
}
