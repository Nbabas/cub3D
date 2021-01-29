/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:57:59 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/27 14:27:54 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgb(char **rgb_tab)
{
	int r;
	int g;
	int b;

	r = ft_atoi(rgb_tab[0]);
	g = ft_atoi(rgb_tab[1]);
	b = ft_atoi(rgb_tab[2]);
	return ((r << 16) + (g << 8) + b);
}

static int	check_colors(t_data *d)
{
	char **rgb;
	int i = -1;

	if (!d->infos[1] || (!ft_strchr(d->infos[1],',')))
		return (COLORS_ERROR);
	if ((rgb = ft_split(d->infos[1], ',')) == 0)
		return (COLORS_ERROR);
	while (rgb[++i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (COLORS_ERROR);
	}
	if (i != 3)
		return (COLORS_ERROR);
	if (ft_strcmp(d->infos[0], "F") == 0)
		d->f_color = get_rgb(rgb);
	else if (ft_strcmp(d->infos[0], "C") == 0)
		d->c_color = get_rgb(rgb);
	free_tab(rgb, d->infos[1], ',', 0);
	return (SUCCESS);
}

int			*get_textures_img(t_data *d, int id)
{
	void	*img;
	int		tab[3];
	int		*ret;

	img = mlx_xpm_file_to_image(g_mlx_ptr, d->infos[1],
								&d->t[id].w, &d->t[id].h);
	if (!img)
		ft_error(d,TEXTURES_ERROR,"Xpm to Img Failed");
	ret = (int *)mlx_get_data_addr(img, &tab[0], &tab[1], &tab[2]);
	ft_free(img);
	return (ret);
}

static int check_textures(t_data *d, int words)
{
	int	fd;

	if ((d->err = check_file_extension(d->infos[1], ".xpm")) < 0)
		ft_error(d, EXT_ERROR, "");
	else
	{
		if ((fd = open(d->infos[1], O_RDONLY)) == - 1)
			return (FD_ERROR);
		close(fd);
		if (ft_strcmp(d->infos[0], "S") == 0 && words == 2)
			d->t[4].addr = get_textures_img(d, 4);
		else if (ft_strcmp(d->infos[0], "NO") == 0 && words == 2)
			d->t[0].addr = get_textures_img(d, 0);
		else if (ft_strcmp(d->infos[0], "SO") == 0 && words == 2)
			d->t[1].addr = get_textures_img(d, 1);
		else if (ft_strcmp(d->infos[0], "WE") == 0 && words == 2)
			d->t[2].addr = get_textures_img(d, 2);
		else if (ft_strcmp(d->infos[0], "EA") == 0 && words == 2)
			d->t[3].addr= get_textures_img(d, 3);
		else
			return (TEXTURES_ERROR);

	}
	return (SUCCESS);
}

static int	check_screen(t_data *d)
{
	d->w_resolution = ft_atoi(d->infos[1]);
	d->h_resolution = ft_atoi(d->infos[2]);
	if (d->w_resolution  <= 0 || d->h_resolution <= 0)
		return (SCREEN_SIZE_ERROR);
	if (d->w_resolution > SCREEN_MAX_HEIGHT)
		d->w_resolution = SCREEN_MAX_HEIGHT;
	if (d->h_resolution > SCREEN_MAX_WIDTH)
		d->h_resolution = SCREEN_MAX_WIDTH;
	return (SUCCESS);
}

void	parse_config(t_data *d)
{
	int	words;

	words = ft_wordcount(d->line, ' ');
	printf("==> %s\n",d->infos[0]);
	if (strcmp(d->infos[0], "R") == 0 && words == 3)
	{
		if ((d->err = check_screen(d)) < 0)
			ft_error(d, CONFIG_ERROR, "");
	}
	else if (ft_strchr("NSEW", d->infos[0][0]) && !(d->infos[0][3]))
	{
		if ((d->err = check_textures(d, words)) < 0)
			ft_error(d, CONFIG_ERROR, d->infos[1]);
	}
	else if (ft_strchr("CF", d->infos[0][0]) && !(d->infos[0][1]))
	{
		if ((d->err = check_colors(d)) < 0)
			ft_error(d, CONFIG_ERROR, d->infos[0]);
	}
	else
		ft_error(d, CONFIG_ERROR, d->infos[0]);
	printf("Check %s ok\n", d->infos[0]);
	free_tab(d->infos, d->line, ' ', 0);
}

