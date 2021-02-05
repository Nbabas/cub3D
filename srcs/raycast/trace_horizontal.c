/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:36:10 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 16:10:11 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int			is_wall(float y, float x, t_data *d)
{
	int		mapx;
	int		mapy;

	if (x < 0 || x > (g_n_col * g_tile_size) ||
		y < 0 || y > (g_n_rows * g_tile_size ))
		return (1);
	mapx = floor(x / g_tile_size);
	mapy = floor(y / g_tile_size);
	if (d->map[mapy][mapx] == '1')
		return (1);
	return (0);
}

static void	trace_horizontal_next(t_ray *r, t_data *d)
{
	while (r->xa >= 0 && r->xa <= d->xmax * g_tile_size &&
			r->ya >= 0 && r->ya <= d->ymax * g_tile_size)
	{
		if (is_wall(d->r.ya - r->faceup, d->r.xa, d))
		{
			if (r->distance > hypot(d->p.x - r->xa, d->p.y - r->ya))
			{
				r->hitx = r->xa;
				r->hity = r->ya;
				r->hitvert = 0;
				r->distance = hypot(d->p.x - r->xa, d->p.y - r->ya);
			}
			return ;
		}
		r->xa += r->x_step;
		r->ya += r->y_step;
	}
}

void		trace_horizontal(t_ray *r, t_data *d)
{
	r->ya = floor(d->p.y / g_tile_size) * g_tile_size;
	if (r->facedown)
		d->r.ya += g_tile_size;
	r->xa = d->p.x + ((r->ya - d->p.y) / tan(d->r.angle));
	r->y_step = g_tile_size;
	if (r->faceup)
		r->y_step *= -1;
	r->x_step = g_tile_size / tan(r->angle);
	if ((r->faceright && r->x_step < 0) || (r->faceleft && r->x_step > 0))
		r->x_step *= -1;
	trace_horizontal_next(r, d);
}
