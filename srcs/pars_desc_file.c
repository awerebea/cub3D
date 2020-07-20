/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_desc_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:22:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/21 00:14:42 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <fcntl.h>

int				f_pars_resolution(char *line, int i, t_sdf *opts)
{
	int errcode;

	errcode = 0;
	i++;
	opts->x_render_size = f_cub3d_atoi(line, &i);
	if (ft_isspace(line[i]))
		opts->y_render_size = f_cub3d_atoi(line, &i);
	if (opts->x_render_size > 0 && opts->y_render_size > 0)
	{
		while (line[i] && !errcode)
			!ft_isspace(line[i++]) ? errcode = 6 : 0;
	}
	if (opts->x_render_size <= 0 || opts->y_render_size <= 0)
		errcode = 6;
	else if ((opts->x_render_size < MIN_X_RENDER_SIZE || \
			opts->x_render_size > MAX_X_RENDER_SIZE || \
			opts->y_render_size < MIN_Y_RENDER_SIZE || \
			opts->y_render_size > MAX_Y_RENDER_SIZE) && !errcode)
		errcode = 7;
	return (errcode);
}

int				f_pars_line(char *line, t_sdf *opts)
{
	int		i;

	i = 0;
	f_skip_spaces(line, &i);
	if (line[i] == 'R' && ft_isspace(line[i + 1]))
		return (f_pars_resolution(line, i, opts));
	else if (!(ft_strncmp(line + i, "NO", 2)) && ft_isspace(line[i + 2]))
		return (f_pars_no_texture(line, i, opts));
	return (!(line[i])) ? 0 : 5;
}

int				f_pars_desc_file(char *map_file, t_sdf *opts)
{
	char	*line;
	int		fd;
	int		gnl_ret;

	if ((fd = open(map_file, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", map_file);
		f_print_err(2);
		return (fd);
	}
	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		if ((gnl_ret = get_next_line(fd, &line)) < 0)
			return (4);
		!opts->errcode ? (opts->errcode = f_pars_line(line, opts)) : 0;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (opts->errcode);
}
