/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:37:28 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:20:22 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*ptr_c;

	str = (char *)s;
	ptr_c = NULL;
	while (*str)
	{
		if (*str == c)
			ptr_c = str;
		str++;
	}
	if (c == '\0')
		ptr_c = str;
	return (ptr_c);
}
