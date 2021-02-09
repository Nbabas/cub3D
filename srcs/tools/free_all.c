/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:38:07 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/09 21:43:05 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	next_free_all(t_data *d)
{
	int		i;

	i = -1;
	while (++i <= 5)
	{
		if (PLATFORM == 2 && d->t[i].img)
			mlx_destroy_image(g_mlx_ptr, d->t[i].img);
		else if (PLATFORM == 1 && d->t[i].img)
		{
			free(d->t[i].img);
			d->t[i].img = 0;
			free(d->t[i].addr);
			d->t[i].addr = 0;
		}
	}
	free(d);
	if (g_mlx_win)
		mlx_destroy_window(g_mlx_ptr, g_mlx_win);
}

void		free_all(t_data *d)
{
	if (d->map)
		free_tab(d->map, "", 0, d->ymax);
	if (d->sprites)
		free(d->buff);
	if (d->sprites)
		free(d->sprites);
	if (d->err < 0 && d->line && check_config(d) < 0)
	{
		if (d->infos[0])
			free_tab(d->infos, d->line, ' ', 0);
		ft_free(d->line);
	}
	next_free_all(d);
}
