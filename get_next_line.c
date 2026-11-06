/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:24 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/06 23:18:48 by gtomasin        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

static char	*get_line(char **keep)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*keep[i] != '\n' && *keep[i] != '\0')
		i++;
	tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (*keep[i - 1] != '\n' && *keep[i] != '\0')
	{
		tmp[i] = *keep[i];
		i++;
	}
	tmp[i] = 0;
	*keep = malloc((ft_strlen(ft_strchr(*keep, '\n')) + 1) * sizeof(char));
	if (!*keep)
		return (NULL);
	*keep = ft_strchr(*keep, '\n');
	return (tmp);
}

static int	read_line(char **keep, int fd)
{
	char	*tmp;
	int		i;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (-1);
	i = read(fd, tmp, BUFFER_SIZE);
	if (i == -1)
		return (free(tmp), -1);
	tmp[i] = 0;
	*keep = ft_strjoin(*keep, tmp);
	free(tmp);
	if (!*keep)
		return (-1);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	int			bytes_read;

	bytes_read = 1;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes_read != 0 && has_newline(keep) == 0)
	{
		bytes_read = read_line(&keep, fd);
		if (bytes_read == -1)
			return (NULL);
	}
	return (get_line(keep));
}
