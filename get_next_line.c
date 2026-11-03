/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:24 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/03 22:53:28 by gtomasin        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	keep_fill(char *keep, char *str)
{
	keep = malloc(ft_strlen((str + 1) * sizeof(char)));
	while (str++)
		keep++ = str++;
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*keep;
	int			bytes_read;
	int			i;

	i = 0;
	tmp = malloc((BUFFER_SIZE + 1 + ft_strlen(keep)) * sizeof(char));
	if (!tmp)
		return (NULL);
	bytes_read = read(fd, tmp, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(tmp), NULL);
	while (keep)
		tmp[bytes_read++] = keep++;
	tmp[bytes_read] = '\0';
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
}
