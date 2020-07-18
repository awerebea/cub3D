/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 12:01:43 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:17:09 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function ’f’ to each character of the string ’s’ to create
** a new string (with malloc) resulting from successive applications of ’f’.
*/

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = (size_t)s;
	while (*s)
		s++;
	len = (size_t)s - len;
	s -= len;
	if (!(result = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = -1;
	while (++i < (unsigned int)len)
		result[i] = f(i, s[i]);
	result[i] = '\0';
	return (result);
}
