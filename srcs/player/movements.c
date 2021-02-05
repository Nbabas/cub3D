/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:18:47 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 16:24:10 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	wich_collision(t_data *d, int mapx, int mapy)
{
	if (d->map[mapy][mapx] == '3')
	{
		d->map[mapy][mapx] = '0';
		d->nb_spr--;
		d->g.collected++;
		get_sprites(d);
	}
}

void		update_player(t_data *d, int step, char var)
{
	int		tmpx;
	int		tmpy;

	tmpx = (int)floor(d->p.x / g_tile_size);
	tmpy = (int)floor(d->p.y / g_tile_size);
	if (d->map[tmpy][tmpx] == '1' || d->map[tmpy][tmpx] == '2')
	{
		if (var == 'x')
			d->p.x = d->p.x - cos(d->p.r_angle) * step;
		else if (var == 'y')
			d->p.y = d->p.y - sin(d->p.r_angle) * step;
		else if (var == 'l')
		{
			d->p.x = d->p.x + d->p.ydir * d->p.speed;
			d->p.y = d->p.y - d->p.xdir * d->p.speed;
		}
		else if (var == 'r')
		{
			d->p.x = d->p.x - d->p.ydir * d->p.speed;
			d->p.y = d->p.y + d->p.xdir * d->p.speed;
		}
	}
	wich_collision(d, tmpx, tmpy);
}

static void	update_var_angle(t_data *d)
{
	float	tmpx;
	float	tmpplanx;
	float	tmpangle;

	tmpx = d->p.xdir;
	tmpplanx = d->p.planx;
	tmpangle = d->p.turn_dir * d->p.r_speed;
	d->p.xdir = d->p.xdir * cos(tmpangle) - d->p.ydir * sin(tmpangle);
	d->p.ydir = tmpx * sin(tmpangle) + d->p.ydir * cos(tmpangle);
	d->p.planx = d->p.planx * cos(tmpangle) - d->p.plany * sin(tmpangle);
	d->p.plany = tmpplanx * sin(tmpangle) + d->p.plany * cos(tmpangle);
}

void		p_moves(t_data *d)
{
	float	step;

	step = d->p.walk_dir * d->p.speed;
	d->p.r_angle += d->p.turn_dir * d->p.r_speed;
	d->p.x = d->p.x + cos(d->p.r_angle) * step;
	update_player(d, step, 'x');
	d->p.y = d->p.y + sin(d->p.r_angle) * step;
	update_player(d, step, 'y');
	if (d->p.rightstep == 1 && d->p.leftstep == 0)
	{
		d->p.x = d->p.x - d->p.ydir * d->p.speed;
		d->p.y = d->p.y + d->p.xdir * d->p.speed;
		update_player(d, step, 'l');
	}
	else if (d->p.leftstep == 1 && d->p.rightstep == 0)
	{
		d->p.x = d->p.x + d->p.ydir * d->p.speed;
		d->p.y = d->p.y - d->p.xdir * d->p.speed;
		update_player(d, step, 'r');
	}
	update_var_angle(d);
}
