/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:58:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/19 13:48:53 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Exit function is to free memory in case of exit because error is occurred
** (exit code -1), or when we exit bacause in FD nothing to read more.
** We search current sheet of list and free it, with no missing pointer to
** next sheet in list.
*/

static int	f_exit(char *buf, int fd, t_list_gnl **g_head, int exit_code)
{
	t_list_gnl		*g_tmp;
	t_list_gnl		*g_tmp_2;

	free(buf);
	g_tmp = *g_head;
	if (g_tmp->fd == fd)
		*g_head = g_tmp->next;
	else
	{
		while (g_tmp->next->fd != fd)
			g_tmp = g_tmp->next;
		g_tmp_2 = g_tmp->next;
		g_tmp->next = g_tmp->next->next;
		g_tmp = g_tmp_2;
	}
	free(g_tmp);
	return (exit_code);
}

/*
** part of step 3.
** check for the presence of a symbol '\n' in the last readed buffer string,
** and duplicatind part of string after '\n' position to remainder. Symbol
** '\n' to '\0' replacement is to limit the attachable to "line" portion of a
** buffer string.
** If '\n' in buffer string is found, we return with 1, and if it is not -
** return with 0. In case of error of ft_strdup, we return to exit function
** with exit code -1.
*/

static int	f_chk_buf(char *buf, t_list_gnl *g_curr, t_list_gnl **g_head)
{
	char			*tmp_ptr;

	if ((tmp_ptr = ft_strchr(buf, '\n')))
	{
		*tmp_ptr = '\0';
		if (!(g_curr->rmndr = ft_strdup(++tmp_ptr)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
		g_curr->rmndr_start = g_curr->rmndr;
	}
	return (tmp_ptr ? 1 : 0);
}

/*
** step 3/
** read FD in buffer string in fragments of BUFFER_SIZE bytes, while there is
** something to read. After reading each fragment, we check it for the presence
** of a symbol '\n' in it. If it is there, then we join to "line" part of buffer
** string before position of '\n', rest of buffer string duplicate to remainder
** and return with "1". If there is no '\n' symbol in the buffer string, we join
** to "line" whole buffer string and read again. If the entire FD is readed and
** the '\n' symbol is not found, we return to exit function with exit code 0.
** In case of error we return to exit function with exit code -1.
*/

static int	f_read_line(t_list_gnl *g_curr, t_list_gnl **g_head, char **line)
{
	long long			result;
	char				*buf;
	char				*tmp_ptr;

	if (!(buf = (char*)(malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (f_exit(buf, g_curr->fd, g_head, -1));
	while ((result = read(g_curr->fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[result] = '\0';
		result = f_chk_buf(buf, g_curr, g_head);
		tmp_ptr = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
		free(tmp_ptr);
		if (result)
		{
			free(buf);
			return (1);
		}
	}
	return (result == 0 ? f_exit(buf, g_curr->fd, g_head, 0) : \
							f_exit(buf, g_curr->fd, g_head, -1));
}

/*
** step 2.
** checking for the existence of the remainder of the line from the previous
** iteration GNL. If it exist - checking for the '\n' symbol in remainder,
** if it is there, then duplicate part of string before position of '\n',
** move pointer of remainder string, and return with "1". Symbol
** '\n' to '\0' replacement is to limit the attachable to "line" portion of a
** buffer string.
** If remainder exist, but there isn't '\n' in it, duplicate whole remainder
** string in "line" and return to next step, to function, that reads FD
** in searh of a symbol '\n'.
** If remainder is not exist, return to next step directly.
** In case of error we return to exit function with exit code -1.
*/

static int	f_chk_rmndr(t_list_gnl *g_curr, t_list_gnl **g_head, char **line)
{
	char				*tmp_ptr;
	char				*start_pos;

	if (!(*line = ft_strdup("")))
		return (f_exit(NULL, g_curr->fd, g_head, -1));
	if (g_curr->rmndr)
	{
		start_pos = g_curr->rmndr;
		if ((tmp_ptr = ft_strchr(g_curr->rmndr, '\n')))
		{
			*tmp_ptr = '\0';
			g_curr->rmndr = ++tmp_ptr;
		}
		tmp_ptr = *line;
		if (!(*line = ft_strdup(start_pos)))
			return (f_exit(NULL, g_curr->fd, g_head, -1));
		free(tmp_ptr);
		if (start_pos != g_curr->rmndr)
			return (1);
		free(g_curr->rmndr_start);
	}
	return (f_read_line(g_curr, g_head, line));
}

/*
** step 1.
** checking of incoming arguments for valid values,
** declaration of head element of list by  static variable (g_head),
** declaration and initialisation of the current scheet of list (g_curr),
** return to function to check remainder of string from previous iteration GNL
** In case of error we return with -1.
*/

int			get_next_line(int fd, char **line)
{
	static t_list_gnl	*g_head;
	t_list_gnl			*g_curr;
	const long long		buf_size = BUFFER_SIZE;
	char				read_chk[1];

	if (fd < 0 || !line || buf_size < 1 || ((read(fd, read_chk, 0) < 0)))
		return (-1);
	if (!(g_curr = f_search_gnl(fd, &g_head)))
		return (-1);
	return (f_chk_rmndr(g_curr, &g_head, line));
}
