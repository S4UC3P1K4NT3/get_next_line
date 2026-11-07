/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: gtomasin <gtomasin@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/01 02:55:33 by gtomasin         #+#    #+#              */
/*   Updated: 2026/11/07 15:27:53 by gtomasin        ###   ########.fr        */
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
	s_len = ft_len(s);
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

size_t	ft_len(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_len(s1);
	len2 = ft_len(s2);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len1 + len2] = '\0';
	while (len2 > 0)
	{
		len2--;
		result[len1 + len2] = s2[len2];
	}
	while (len1 > 0)
	{
		len1--;
		result[len1] = s1[len1];
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	while (*s && (unsigned char)*s != (unsigned char) c)
		s++;
	if (!*s || !s[1])
		return (NULL);
	s++;
	result = malloc((ft_len(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
