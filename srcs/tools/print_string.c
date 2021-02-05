/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:29:10 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 16:46:00 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		write_nbr_in(char *str, int nbr, int start)
{
	int	len;
	int tmp;

	len = 1;
	tmp = nbr;
	while (tmp > 9)
	{
		len++;
		tmp = tmp / 10;
	}
	if (nbr == 0)
		str[start++] = '0';
	else
	{
		tmp = len;
		while (nbr > 0)
		{
			str[start + --tmp] = "0123456789"[nbr % 10];
			nbr = nbr / 10;
		}
		start += len;
	}
	str[start] = 0;
	return (start);
}

int		write_str_in(char str[], char *s, int start)
{
	int i;

	i = 0;
	while (s[i])
		str[start++] = s[i++];
	str[start] = 0;
	return (start);
}

void check_strings(t_data *d)
{

	char str[50];
	int i;

	i = 0;
	if (d->minimap == 0)
		mlx_string_put(g_mlx_ptr, g_mlx_win, 5,
						10, 0x000000, "Map Too Big");

	if (d->g.tocollect > 0)
	{
		i = write_str_in(str, "Items : ", 0);
		i = write_str_in(str, " / ", write_nbr_in(str, d->g.collected, i));
		i = write_nbr_in(str, d->g.tocollect, i);
		if (d->g.collected == d->g.tocollect)
			mlx_string_put(g_mlx_ptr, g_mlx_win, g_w_resolution / 2 - 50,
						g_h_resolution / 2, 0x000000, "T'es trop fort!");
		else
			mlx_string_put(g_mlx_ptr, g_mlx_win, g_w_resolution - 100,
						g_h_resolution - 20, 0x000000, str);
	}
}