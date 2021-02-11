/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 20:31:57 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 16:09:53 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw_weapon(t_data *d)
{
	float	x;
	float	y;
	int		c;
	float	i;
	float	j;

	j = 0;
	y = (float)g_h_resolution * 0.6 - 1;
	while (++y <= (g_h_resolution - 1))
	{
		x = ((float)g_w_resolution * 0.4 - 1);
		i = 0;
		while (x < (float)(g_w_resolution * 0.65 - 1))
		{
			c = d->t[7].addr[(int)((int)j * (d->t[7].w) + (int)i)];
			if (c != -16777216 && c != 0)
				g_img_addr[(int)x + (int)y * g_w_resolution] = c;
			i += (float)(d->t[7].w) / (float)((g_w_resolution) * 0.25);
			x++;
		}
		j += (float)(d->t[7].h - 1) / (float)(g_h_resolution * 0.5);
	}
}

static void		draw_rect(int c)
{
	int			i;
	int			j;
	int			x;
	int			y;

	x = g_w_resolution * 0.375;
	y = g_h_resolution * 0.900;
	j = 0;
	while (j < g_h_resolution / 40)
	{
		i = 0;
		while (i < g_w_resolution / 4)
		{
			if (j == 0 || j == g_h_resolution / 40 - 1 ||
				i == 0 || i == g_w_resolution / 4 - 1)
				if (i + x > 0 && i + x < g_w_resolution &&
					j + y > 0 && j + y < g_h_resolution)
					g_img_addr[(j + y) * g_w_resolution + (i + x)] = c;
			i++;
		}
		j++;
	}
}

static void		fill_life(t_data *d, int c)
{
	int			i;
	int			j;
	int			x;
	int			y;

	x = g_w_resolution * 0.375;
	y = g_h_resolution * 0.900;
	j = 0;
	while (j < g_h_resolution / 40)
	{
		i = 0;
		while (i < d->g.life * (g_w_resolution / 4) / 100)
		{
			if (i + x > 0 && i + x < g_w_resolution &&
				j + y > 0 && j + y < g_h_resolution)
				g_img_addr[(j + y) * g_w_resolution + (i + x)] = c;
			i++;
		}
		j++;
	}
}

void			draw_life(t_data *d)
{
	int			c;

	c = 0;
	(d->g.life > 100) ? d->g.life = 100 : 0;
	(d->g.life > 0) ? c = 0xEC0F0F : 0;
	(d->g.life >= 35) ? c = 0xEC7B0F : 0;
	(d->g.life >= 70) ? c = 0xA8F1A2 : 0;
	draw_rect(c);
	fill_life(d, c);
}
