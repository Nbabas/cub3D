/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:12:35 by nbascaul          #+#    #+#             */
/*   Updated: 2020/11/25 11:55:22 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_infos(t_inf *inf)
{
	inf->width = -1;
	inf->precision = -1;
	inf->plus = -1;
	inf->space = -1;
	inf->len_modif = -1;
	inf->zeros = -1;
	inf->left_align = -1;
	inf->hexa = 0;
	inf->signe = '\0';
	inf->type = '\0';
}
