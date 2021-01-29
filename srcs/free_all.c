/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:38:07 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/28 15:24:59 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	destroy(t_data *d)
{
	if (d->map)
		free_tab(d->map,"", 0,d->ymax);
	if(d->sprites)
		free(d->sprites);
	if(g_mlx_win)
		mlx_destroy_window(g_mlx_ptr, g_mlx_win);

}

void	free_all(t_data *d)
{
	destroy(d);
}