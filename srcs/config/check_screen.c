/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:33:50 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 17:44:46 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	free_then_exit(t_data *d, char **tab)
{
	d->init_infos = 0;
	free_tab(tab, d->line, ' ', 0);
	return (SCREEN_SIZE_ERROR);
}

static int  next_check_screen(t_data *d)
{
    int		maxx;
	int		maxy;
    
	if (PLATFORM == 2)
	{
		mlx_get_screen_size(g_mlx_ptr, &maxx, &maxy);
		if (d->w_resolution > maxx)
			d->w_resolution = maxx;
		if (d->h_resolution > maxy)
			d->h_resolution = maxy - 45;
	}
	else
	{
		if (d->h_resolution > SCREEN_MAX_HEIGHT)
			d->h_resolution = SCREEN_MAX_HEIGHT;
		if (d->w_resolution > SCREEN_MAX_WIDTH)
			d->w_resolution = SCREEN_MAX_WIDTH - 45;
	}
    return (SUCCESS);
}

int	check_screen(t_data *d)
{
    int     i;

    i = 0;
    
    if (d->w_resolution || d->h_resolution)
        return (free_then_exit(d, d->infos));
	while (d->infos[++i])
		if (!is_number(d->infos[i]))
			return (free_then_exit(d, d->infos));
	d->w_resolution = ft_atoi(d->infos[1]);
	d->h_resolution = ft_atoi(d->infos[2]);
	if (d->w_resolution < 200 || d->h_resolution < 200)
		return (free_then_exit(d, d->infos));
    next_check_screen(d);
	return (SUCCESS);
}