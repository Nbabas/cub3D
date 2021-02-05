/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 03:57:17 by bfleury           #+#    #+#             */
/*   Updated: 2021/02/04 14:16:46 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordlen(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' && *ptr != '\0')
		ptr++;
	return (ptr - str);
}

static int		ft_nbword(char *str)
{

	int				i;
	int				cmp;

	cmp = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == '\t' || str[i] == ' '))
			i++;
		if (str[i] && (str[i] != '\t' && str[i] != ' '))
			cmp++;
		while (str[i] && (str[i] != '\t' && str[i] != ' '))
			i++;
	}
	return (cmp);
}

char			**ft_split_whitespaces(char *str)
{
	int		i;
	char	*tmp;
	char	**result;
	
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (!(result = (char**)malloc((sizeof(char*) * ft_nbword(str)) + 1)))
		return (NULL);
	i = 0;
	while (ft_nbword(str) != 0 && *str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (!(tmp = (char*)malloc(sizeof(char) * ft_wordlen(str) + 1)))
			return (NULL);
		ft_strncpy(tmp, str, ft_wordlen(str));
		tmp[ft_wordlen(str)] = '\0';
		result[i++] = tmp;
		str += ft_wordlen(str);
	}
	result[i] = NULL;
	return (result);
}
