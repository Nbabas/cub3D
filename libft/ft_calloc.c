/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:48:26 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/23 13:54:01 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Return pointer to memory zone allocated for n members of size each.
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tmp;

	tmp = malloc(size * nmemb);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, size * nmemb);
	return (tmp);
}
