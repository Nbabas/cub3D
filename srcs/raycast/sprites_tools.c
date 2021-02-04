/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:24:06 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/03 17:08:41 by nbascaul         ###   ########.fr       */
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

void	sort_sprites(t_data *d)
{
	int		i;
	int		n;
	int		sorted;
	t_spr	tmp;

	sorted = 0;
	n = d->nb_spr;
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

float	calcul_angle(t_data *d, float x, float y)
{
	float	vx;
	float	vy;
	float	angle_p_spr;
	float	angle_p;
	float	angle_spr;

	vx = x - d->p.x;
	vy = y - d->p.y;
	angle_p_spr = atan2(vy, vx);
	angle_p = get_angle(d->p.r_angle);
	angle_spr = angle_p - angle_p_spr;
	if (angle_spr < -M_PI)
		angle_spr += 2 * M_PI;
	if (angle_spr > M_PI)
		angle_spr -= 2 * M_PI;
	angle_spr = fabs(angle_spr);
	return (angle_spr);
}

int		is_visible(t_data *d, int i)
{
	float	angle_a;
	float	angle_b;
	float	angle_c;
	float	size;
	float	fov;

	size = d->sprites[i].size;
	angle_a = fabs(calcul_angle(d, d->sprites[i].x, d->sprites[i].y));
	angle_b = fabs(calcul_angle(d, d->sprites[i].x + size,
								d->sprites[i].y + size));
	angle_c = fabs(angle_b - angle_a);
	fov = g_fov_angle / 2 + angle_c;
	if (angle_a < fov)
		return (1);
	return (0);
}
