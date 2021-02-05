/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:48:17 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/25 16:37:10 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long long n)
{
	int					len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_lltoa(long long n)
{
	int					len;
	char				*res;
	unsigned long long	ull_nbr;

	len = get_len(n);
	ull_nbr = n;
	if (n < 0)
		ull_nbr = -n;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	while (len >= 0)
	{
		res[len] = ull_nbr % 10 + '0';
		ull_nbr = ull_nbr / 10;
		len--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
