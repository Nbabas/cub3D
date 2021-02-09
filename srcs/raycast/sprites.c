/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:25:43 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/10 00:37:49 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	new_sprite(t_data *d, int i, int x, int y)
{
	d->sprites[i].startx = 0;
	d->sprites[i].starty = 0;
	d->sprites[i].endx = 0;
	d->sprites[i].endy = 0;
	d->sprites[i].screenx = 0;
	d->sprites[i].newy = 0;
	d->sprites[i].x = x * g_tile_size + g_tile_size / 2;
	d->sprites[i].y = y * g_tile_size + g_tile_size / 2;
	d->sprites[i].dist = hypot(d->sprites[i].x - d->p.x,
							d->sprites[i].y - d->p.y);
	d->sprites[i].type = d->map[y][x] - '0';
	d->sprites[i].h = d->t[d->sprites[i].type + 2].h;
	d->sprites[i].w = d->t[d->sprites[i].type + 2].w;
	if (d->t[d->sprites[i].type + 2].img == NULL)
	{
		d->err = TEXTURES_ERROR;
		ft_error(d, CONFIG_ERROR, "Sprites Texture Missing");
	}
}

void	draw_textures_sprite(t_spr *spr, int x, int y, t_data *d)
{
	int	color;
	int	textx;
	int	texty;
	int	offsety;

	textx = (int)(256 * (x - (-spr->size / 2 + spr->screenx)) *
				(spr->w - 1) / spr->size) / 256;
	while (y < spr->endy)
	{
		offsety = (y) * 256 - g_h_resolution * 128 + spr->size * 128;
		texty = ((offsety * spr->h) / spr->size) / 256;
		if ((texty * spr->w) + textx <
			(int)sizeof(d->t[spr->type + 2].addr))
			return ;
		color = d->t[spr->type + 2].addr[texty * spr->w + textx];
		if (color != -16777216 && color != 0)
			g_img_addr[(y) * g_w_resolution + x] = color;
		y++;
	}
}

void	draw_sprite(t_spr *spr, float newy, t_data *d)
{
	int	x;
	int	y;

	x = spr->startx;
	while (x <= spr->endx)
	{
		if (newy > 0 && x > 0 && x < g_w_resolution && newy < d->buff[x])
		{
			y = spr->starty;
			draw_textures_sprite(spr, x, y, d);
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
			g_tile_size * 0.2 / d->sprites[i].dist * d->w.dist;
		else
			d->sprites[i].size =
			g_tile_size / d->sprites[i].dist * d->w.dist;
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
