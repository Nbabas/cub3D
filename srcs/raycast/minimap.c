/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:19:46 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 15:38:27 by nbascaul         ###   ########.fr       */
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


int	draw_pixel_map(int x, int y, int c)
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
			if (y * g_w_resolution + x < (g_w_resolution * g_h_resolution))
				g_img_addr[y * g_w_resolution + x] = c;
			else
				return (ERROR);
			x++;
		}
		y++;
		x = tmpx;
	}
	return (SUCCESS);
}

int	draw_basics(t_data *d)
{
	int		x;
	int		y;
	char	c;

 	y = -1;
	while (++y < d->ymax)
	{
		x = -1;
		while (++x < d->xmax)
		{
			c = d->map[y][x];
			if (c == '2' || c == '3' || c == '0')
				if (draw_pixel_map(x, y, 0xFFFFFF) < 0)
					return (ERROR);
			if (c == '3')
				draw_p_collect((x + 0.5) * g_tile_size * g_mini_scale,
							(y + 0.5) * g_tile_size * g_mini_scale, 20 * g_mini_scale, 0x47E53A);
		}
	}
	return (SUCCESS);
}

void		draw_map(t_data *d)
{
	int pixelmaxx;
	int pixelmaxy;

	pixelmaxx = (d->xmax * g_tile_size * g_mini_scale);
	pixelmaxy = (d->ymax * g_tile_size * g_mini_scale);
	if (pixelmaxx > g_w_resolution || pixelmaxy > g_h_resolution)
	{
		d->minimap = 0;
		return ;
	}
	if (draw_basics(d) < 0)
		;
	draw_p_collect(d->p.x * g_mini_scale,
				d->p.y * g_mini_scale,
				d->p.size * g_mini_scale, 0x0078FF);
	draw_fov(d->p.x * g_mini_scale, d->p.y * g_mini_scale, d->p.r_angle, 'L');
	draw_fov(d->p.x * g_mini_scale, d->p.y * g_mini_scale, d->p.r_angle, 'R');

}
