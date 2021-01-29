/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:14:16 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/28 17:09:46 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_open_map(char *file, t_data *d)
{
	if (check_file_extension(file, ".cub") < 0)
		ft_exit(d);
	d->fd = open(file, O_RDONLY);
	if (d->fd == -1)
		return (FD_ERROR);
	return (SUCCESS);
}

int main(int argc, char *argv[])
{
	t_data *d;
	(void) argc;

	d = malloc(sizeof(t_data));
	if (!d)
		ft_error(d,MALLOC_ERROR, "");
	ft_init(d);
	if ((d->err = check_open_map(argv[1], d)) < 0)
		ft_error(d, CONFIG_ERROR, argv[1]);

	g_mlx_ptr = mlx_init();

	parsing(d, argv[1]);

	check_map(d);
	g_mlx_win = mlx_new_window(g_mlx_ptr, d->w_resolution, d->h_resolution, "C'est mon CUBE");

	ft_init_global(d);
	ft_init_player(d);
	ft_init_sprites(d);
	raycast_process(d);

//printf("infos : %s\n", map->infos[0]);
	listen_actions(d);

	destroy(d);
//	system("leaks cub3D");
	return (SUCCESS);
}
