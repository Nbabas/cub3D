/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 00:07:36 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 15:42:08 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_player_pos(t_data *d, int i, int j, char *line)
{
	if (d->por != '?')
		d->por = '!';
	else
		d->por = line[j];
	d->map[i][j] = '0';
	d->px = j;
	d->py = i;
}

int		put_map_in_tab(t_data *d, char *line)
{
	static int	i = 0;
	int			j;

	j = 0;
	d->map[i] = malloc(sizeof(char) * d->xmax + 1);
	if (d->map[i] == 0)
		return (ERROR);
	while (line[j] != '\0')
	{
		if (line[j] == ' ' || line[j] == '\t')
			d->map[i][j] = '1';
		else if (ft_strchr("NSWE", line[j]))
			set_player_pos(d, i, j, line);
		else
			d->map[i][j] = line[j];
		j++;
	}
	while (j < d->xmax)
		d->map[i][j++] = '1';
	d->map[i][j] = '\0';
	i++;
	d->currenty++;
	return (SUCCESS);
}

int		line_is_map(char *line)
{
	if (strchr(line, '1'))
	{
		while (*line)
		{
			if (!strchr(MAP, *line))
				return (WRONG_SIGN);
			line++;
		}
		return (1);
	}
	return (MAP_ERROR);
}

void	process_map(t_data *d, char *file)
{
	static int	ret = 1;
	char		*nl;

	nl = 0;
	d->init_infos = 1;
	if (d->xmax == 0 || d->ymax == 0)
		ft_error(d, MAP_ERROR, "");
	if ((d->fd = open(file, O_RDONLY)) < 0)
		ft_error(d, FD_ERROR, "");
	d->map = malloc(sizeof(char *) * d->ymax + 1);
	if (d->map == 0)
		ft_error(d, MALLOC_ERROR, "");
	while (ret != 0)
	{
		ret = get_next_line(d->fd, &nl);
		if (line_is_map(nl) == 1)
			put_map_in_tab(d, nl);
		if (line_is_space(nl) == SUCCESS &&
			d->currenty > 0 && d->currenty != d->ymax)
			ft_error(d, MAP_ERROR, "Empty line in map");
		ft_free(nl);
	}
	close(d->fd);
}
