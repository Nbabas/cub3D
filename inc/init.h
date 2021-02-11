/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:28:01 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/11 16:41:48 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# if defined(__linux__)
#  define PLATFORM 2
# elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
#  include <sys/param.h>
#  if defined(BSD)
#   define PLATFORM 2
#  endif
# elif defined(__APPLE__) && defined(__MACH__)
#  define PLATFORM 1
# endif

# if PLATFORM == 1
#  include "../mlxopengl/mlx.h"
#  define ESC 53
#  define W 6
#  define A 12
#  define S 1
#  define D 2
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
#  define TAB 48
#  define SPACE_BAR 49
#  define MAJ 257
#  define R 15
# elif PLATFORM == 2
#  include "../minilibx-linux/mlx.h"
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define R 114
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define TAB 65289
#  define SPACE_BAR 32
#  define MAJ 65505
# endif
#endif
