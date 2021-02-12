/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:14:11 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 12:34:31 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "init.h"
# include "global.h"

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# define ERROR -1
# define MAP_ERROR -2
# define SCREEN_SIZE_ERROR -3
# define FD_ERROR -4
# define TEXTURES_ERROR -5
# define COLORS_ERROR -6
# define EXT_ERROR -7
# define CONFIG_ERROR -8
# define WRONG_SIGN -9
# define MALLOC_ERROR -10
# define MISS_ARG_ERROR -11
# define INPUT_ERROR -12
# define BMP_ERROR -13
# define DOUBLE_LINE_ERROR -14
# define KEY_UNDEF -15
# define MLX_ERROR -16
# define MISS_TEXTURES_ERROR -17

# define SUCCESS 1

typedef struct	s_ray
{
	int			i;
	float		angle;
	float		hitx;
	float		hity;
	float		distance;
	int			hitvert;
	int			faceleft;
	int			faceright;
	int			faceup;
	int			facedown;
	float		xa;
	float		ya;
	float		x_step;
	float		y_step;
}				t_ray;

typedef struct	s_spr
{
	float		x;
	float		y;
	float		dist;
	int			type;
	int			startx;
	int			starty;
	int			endy;
	int			endx;
	int			screenx;
	float		newy;
	int			w;
	int			h;
	float		size;
}				t_spr;

typedef struct	s_game
{
	int			tocollect;
	int			collected;
	int			life;
	int			weapon;
}				t_game;

typedef struct	s_p
{
	float		x;
	float		y;
	int			turn_dir;
	int			walk_dir;
	int			leftstep;
	int			rightstep;
	float		xdir;
	float		ydir;
	float		plany;
	float		planx;
	float		r_angle;
	float		speed;
	float		r_speed;
	int			size;
}				t_p;

typedef struct	s_textures
{
	void		*img;
	int			*addr;
	int			h;
	int			w;
}				t_textures;

typedef struct	s_wall
{
	int			h;
	int			start;
	int			end;
	float		dist;
	float		good_dist;
}				t_wall;

/*
**	0	no_text;
**	1	so_text;
**	2	we_text;
**	3	ea_text;
**	4	s_text;
*/
typedef struct	s_data
{
	int			w_resolution;
	int			h_resolution;
	t_textures	t[8];
	int			c_color;
	int			f_color;
	int			fd;
	char		*line;
	char		**infos;
	char		**map;
	int			xmax;
	int			ymax;
	char		por;
	int			px;
	int			py;
	int			err;
	int			nb_spr;
	t_spr		*sprites;
	t_p			p;
	t_ray		r;
	t_wall		w;
	t_game		g;
	float		*buff;
	int			bmp;
	int			minimap;
	int			currenty;
	int			init_infos;
}				t_data;

void			ft_init(t_data *d);
void			ft_init_global(t_data *d);
void			ft_init_player(t_data *d);
void			ft_init_sprites(t_data *d);
void			parsing(t_data *d, char *file);

/*
** parsing file
*/
void			parse_config(t_data *d);
int				line_is_space(char *line);
int				line_is_map(char *line);
int				get_rgb(char **rgb_tab);

/*
** parsing map
*/
void			process_map(t_data *d, char *file);
int				*get_textures_img(t_data *d, int id);
int				check_config(t_data *d);

/*
**checks / textures
*/
int				check_file_extension(char *file, char *extension_name);
int				check_map(t_data *d);
int				check_textures(t_data *d, int words);
int				check_screen(t_data *d);

/*
**sprites
*/
void			get_sprites(t_data *d);
void			draw_sprites(t_data *d);
int				is_visible(t_data *d, int i);
float			calcul_angle(t_data *d, float x, float y);
void			sort_sprites(t_data *d);
void			get_coord_draw(t_spr *spr);
void			get_newy(t_data *d, int i);
void			get_spr_size(t_data *d, int i);

/*
**raycasting
*/
void			create_image(t_data *d);
int				raycast_process(t_data *d);
void			draw_background(t_data *d);
void			draw_column(t_ray *r, t_data *d, t_wall *w);
void			draw_map(t_data *d);
float			get_angle(float angle);
void			trace_horizontal(t_ray *r, t_data *d);
void			trace_vertical(t_ray *r, t_data *d);
int				is_wall(float y, float x, t_data *d);

int				listen_actions(t_data *d);
void			p_moves(t_data *d);
void			towin_collision(t_data *d, int mapx, int mapy);
void			health_collision(t_data *d, int mapx, int mapy);
void			weapon_collision(t_data *d, int mapx, int mapy);
void			ennemy_collision(t_data *d, int mapx, int mapy);
/*
** utils.c
*/

int				ft_wordcount(char const *str, char c);
void			bmp_saver(t_data *d);
void			ft_error(t_data *d, int err, char *str);
void			ft_free(char *tofree);
void			free_tab(char **tab, char const *s, char sep, int n);
void			free_all(t_data *d);
int				is_number(char *str);
void			clean_image(void);
int				ft_exit(t_data *d);

/*
** print_strings.c / HUD
*/

void			check_strings(t_data *d);
void			play_sound(char var);
void			draw_life(t_data *d);
void			draw_weapon(t_data *d);
#endif
