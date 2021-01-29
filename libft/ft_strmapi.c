/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:51:48 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 18:03:38 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Apply the function (f) to any char of S. and return a new allocated str.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	if (!s || !f)
		return (NULL);
	i = 0;
	dest = ft_strdup(s);
	if (!dest)
		return (NULL);
	while (dest[i])
	{
		dest[i] = f(i, dest[i]);
		i++;
	}
	return (dest);
}
