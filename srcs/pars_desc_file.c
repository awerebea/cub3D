/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_desc_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:22:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/19 00:52:41 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "cub3d.h"
#include <stdlib.h>
#include <fcntl.h>

int				f_parsing_line(char **line, t_sdf *opts)
{
	(void)line;
	(void)opts;
	return (0);
}

int				f_parsing_desc_file(char *map_file, t_sdf *opts)
{
	char	*line;
	int		fd;
	int		gnl_ret;
	int		errcode;

	if((fd = open(map_file, O_RDONLY)) < 0)
		return (fd);
	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		if((gnl_ret = get_next_line(fd, &line)) < 0)
			return (4);
		if((errcode = f_parsing_line(&line, opts)))
			return (errcode);
	}
	return (0);
}
