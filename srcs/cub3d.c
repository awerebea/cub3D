/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/25 00:04:58 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"
#include <string.h>
#include <errno.h>

void			f_clean_mem(t_sdf *opts)
{
	free((opts->north_texture_path) ? opts->north_texture_path : NULL);
	opts->north_texture_path = NULL;
	free((opts->south_texture_path) ? opts->south_texture_path : NULL);
	opts->south_texture_path = NULL;
	free((opts->west_texture_path) ? opts->west_texture_path : NULL);
	opts->west_texture_path = NULL;
	free((opts->east_texture_path) ? opts->east_texture_path : NULL);
	opts->east_texture_path = NULL;
	free((opts->sprite_texture_path) ? opts->sprite_texture_path : NULL);
	opts->sprite_texture_path = NULL;
	free((opts->err_string) ? opts->err_string : NULL);
	opts->err_string = NULL;
	free((opts->map_line) ? opts->map_line : NULL);
	opts->map_line = NULL;
}

void			f_opts_init(t_sdf *opts)
{
	opts->x_render_size = -1;
	opts->y_render_size = -1;
	opts->north_texture_path = NULL;
	opts->south_texture_path = NULL;
	opts->west_texture_path = NULL;
	opts->east_texture_path = NULL;
	opts->sprite_texture_path = NULL;
	opts->floor_color = -1;
	opts->ceiling_color = -1;
	opts->gnl_ret = 1;
	opts->screenshot = 0;
	opts->pars_map_started = 0;
	opts->spawn_point_x = -1;
	opts->spawn_point_y = -1;
	opts->spawn_orientation = '\0';
	opts->line_count = -1;
	opts->max_length = -1;
	opts->errcode = 0;
	opts->err_string = NULL;
	opts->map_line = NULL;
	opts->map_row_index = -1;
}

int				f_exit(int errcode, t_sdf *opts)
{
	if (errcode > 0)
		f_print_err(errcode, opts);
	else if (errcode < 0)
		ft_printf("%s\n", strerror(errno));
	f_clean_mem(opts);
	return (errcode);
}

int				main(int argc, char **argv)
{
	int		errcode;
	t_sdf	opts;
	int		r;
	int		g;
	int		b;

	errcode = 0;
	f_opts_init(&opts);
	if ((errcode = f_check_args(argc, argv, &opts)))
		return (f_exit(errcode, &opts));
	if ((errcode = f_pars_desc_file(argv[1], &opts)))
		return (f_exit(errcode, &opts));
	ft_printf("All is OK!\nScreenshot: %d\n", opts.screenshot);
	r = (opts.floor_color & 0xFF0000) >> 16;
	g = (opts.floor_color & 0xFF00) >> 8;
	b = opts.floor_color & 0xFF;
	ft_printf("Floor RGB:   %3d, %3d, %3d\n", r, g, b);
	r = (opts.ceiling_color & 0xFF0000) >> 16;
	g = (opts.ceiling_color & 0xFF00) >> 8;
	b = opts.ceiling_color & 0xFF;
	ft_printf("Ceiling RGB: %3d, %3d, %3d\n", r, g, b);
	ft_printf("Spawn X: %d, Y: %d orientation: %c\n", \
			opts.spawn_point_x, opts.spawn_point_y, opts.spawn_orientation);
	return (f_exit(errcode, &opts));
}
