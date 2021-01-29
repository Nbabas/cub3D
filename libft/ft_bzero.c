/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:22:27 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 16:37:03 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The bzero() function sets the first n bytes
**	of the area starting at s to zero (bytes containing aq\0aq).
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;
	unsigned char	*ptr;

	i = 0;
	if (n <= 0)
		return ;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = '\0';
}
