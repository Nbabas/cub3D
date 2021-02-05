/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:12:56 by nbascaul          #+#    #+#             */
/*   Updated: 2021/02/05 11:06:26 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		line_is_space(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == '\n' || *line == '\0')
		return (SUCCESS);
	else
		return (ERROR);
}

void	ft_free(char *tofree)
{
	if (tofree)
	{
		free(tofree);
		tofree = NULL;
	}
}

int		ft_wordcount(char const *str, char c)
{
	int		i;
	int		cmp;

	cmp = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			cmp++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cmp);
}

void	free_tab(char **tab, char const *s, char sep, int n)
{
	int		i;

	if (n == 0)
		n = ft_wordcount(s, sep);
	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	tab = 0;
}
