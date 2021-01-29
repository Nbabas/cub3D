/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:27:25 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/28 17:09:51 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_sprites(t_data *d)
{

	d->buff = malloc(sizeof(float) * g_w_resolution);
	if (d->buff == NULL)
		ft_error(d,MALLOC_ERROR,"");
	//ft_bzero(d->buff, sizeof(float) * g_w_resolution);
	get_sprites(d);
}

void	ft_init(t_data *d)
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
	d->Por = '?';
	d->Px = 0;
	d->Py = 0;
	d->nb_spr = 0;
	d->sprites = NULL;

	}

void	ft_init_global(t_data *d)
{
	g_tile_size = (d->w_resolution / d->xmax);
	g_w_resolution = d->w_resolution;
	g_h_resolution = d->h_resolution;
	g_n_rows = d->ymax;
	g_n_col = d->xmax;
	g_n_rays = g_w_resolution;
	g_map = (char **)d->map;
	g_fov_angle = (60 * (M_PI / 180));

}
static void	get_p_dir_next(t_data *d)
{
	if (d->Por == 'N')
	{
		d->p.r_angle = 1.5 * M_PI;
		d->p.xdir = 0;
		d->p.ydir = -1;
		d->p.planx = -0.66;
		d->p.plany = 0;
	}
	else if (d->Por == 'S')
	{
		d->p.r_angle = 0.5 * M_PI;
		d->p.xdir = 0;
		d->p.ydir = 1;
		d->p.planx = 0.66;
		d->p.plany = 0;
	}
}
static void	get_p_dir(t_data *d)
{
	if (d->Por == 'W')
	{
		d->p.r_angle = M_PI;
		d->p.xdir = -1;
		d->p.ydir = 0;
		d->p.planx = 0;
		d->p.plany = 0.6;
	}
	else if (d->Por == 'E')
	{
		d->p.r_angle = 0;
		d->p.xdir = 1;
		d->p.ydir = 0;
		d->p.planx = 0;
		d->p.plany = -0.6;
	}
	get_p_dir_next(d);

}
void	ft_init_player(t_data *d)
{
	d->p.x = g_tile_size * d->Px + g_tile_size / 2;
	d->p.y = g_tile_size * d->Py + g_tile_size / 2;
	d->p.turn_dir = 0;
	d->p.walk_dir = 0;
	d->p.speed = P_SPEED;
	d->p.r_speed = R_SPEED * (M_PI / 180);
	printf("nb de cases x:%i * y:%i = %i\n",d->xmax, d->ymax,d->xmax * d->ymax);
	d->p.size = 5;//floor((d->xmax * d->ymax) * -0.004122 + 15.47403132);
	printf("P.size = %d\n", d->p.size);
	get_p_dir(d);
}