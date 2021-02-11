/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:38:07 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 17:19:29 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		clean_image(void)
{
	if (PLATFORM == 2)
		mlx_destroy_image(g_mlx_ptr, g_img_ptr);
	else
	{
		free(g_img_ptr);
		g_img_addr = 0;
		free(g_img_addr);
		g_img_addr = 0;
	}
}

static void	clean_window(void)
{
	if (g_mlx_win)
		mlx_destroy_window(g_mlx_ptr, g_mlx_win);
	if (g_mlx_ptr)
	{
		if (PLATFORM == 2)
			mlx_destroy_display(g_mlx_ptr);
		free(g_mlx_ptr);
	}
}

static void	next_free_all(t_data *d)
{
	int		i;

	i = -1;
	while (++i <= 7)
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
	clean_window();
}

void		free_all(t_data *d)
{
	if (d->map)
		free_tab(d->map, "", 0, d->currenty);
	if (d->buff)
		free(d->buff);
	if (d->sprites)
		free(d->sprites);
	if (d->err < 0 && d->line && check_config(d) < 0)
	{
		if (d->init_infos)
			free_tab(d->infos, d->line, ' ', 0);
		ft_free(d->line);
	}
	else if (d->err < 0 && d->init_infos == 0)
		ft_free(d->line);
	next_free_all(d);
}
