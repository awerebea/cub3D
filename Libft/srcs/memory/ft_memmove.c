/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 22:06:39 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:08:38 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 1;
	if (src < dest)
	{
		while (i <= n)
		{
			d[n - i] = s[n - i];
			i++;
		}
	}
	else if (src > dest)
	{
		while (n--)
			*d++ = *s++;
	}
	else
		return (dest);
	return (dest);
}
