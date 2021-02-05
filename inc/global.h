/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:38:24 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 13:34:32 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

/*
**# define MINI_SCALE 0.20
*/
# define P_SPEED 8
# define R_SPEED 8
# define SCREEN_MAX_WIDTH 1920
# define SCREEN_MAX_HEIGHT 1080

float		g_mini_scale;
int			g_w_resolution;
int			g_h_resolution;
int			g_n_rows;
int			g_n_col;
int			g_tile_size;
int			g_n_rays;
char		**g_map;
void		*g_mlx_ptr;
void		*g_mlx_win;
void		*g_img_ptr;
int			*g_img_addr;
int			g_s_line;
int			g_bpp;
float		g_fov_angle;
#endif
