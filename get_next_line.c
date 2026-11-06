/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:24 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/07 00:41:15 by gtomasin        ###   ########.fr        */
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

static char	*get_line(char *keep)
{
}

static char	*read_line(char *keep, int fd)
{
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*keep;
	int			bytes_read;

	bytes_read = 1;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (has_newline(keep) == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
	}
	return ;
}
