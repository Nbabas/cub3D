/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:50:19 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/27 14:30:09 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_config(t_data *d)
{
	if (d->w_resolution == 0 || d->h_resolution == 0 ||
	d->t[0].addr == 0 ||	d->t[1].addr == 0 || d->t[2].addr== 0 ||
	d->t[3].addr == 0 ||	d->c_color == -1 || d->f_color == -1 ||
	d->t[4].addr== 0)
		return(MISS_ARG_ERROR);
	return (SUCCESS);
}

static int	get_nb_lines(char *line, t_data *d)
{
	if ((d->err = line_is_map(line)) < 1)
		return(d->err);
	else
	{
		d->ymax++;
		return (SUCCESS);
	}
		//printf("%s\n", d->line);
		//test = ft_strepur(d->line);
		//printf("%s\n", test);
		//free(test);
}

static void	parse_file(t_data *d)
{
	int	xtmp;

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
	//printf("xtmp : %i\n",xtmp);
	if (xtmp > d->xmax)
		d->xmax = xtmp;
	//ft_free(d->line);
	//d->line = NULL;
}

void parsing(t_data *d, char *file)
{
	d->line = 0;
	static int ret = 1;
	(void) file;
	while (ret != 0)
	{
		ret = get_next_line(d->fd, &(d->line));
 		while (ft_isspace(*d->line) && !check_config(d))
			(d->line)++;
		//printf("line = %s\n",d->line);
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