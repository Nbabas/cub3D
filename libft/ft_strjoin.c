/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:47:47 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 18:04:48 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  Return allocated String from concatenation of s1 and s2.
**  Return NULL if allocation fails.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1, len_s1 + 1);
	ft_strlcat(newstr + len_s1, s2, len_s2 + 1);
	return (newstr);
}
