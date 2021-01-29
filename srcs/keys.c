/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:11:00 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/25 13:55:13 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"



static int	key_pressed(int keycode, t_data *d)
{
	if (keycode == UP_ARROW)
		d->p.walk_dir = 1;
	else if (keycode == DOWN_ARROW)
		d->p.walk_dir = -1;
	else if (keycode == LEFT_ARROW)
		d->p.turn_dir = -1;
	else if (keycode == RIGHT_ARROW)
		d->p.turn_dir = 1;
	else if (keycode == 53)
		ft_exit(d);
	return (SUCCESS);
}

static int	key_released(int keycode, t_data *d)
{
	(void)d;
	(void)keycode;
	if (keycode == UP_ARROW)
		d->p.walk_dir = 0;
	else if (keycode == DOWN_ARROW)
		d->p.walk_dir = 0;
	else if (keycode == LEFT_ARROW)
		d->p.turn_dir = 0;
	else if (keycode == RIGHT_ARROW)
		d->p.turn_dir = 0;
	return (SUCCESS);
}

int	listen_actions(t_data *d)
{
	mlx_hook(g_mlx_win, 2, 0, key_pressed, d);
	mlx_hook(g_mlx_win, 3, 17, key_released, d);
	mlx_hook(g_mlx_win, 17, 0, ft_exit, d);
	mlx_loop_hook(g_mlx_ptr, raycast_process, d);
	mlx_loop(g_mlx_ptr);
	return (SUCCESS);
}