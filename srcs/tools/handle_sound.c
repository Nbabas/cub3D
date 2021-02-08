/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:53:33 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/08 17:37:34 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	play_sound(char var)
{
	if (PLATFORM == 1)
	{
		(var == 'E') ? system("afplay ./sound/end.mp3 &") : 0;
		(var == 'N') ? system("afplay ./sound/beh.mp3 &") : 0;
		(var == 'I') ? system("afplay ./sound/itemtaken.mp3 &") : 0;
	}
	else if (PLATFORM == 2)
	{
		(var == 'E') ? system("mpg123 ./sound/end.mp3 &") : 0;
		(var == 'N') ? system("mpg123 ./sound/beh.mp3 &") : 0;
		(var == 'I') ? system("mpg123 ./sound/itemtaken.mp3 &") : 0;
	}
}
