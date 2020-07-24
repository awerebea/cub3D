/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:38:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/24 13:14:31 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		f_chek_opts_completeness(t_sdf *opts)
{
	return (opts->x_render_size == -1 || opts->y_render_size == -1 || \
		!opts->north_texture_path || !opts->south_texture_path || \
		!opts->west_texture_path || !opts->east_texture_path || \
		!opts->sprite_texture_path || opts->floor_color == -1 || \
		opts->ceiling_color == -1) ? 1 : 0;
}

int				f_pars_map(char *line, int i, t_sdf *opts)
{
	(void)line;
	(void)i;
	if (f_chek_opts_completeness(opts))
		return (340);
	return (0);
}
