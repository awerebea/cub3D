/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_options_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:40:04 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/25 16:56:24 by awerebea         ###   ########.fr       */
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
	if (!(opts->north_texture_path = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->north_texture_path, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(opts->north_texture_path)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 320 : errcode;
}

static int	f_pars_south_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->south_texture_path = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->south_texture_path, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(opts->south_texture_path)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 320 : errcode;
}

static int	f_pars_west_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->west_texture_path = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->west_texture_path, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(opts->west_texture_path)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 320 : errcode;
}

static int	f_pars_east_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->east_texture_path = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->east_texture_path, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(opts->east_texture_path)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 320 : errcode;
}

int			f_pars_wall_textures(char *line, int i, t_sdf *opts)
{
	if (line[i] == 'N')
	{
		if (opts->north_texture_path)
			return (opts->err_string = ft_strdup("NO")) ? 301 : 200;
		return (f_pars_north_texture(line, i, opts));
	}
	if (line[i] == 'S')
	{
		if (opts->south_texture_path)
			return (opts->err_string = ft_strdup("SO")) ? 301 : 200;
		return (f_pars_south_texture(line, i, opts));
	}
	if (line[i] == 'W')
	{
		if (opts->west_texture_path)
			return (opts->err_string = ft_strdup("WE")) ? 301 : 200;
		return (f_pars_west_texture(line, i, opts));
	}
	else
	{
		if (opts->east_texture_path)
			return (opts->err_string = ft_strdup("EA")) ? 301 : 200;
		return (f_pars_east_texture(line, i, opts));
	}
}
