/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:07:04 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/09 16:10:56 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	get_p_dir_next(t_data *d)
{
	if (d->por == 'N')
	{
		d->p.r_angle = 1.5 * M_PI;
		d->p.xdir = 0;
		d->p.ydir = -1;
		d->p.planx = -0.55;
		d->p.plany = 0;
	}
	else if (d->por == 'S')
	{
		d->p.r_angle = 0.5 * M_PI;
		d->p.xdir = 0;
		d->p.ydir = 1;
		d->p.planx = 0.55;
		d->p.plany = 0;
	}
}

static void	get_p_dir(t_data *d)
{
	if (d->por == 'W')
	{
		d->p.r_angle = M_PI;
		d->p.xdir = -1;
		d->p.ydir = 0;
		d->p.planx = 0;
		d->p.plany = 0.55;
	}
	else if (d->por == 'E')
	{
		d->p.r_angle = 0;
		d->p.xdir = 1;
		d->p.ydir = 0;
		d->p.planx = 0;
		d->p.plany = -0.55;
	}
	get_p_dir_next(d);
}

void		ft_init_player(t_data *d)
{
	d->p.x = g_tile_size * d->px + g_tile_size / 2;
	d->p.y = g_tile_size * d->py + g_tile_size / 2;
	d->p.turn_dir = 0;
	d->p.walk_dir = 0;
	d->p.leftstep = 0;
	d->p.rightstep = 0;
	d->p.speed = (1.01646 - (0.00000326584 * (d->xmax * d->ymax))) * P_SPEED;
	d->p.speed = (d->p.speed * P_SPEED);
	d->p.r_speed = R_SPEED * (M_PI / 180);
	d->p.size = 5;
	get_p_dir(d);
}
