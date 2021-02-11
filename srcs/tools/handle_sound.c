/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:53:33 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 13:56:03 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	play_sound(char var)
{
	if (PLATFORM == 1)
	{
		(var == 'E') ? system("afplay ./sound/end.mp3 &") : 0;
		(var == 'H') ? system("afplay ./sound/hit.mp3") : 0;
		(var == 'I') ? system("afplay ./sound/itemtaken.mp3 &") : 0;
		(var == 'A') ? system("afplay ./sound/pouf.mp3 ") : 0;
	}
	else if (PLATFORM == 2)
	{
		(var == 'E') ? system("mpg123 ./sound/end.mp3 &") : 0;
		(var == 'H') ? system("mpg123 ./sound/hit.mp3 &") : 0;
		(var == 'I') ? system("mpg123 ./sound/itemtaken.mp3 &") : 0;
		(var == 'A') ? system("mpg123 ./sound/pouf.mp3 &") : 0;
	}
}
