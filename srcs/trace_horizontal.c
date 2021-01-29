/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:36:10 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/28 16:50:42 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int		is_wall(float y, float x, t_data *d)
{
	int		mapx;
	int		mapy;

	if (x < 0 || x > (g_n_col * g_tile_size) ||
		y < 0 || y > (g_n_rows * g_tile_size))
		return (1);
	mapx = floor(x / g_tile_size);
	mapy = floor(y / g_tile_size);
	/*printf("Map[%i][%i] = %c\n",mapx,mapy,d->map[mapy][mapx]);*/
	if (d->map[mapy][mapx] == '1')
		return (1);
	if (d->map[mapy][mapx] == '2' && d->r.distance < INTMAX_MAX)
		put_spr_visible(d,mapx ,mapy);
	return (0);
}

/* static void	trace_horizontal_next(t_ray *r, t_data *d)
{
	while (r->xA >= 0 && r->xA <= g_w_resolution &&
			r->yA >= 0 && r->yA <= g_h_resolution)
	{
		if (is_wall(d->r.yA - r->FaceUp, d->r.xA, d))
		{
				r->hitx_hor = r->xA;
				r->hity_hor = r->yA;
				r->HitVert = 0;
				return ;
		}
		r->xA += r->x_step;
		r->yA += r->y_step;
	}
} */
static void	trace_horizontal_next(t_ray *r, t_data *d)
{
	while (r->xA >= 0 && r->xA <= g_w_resolution &&
			r->yA >= 0 && r->yA <= g_h_resolution)
	{
		if (is_wall(d->r.yA - r->FaceUp, d->r.xA, d))
		{
			if (r->distance > hypot(d->p.x - r->xA, d->p.y - r->yA))
			{
				r->Hitx = r->xA;
				r->Hity = r->yA;
				r->HitVert = 0;
				r->distance = hypot(d->p.x - r->xA, d->p.y - r->yA);
			}
			return ;
		}
		r->xA += r->x_step;
		r->yA += r->y_step;
		}
}

void	trace_horizontal(t_ray *r, t_data *d)
{
	r->yA = floor(d->p.y / g_tile_size) * g_tile_size;
	if (r->FaceDown)
		d->r.yA += g_tile_size;
	r->xA = d->p.x + ((r->yA - d->p.y) / tan(d->r.angle));
	r->y_step = g_tile_size;
	if (r->FaceUp)
		r->y_step *= -1;
	r->x_step = g_tile_size / tan(r->angle);
	if ((r->FaceRight && r->x_step < 0) || (r->FaceLeft && r->x_step > 0))
		r->x_step *= -1;
	//printf("HorizontalCast : X: %f Y:%f || Xtep : %f || Ystep : %f\n", r->xA, r->yA, r->x_step, r->y_step);
	trace_horizontal_next(r, d);
}