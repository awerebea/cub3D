/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_desc_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:22:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/30 16:27:03 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <fcntl.h>

static int		f_pars_resolution(char *line, int i, t_sdf *opts)
{
	int errcode;

	errcode = 0;
	if (opts->x_win_size != -1)
		return (opts->err_string = ft_strdup("R")) ? 301 : 200;
	i++;
	opts->x_win_size = f_cub3d_atoi(line, &i);
	if (ft_isspace(line[i]))
		opts->y_win_size = f_cub3d_atoi(line, &i);
	if (opts->x_win_size > 0 && opts->y_win_size > 0)
	{
		while (!errcode && line[i])
			!ft_isspace(line[i++]) ? errcode = 310 : 0;
	}
	if (opts->x_win_size <= 0 || opts->y_win_size <= 0)
		errcode = 310;
	else if (!errcode && (opts->x_win_size < MIN_X_WIN_SIZE || \
			opts->x_win_size > MAX_X_WIN_SIZE || \
			opts->y_win_size < MIN_Y_WIN_SIZE || \
			opts->y_win_size > MAX_Y_WIN_SIZE))
		errcode = 311;
	return (errcode);
}

static int		f_pars_line(char *line, t_sdf *opts)
{
	int		i;

	i = 0;
	f_skip_spaces(line, &i);
	if (line[i] == 'R' && ft_isspace(line[i + 1]))
		return (f_pars_resolution(line, i, opts));
	if ((!(ft_strncmp(line + i, "NO", 2)) || \
		!(ft_strncmp(line + i, "SO", 2)) || !(ft_strncmp(line + i, "WE", 2)) \
		|| !(ft_strncmp(line + i, "EA", 2))) && ft_isspace(line[i + 2]))
		return (f_pars_wall_textures(line, i, opts));
	if (line[i] == 'S' && ft_isspace(line[i + 1]))
		return (f_pars_sprite_texture(line, i, opts));
	if (line[i] == 'F' && ft_isspace(line[i + 1]))
		return (f_pars_floor_color(line, i, opts));
	if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (f_pars_ceiling_color(line, i, opts));
	if (line[i] == '1')
		return (f_pars_map(line, opts));
	if (line[i] && opts->pars_map_started && opts->gnl_ret)
		return (opts->err_string = ft_strdup(line)) ? 302 : 200;
	if (!line[i] && opts->pars_map_started && opts->gnl_ret)
		return (303);
	if (!opts->gnl_ret && !opts->spawn_orientation)
		return (opts->pars_map_started) ? 343 : 344;
	return (!line[i]) ? 0 : 300;
}

static int		f_map_array_check_columns(t_sdf *opts)
{
	int		col;
	int		row;

	col = 0;
	while (col < opts->max_mapline_len)
	{
		row = 1;
		while (row <= opts->map_row_index)
		{
			if ((opts->map_array[row][col] == ' ' && \
				!(opts->map_array[row - 1][col] == '1' || \
				opts->map_array[row - 1][col] == ' ')) || \
				((ft_strchr("02NSWE", opts->map_array[row][col])) && \
				(row + 1 > opts->map_row_index || \
				opts->map_array[row - 1][col] == ' ')))
			{
				return ((opts->err_string = \
					ft_itoa(col + opts->prior_spaces_mapline + 1)) ? 346 : 200);
			}
			row++;
		}
		col++;
	}
	return (0);
}

int				f_pars_desc_file(char *map_file, t_sdf *opts)
{
	char	*line;
	int		fd;

	if ((fd = open(map_file, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(map_file)))
			return (200);
		f_print_err(101, opts);
		return (fd);
	}
	while (opts->gnl_ret > 0)
	{
		if ((opts->gnl_ret = get_next_line(fd, &line)) < 0)
			return (104);
		!opts->errcode ? (opts->errcode = f_pars_line(line, opts)) : 0;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (opts->errcode)
		return (opts->errcode);
	return ((opts->errcode = f_map_array_preparing(opts)) ? \
			opts->errcode : f_map_array_check_columns(opts));
}
