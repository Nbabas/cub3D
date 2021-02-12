/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:57:59 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 12:37:40 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	free_then_exit(t_data *d, char **tab)
{
	d->init_infos = 0;
	free_tab(tab, d->infos[1], ',', 0);
	free_tab(d->infos, d->line, ' ', 0);
	return (COLORS_ERROR);
}

static int	check_colors(t_data *d)
{
	char	**rgb;
	int		i;

	i = -1;
	if (!d->infos[1] || (!ft_strchr(d->infos[1], ',')))
		return (COLORS_ERROR);
	if ((rgb = ft_split(d->infos[1], ',')) == 0)
		return (COLORS_ERROR);
	while (rgb[++i])
		if (!is_number(rgb[i]) || ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (free_then_exit(d, rgb));
	if ((i != 3) || (ft_strcmp(d->infos[0], "F") != 0 &&
			(ft_strcmp(d->infos[0], "C") != 0)))
		return (free_then_exit(d, rgb));
	if (ft_strcmp(d->infos[0], "F") == 0 && d->f_color == -1)
		d->f_color = get_rgb(rgb);
	else if (ft_strcmp(d->infos[0], "C") == 0 && d->c_color == -1)
		d->c_color = get_rgb(rgb);
	else
		return (free_then_exit(d, rgb));
	free_tab(rgb, d->infos[1], ',', 0);
	return (SUCCESS);
}

void		parse_config(t_data *d)
{
	int		words;

	words = ft_wordcount(d->line, ' ');
	if (strcmp(d->infos[0], "R") == 0 && words == 3)
	{
		if ((d->err = check_screen(d)) < 0)
			ft_error(d, d->err, "Screen resolution");
	}
	else if (ft_strchr("NSEW", d->infos[0][0]) && words == 2)
	{
		if ((d->err = check_textures(d, words)) < 0)
			ft_error(d, d->err, d->line);
	}
	else if (ft_strchr("CF", d->infos[0][0]) && words == 2)
	{
		if ((d->err = check_colors(d)) < 0)
			ft_error(d, CONFIG_ERROR, "C/F");
	}
	else
	{
		free_tab(d->infos, d->line, ' ', 0);
		ft_error(d, CONFIG_ERROR, d->line);
	}
	free_tab(d->infos, d->line, ' ', 0);
}
