/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:17:15 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/12 12:38:20 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int			ft_exit(t_data *d)
{
	free_all(d);
	exit(0);
}

static void	ft_error_2(t_data *d, int err_type, char *str)
{
	(void)d;
	if (err_type == MISS_TEXTURES_ERROR)
		ft_printf(2, "Error\nTexture Missing", str);
	if (err_type == BMP_ERROR)
		ft_printf(2, "Error\nFail with .bmp");
}

void		ft_error(t_data *d, int err_type, char *str)
{
	if (err_type == MALLOC_ERROR)
		ft_printf(2, "Error\nMalloc failed\n");
	else if (err_type == INPUT_ERROR)
		ft_printf(2, "Error\n%s", str);
	else if (err_type == FD_ERROR)
		ft_printf(2, "Error\nFD error with >%s<", str);
	else if (err_type == MLX_ERROR)
		ft_printf(2, "Error\nFailed with MLX : %s", str);
	else if (err_type == DOUBLE_LINE_ERROR)
		ft_printf(2, "Error\nDouble configuration for : %s", str);
	else if (err_type == SCREEN_SIZE_ERROR)
		ft_printf(2, "Error\nScreen Size Error : 200x200 required");
	else if (err_type == KEY_UNDEF)
		ft_printf(2, "Error\nConfig Key unknown : %s", str);
	else if (err_type == CONFIG_ERROR)
		ft_printf(2, "Error\nBad Configuration at line->|%s|<-\n", str);
	else if (err_type == MISS_ARG_ERROR)
		ft_printf(2, "Error\nMissing R/NO/EA/WE/SO/C/F or %s", str);
	else if (err_type == WRONG_SIGN)
		ft_printf(2, "Error\nSome bad sign in map at line->|%s|<-\n", d->line);
	else if (err_type == MAP_ERROR)
		ft_printf(2, "Error\nLine : %s\n", str);
	else
		ft_error_2(d, err_type, str);
	ft_exit(d);
}
