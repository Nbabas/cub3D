/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:13:33 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/16 17:30:22 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	c_is_in_s(char c, char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_putstr_return(char *str, int fd)
{
	int len;

	len = ft_strlen(str);
	write(fd, str, len);
	return (len);
}

int	ft_putchar_return(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
