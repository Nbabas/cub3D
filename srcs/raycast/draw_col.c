/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_col.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:10:13 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/10 17:25:28 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		get_id_text(t_ray *r)
{
	if (r->hitvert == 0 && r->faceup)
		return (0);
	if (r->hitvert == 0 && r->facedown)
		return (1);
	if (r->hitvert && r->faceleft)
		return (2);
	if (r->hitvert && r->faceright)
		return (3);
	return (ERROR);
}

void	put_pixel_text(t_data *d, t_ray *r, t_wall *w)
{
	int		color;
	int		xtext;
	int		ytext;
	int		id_t;

	id_t = get_id_text(r);
	if (r->hitvert == 1)
		xtext = (int)(r->hity * d->t[id_t].w / g_tile_size) % d->t[id_t].w;
	else
		xtext = (int)(r->hitx * d->t[id_t].w / g_tile_size) % d->t[id_t].w;
	while (w->start < w->end)
	{
		ytext = w->start + (w->h / 2) - (g_h_resolution / 2);
		ytext = ytext * ((float)d->t[id_t].h / w->h);
		color = d->t[id_t].addr[(d->t[id_t].w * ytext) + xtext];
		if (color != 0x000000 && color != -16777216)
			g_img_addr[(w->start * g_w_resolution) + r->i] = color;
		w->start++;
	}
}

void	draw_column(t_ray *r, t_data *d, t_wall *w)
{
	w->good_dist = r->distance * cos(r->angle - d->p.r_angle);
	d->buff[r->i] = r->distance;
	w->h = (g_tile_size / w->good_dist) * w->dist;
	w->start = (g_h_resolution / 2) - (w->h / 2);
	if (w->start < 0)
		w->start = 0;
	w->end = (g_h_resolution / 2) + (w->h / 2);
	if (w->end > g_h_resolution)
		w->end = g_h_resolution;
	put_pixel_text(d, r, w);
}

void	draw_background(t_data *d)
{
	int x;
	int y;

	y = -1;
	while (++y < g_h_resolution)
	{
		x = -1;
		while (++x < g_w_resolution)
		{
			if (y < g_h_resolution / 2)
				g_img_addr[(y * g_w_resolution + x)] = d->c_color;
			else
				g_img_addr[(y * g_w_resolution + x)] = d->f_color;
		}
	}
}
