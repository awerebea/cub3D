/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:18:33 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:16:24 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		count;
	size_t		i;

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
