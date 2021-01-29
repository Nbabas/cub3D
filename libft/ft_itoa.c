/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:40:17 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 16:50:03 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getintlen(int n)
{
	int				i;
	unsigned int	u_nbr;

	u_nbr = n;
	i = 0;
	if (n < 0 || n == 0)
	{
		i++;
		u_nbr = -n;
	}
	while (u_nbr)
	{
		i++;
		u_nbr = u_nbr / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int				len;
	char			*res;
	unsigned int	u_nbr;

	len = ft_getintlen(n);
	u_nbr = n;
	if (n < 0)
		u_nbr = -n;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len--] = '\0';
	while (len >= 0)
	{
		res[len] = u_nbr % 10 + '0';
		u_nbr = u_nbr / 10;
		len--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
