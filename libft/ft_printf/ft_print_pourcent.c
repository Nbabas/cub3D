/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pourcent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:09:32 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:25:24 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*put_width(t_inf *inf, char *strfilled, char c)
{
	if (inf->width < 2)
		inf->width = 1;
	if (inf->zeros == 1 && inf->left_align == -1)
		strfilled = fill_stroptions(inf->width, '0');
	else
		strfilled = fill_stroptions(inf->width, ' ');
	if (!strfilled)
		return (NULL);
	if (inf->left_align == 1)
		strfilled[0] = c;
	else
		strfilled[inf->width - 1] = c;
	return (strfilled);
}

int			ft_print_pourcent(t_inf *inf, va_list ap, char c, int fd)
{
	t_strfill	*stroptions;
	char		*str;

	(void) ap;
	stroptions = get_stroptions();
	str = put_width(inf, stroptions->width, c);
	inf->printed += ft_putstr_return(str, fd);
	free_stroptions(stroptions);
	return (0);
}
