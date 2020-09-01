/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line_n_check_opts_completeness.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:38:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/09/01 16:06:45 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#ifdef BONUS

int		f_pars_line(char *line, t_sdf *opts)
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
		return (f_pars_floor_texture(line, i, opts));
	if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (f_pars_ceiling_texture(line, i, opts));
	if (line[i] == '1')
		return (f_pars_map(line, opts));
	if (line[i] && opts->pars_map_started && opts->gnl_ret)
		return (opts->err_str = ft_strdup(line)) ? 302 : 200;
	if (!line[i] && opts->pars_map_started && opts->gnl_ret)
		return (303);
	if (!opts->gnl_ret && !opts->spawn_orientation)
		return (opts->pars_map_started) ? 343 : 344;
	return (!line[i]) ? 0 : 300;
}

int		f_check_opts_completeness(t_sdf *opts)
{
	if (opts->x_win_size == -1 || opts->y_win_size == -1 || !opts->no_tex \
		|| !opts->so_tex || !opts->we_tex || !opts->ea_tex \
		|| !opts->sp_tex || !opts->fl_tex || !opts->ce_tex)
		return (1);
	opts->pars_map_started = 1;
	return (0);
}

#else

int		f_pars_line(char *line, t_sdf *opts)
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
		return (opts->err_str = ft_strdup(line)) ? 302 : 200;
	if (!line[i] && opts->pars_map_started && opts->gnl_ret)
		return (303);
	return (!line[i]) ? 0 : 300;
}

int		f_check_opts_completeness(t_sdf *opts)
{
	if (opts->x_win_size == -1 || opts->y_win_size == -1 || !opts->no_tex \
		|| !opts->so_tex || !opts->we_tex || !opts->ea_tex \
		|| !opts->sp_tex || opts->floor_color == -1 || \
		opts->ceiling_color == -1)
		return (1);
	opts->pars_map_started = 1;
	return (0);
}

#endif
