/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_options_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:40:04 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/12 15:19:41 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	f_pars_north_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->no_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->no_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->no_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}

static int	f_pars_south_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->so_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->so_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->so_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}

static int	f_pars_west_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->we_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->we_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->we_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}

static int	f_pars_east_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->ea_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->ea_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->ea_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}

int			f_pars_wall_textures(char *line, int i, t_sdf *opts)
{
	if (line[i] == 'N')
	{
		if (opts->no_tex)
			return (opts->err_str = ft_strdup("NO")) ? 301 : 200;
		return (f_pars_north_texture(line, i, opts));
	}
	if (line[i] == 'S')
	{
		if (opts->so_tex)
			return (opts->err_str = ft_strdup("SO")) ? 301 : 200;
		return (f_pars_south_texture(line, i, opts));
	}
	if (line[i] == 'W')
	{
		if (opts->we_tex)
			return (opts->err_str = ft_strdup("WE")) ? 301 : 200;
		return (f_pars_west_texture(line, i, opts));
	}
	else
	{
		if (opts->ea_tex)
			return (opts->err_str = ft_strdup("EA")) ? 301 : 200;
		return (f_pars_east_texture(line, i, opts));
	}
}
