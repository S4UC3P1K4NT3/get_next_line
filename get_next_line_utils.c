/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:33 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/06 21:30:17 by gtomasin        ###   ########.fr        */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc((len) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, s1, len);
	ft_strlcat(str, s2, len);
	return (str);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	j = 0;
	while (i < destsize && dest[i])
		i++;
	dest_len = i;
	if (i == destsize)
		return (destsize + src_len);
	while (src[j] && (i + j + 1) < destsize)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < destsize)
		dest[i + j] = '\0';
	return (dest_len + src_len);
}
