/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:25:43 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 15:58:29 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	new_sprite(t_data *d, int i, int x, int y)
{
	d->sprites[i].startx = 0;
	d->sprites[i].starty = 0;
	d->sprites[i].endx = 0;
	d->sprites[i].endx = 0;
	d->sprites[i].screenx = 0;
	d->sprites[i].newy = 0;
	d->sprites[i].x = x * g_tile_size + g_tile_size / 2;
	d->sprites[i].y = y * g_tile_size + g_tile_size / 2;
	d->sprites[i].dist = hypot(d->p.x - d->sprites[i].x, d->p.y - d->sprites[i].y);
	d->sprites[i].type = d->map[y][x] - '0';
	if (d->t[d->sprites[i].type + 2].addr == NULL)
	{
		d->err = CONFIG_ERROR;
		ft_error(d, TEXTURES_ERROR, "Sprites Texture Missing");
	}
}

void	draw_textures_sprite(t_spr *spr, int x, int y, t_data *d)
{
	int	color;
	int	textx;
	int	texty;
	int	offsety;

	textx = ((x - (-spr->size / 2 + spr->screenx)) *
				d->t[spr->type + 2].w / spr->size);
	offsety = (y) * 256 - g_h_resolution * 128 + spr->size * 128;
	texty = ((offsety * d->t[spr->type + 2].h) / spr->size) / 256;
	if ((texty * d->t[spr->type + 2].w) + textx <
		(int)sizeof(d->t[spr->type + 2].addr))
		return ;
	color = d->t[spr->type + 2].addr[texty * d->t[spr->type + 2].w + textx];
	if (color != -16777216 && color != 0)
		g_img_addr[(y) * g_w_resolution + x] = color;
}

void	draw_sprite(t_spr *spr, float newy, t_data *d)
{
	int	x;
	int	y;

	x = spr->startx;
	while (x < spr->endx && x < g_w_resolution)
	{
		if (newy > 0 && x >= 0 && x < g_w_resolution && newy < d->buff[x])
		{
			y = spr->starty;
			while (y < spr->endy)
			{
				draw_textures_sprite(spr, x, y, d);
				y++;
			}
		}
		x++;
	}
}

void	draw_sprites(t_data *d)
{
	int	i;

	i = 0;
	sort_sprites(d);
	while (i < d->nb_spr)
	{
		get_newy(d, i);
		if (d->sprites[i].type == 3)
			d->sprites[i].size =
				fabs((g_w_resolution * g_tile_size * 0.2 / d->sprites[i].newy));
		else
			d->sprites[i].size =
				fabs((g_w_resolution * g_tile_size / d->sprites[i].newy));
			get_coord_draw(&d->sprites[i]);
			draw_sprite(&d->sprites[i], d->sprites[i].newy, d);

		i++;
	}
}

void	get_sprites(t_data *d)
{
	int	x;
	int	y;
	int	n;

	if (d->sprites != NULL)
		free(d->sprites);
	n = 0;
	y = -1;
	d->sprites = malloc(sizeof(t_spr) * d->nb_spr);
	if (!d->sprites)
		ft_error(d, MALLOC_ERROR, "Sprites Malloc Failed");
	while (++y < d->ymax)
	{
		x = -1;
		while (++x < d->xmax)
		{
			if (d->map[y][x] == '2' || d->map[y][x] == '3')
			{
				new_sprite(d, n, x, y);
				n++;
			}
		}
	}
}
