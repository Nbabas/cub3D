/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:25:43 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/29 12:45:50 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	put_spr_visible(t_data *d, int mapx, int mapy)
{
	int i = 0;
	int spx;
	int	spy;



	while (i < d->nb_spr)
	{
		spx = floor(d->sprites[i].x / g_tile_size);
		spy = floor(d->sprites[i].y / g_tile_size);
		if (spx == mapx && spy == mapy)
			d->sprites[i].isVisible = 1;
		i++;
	}
}
void	new_sprite(t_data *d, int i)
{
	d->sprites[i].startx = 0;
	d->sprites[i].starty = 0;
	d->sprites[i].endx = 0;
	d->sprites[i].endx = 0;
	d->sprites[i].screenx = 0;
}
void	get_sprites_dist(t_data *d)
{
	int i;
	int tmpX;
	int tmpY;

	tmpY = floor(d->r.yA / g_tile_size);
	tmpX = floor(d->r.xA / g_tile_size);
	i = 0;
	while (i < d->nb_spr)
	{
		d->sprites[i].dist = hypot(d->p.x - d->sprites[i].x, d->p.y - d->sprites[i].y);
		i++;
	}
}
 void	sort_sprites(t_data *d)
{
	int i;
	int	n;
	int sorted;
	t_spr tmp;

	i = 0;
	sorted = 0;
	n = d->nb_spr;
	while (sorted == 0)
	{
		sorted = 1;
		while (i < n - 1)
		{
			if (d->sprites[i].dist < d->sprites[i + 1].dist)
			{
				tmp = d->sprites[i];
				d->sprites[i] = d->sprites[i + 1];
				d->sprites[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		n--;
	}
}

float	get_newY(t_data *d, int i)
{
	float deltaX;
	float deltaY;
	float	infov;
	float	newx;
	float	newy;

	printf("Sprite n %i || x %f || y %f \n", i, d->sprites[i].x, d->sprites[i].y);
	deltaX = d->sprites[i].x - d->p.x;
	deltaY = d->sprites[i].y - d->p.y;
	infov = 1.0 / (d->p.planx * d->p.ydir - d->p.xdir * d->p.plany);
	newx = infov * (d->p.ydir * deltaX - d->p.xdir * deltaY);
	newy = infov * (-d->p.plany * deltaX + d->p.planx * deltaY);
	d->sprites[i].screenx = (int)((g_w_resolution / 2) * (1 + -newx / newy));
	return (newy);
}

void	get_coord_draw(t_spr *spr)
{
spr->w = spr->size;
spr->startx = -spr->w / 2 + spr->screenx;
if (spr->startx < 0)
	spr->startx = 0;
spr->endx = spr->w / 2 + spr->screenx;
if (spr->endx >= g_w_resolution)
	spr->endx = g_w_resolution -1;


spr->h = spr->size;

spr->starty = -spr->h / 2 + g_h_resolution / 2;
if (spr->starty < 0)
	spr->starty = 0;
spr->endy = spr->h / 2 + g_h_resolution / 2;
if (spr->endy >= g_h_resolution)
	spr->endy = g_h_resolution - 1;


}

void	draw_textures_sprite(t_spr *spr, int x , int y, t_data *d)
{
	int color;
	int	textx;
	int	texty;
	int	offsetY;

	textx = (int)(256 * (x - (-spr->size / 2 + spr->screenx)) * d->t[4].w / spr->size) / 256;
	offsetY = (y) * 256 - g_h_resolution * 128 + spr->size * 128;
	texty = (int)((offsetY * d->t[4].h) / spr->size) / 256;
	if ((texty * d->t[4].w) + textx < (int)sizeof(d->t[4].addr))
		return ;
	color = d->t[4].addr[texty * d->t[4].w + textx];
	if (color != 0x000000)
		g_img_addr[y * g_w_resolution + x] = color;
}

void	draw_sprite(t_spr *spr, float newY, t_data *d)
{
	int x;
	int y;

	x = spr->startx;
	while (x < spr->endx)
	{

		if (newY > 0 && x >= 0 && x < g_w_resolution && newY < d->buff[x])
		{
			y = spr->starty;
			while (y < spr->endy)
			{
				draw_textures_sprite(spr, x , y, d);
				y++;
			}
		}
		x++;
	}
}

float	calcul_angle(t_data *d, float x, float y)
{
	float	vx;
	float	vy;
	float	angle_p_spr;
	float	angle_p;
	float	angle_spr;

	vx = x - d->p.x;
	vy = y - d->p.y;
	angle_p_spr = atan2(vy, vx);
	angle_p = get_angle(d->p.r_angle);
	angle_spr = angle_p - angle_p_spr;
	if (angle_spr < -M_PI)
		angle_spr += 2 * M_PI;
	if (angle_spr > M_PI)
		angle_spr -= 2 * M_PI;
	angle_spr = fabs(angle_spr);
	return (angle_spr);
}

int		isVisible(t_data *d, int i)
{
	float	angleA;
	float	angleB;
	float	angleC;
	float	size;
	float	fov;

	size = d->sprites[i].size;

	angleA = fabs(calcul_angle(d, d->sprites[i].x, d->sprites[i].y));
	angleB = fabs(calcul_angle(d, d->sprites[i].x + size, d->sprites[i].y + size));
	angleC = fabs(angleB - angleA);
	fov = g_fov_angle / 2 + angleC;
	if (angleA < fov)
		return (1);
	return (0);
}

void	handle_sprites(t_data *d)
{
	int		i;
	float	newY;
	//int pos;

	i = 0;
	get_sprites_dist(d);
	sort_sprites(d);
	while (i < d->nb_spr)
	{
		d->sprites[i].size = (0.5 * g_tile_size) / d->sprites[i].dist * d->w.dist;
		new_sprite(d, i);
		if (isVisible(d, i))//(d->sprites[i].isVisible == 1)
		{
			newY = get_newY(d, i);
			get_coord_draw(&d->sprites[i]);
			draw_sprite(&d->sprites[i], newY, d);
			printf("Object en (%f)(%f) || distance : %f || visible : %i\n", d->sprites[i].x, d->sprites[i].y, d->sprites[i].dist, d->sprites[i].isVisible);
		}
		i++;

	}
}



void	get_sprites(t_data *d)
{
	int x;
	int y;
	int n;

	if (d->sprites != NULL)
		free(d->sprites);
	n = 0;
	y = -1;
	d->sprites = malloc(sizeof(t_spr) * d->nb_spr);
	if (!d->sprites)
		ft_error(d,MALLOC_ERROR,"Sprites Malloc Failed");
	while (++y < d->ymax)
	{
		x = -1;
		while (++x < d->xmax)
		{
			if (d->map[y][x] == '2')
			{
				d->sprites[n].x = x * g_tile_size + g_tile_size / 2;
				d->sprites[n].y = y  * g_tile_size + g_tile_size / 2;
				d->sprites[n].isVisible = 0;
				d->sprites[n].dist = hypot(d->sprites[n].x - d->p.x,d->sprites[n].y - d->p.y);
				printf("objet en %i,%i\n",x,y);
				n++;
			}
		}
	}
}