/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:50:18 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 18:10:12 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (*tofind == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] == tofind[j] && (i + j) < n)
		{
			j++;
			if (tofind[j] == 0)
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}
