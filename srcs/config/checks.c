/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:12:21 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 11:15:40 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	map_is_closed(t_data *d)
{
	int		x;
	int		y;

	y = -1;
	while (++y < d->ymax)
	{
		x = -1;
		while (++x < d->xmax)
		{
			if (d->map[y][x] != '1' && y == 0)
				return (ERROR);
			else if (d->map[y][x] != '1' && y == d->ymax - 1)
				return (ERROR);
			else if (d->map[y][x] != '1' && x == 0)
				return (ERROR);
			else if (d->map[y][x] != '1' && x == d->xmax - 1)
				return (ERROR);
			else if (strchr(SPRITES, d->map[y][x]))
				d->nb_spr++;
			if (d->map[y][x] == '4')
				d->g.tocollect++;
		}
	}
	return (SUCCESS);
}

int			check_map(t_data *d)
{
	if (d->xmax < 3 || d->ymax < 3)
		ft_error(d, MAP_ERROR, "Too small map");
	if (d->por == '?')
		ft_error(d, MAP_ERROR, "Unable to find starting position");
	if (d->por == '!')
		ft_error(d, MAP_ERROR, "More than 1 starting point");
	if (map_is_closed(d) < 0)
		ft_error(d, MAP_ERROR, "Map not closed by '1'");
	return (SUCCESS);
}

int			check_file_extension(char *file, char *extension_name)
{
	int		end;

	end = (int)ft_strlen(file) - 1;
	while (end && ft_isspace(file[end]))
		file[end--] = '\0';
	end -= 3;
	if (end >= 1)
	{
		if (ft_strcmp(file + end, extension_name))
		{
			ft_printf(2, "Error\nFile %s is not a %s\n"
			, file, extension_name);
			return (EXT_ERROR);
		}
	}
	else
	{
		ft_printf(2, "Error\nProblem with extension file.");
		return (EXT_ERROR);
	}
	return (SUCCESS);
}
