/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:38:29 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/29 12:39:18 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	draw_background(t_data *d)
{
	int x;
	int y;

	y = -1;
	while (++y < g_h_resolution)
	{
		x = -1;
		while (++x < g_w_resolution)
		{
			if (y < g_h_resolution / 2)
				g_img_addr[(y * g_w_resolution + x)] = d->c_color;
			else
				g_img_addr[(y * g_w_resolution + x)] = d->f_color;
		}
	}
}

static void	get_orientation_ray(t_ray *r)
{
	if (r->angle > 0 && r->angle < M_PI)
		r->FaceDown = 1;
	else
		r->FaceUp = 1;
	if (r->angle < (0.5 * M_PI) || r->angle > (1.5 * M_PI))
		r->FaceRight = 1;
	else
		r->FaceLeft = 1;
}

void	get_shorter_ray(t_ray *r, t_data *d)
{
	float ver_d;
	float hor_d;

	ver_d = 0;
	hor_d = 0;
	if (r->HitVert == 1)
		ver_d =  hypot(d->p.x - r->hitx_vert,d->p.y -  r->hity_vert);
	else
		ver_d = INTMAX_MAX;
	if (r->HitVert == 0)
		hor_d = hypot(d->p.x - r->hitx_hor, d->p.y -  r->hity_hor);
	else
		hor_d = INTMAX_MAX;

	if (hor_d < ver_d)
	{
		r->Hitx = r->hitx_hor;
		r->Hity = r->hity_hor;
		r->distance = hor_d;
	}
	else
	{
		r->Hitx = r->hitx_vert;
		r->Hity = r->hity_vert;
		r->distance = ver_d;
	}
	if (ver_d < hor_d)
		r->HitVert = 1;
}

void	draw_column(t_ray *r, t_data *d, t_wall *w)
{


	w->good_dist = r->distance * cos(r->angle - d->p.r_angle);
	d->buff[r->i] = r->distance;
	w->dist = (g_w_resolution / 2) / tan(g_fov_angle / 2);
	w->h = (g_tile_size / w->good_dist) * w->dist;
	w->start = (g_h_resolution / 2) - (w->h / 2);
	if (w->start < 0)
		w->start = 0;
	w->end = (g_h_resolution / 2) + (w->h / 2);
	if (w->end > g_h_resolution)
		w->end = g_h_resolution - 1;

	int	id_text;
	int	color;
	int	xtext;
	int	ytext;
	if (r->HitVert == 0 && r->FaceUp)
		id_text = 0; /*texture north*/
	if (r->HitVert == 0 && r->FaceDown)
		id_text = 1; /*texture south*/
	if (r->HitVert && r->FaceLeft)
		id_text = 2;/*texture West*/
	if (r->HitVert && r->FaceRight)
		id_text = 3;/*texture est*/

	if (r->HitVert == 1)
		xtext = (int)(r->Hity * d->t[id_text].w / g_tile_size) % d->t[id_text].w;
	else
		xtext = (int)(r->Hitx * d->t[id_text].w / g_tile_size) % d->t[id_text].w;

	while (w->start < w->end)
	{
		ytext = w->start + (w->h / 2 ) - (g_h_resolution / 2);
		ytext = ytext * ((float)d->t[id_text].h / w->h);
		color = d->t[id_text].addr[(d->t[id_text].w * ytext) + xtext];
		if (color != 0x000000)
			g_img_addr[(w->start * g_w_resolution) + r->i] = color;//0xFFF5EE;
		w->start++;
	}
}

void	ft_new_ray(t_ray *r, t_data *d)
{
	(void)d;
	r->FaceDown = 0;
	r->FaceUp = 0;
	r->FaceLeft = 0;
	r->FaceRight = 0;
	r->xA = 0;
	r->yA = 0;
	r->x_step = 0;
	r->y_step = 0;
	r->Hitx = 0;
	r->Hity = 0;
	r->distance = INTMAX_MAX;
	r->HitVert = 0;

	r->hitx_vert = 0;
	r->hity_vert = 0;
	r->hitx_hor = 0;
	r->hity_hor = 0;
}


float	get_angle(float angle)
{
	angle = remainder(angle, (M_PI * 2));
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

void	draw_img(t_data *d)
{


	d->r.i = 0;


	d->r.angle = d->p.r_angle - (g_fov_angle / 2);
	//printf("Player Angle %f\n",d->p.r_angle);
	while (d->r.i < g_n_rays)
	{
		d->r.angle = get_angle(d->r.angle);
		ft_new_ray(&d->r, d);
		get_orientation_ray(&d->r);
		trace_horizontal(&d->r,d);
		trace_vertical(&d->r, d);

		draw_column(&d->r, d, &d->w);

		/* 	printf("P.angle = %f || n° : %i || r.angle = %f ||", d->p.r_angle, r->i, r->angle);
	printf("Hit x  = %f || Hit y = %f || Distance = %f || Hit Vertical = %i || ", r->Hitx, r->Hity, r->distance, r->HitVert);
	r->FaceUp ? printf("Look UP "):0;
	r->FaceDown ? printf("Look DOWN "):0;
	r->FaceRight ? printf("& RIGHT\n"):0;
	r->FaceLeft ? printf("& LEFT\n"):0; */
		d->r.angle += (g_fov_angle / g_n_rays);
		d->r.i++;
	}
}

int	raycast_process(t_data *d)
{
	int			bpp;
	int			endian;


	g_img_ptr = mlx_new_image(g_mlx_ptr, d->w_resolution, d->h_resolution);
	g_img_addr = (int *)mlx_get_data_addr(g_img_ptr, &bpp, &g_s_line, &endian);
	g_bpp = bpp;
	//LINUX : mlx_get_screen_size(g_mlx_ptr, &g_w_resolution, &g_h_resolution);

	p_moves(d);
	draw_background(d);
	get_sprites(d);
	printf("*************\n");
	handle_sprites(d);
	draw_img(d);
	handle_sprites(d);
	draw_map(d);



/* 	printf("bpp = %i | endian = %i | sizeline = %i | addr = %p\n", bpp, endian, g_s_line, g_img_addr);
	printf("Map de %i par %i\n", d->xmax, d->ymax);
	printf("f color = %i\n", d->f_color);
	printf("c color = %i\n", d->c_color);
	printf("Joueur en x:%i | y:%i | orientation:%c\n",d->Px,d->Py,d->Por);
	printf("nombre de sprites : %i\n", d->nb_spr); */

	mlx_put_image_to_window(g_mlx_ptr, g_mlx_win, g_img_ptr,0,0);
	mlx_destroy_image(g_mlx_ptr,g_img_ptr);
	g_img_ptr = 0;
	return(SUCCESS);
}