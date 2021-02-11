/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:52:43 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/10 19:55:12 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			get_rgb(char **rgb_tab)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(rgb_tab[0]);
	g = ft_atoi(rgb_tab[1]);
	b = ft_atoi(rgb_tab[2]);
	return ((r << 16) + (g << 8) + b);
}
