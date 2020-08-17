/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:38:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/17 18:31:55 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"

static int		f_check_opts_completeness(t_sdf *opts)
{
	if (opts->x_win_size == -1 || opts->y_win_size == -1 || !opts->no_tex \
		|| !opts->so_tex || !opts->we_tex || !opts->ea_tex \
		|| !opts->sp_tex || !opts->fl_tex|| !opts->ce_tex)
		return (1);
	opts->pars_map_started = 1;
	return (0);
}

static int		f_check_line(char *line, int i, t_sdf *opts)
{
	while (line[++i])
	{
		if (!opts->map_row_index && !ft_strchr(" 1", line[i]))
			return (opts->err_str = ft_strdup(line)) ? 345 : 200;
		if (opts->map_row_index && !ft_strchr(" 012NSWE", line[i]))
			return (opts->err_str = ft_strdup(line)) ? 341 : 200;
		if (line[i] == ' ' && !(line[i - 1] == '1' || line[i - 1] == ' '))
			return (opts->err_str = ft_strdup(line)) ? 341 : 200;
		if (ft_strchr("02NSWE", line[i]) && line[i + 1] == '\0')
			return (opts->err_str = ft_strdup(line)) ? 341 : 200;
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
	int		errcode;
	int		i;

	i = 0;
	if (!opts->pars_map_started && f_check_opts_completeness(opts))
		return (340);
	opts->map_row_index++;
	while (line[i] != '1')
	{
		if (line[i] != ' ')
			return (opts->err_str = ft_strdup(line)) ? 341 : 200;
		i++;
	}
	if (opts->prior_spaces_mapline < 0)
		opts->prior_spaces_mapline = i;
	else if (opts->prior_spaces_mapline > i)
		opts->prior_spaces_mapline = i;
	if ((errcode = f_check_line(line, i, opts)))
		return (errcode);
	if ((errcode = f_map_line_join(line, opts)))
		return (errcode);
	return (0);
}
