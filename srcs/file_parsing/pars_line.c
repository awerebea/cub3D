/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:22:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 12:41:31 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

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
	if (!opts->gnl_ret && !opts->spawn_orientation)
		return (opts->pars_map_started) ? 343 : 344;
	return (!line[i]) ? 0 : 300;
}
