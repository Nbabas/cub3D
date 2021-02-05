/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:38:07 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 15:50:36 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_all(t_data *d)
{
 	int i = -1;
	if (d->map)
		free_tab(d->map, "", 0, d->ymax);
	if (d->sprites)
		free(d->buff);
	if (d->sprites)
		free(d->sprites);
	while (d->t[++i].img != NULL && i <= 5)
	{
		if (PLATFORM == 2)
			mlx_destroy_image(g_mlx_ptr, d->t[i].img);
		else if (PLATFORM == 1)
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
