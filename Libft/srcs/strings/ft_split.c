/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:01:37 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 21:13:02 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc) and returns an array of strings obtained by
** splitting ’s’ using the character ’c’ as a delimiter.
** The array must be ended by a NULL pointer.
*/

#include <stdlib.h>

static size_t	f_str_counter(char const *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			counter++;
		while (*s && *s != c)
			s++;
	}
	return (counter);
}

static char		*f_str_filler(char const *s, char c, size_t *position)
{
	char	*str;
	size_t	i;
	size_t	str_len;
	size_t	start_pos;

	if (!s)
		return (NULL);
	i = *position;
	while (s[i] == c)
		i++;
	start_pos = i;
	str_len = 0;
	while (s[i] && s[i++] != c)
		str_len++;
	if (!(str = malloc(sizeof(char) * (str_len + 1))))
		return (NULL);
	*position = i;
	i = 0;
	while (i < str_len)
		str[i++] = s[start_pos++];
	str[i] = '\0';
	return (str);
}

char			**ft_split(char const *s, char c)
{
	char	**str_array;
	size_t	str_index;
	size_t	str_count;
	size_t	position;

	if (!s)
		return (NULL);
	str_count = f_str_counter(s, c);
	if (!(str_array = malloc(sizeof(char *) * (str_count + 1))))
		return (NULL);
	str_index = 0;
	position = 0;
	while (str_index < str_count)
	{
		if (!(str_array[str_index++] = f_str_filler(s, c, &position)))
		{
			str_index--;
			while (str_index && str_array[--str_index])
				free(str_array[str_index]);
			free(str_array);
			return (NULL);
		}
	}
	str_array[str_index] = NULL;
	return (str_array);
}
