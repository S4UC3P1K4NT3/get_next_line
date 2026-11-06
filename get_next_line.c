/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:24 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/06 20:53:08 by gtomasin        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(char *str)
{
	int	i;

	while (str && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

static char	*get_line(char *keep);

static int	*read_line(char *keep)
{
	char	*tmp;

	keep = malloc((ft_strlen(keep) + 1 + BUFFER_SIZE) * sizeof(char));
	if (!keep)
		return (free(keep), -1);
	while ()
	{
	}
}

char	*get_next_line(int fd)
{
	static char	*keep;
	int			bytes_read;

	while (has_newline(keep) == 0)
	{
		bytes_read = read_line(keep);
		if (bytes_read == -1)
			return (NULL);
	}
}
