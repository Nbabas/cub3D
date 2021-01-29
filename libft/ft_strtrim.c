/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:02:00 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 18:11:06 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Return an allocated (malloc) copy of S without any char from set at
**	beginning and at the end of S.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s;
	char	*newstr;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len_s = ft_strlen(s1);
	while (len_s && ft_strchr(set, s1[len_s]))
		len_s--;
	newstr = ft_substr((char*)s1, 0, len_s + 1);
	if (newstr == NULL)
		return (NULL);
	return (newstr);
}
