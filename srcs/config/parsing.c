/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:50:19 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 12:37:32 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int				check_config(t_data *d)
{
	if (d->w_resolution == 0 || d->h_resolution == 0 || \
	d->t[0].w == 0 || d->t[1].w == 0 || d->t[2].w == 0 || \
	d->t[3].w == 0 || d->c_color == -1 || d->f_color == -1)
		return (MISS_ARG_ERROR);
	return (SUCCESS);
}

static int		get_nb_lines(char *line, t_data *d)
{
	if (((d->err = line_is_map(line)) < 1))
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

	d->init_infos = 0;
	xtmp = 0;
	if (line_is_space(d->line) == SUCCESS)
		return ;
	if ((d->err = get_nb_lines(d->line, d)) < 0)
		ft_error(d, d->err, d->line);
	if ((d->err = check_config(d)) < 0)
		ft_error(d, d->err, "Space in empty line");
	xtmp = ft_strlen(d->line);
	if (xtmp > d->xmax)
		d->xmax = xtmp;
}

void			parsing(t_data *d, char *file)
{
	static int	ret;

	ret = 1;
	d->currenty = 0;
	d->init_infos = 0;
	while (ret != 0)
	{
		ret = get_next_line(d->fd, &(d->line));
		while (ft_isspace(*d->line) && check_config(d) < 0)
			(*d->line)++;
		if (*(d->line) && ft_strchr("NSEWRCF", *(d->line)))
		{
			d->infos = ft_split_whitespaces(d->line);
			parse_config(d);
		}
		else
			parse_file(d);
		ft_free(d->line);
	}
	close(d->fd);
	process_map(d, file);
}
