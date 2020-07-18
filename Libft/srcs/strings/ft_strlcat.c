/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:03:45 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:16:02 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		count_d;
	size_t		count_s;
	size_t		start;
	char		*d;

	start = (size_t)dst;
	while (*dst)
		dst++;
	count_d = ((size_t)dst - start);
	start = (size_t)src;
	dst -= count_d;
	while (*src)
		src++;
	count_s = ((size_t)src - start);
	src -= count_s;
	d = dst + count_d;
	if (!size)
		return (count_s);
	count_s += (size > count_d ? count_d : size);
	while (*src && (size_t)d - (size_t)dst < size - 1)
		*d++ = *src++;
	*d = '\0';
	return (count_s);
}
