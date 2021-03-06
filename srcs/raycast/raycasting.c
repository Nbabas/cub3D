/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:38:29 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 14:59:34 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	get_orientation_ray(t_ray *r)
{
	if (r->angle > 0 && r->angle < M_PI)
		r->facedown = 1;
	else
		r->faceup = 1;
	if (r->angle < (0.5 * M_PI) || r->angle > (1.5 * M_PI))
		r->faceright = 1;
	else
		r->faceleft = 1;
}

static void	ft_new_ray(t_ray *r, t_data *d)
{
	(void)d;
	r->facedown = 0;
	r->faceup = 0;
	r->faceleft = 0;
	r->faceright = 0;
	r->xa = 0;
	r->ya = 0;
	r->x_step = 0;
	r->y_step = 0;
	r->hitx = 0;
	r->hity = 0;
	r->distance = 2147483647;
	r->hitvert = 0;
}

float		get_angle(float angle)
{
	angle = (float)remainder(angle, (M_PI * 2));
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

static void	draw_img(t_data *d)
{
	d->r.i = 0;
	d->w.dist = (g_w_resolution / 2) / tanf(g_fov_angle / 2);
	while (d->r.i < g_n_rays)
	{
		d->r.angle = d->p.r_angle + atanf((d->r.i - g_n_rays / 2) / d->w.dist);
		d->r.angle = get_angle(d->r.angle);
		ft_new_ray(&d->r, d);
		get_orientation_ray(&d->r);
		trace_horizontal(&d->r, d);
		trace_vertical(&d->r, d);
		draw_column(&d->r, d, &d->w);
		d->r.i++;
	}
}

/*
**	printf("g tile : %i \n", g_tile_size);
**	printf("\nPxy %f:%f P.angle = %f || n° : %i || r.angle = %f ||",
**	d->p.x,d->p.y, d->p.r_angle, d->r.i, d->r.angle);
**	printf("Hit x  = %f || Hit y = %f || Distance = %f || Hit Vertical = %i ||",
**	d->r.hitx, d->r.hity, d->r.distance, d->r.hitvert);
**	d->r.faceup ? printf("Look UP "):0;
**	d->r.facedown ? printf("Look DOWN "):0;
**	d->r.faceright ? printf("& RIGHT\n"):0;
**	d->r.faceleft ? printf("& LEFT\n"):0;
*/

int			raycast_process(t_data *d)
{
	create_image(d);
	p_moves(d);
	draw_background(d);
	draw_img(d);
	draw_sprites(d);
	draw_map(d);
	if (d->g.weapon)
		draw_weapon(d);
	if (d->bmp == 1)
		bmp_saver(d);
	mlx_put_image_to_window(g_mlx_ptr, g_mlx_win, g_img_ptr, 0, 0);
	check_strings(d);
	clean_image();
	return (SUCCESS);
}
