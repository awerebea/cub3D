/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/21 00:11:48 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <string.h>
#include <errno.h>

void			f_clean_mem(t_sdf *opts)
{
	if (opts->north_texture_path)
	{
		free(opts->north_texture_path);
		opts->north_texture_path = NULL;
	}
	opts->south_texture_path = NULL;
	opts->west_texture_path = NULL;
	opts->east_texture_path = NULL;
	opts->sprite_texture_path = NULL;
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
	opts->floor_colour = -1;
	opts->ceiling_colour = -1;
	opts->screenshot = 0;
	opts->spawn_point = -1;
	opts->line_count = -1;
	opts->max_length = -1;
	opts->errcode = 0;
}

int				f_exit(int errcode, t_sdf *opts)
{
	if (errcode > 0)
		f_print_err(errcode);
	else if (errcode < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
	}
	f_clean_mem(opts);
	return (errcode);
}

int				main(int argc, char **argv)
{
	int		errcode;
	t_sdf	opts;

	errcode = 0;
	f_opts_init(&opts);
	if ((errcode = f_check_args(argc, argv, &opts)))
		return (f_exit(errcode, &opts));
	if ((errcode = f_pars_desc_file(argv[1], &opts)))
		return (f_exit(errcode, &opts));
	ft_putstr_fd("All is OK!\n", 1);
	ft_putnbr_fd(opts.screenshot, 1);
	ft_putchar_fd('\n', 1);
	return (f_exit(errcode, &opts));
}
