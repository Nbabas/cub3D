/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:19:46 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/26 11:13:34 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include "global.h"

static void	draw_fov(int px, int py, float Pangle, char L_R)
{
	int		y;
	int		x;
	int		i;
	float	angleLine;

	y = 0;
	x = 0;
	i = 0;
	if (L_R == 'L')
		angleLine = Pangle - (g_fov_angle / 2);
	else
		angleLine = Pangle + (g_fov_angle / 2);
	while (i < 10)
	{
		if (&g_img_addr[(py + y) * g_w_resolution + (px + x)] < g_img_addr)
			return ;
		g_img_addr[(py + y) * g_w_resolution + (px + x)] = 0x0078FF;
		x = cos(angleLine) * i;
		y = sin(angleLine) * i;
		i++;
	}
}
static void	draw_player(int x, int y, int s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s)
	{
		j = -1;
		while (++j < s)
		{
			g_img_addr[(i + y - s / 2) * g_w_resolution + (j + x - s / 2)]
						= 0x0078FF;
		}
	}
}
static void	draw_pixel_mini_map(int	*m_y, int *m_x, int color, int o_x)
{
	int		y;
	int		x;

	y = 0;
	while (y < (g_tile_size * MINI_SCALE))
	{
		x = 0;
		while (x < (g_tile_size * MINI_SCALE))
		{
			g_img_addr[*m_y * g_w_resolution + *m_x] = color;
			*m_x += 1;
			x++;
		}
		*m_y += 1;
		*m_x = o_x * g_tile_size * MINI_SCALE;
		y++;
	}
}
static void	draw_basics(t_data *d)
{
	int		x;
	int		y;
	int		lx;
	int		ly;

	y = 0;
	while (y < d->ymax)
	{
		x= 0;
		while (x < d->xmax)
		{
			lx = x * g_tile_size * MINI_SCALE;
			ly = y * g_tile_size * MINI_SCALE;
			if (d->map[y][x] == '0')
				draw_pixel_mini_map(&ly, &lx, 0xFFFFFF, x);
			else if (d->map[y][x] == '2')
				draw_pixel_mini_map(&ly, &lx, 0x47E53A, x);
			else if (d->map[y][x] == '1')
				;/*draw_pixel_mini_map(&ly, &lx, 0x0000FF, x);*/
			x++;
		}
		y++;
	}
}
void		draw_map(t_data *d)
{
	draw_basics(d);
	draw_player(d->p.x * MINI_SCALE,
				d->p.y * MINI_SCALE,
				d->p.size);
	draw_fov(d->p.x * MINI_SCALE, d->p.y * MINI_SCALE, d->p.r_angle, 'L');
	draw_fov(d->p.x * MINI_SCALE, d->p.y * MINI_SCALE, d->p.r_angle, 'R');
}