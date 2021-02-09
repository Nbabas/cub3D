/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:50:36 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/09 19:45:34 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		create_image(t_data *d)
{
	int		bpp;
	int		endian;

	g_img_ptr = 0;
	g_img_ptr = mlx_new_image(g_mlx_ptr, d->w_resolution, d->h_resolution);
	if (!g_img_ptr)
		ft_error(d, MLX_ERROR, "New Image Failed");
	g_img_addr = (int *)mlx_get_data_addr(g_img_ptr, &bpp, &g_s_line, &endian);
	if (!g_img_addr)
		ft_error(d, MLX_ERROR, "Impossible to get img address");
	g_bpp = bpp;
}

int			*get_textures_img(t_data *d, int id)
{
	int		tab[3];
	int		*ret;

	if (d->t[id].img)
	{
		d->err = TEXTURES_ERROR;
		ft_error(d, CONFIG_ERROR, "Double textures");
	}
	d->t[id].img = mlx_xpm_file_to_image(g_mlx_ptr, d->infos[1],
								&d->t[id].w, &d->t[id].h);
	if (!d->t[id].img)
	{
		d->err = TEXTURES_ERROR;
		ft_error(d, MLX_ERROR, d->infos[1]);
	}
	ret = (int *)mlx_get_data_addr(d->t[id].img, &tab[0], &tab[1], &tab[2]);
	if (!ret)
		ft_error(d, MLX_ERROR, "Impossible to get img address");
	return (ret);
}
