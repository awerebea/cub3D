/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:24:54 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/22 21:16:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc) and returns a copy of ’s1’ with the characters
** specified in ’set’ removed from the beginning and the end of the string.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = (size_t)s1;
	while (*s1)
		s1++;
	len = (size_t)s1 - len;
	s1 -= len;
	while (len && ft_strchr(set, s1[len - 1]))
		len--;
	if (!(result = ft_substr((char *)s1, 0, len)))
		return (NULL);
	return (result);
}
