/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:42:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/19 15:51:33 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

/*
** fd - file descriptor
** rmndr - remainder of readed line from last iteration of GNL function
** rmndr_start - pointer to start of 'rmndr' string (for 'free')
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_list_gnl
{
	int					fd;
	char				*rmndr;
	char				*rmndr_start;
	struct s_list_gnl	*next;
}				t_list_gnl;

int				get_next_line(int fd, char **line);
t_list_gnl		*f_gnl_new(int fd);
t_list_gnl		*f_search_gnl(int fd, t_list_gnl **g_head);

#endif
