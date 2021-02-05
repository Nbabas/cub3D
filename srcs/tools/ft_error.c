/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:17:15 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 17:09:39 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int			ft_exit(t_data *d)
{

	free_all(d);
	//system("leaks cub3D");
	exit(0);
}

static void	ft_error_2(t_data *d, int err_type, char *str)
{
	if (err_type == MAP_ERROR && d->err == WRONG_SIGN)
		ft_printf(2, "Error\nSome bad sign in map at line->|%s|<-\n", d->line);
	else if (err_type == MAP_ERROR && d->err == MAP_ERROR)
		ft_printf(2, "Error\nWrong Map at line->|%s|<-\n", d->line);
	else if (err_type == MAP_ERROR || err_type == INPUT_ERROR)
		ft_printf(2, "Error\n%s\n", str);
	else if (d->err == FD_ERROR)
		ft_putstr_fd("Error\nFD error\n", 2);
	else if (err_type == BMP_ERROR)
		ft_printf(2, "Error\nFail with .bmp");
}

void		ft_error(t_data *d, int err_type, char *str)
{
	if (d->err == MALLOC_ERROR && err_type == MALLOC_ERROR)
		ft_printf(2, "Error\nMalloc failed\n");
	else if (err_type == CONFIG_ERROR && d->err == FD_ERROR)
		ft_printf(2, "Error\nFile %s can't be found\n", str);
	else if (err_type == CONFIG_ERROR && d->err == COLORS_ERROR)
		ft_printf(2, "Error\nLoading %s colors failed\n", str);
	else if (err_type == CONFIG_ERROR && d->err == MISS_ARG_ERROR)
		ft_printf(2, "Error\nConfiguration - Bad or Missing elements\n");
	else if (err_type == CONFIG_ERROR || d->err == SCREEN_SIZE_ERROR)
		ft_printf(2, "Error\nScreen Size Error %s\n", str);
	else if (err_type == CONFIG_ERROR)
		ft_printf(2, "Error\nBad Configuration at line->|%s|<-\n", d->line);
	else if (err_type == TEXTURES_ERROR && d->err == FD_ERROR)
		ft_printf(2, "Error\nTexture %s can't be found\n", str);
	else if (err_type == TEXTURES_ERROR && d->err == CONFIG_ERROR)
		ft_printf(2, "Error\n%s", str);
	else if (err_type == MLX_ERROR && d->err == TEXTURES_ERROR)
		ft_printf(2, "Error\nFailed with MLX : %s", str);
	else if (err_type == MLX_ERROR)
		ft_printf(2, "Error\nFailed with MLX : %s", str);
	else
		ft_error_2(d, err_type, str);
	ft_exit(d);
}
