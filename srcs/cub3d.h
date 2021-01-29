/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:14:11 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/28 17:37:08 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "global.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <fcntl.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 999
# endif

# define ERROR 0
# define MAP_ERROR -2
# define SCREEN_SIZE_ERROR -3
# define FD_ERROR -4
# define TEXTURES_ERROR -5
# define COLORS_ERROR -6
# define EXT_ERROR -7
# define CONFIG_ERROR -8
# define MISS_ARG_ERROR -11
# define WRONG_SIGN -9
# define MALLOC_ERROR -10

# define SUCCESS 1

typedef struct s_ray
{
	int		i;
	float	angle;
	float	Hitx;
	float	Hity;
	float	distance;
	int		HitVert;
	int		FaceLeft;
	int		FaceRight;
	int		FaceUp;
	int		FaceDown;
	float	xA;
	float	yA;
	float	x_step;
	float	y_step;

	float	hitx_vert;
	float	hity_vert;
	float	hitx_hor;
	float	hity_hor;
}				t_ray;

typedef struct	s_spr
{
	float	x;
	float y;
	float	dist;
	int	isVisible;

	float	startx;
	float	starty;
	float	endy;
	float	endx;
	float	screenx;
	float	w;
	float	h;
	float	size;
}				t_spr;

typedef struct	s_p
{
	float	x;
	float	y;
	int		turn_dir;
	int		walk_dir;
	float	xdir;
	float	ydir;
	float	plany;
	float	planx;
	float	r_angle;
	float	speed;
	float	r_speed;
	int		size;

}				t_p;

typedef struct s_textures
{
	int		*addr;
	int		h;
	int		w;
}				t_textures;

typedef struct	s_wall
{
	int		h;
	int		start;
	int		end;
	float	dist;
	float	good_dist;
}				t_wall;

typedef struct	s_data
{
	int		w_resolution;
	int		h_resolution;
/* 	0	no_text;
	1	so_text;
	2	we_text;
	3	ea_text;
	4	s_text; */
	t_textures	t[5];
	int		c_color;
	int		f_color;
	int		fd;
	char	*line;
	char	**infos;
	char	**map;
	int		xmax;
	int		ymax;
	char	Por;
	int		Px;
	int		Py;
	int		err;
	int		nb_spr;
	t_spr	*sprites;
	t_p		p;
	t_ray	r;
	t_wall	w;
	float	*buff;
}				t_data;


//main
void		ft_init(t_data *d);
void		ft_init_global(t_data *d);
void		ft_init_player(t_data *d);
void		ft_init_sprites(t_data *d);
void		ft_new_ray(t_ray *r, t_data *d);
void		parsing(t_data *d, char *file);

//parsing file
int			get_next_line(int fd, char **line);
void		parse_config(t_data *d);
int			line_is_space(char *line);
int			line_is_map(char *line);

//parsing map
void		process_map(t_data *d, char *file);

//checks
int			check_file_extension(char *file, char *extension_name);
int			check_map(t_data *d);
//sprites
void		get_sprites(t_data *d);
void	handle_sprites(t_data *d);
void	put_spr_visible(t_data *d, int mapx, int mapy);
//raycasting
int			raycast_process(t_data *d);
void		draw_map(t_data *d);
float	get_angle(float angle);
void	trace_horizontal(t_ray *r, t_data *d);
void	trace_vertical(t_ray *r, t_data *d);
int		is_wall(float y, float x, t_data *d);
//
int			ft_exit(t_data *d);
int			listen_actions(t_data *d);
void		p_moves(t_data *d);
//int	key_pressed(int keycode, t_data *d);
//int	key_released(int keycode, t_data *d);
int			ft_wordcount(char const *str, char c);
void		ft_error(t_data *d, int err, char *str);
void		ft_free(char *tofree);
void		free_tab(char **tab, char const *s, char sep, int n);
void		destroy(t_data *d);
void		free_all(t_data *d);



#endif