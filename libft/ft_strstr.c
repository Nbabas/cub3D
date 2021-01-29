/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:37:45 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 18:10:40 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *tofind)
{
	unsigned int	i;

	i = 0;
	if (*tofind == 0)
		return ((char *)str);
	while (str)
	{
		while (str[i] == tofind[i] && tofind[i])
			i++;
		if (tofind[i] == 0)
			return ((char *)str);
		str++;
		i = 0;
	}
	return (NULL);
}
