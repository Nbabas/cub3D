/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:19:46 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/03 17:01:21 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_fov(int px, int py, float pangle, char l_r)
{
	int		y;
	int		x;
	int		i;
	float	angleline;

	y = 0;
	x = 0;
	i = 0;
	if (l_r == 'L')
		angleline = pangle - (g_fov_angle / 2);
	else
		angleline = pangle + (g_fov_angle / 2);
	while (i < 50 * g_mini_scale)
	{
		if (&g_img_addr[(py + y) * g_w_resolution + (px + x)] < g_img_addr)
			return ;
		g_img_addr[(py + y) * g_w_resolution + (px + x)] = 0x0078FF;
		x = cos(angleline) * i;
		y = sin(angleline) * i;
		i++;
	}
}

static void	draw_p_collect(int x, int y, int s, int c)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s)
	{
		j = -1;
		while (++j < s)
			g_img_addr[(i + y - s / 2) * g_w_resolution + (j + x - s / 2)] = c;
	}
}

static void	draw_pixel_map(int x, int y, int c)
{
	int		x_rect;
	int		y_rect;
	int		tmpx;

	x = (x * g_tile_size * g_mini_scale);
	y = (y * g_tile_size * g_mini_scale);
	tmpx = x;
	y_rect = -1;
	while (++y_rect < g_tile_size * g_mini_scale)
	{
		x_rect = -1;
		while (++x_rect < g_tile_size * g_mini_scale)
		{
			g_img_addr[y * g_w_resolution + x] = c;
			x++;
		}
		y++;
		x = tmpx;
	}
}

static void	draw_basics(t_data *d)
{
	int		x;
	int		y;

	y = -1;
	while (++y < d->ymax)
	{
		x = -1;
		while (++x < d->xmax)
		{
			if (d->map[y][x] == '2' ||
				d->map[y][x] == '3' ||
				d->map[y][x] == '0')
			{
				draw_pixel_map(x, y, 0xFFFFFF);
			}
			if (d->map[y][x] == '3')
				draw_p_collect((x + 0.5) * g_tile_size * g_mini_scale,
							(y + 0.5) * g_tile_size * g_mini_scale, 20 * g_mini_scale, 0x47E53A);
		}
	}
}

void		draw_map(t_data *d)
{
	draw_basics(d);
	draw_p_collect(d->p.x * g_mini_scale,
				d->p.y * g_mini_scale,
				d->p.size * g_mini_scale, 0x0078FF);
	draw_fov(d->p.x * g_mini_scale, d->p.y * g_mini_scale, d->p.r_angle, 'L');
	draw_fov(d->p.x * g_mini_scale, d->p.y * g_mini_scale, d->p.r_angle, 'R');
}
