/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:18:47 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/29 12:32:15 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void		update_player(t_data *d, int step, char x_y)
{
	int		tmpx;
	int		tmpy;

	tmpx = (int)floor(d->p.x / g_tile_size);
	tmpy = (int)floor(d->p.y / g_tile_size);
	if (x_y == 'x')
	{
		if (d->map[tmpy][tmpx] == '1' )
			d->p.x = d->p.x - cos(d->p.r_angle) * step;
	}
	else
		if (d->map[tmpy][tmpx] == '1' )
			d->p.y = d->p.y - sin(d->p.r_angle) * step;

	if (d->map[tmpy][tmpx] == '2')
	{
		d->map[tmpy][tmpx] = '0';
		d->nb_spr--;
		get_sprites(d);
	}
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
	update_var_angle(d);
/* 	if (is_wall(new_py,new_px,d) == 0)
	{
		d->p.x = new_px;
		d->p.y = new_py;
	} */
	//printf("map[%i][%i] = %c\n", tmpx, tmpy, d->map[tmpy][tmpx]);
}