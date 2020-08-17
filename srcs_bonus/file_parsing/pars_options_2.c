/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_options_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:05:01 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/17 19:00:56 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int			f_pars_floor_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	if (opts->fl_tex)
		return (opts->err_str = ft_strdup("F")) ? 301 : 200;
	errcode = 0;
	i += 2;
	f_skip_spaces(line, &i);
	if (!(opts->fl_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->fl_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->fl_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}

int			f_pars_ceiling_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	if (opts->ce_tex)
		return (opts->err_str = ft_strdup("C")) ? 301 : 200;
	errcode = 0;
	i += 2;
	f_skip_spaces(line, &i);
	if (!(opts->ce_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->ce_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->ce_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}

int			f_pars_sprite_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	if (opts->sp_tex)
		return (opts->err_str = ft_strdup("S")) ? 301 : 200;
	errcode = 0;
	i += 2;
	f_skip_spaces(line, &i);
	if (!(opts->sp_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->sp_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->sp_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}
