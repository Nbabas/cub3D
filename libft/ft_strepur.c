/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strepur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 00:52:20 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/17 20:57:09 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	count;
	char	*str;

	count = 0;
	str = NULL;
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str)
	{
		while (count < size + 1)
		{
			str[count] = '\0';
			count++;
		}
	}
	return (str);
}

static int	ft_count_spaces(char *str)
{
	int	count;
	int	count_spaces;

	count = 0;
	count_spaces = 0;
	while (str[count])
	{
		if (str[count] == ' ')
			count_spaces++;
		count++;
	}
	return (count_spaces);
}

char		*ft_strepur(char *str)
{
	int		count;
	int		count_str;
	char	*str_new;

	count = 0;
	count_str = 0;
	str_new = ft_strnew(ft_strlen(str) - ft_count_spaces(str));
	while (str[count_str])
	{
		if (str[count_str] == ' ' || str[count_str] == '\t')
			count_str++;
		else
		{
			str_new[count] = str[count_str];
			count++;
			count_str++;
		}
	}
	return (str_new);
}