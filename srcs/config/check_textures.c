/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:04:23 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 12:37:22 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	next_check(t_data *d, int words)
{
	if (ft_strcmp(d->infos[0], "NO") == 0 && words == 2)
		d->t[0].addr = get_textures_img(d, 0);
	else if (ft_strcmp(d->infos[0], "SO") == 0 && words == 2)
		d->t[1].addr = get_textures_img(d, 1);
	else if (ft_strcmp(d->infos[0], "WE") == 0 && words == 2)
		d->t[2].addr = get_textures_img(d, 2);
	else if (ft_strcmp(d->infos[0], "EA") == 0 && words == 2)
		d->t[3].addr = get_textures_img(d, 3);
	else if (ft_strcmp(d->infos[0], "S") == 0 && words == 2)
		d->t[4].addr = get_textures_img(d, 4);
	else if (ft_strcmp(d->infos[0], "S1") == 0 && words == 2)
		d->t[5].addr = get_textures_img(d, 5);
	else if (ft_strcmp(d->infos[0], "S2") == 0 && words == 2)
		d->t[6].addr = get_textures_img(d, 6);
	else if (ft_strcmp(d->infos[0], "W") == 0 && words == 2)
		d->t[7].addr = get_textures_img(d, 7);
	else
	{
		free_tab(d->infos, d->line, ' ', 0);
		return (KEY_UNDEF);
	}
	return (SUCCESS);
}

int			check_textures(t_data *d, int words)
{
	int		fd;

	if ((d->err = check_file_extension(d->infos[1], ".xpm")) < 0)
	{
		free_tab(d->infos, d->line, ' ', 0);
		ft_error(d, d->err, "");
	}
	else
	{
		if ((fd = open(d->infos[1], O_RDONLY)) == -1)
		{
			free_tab(d->infos, d->line, ' ', 0);
			return (FD_ERROR);
		}
		close(fd);
	}
	return (next_check(d, words));
}
