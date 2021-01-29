/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:17:15 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/26 08:51:04 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_data *d)
{
	free_all(d);
	exit(1);
}

static void	ft_error_2(t_data *d, int err_type, char *str)
{
	(void)err_type;
	(void)str;

	ft_exit(d);
}

void	ft_error(t_data *d, int err_type, char *str)
{
	//printf("Type Err = %i || Precision : %i || str : %s", err_type, d->err, str);
	if (d->err == MALLOC_ERROR && err_type == MALLOC_ERROR)
		ft_printf(2, "Error\nMalloc failed\n");
	else if (err_type == CONFIG_ERROR && d->err == FD_ERROR)
		ft_printf(2, "Error\nFile %s can't be found\n", str);
	else if (d->err  == SCREEN_SIZE_ERROR || err_type == SCREEN_SIZE_ERROR)
		ft_printf(2, "Error\nScreen Size Error\n", str);
	else if (err_type == TEXTURES_ERROR && d->err  == FD_ERROR)
		ft_printf(2, "Error\nTexture %s can't be found\n", str);
	else if (err_type  == CONFIG_ERROR && d->err == COLORS_ERROR)
		ft_printf(2, "Error\nLoading %s colors failed\n", str);
	else if (err_type == CONFIG_ERROR && d->err == MISS_ARG_ERROR)
		ft_printf(2, "Error\nConfiguration - Bad or Missing elements\n");
	else if (err_type == MAP_ERROR && d->err == WRONG_SIGN)
		ft_printf(2, "Error\nSome bad sign in map at line->|%s|<-\n",d->line);
	else if (err_type == MAP_ERROR && d->err == MAP_ERROR)
		ft_printf(2, "Error\nWrong Map at line->|%s|<-\n", d->line);
	else if (err_type == CONFIG_ERROR)
		ft_printf(2, "Error\nBad Configuration at line->|%s|<-\n",d->line);
	else if (err_type == MAP_ERROR)
		ft_printf(2, "Error\n%s\n",str);
	else if (d->err  == FD_ERROR)
		ft_putstr_fd("Error\nFD error\n", 2);
	ft_error_2(d, err_type, str);
}

