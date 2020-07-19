/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_desc_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:22:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/19 21:24:23 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>

int				f_pars_line(char *line, t_sdf *opts)
{
	int		i;
	int		errcode;

	(void)opts;
	i = 0;
	while (line[i] && ft_strchr(" \t\v\f", line[i]))
		i++;
	if (!(line[i]))
		return (0);
	if ((!(ft_strncmp(line + i, "NO", 2)) && ft_isspace(line[i + 2])))
	{
		errcode = 0;
		ft_putstr_fd("NO\n", 1);
	}
	else
		errcode = 5;
	return (errcode);
}

int				f_pars_desc_file(char *map_file, t_sdf *opts)
{
	char	*line;
	int		fd;
	int		gnl_ret;
	int		errcode;

	if ((fd = open(map_file, O_RDONLY)) < 0)
		return (fd);
	gnl_ret = 1;
	errcode = 0;
	while (gnl_ret > 0 && !errcode)
	{
		if ((gnl_ret = get_next_line(fd, &line)) < 0)
			return (4);
		errcode = f_pars_line(line, opts);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (errcode);
}
