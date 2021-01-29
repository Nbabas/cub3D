/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:39:07 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 17:01:21 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*next;

	cursor = *lst;
	while (cursor)
	{
		next = cursor->next;
		ft_lstdelone(cursor, del);
		cursor = next;
	}
	*lst = 0;
}
