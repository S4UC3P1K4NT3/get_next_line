/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/07 14:40:02 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/10 05:54:32 by gtomasin        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(char **k)
{
	char	*tmp;
	char	*rest;
	size_t	i;

	i = 0;
	while ((*k)[i] && (*k)[i] != '\n')
		i++;
	if ((*k)[i] == '\n')
		i++;
	tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	rest = ft_strchr(*k, '\n');
	if ((*k)[i] && !rest)
	{
		free(tmp);
		return (NULL);
	}
	tmp[i] = '\0';
	while (i-- > 0)
		tmp[i] = (*k)[i];
	free(*k);
	*k = rest;
	return (tmp);
}

static char	*eof(char *tmp, char **keep, ssize_t br)
{
	char	*line;

	free(tmp);
	if (br < 0 || !*keep || !**keep)
	{
		free(*keep);
		*keep = NULL;
		return (NULL);
	}
	line = get_line(keep);
	if (!line)
	{
		free(*keep);
		*keep = NULL;
	}
	return (line);
}

static char	*read_line(char **keep, int fd)
{
	ssize_t	br;
	char	*tmp;
	char	*joined;

	if (has_newline(*keep))
		return (eof(NULL, keep, 1));
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (eof(NULL, keep, -1));
	br = 1;
	tmp[0] = '\0';
	while (!has_newline(tmp) && br > 0)
	{
		br = read(fd, tmp, BUFFER_SIZE);
		if (br <= 0)
			break ;
		tmp[br] = '\0';
		joined = ft_strjoin(*keep, tmp);
		free(*keep);
		*keep = joined;
		if (!joined)
			return (eof(tmp, keep, -1));
	}
	return (eof(tmp, keep, br));
}

char	*get_next_line(int fd)
{
	static char	*keep;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	return (read_line(&keep, fd));
}
