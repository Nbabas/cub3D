/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:52:01 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/19 17:52:22 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u_nbr;

	u_nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u_nbr = -n;
	}
	if (u_nbr > 9)
		ft_putnbr_fd(u_nbr / 10, fd);
	ft_putchar_fd((char)(u_nbr % 10 + '0'), fd);
}
