/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:50:36 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 15:46:32 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		put_pixel(unsigned int color, int p_x, int p_y)
{
	if (p_y >= g_h_resolution || p_x >= g_w_resolution || p_x < 0 ||
		p_y < 0 || ((p_y * g_w_resolution + p_x) >=
		(g_w_resolution * g_h_resolution - 1)))
		return ;
	g_img_addr[p_y * g_w_resolution + p_x] = color;
}

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
	if (!(d->t[id].img = mlx_xpm_file_to_image(g_mlx_ptr, d->infos[1],
								&d->t[id].w, &d->t[id].h)))
	{
		d->err = TEXTURES_ERROR;
		ft_error(d, MLX_ERROR, d->infos[1]);
	}
	ret = (int *)mlx_get_data_addr(d->t[id].img, &tab[0], &tab[1], &tab[2]);
	if (!ret)
		ft_error(d, MLX_ERROR, "Impossible to get img address");
	return (ret);
}
