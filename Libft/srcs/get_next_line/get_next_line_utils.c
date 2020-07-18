/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:59:14 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/19 23:48:02 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len;
	size_t	start;

	if (!s1 || !s2)
		return (NULL);
	start = (size_t)s1;
	while (*s1)
		s1++;
	len = ((size_t)s1 - start);
	s1 -= ((size_t)s1 - start);
	start = (size_t)s2;
	while (*s2)
		s2++;
	len += ((size_t)s2 - start);
	s2 -= ((size_t)s2 - start);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	result -= len;
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;
	size_t	start;

	start = (size_t)s;
	while (*s)
		s++;
	len = (size_t)s - start;
	s -= len;
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s)
		*dest++ = (char)*s++;
	*dest = '\0';
	dest -= len;
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

t_list	*f_gnl_new(int fd)
{
	t_list		*gnl;

	if (!(gnl = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	gnl->fd = fd;
	gnl->rmndr = NULL;
	gnl->rmndr_start = NULL;
	gnl->next = NULL;
	return (gnl);
}

t_list	*f_search_gnl(int fd, t_list **g_head)
{
	t_list			*g_tmp;

	if (!*g_head)
		return ((*g_head = f_gnl_new(fd)) ? *g_head : NULL);
	g_tmp = *g_head;
	while (g_tmp->fd != fd && g_tmp->next)
		g_tmp = g_tmp->next;
	if (g_tmp->fd == fd)
		return (g_tmp);
	return ((g_tmp->next = f_gnl_new(fd)) ? g_tmp->next : NULL);
}
