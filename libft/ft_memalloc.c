/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:05:35 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 17:11:52 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ptrmem;

	ptrmem = malloc(size);
	if (ptrmem == NULL)
		return (NULL);
	else
	{
		ft_bzero(ptrmem, size);
		return (ptrmem);
	}
}
