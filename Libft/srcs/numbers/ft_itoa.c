/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:44:49 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:05:54 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc) and returns a string representing the integer
** received as an argument. Negative numbers must be handled.
*/

#include <stdlib.h>

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				m;
	unsigned int	num;

	i = 1;
	if (n < 0)
		i++;
	m = n;
	while (m /= 10)
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	num = (n < 0) ? ((unsigned int)n * -1) : (unsigned int)n;
	str[i--] = '\0';
	while (num >= 10)
	{
		str[i--] = num % 10 + '0';
		num /= 10;
	}
	str[i--] = num + '0';
	return (str);
}
