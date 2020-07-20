/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/07/20 00:35:02 by awerebea         ###   ########.fr       */
=======
/*   Updated: 2020/07/20 00:21:46 by awerebea         ###   ########.fr       */
>>>>>>> test
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <string.h>
#include <errno.h>

void			f_opts_init(t_sdf *opts)
{
	opts->screenshot = 0;
	opts->x_render_size = -8;
	opts->y_render_size = -8;
	opts->north_texture_path = NULL;
	opts->south_texture_path = NULL;
	opts->west_texture_path = NULL;
	opts->east_texture_path = NULL;
	opts->sprite_texture_path = NULL;
	opts->floor_colour = -8;
	opts->ceiling_colour = -8;
	opts->spawn_point = -8;
	opts->line_count = -8;
	opts->max_length = -8;
}

int				f_exit(int errcode)
{
	if (errcode > 0 && errcode <= 5)
		f_print_error_1_4(errcode);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 1);
	}
	return (errcode);
}

int				main(int argc, char **argv)
{
	int		errcode;
	t_sdf	opts;

	f_opts_init(&opts);
	if ((errcode = f_check_args(argc, argv, &opts)))
		return (f_exit(errcode));
	if ((errcode = f_pars_desc_file(argv[1], &opts)))
		return (f_exit(errcode));
	/* ft_putstr_fd("All is OK!\n", 1);  */
	/* ft_putnbr_fd(opts.screenshot, 1); */
	/* ft_putchar_fd('\n', 1);           */
	return (0);
}
