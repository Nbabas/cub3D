/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:09:25 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/03 17:06:19 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	trace_vertical_next(t_ray *r, t_data *d)
{
	while (r->xa >= 0 && r->xa <= g_w_resolution &&
			r->ya >= 0 && r->ya <= g_h_resolution)
	{
		if (is_wall(d->r.ya, d->r.xa - r->faceleft, d))
		{
			if (r->distance > hypot(d->p.x - r->xa, d->p.y - r->ya))
			{
				r->hitx = r->xa;
				r->hity = r->ya;
				r->hitvert = 1;
				r->distance = hypot(d->p.x - r->xa, d->p.y - r->ya);
			}
			return ;
		}
		r->xa += r->x_step;
		r->ya += r->y_step;
	}
}

void		trace_vertical(t_ray *r, t_data *d)
{
	r->xa = floor(d->p.x / g_tile_size) * g_tile_size;
	if (r->faceright)
		d->r.xa += g_tile_size;
	r->ya = d->p.y + ((r->xa - d->p.x) * tan(d->r.angle));
	r->x_step = g_tile_size;
	if (r->faceleft)
		r->x_step *= -1;
	r->y_step = g_tile_size * tan(r->angle);
	if ((r->facedown && r->y_step < 0) || (r->faceup && r->y_step > 0))
		r->y_step *= -1;
	trace_vertical_next(r, d);
}
