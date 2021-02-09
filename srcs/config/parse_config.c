/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:57:59 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:47 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_rgb(char **rgb_tab)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(rgb_tab[0]);
	g = ft_atoi(rgb_tab[1]);
	b = ft_atoi(rgb_tab[2]);
	return ((r << 16) + (g << 8) + b);
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
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (COLORS_ERROR);
	if ((i != 3) || (ft_strcmp(d->infos[0], "F") != 0 &&
			(ft_strcmp(d->infos[0], "C") != 0)))
	{
		free_tab(rgb, d->infos[1], ',', 0);
		return (COLORS_ERROR);
	}
	if (ft_strcmp(d->infos[0], "F") == 0)
		d->f_color = get_rgb(rgb);
	else if (ft_strcmp(d->infos[0], "C") == 0)
		d->c_color = get_rgb(rgb);
	free_tab(rgb, d->infos[1], ',', 0);
	return (SUCCESS);
}

static int	check_textures(t_data *d, int words)
{
	int	fd;

	if ((d->err = check_file_extension(d->infos[1], ".xpm")) < 0)
		ft_error(d, EXT_ERROR, "");
	else
	{
		if ((fd = open(d->infos[1], O_RDONLY)) == -1)
			return (FD_ERROR);
		close(fd);
		if (ft_strcmp(d->infos[0], "S1") == 0 && words == 2)
			d->t[4].addr = get_textures_img(d, 4);
		else if (ft_strcmp(d->infos[0], "S2") == 0 && words == 2)
			d->t[5].addr = get_textures_img(d, 5);
		else if (ft_strcmp(d->infos[0], "NO") == 0 && words == 2)
			d->t[0].addr = get_textures_img(d, 0);
		else if (ft_strcmp(d->infos[0], "SO") == 0 && words == 2)
			d->t[1].addr = get_textures_img(d, 1);
		else if (ft_strcmp(d->infos[0], "WE") == 0 && words == 2)
			d->t[2].addr = get_textures_img(d, 2);
		else if (ft_strcmp(d->infos[0], "EA") == 0 && words == 2)
			d->t[3].addr = get_textures_img(d, 3);
		else
			return (TEXTURES_ERROR);
	}
	return (SUCCESS);
}

static int	check_screen(t_data *d)
{
	int		maxx;
	int		maxy;

	d->w_resolution = ft_atoi(d->infos[1]);
	d->h_resolution = ft_atoi(d->infos[2]);
	if (d->w_resolution < 200 || d->h_resolution < 200)
		return (SCREEN_SIZE_ERROR);
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

void		parse_config(t_data *d)
{
	int		words;

	words = ft_wordcount(d->line, ' ');
	if (strcmp(d->infos[0], "R") == 0 && words == 3)
	{
		if ((d->err = check_screen(d)) < 0)
			ft_error(d, CONFIG_ERROR, "- at least 200x200");
	}
	else if (ft_strchr("NSEW", d->infos[0][0]) && words == 2)
	{
		if ((d->err = check_textures(d, words)) < 0)
			ft_error(d, CONFIG_ERROR, d->infos[1]);
	}
	else if (ft_strchr("CF", d->infos[0][0]) && words == 2)
	{
		if ((d->err = check_colors(d)) < 0)
			ft_error(d, CONFIG_ERROR, d->infos[0]);
	}
	else
	{
		d->err = CONFIG_ERROR;
		ft_error(d, CONFIG_ERROR, d->infos[0]);
	}
	free_tab(d->infos, d->line, ' ', 0);
}
