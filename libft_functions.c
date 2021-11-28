/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveiled <eveiled@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:47:15 by eveiled           #+#    #+#             */
/*   Updated: 2021/11/28 18:34:34 by eveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evgenii.h"

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	count;
	size_t	len_substr;
	size_t	chars;

	if (!s)
		return (NULL);
	count = 0;
	chars = 0;
	len_substr = 0;
	while (s[start + len_substr] && len_substr < len)
		len_substr++;
	substr = (char *)malloc(sizeof(char) * (len_substr + 1));
	if (NULL == substr)
		return (NULL);
	while (s[count])
	{
		if (count >= start && chars < len_substr)
			substr[chars++] = s[count];
		count++;
	}
	substr[chars] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		size;

	size = 0;
	while (*(s1 + size))
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (NULL == ret)
		return (NULL);
	size = 0;
	while (*(s1 + size))
	{
		*(ret + size) = *(s1 + size);
		size++;
	}
	*(ret + size) = '\0';
	return (ret);
}
