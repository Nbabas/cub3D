/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:50:19 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/08 13:21:41 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int		check_config(t_data *d)
{
	if (d->w_resolution == 0 || d->h_resolution == 0 || \
	d->t[0].w == 0 || d->t[1].w == 0 || d->t[2].w == 0 || \
	d->t[3].w == 0 || d->c_color == -1 || d->f_color == -1 || \
	d->t[4].w == 0)
		return (MISS_ARG_ERROR);
	return (SUCCESS);
}

static int		get_nb_lines(char *line, t_data *d)
{
	if ((d->err = line_is_map(line)) < 1)
		return (d->err);
	else
	{
		d->ymax++;
		return (SUCCESS);
	}
}

/*
**ft_free(d->line);
**d->line = NULL;
*/

static void		parse_file(t_data *d)
{
	int			xtmp;

	xtmp = 0;
	if (line_is_space(d->line) == SUCCESS && d->ymax > 0)
		ft_error(d, MAP_ERROR, "Empty line detected");
	else if (line_is_space(d->line) == SUCCESS)
		return ;
	if ((d->err = check_config(d)) < 0)
		ft_error(d, CONFIG_ERROR, "");
	if ((d->err = get_nb_lines(d->line, d)) < 0)
		ft_error(d, MAP_ERROR, "");
	xtmp = ft_strlen(d->line);
	if (xtmp > d->xmax)
		d->xmax = xtmp;
}

void			parsing(t_data *d, char *file)
{
	static int	ret;
	char		*ptr;

	ptr = d->line;
	d->line = 0;
	ret = 1;
	(void)file;
	while (ret != 0)
	{
		ret = get_next_line(d->fd, &(d->line));
		while (ft_isspace(*d->line) && !check_config(d))
			(d->line)++;
		if (*(d->line) && ft_strchr("NSEWRCF", *(d->line))
			&& check_config(d) < 0)
		{
			d->infos = ft_split_whitespaces(d->line);
			parse_config(d);
		}
		else
			parse_file(d);
		free(d->line);
	}
	close(d->fd);
	process_map(d, file);
}
