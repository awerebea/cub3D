/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:59:14 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/19 15:47:56 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list_gnl	*f_gnl_new(int fd)
{
	t_list_gnl	*gnl;

	if (!(gnl = (t_list_gnl*)malloc(sizeof(t_list_gnl))))
		return (NULL);
	gnl->fd = fd;
	gnl->rmndr = NULL;
	gnl->rmndr_start = NULL;
	gnl->next = NULL;
	return (gnl);
}

t_list_gnl	*f_search_gnl(int fd, t_list_gnl **g_head)
{
	t_list_gnl	*g_tmp;

	if (!*g_head)
		return ((*g_head = f_gnl_new(fd)) ? *g_head : NULL);
	g_tmp = *g_head;
	while (g_tmp->fd != fd && g_tmp->next)
		g_tmp = g_tmp->next;
	if (g_tmp->fd == fd)
		return (g_tmp);
	return ((g_tmp->next = f_gnl_new(fd)) ? g_tmp->next : NULL);
}
