/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 10:35:45 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/14 17:26:27 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_printf_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char			*ft_printf_strdup(const char *s)
{
	char	*dest;
	size_t	len;

	len = (size_t)s;
	while (*s)
		s++;
	len = (size_t)s - len;
	s -= len;
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s)
		*dest++ = (char)*s++;
	*dest = '\0';
	dest -= len;
	return (dest);
}

size_t			ft_printf_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	i;

	if (!src || !dst)
		return (0);
	count = (size_t)src;
	while (*src)
		src++;
	count = (size_t)src - count;
	src -= count;
	i = count;
	if (size)
	{
		while (size-- > 1 && i--)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (count);
}

size_t			ft_printf_strlen(const char *s)
{
	size_t	start;

	start = (size_t)s;
	while (*s)
		s++;
	return ((size_t)s - start);
}

int				ft_printf_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
