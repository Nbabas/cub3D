/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:11:00 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 10:31:03 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_pressed(int keycode, t_data *d)
{
	if (keycode == UP_ARROW || keycode == W)
		d->p.walk_dir = 1;
	else if (keycode == DOWN_ARROW || keycode == S)
		d->p.walk_dir = -1;
	else if (keycode == LEFT_ARROW)
		d->p.turn_dir = -1;
	else if (keycode == RIGHT_ARROW)
		d->p.turn_dir = 1;
	else if (keycode == A)
		d->p.leftstep = 1;
	else if (keycode == D)
		d->p.rightstep = 1;
	else if (keycode == SPACE_BAR)
	{
		if ((int)g_mini_scale == 0)
			g_mini_scale = 1.0;
		else
			g_mini_scale = .2;
	}
	else if (keycode == TAB)
	{
		if (PLATFORM == 1)
			system("afplay ./textures/beh.mp3 -t 1 &");
		else if (PLATFORM == 2)
			system("mpg123 ./textures/beh.mp3 &");
	}
	else if (keycode == ESC)
		ft_exit(d);
	return (SUCCESS);
}

int	key_released(int keycode, t_data *d)
{
	(void)d;
	(void)keycode;
	if (keycode == UP_ARROW || keycode == W)
		d->p.walk_dir = 0;
	else if (keycode == DOWN_ARROW || keycode == S)
		d->p.walk_dir = 0;
	else if (keycode == LEFT_ARROW)
		d->p.turn_dir = 0;
	else if (keycode == RIGHT_ARROW)
		d->p.turn_dir = 0;
	else if (keycode == A)
		d->p.leftstep = 0;
	else if (keycode == D)
		d->p.rightstep = 0;
	return (SUCCESS);
}

int	listen_actions(t_data *d)
{
	if (PLATFORM == 1)
	{
		mlx_hook(g_mlx_win, 2, 0, key_pressed, d);
		mlx_hook(g_mlx_win, 3, 17, key_released, d);
		mlx_hook(g_mlx_win, 17, 0, ft_exit, d);
	}
	else if (PLATFORM == 2)
	{
		mlx_hook(g_mlx_win, 2, 1L << 0, key_pressed, d);
		mlx_hook(g_mlx_win, 3, 1L << 1, key_released, d);
		mlx_hook(g_mlx_win, 33, 1L << 17, ft_exit, d);
	}
	mlx_loop_hook(g_mlx_ptr, raycast_process, d);
	mlx_loop(g_mlx_ptr);
	return (SUCCESS);
}