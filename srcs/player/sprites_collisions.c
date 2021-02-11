/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_collisions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:51:37 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 14:28:26 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ennemy_collision(t_data *d, int mapx, int mapy)
{
	if (d->g.weapon && d->p.walk_dir == 1)
	{
		d->map[mapy][mapx] = '0';
		d->nb_spr--;
		play_sound('A');
	}
	else
	{
		d->g.life -= 5;
		play_sound('H');
		if (d->g.life <= 0 && d->g.weapon)
			d->map[mapy][mapx] = '5';
	}
}

void	towin_collision(t_data *d, int mapx, int mapy)
{
	d->map[mapy][mapx] = '0';
	d->g.collected++;
	d->nb_spr--;
	if (d->g.collected == d->g.tocollect)
		play_sound('E');
	else
		play_sound('I');
}

void	health_collision(t_data *d, int mapx, int mapy)
{
	d->map[mapy][mapx] = '0';
	d->nb_spr--;
	d->g.life += 10;
	play_sound('I');
}

void	weapon_collision(t_data *d, int mapx, int mapy)
{
	if (d->g.weapon == 0)
	{
		d->g.weapon = 1;
		d->map[mapy][mapx] = '0';
		d->nb_spr--;
	}
}
