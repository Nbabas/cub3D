/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:09:25 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/28 11:43:32 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

/* static void	trace_vertical_next(t_ray *r, t_data *d)
{
	while (r->xA >= 0 && r->xA <= g_w_resolution &&
			r->yA >= 0 && r->yA <= g_h_resolution)
	{
		if (is_wall(d->r.yA, d->r.xA  - r->FaceLeft, d))
		{
				r->hitx_vert = r->xA;
				r->hity_vert = r->yA;
				r->HitVert = 1;
				return ;
		}
		r->xA += r->x_step;
		r->yA += r->y_step;
	}
} */
static void	trace_vertical_next(t_ray *r, t_data *d)
{
	while (r->xA >= 0 && r->xA <= g_w_resolution &&
			r->yA >= 0 && r->yA <= g_h_resolution)
	{
		if (is_wall(d->r.yA, d->r.xA  - r->FaceLeft, d))
		{
			//printf("\n*********\nVerticalCast \n X: %f Y:%f || Xtep : %f || Ystep : %f\n Distance save : %f || Hitx %f || Hity %f\n******\n", r->xA, r->yA, r->x_step, r->y_step, r->distance, r->Hitx, r->Hity);
			if (r->distance > hypot(d->p.x - r->xA, d->p.y - r->yA))
			{
				r->Hitx = r->xA;
				r->Hity = r->yA;
				r->HitVert = 1;
				r->distance = hypot(d->p.x - r->xA, d->p.y - r->yA);
				//printf("-------------------\n Distance updated : %f\n-------------\n", r->distance);

			}
			return ;
		}
		r->xA += r->x_step;
		r->yA += r->y_step;
	}
}

void	trace_vertical(t_ray *r, t_data *d)
{
	r->xA = floor(d->p.x / g_tile_size) * g_tile_size;
	if (r->FaceRight)
		d->r.xA += g_tile_size;
	r->yA = d->p.y + ((r->xA - d->p.x) * tan(d->r.angle));
	r->x_step = g_tile_size;
	if (r->FaceLeft)
		r->x_step *= -1;
	r->y_step = g_tile_size * tan(r->angle);
	if ((r->FaceDown && r->y_step < 0) || (r->FaceUp && r->y_step > 0))
		r->y_step *= -1;

	trace_vertical_next(r, d);
}