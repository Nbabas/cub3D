/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:27:25 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 15:52:47 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		ft_init_sprites(t_data *d)
{
	d->buff = malloc(sizeof(float) * g_w_resolution);
	if (d->buff == NULL)
		ft_error(d, MALLOC_ERROR, "");
	ft_bzero(d->buff, sizeof(float) * g_w_resolution);
	get_sprites(d);
}

void		ft_next_init(t_data *d)
{
	d->nb_spr = 0;
	d->sprites = NULL;
	d->t[0].img = NULL;
	d->t[1].img = NULL;
	d->t[2].img = NULL;
	d->t[3].img = NULL;
	d->t[4].img = NULL;
	d->t[5].img = NULL;
	d->g.collected = 0;
	d->g.tocollect = 0;
	d->bmp = 0;
	d->minimap = 1;
}

void		ft_init(t_data *d)
{
	d->w_resolution = 0;
	d->h_resolution = 0;
	d->c_color = -1;
	d->f_color = -1;
	d->fd = -1;
	d->line = NULL;
	d->infos = NULL;
	d->map = NULL;
	d->err = 0;
	d->xmax = 0;
	d->ymax = 0;
	d->por = '?';
	d->px = 0;
	d->py = 0;
	ft_next_init(d);
}

void		ft_init_global(t_data *d)
{
	g_tile_size = (d->w_resolution / d->xmax);
	g_n_rows = d->ymax;
	g_n_col = d->xmax;
	g_n_rays = g_w_resolution;
	g_fov_angle = (60 * (M_PI / 180));
}
