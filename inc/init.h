/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:28:01 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/03 17:52:16 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# if defined(__linux__)
#  define PLATFORM 3
# elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
#  include <sys/param.h>
#  if defined(BSD)
#   define PLATFORM 2
#  endif
# elif defined(__APPLE__) && defined(__MACH__)
#  define PLATFORM 1
# endif
#endif
