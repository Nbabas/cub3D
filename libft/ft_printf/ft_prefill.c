/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:21:44 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/25 11:55:47 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_strfill	*get_stroptions(void)
{
	t_strfill	*stroptions;

	stroptions = malloc(sizeof(t_strfill));
	if (!stroptions)
		return (NULL);
	stroptions->precision = NULL;
	stroptions->width = NULL;
	return (stroptions);
}

char		*fill_stroptions(int size, char tofill)
{
	char		*strfilled;

	strfilled = malloc(sizeof(char) * (size + 1));
	if (!strfilled)
		return (NULL);
	ft_memset(strfilled, tofill, size);
	strfilled[size] = '\0';
	return (strfilled);
}

void		free_stroptions(t_strfill *stroptions)
{
	if (stroptions->width)
		free(stroptions->width);
	if (stroptions->precision)
		free(stroptions->precision);
	free(stroptions);
}
