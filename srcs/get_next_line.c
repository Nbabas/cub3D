/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbascaul <nbascaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 21:15:16 by nbascaul          #+#    #+#             */
/*   Updated: 2021/01/20 17:29:51 by nbascaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static int		process_line(char **backup, char **line, char *nl_str)
{
	char			*tmp;

	if (nl_str != NULL)
	{
		*line = ft_strndup(*backup, nl_str - *backup);
		tmp = ft_strndup(nl_str + 1, ft_strlen(nl_str + 1));
		free(*backup);
		*backup = tmp;
		return (1);
	}
	if (*backup != NULL)
	{
		*line = *backup;
		*backup = NULL;
	}
	else
		*line = ft_strndup("", 1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char		*backup[256];
	static char			buffer[BUFFER_SIZE + 1];
	char			*tmp;
	int				len_read;
	char			*nl_str;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((nl_str = ft_strchr(backup[fd], '\n')) == 0
			&& (len_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len_read] = 0;
		if (backup[fd] == NULL)
			tmp = ft_strndup(buffer, len_read);
		else
			tmp = ft_strjoin(backup[fd], buffer);
		if (backup[fd] != 0)
			free(backup[fd]);
		backup[fd] = tmp;
	}
	if (len_read < 0)
		return (-1);
	return (process_line(&backup[fd], line, nl_str));
}