/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:14:16 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 10:58:39 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_open_map(char *file, t_data *d)
{
	if (check_file_extension(file, ".cub") < 0)
		ft_exit(d);
	d->fd = open(file, O_RDONLY);
	if (d->fd == -1)
		return (FD_ERROR);
	return (SUCCESS);
}
/*
**int		h;
**int		w;
**mlx_get_screen_size(g_mlx_ptr, &w, &h);
**	if (g_h_resolution > h)
**	g_h_resolution = h;
**if (g_w_resolution > w)
**	g_w_resolution = w;
*/

static void	create_window(t_data *d)
{
	g_h_resolution = d->h_resolution;
	g_w_resolution = d->w_resolution;
	if (d->bmp == 1)
		return ;
	g_mlx_win = mlx_new_window(
				g_mlx_ptr, g_w_resolution, g_h_resolution, "That's my boy");
	if (!g_mlx_win)
		ft_error(d, MLX_ERROR, "Failed to create window");
}

void		game(t_data *d, char *pathmap)
{
	if ((g_mlx_ptr = mlx_init()) == 0)
		ft_error(d, MLX_ERROR, "MLX init abort");
	g_mini_scale = 0.20;
	parsing(d, pathmap);
	check_map(d);
	create_window(d);
	ft_init_global(d);
	ft_init_player(d);
	ft_init_sprites(d);
	raycast_process(d);
}

static void	check_input(t_data *d, int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
			ft_error(d, INPUT_ERROR, "Start : ./cub3D [path_map] [--save]");
		else
			d->bmp = 1;
	}
	else if (argc != 2)
		ft_error(d, INPUT_ERROR, "Start : ./cub3D [path_map] [--save]");
	if ((d->err = check_open_map(argv[1], d)) < 0)
		ft_error(d, CONFIG_ERROR, argv[1]);
}

int			main(int argc, char *argv[])
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		ft_error(d, MALLOC_ERROR, "");
	ft_init(d);
	check_input(d, argc, argv);
	game(d, argv[1]);
	return (0);
}
