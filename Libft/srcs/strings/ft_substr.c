/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:34:49 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:21:16 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc) and returns a substring from the string ’s’.
** The substring begins at index ’start’ and is of maximum size ’len’.
*/

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	count;

	if (!s)
		return (NULL);
	if (len)
	{
		count = (size_t)s;
		while (*s)
			s++;
		count = (size_t)s - count;
		s -= count;
		if (len > (count - start) && count > start)
			len = count - start;
		else if (start >= count)
			len = 0;
	}
	if (!(substr = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	count = len;
	while (*s && count--)
		*substr++ = s[start++];
	*substr = '\0';
	return (substr - len);
}
