/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpsaver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:59:06 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/08 18:02:27 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_header(int fd)
{
	int		tmp;
	int		i;

	i = -1;
	write(fd, "BM", 2);
	tmp = 54 + 4 * g_h_resolution * g_h_resolution;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &g_w_resolution, 4);
	write(fd, &g_h_resolution, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	tmp = 32;
	write(fd, &tmp, 2);
	tmp = 0;
	while (++i < 6)
		write(fd, &tmp, 4);
}

static void	fill_pixel(int fd)
{
	int		x;
	int		y;

	y = g_h_resolution;
	while (--y >= 0)
	{
		x = -1;
		while (++x < g_w_resolution)
			write(fd, &g_img_addr[y * g_w_resolution + x], 4);
	}
}

void		bmp_saver(t_data *d)
{
	int		fd;

	ft_printf(1, "Saving...");
	fd = open("img_saved.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd > 0)
	{
		fill_header(fd);
		fill_pixel(fd);
	}
	else
		ft_error(d, BMP_ERROR, "");
	if (PLATFORM == 2)
		mlx_destroy_image(g_mlx_ptr, g_img_ptr);
	else
		free(g_img_ptr);
	ft_printf(1, "OK\n");
	ft_exit(d);
}
