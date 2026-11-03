/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:33 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/03 22:46:54 by gtomasin        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if ((s_len - start) < len)
		len = s_len - start;
	r = malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = s[start];
		i++;
		start++;
	}
	r[i] = 0;
	return (r);
}

size_t	ft_strlen(const char *s)
{
	size_t	compt;

	compt = 0;
	while (s[compt] != '\0')
	{
		compt++;
	}
	return (compt);
}
