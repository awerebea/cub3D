/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 13:38:29 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#ifdef BONUS

int		f_opts_init(t_sdf *opts)
{
	opts->x_win_size = -1;
	opts->y_win_size = -1;
	opts->no_tex = NULL;
	opts->so_tex = NULL;
	opts->we_tex = NULL;
	opts->ea_tex = NULL;
	opts->sp_tex = NULL;
	opts->fl_tex = NULL;
	opts->ce_tex = NULL;
	opts->gnl_ret = 1;
	opts->screenshot = 0;
	opts->pars_map_started = 0;
	opts->spawn_point_x = -1;
	opts->spawn_point_y = -1;
	opts->spawn_orientation = '\0';
	opts->max_mapline_len = 0;
	opts->prior_spaces_mapline = -1;
	opts->errcode = 0;
	opts->err_str = NULL;
	opts->map_row_index = -1;
	opts->map_array = NULL;
	if (!(opts->map_line = ft_strdup("")))
		return (200);
	return (0);
}

int		f_exit(int errcode, t_sdf *opts)
{
	int		i;

	i = 0;
	f_print_err(errcode, opts);
	free((opts->no_tex) ? opts->no_tex : NULL);
	free((opts->so_tex) ? opts->so_tex : NULL);
	free((opts->we_tex) ? opts->we_tex : NULL);
	free((opts->ea_tex) ? opts->ea_tex : NULL);
	free((opts->sp_tex) ? opts->sp_tex : NULL);
	free((opts->fl_tex) ? opts->fl_tex : NULL);
	free((opts->ce_tex) ? opts->ce_tex : NULL);
	free((opts->err_str) ? opts->err_str : NULL);
	free((opts->map_line) ? opts->map_line : NULL);
	if (opts->map_array)
	{
		while (opts->map_array[i])
		{
			free(opts->map_array[i]);
			opts->map_array[i++] = NULL;
		}
		free(opts->map_array);
		opts->map_array = NULL;
	}
	return (errcode);
}

#else

int		f_opts_init(t_sdf *opts)
{
	opts->x_win_size = -1;
	opts->y_win_size = -1;
	opts->no_tex = NULL;
	opts->so_tex = NULL;
	opts->we_tex = NULL;
	opts->ea_tex = NULL;
	opts->sp_tex = NULL;
	opts->floor_color = -1;
	opts->ceiling_color = -1;
	opts->gnl_ret = 1;
	opts->screenshot = 0;
	opts->pars_map_started = 0;
	opts->spawn_point_x = -1;
	opts->spawn_point_y = -1;
	opts->spawn_orientation = '\0';
	opts->max_mapline_len = 0;
	opts->prior_spaces_mapline = -1;
	opts->errcode = 0;
	opts->err_str = NULL;
	opts->map_row_index = -1;
	opts->map_array = NULL;
	if (!(opts->map_line = ft_strdup("")))
		return (200);
	return (0);
}

int		f_exit(int errcode, t_sdf *opts)
{
	int		i;

	i = 0;
	f_print_err(errcode, opts);
	free((opts->no_tex) ? opts->no_tex : NULL);
	free((opts->so_tex) ? opts->so_tex : NULL);
	free((opts->we_tex) ? opts->we_tex : NULL);
	free((opts->ea_tex) ? opts->ea_tex : NULL);
	free((opts->sp_tex) ? opts->sp_tex : NULL);
	free((opts->err_str) ? opts->err_str : NULL);
	free((opts->map_line) ? opts->map_line : NULL);
	if (opts->map_array)
	{
		while (opts->map_array[i])
		{
			free(opts->map_array[i]);
			opts->map_array[i++] = NULL;
		}
		free(opts->map_array);
		opts->map_array = NULL;
	}
	return (errcode);
}

#endif
