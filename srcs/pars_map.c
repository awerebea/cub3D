/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:38:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/25 15:31:33 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int		f_check_opts_completeness(t_sdf *opts)
{
	if (opts->x_render_size == -1 || opts->y_render_size == -1 || \
		!opts->north_texture_path || !opts->south_texture_path || \
		!opts->west_texture_path || !opts->east_texture_path || \
		!opts->sprite_texture_path || opts->floor_color == -1 || \
		opts->ceiling_color == -1)
		return (1);
	opts->pars_map_started = 1;
	return (0);
}

static int		f_check_line(char *line, int i, t_sdf *opts)
{
	while (line[++i])
	{
		if (!opts->map_row_index && !ft_strchr(" 1", line[i]))
			return (opts->err_string = ft_strdup(line)) ? 345 : 200;
		if (opts->map_row_index && !ft_strchr(" 012NSWE", line[i]))
			return (opts->err_string = ft_strdup(line)) ? 341 : 200;
		if (line[i] == ' ' && !(line[i - 1] == '1' || line[i - 1] == ' '))
			return (opts->err_string = ft_strdup(line)) ? 341 : 200;
		if (ft_strchr("02NSWE", line[i]) && line[i + 1] == '\0')
			return (opts->err_string = ft_strdup(line)) ? 341 : 200;
		if (ft_strchr("NSWE", line[i]) && !opts->spawn_orientation)
		{
			opts->spawn_orientation = line[i];
			opts->spawn_point_x = i;
			opts->spawn_point_y = opts->map_row_index;
		}
		else if (ft_strchr("NSWE", line[i]) && opts->spawn_orientation)
			return (342);
	}
	return (0);
}

static int		f_map_line_join(char *line, t_sdf *opts)
{
	char	*tmp_map_line;
	char	*tmp_line;

	tmp_map_line = opts->map_line;
	if (!(tmp_line = ft_strjoin(line, "\n")))
		return (200);
	if (!(opts->map_line = ft_strjoin(opts->map_line, tmp_line)))
		return (200);
	free(tmp_map_line);
	free(tmp_line);
	return (0);
}

int				f_pars_map(char *line, t_sdf *opts)
{
	int		i;

	i = -1;
	if (!opts->pars_map_started && f_check_opts_completeness(opts))
		return (340);
	opts->map_row_index++;
	while (line[++i] != '1')
	{
		if (line[i] != ' ')
			return (opts->err_string = ft_strdup(line)) ? 341 : 200;
	}
	if (opts->prior_spaces_mapline < 0)
		opts->prior_spaces_mapline = i;
	else if (opts->prior_spaces_mapline > i)
		opts->prior_spaces_mapline = i;
	if ((i = f_check_line(line, i, opts)))
		return (i);
	if ((i = f_map_line_join(line, opts)))
		return (i);
	return (0);
}
