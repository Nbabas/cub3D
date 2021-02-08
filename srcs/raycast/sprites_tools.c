/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:24:06 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/08 17:47:49 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	get_newy(t_data *d, int i)
{
	float	delta_x;
	float	delta_y;
	float	inv_det;
	float	newx;
	float	newy;

	delta_x = d->sprites[i].x - d->p.x;
	delta_y = d->sprites[i].y - d->p.y;
	inv_det = 1.0 / ((d->p.planx * d->p.ydir) - (d->p.xdir * d->p.plany));
	newx = inv_det * (d->p.ydir * delta_x - d->p.xdir * delta_y);
	newy = inv_det * (-d->p.plany * delta_x + d->p.planx * delta_y);
	d->sprites[i].screenx = (int)((g_w_resolution / 2) * (1 + -newx / newy));
	d->sprites[i].newy = newy;
}

void	get_coord_draw(t_spr *spr)
{
	spr->w = spr->size;
	spr->startx = -spr->w / 2 + spr->screenx;
	if (spr->startx < 0)
		spr->startx = 0;
	spr->endx = spr->w / 2 + spr->screenx;
	if (spr->endx >= g_w_resolution)
		spr->endx = g_w_resolution;
	spr->h = spr->size;
	spr->starty = -spr->h / 2 + g_h_resolution / 2;
	if (spr->starty < 0)
		spr->starty = 0;
	spr->endy = spr->h / 2 + g_h_resolution / 2;
	if (spr->endy >= g_h_resolution)
		spr->endy = g_h_resolution;
}

void	update_dist_sprites(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->nb_spr)
	{
		d->sprites[i].dist = hypot(d->p.x - d->sprites[i].x,
							d->p.y - d->sprites[i].y);
	}
}

void	sort_sprites(t_data *d)
{
	int		i;
	int		n;
	int		sorted;
	t_spr	tmp;

	sorted = 0;
	n = d->nb_spr;
	update_dist_sprites(d);
	while (sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < n - 1)
		{
			if (d->sprites[i].dist < d->sprites[i + 1].dist)
			{
				tmp = d->sprites[i];
				d->sprites[i] = d->sprites[i + 1];
				d->sprites[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		n--;
	}
}
