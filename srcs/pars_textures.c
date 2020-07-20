/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:40:04 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/21 01:53:57 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

static int	f_pars_north_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				i_bckp;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	i_bckp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!(i - i_bckp))
		return (9);
	if (!(opts->north_texture_path = malloc(i - i_bckp + 1)))
		return (8);
	ft_strlcpy(opts->north_texture_path, line + i_bckp, i - i_bckp + 1);
	if ((fd = open(opts->north_texture_path, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", opts->north_texture_path);
		f_print_err(10);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 10 : errcode;
}

static int	f_pars_south_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				i_bckp;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	i_bckp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!(i - i_bckp))
		return (9);
	if (!(opts->south_texture_path = malloc(i - i_bckp + 1)))
		return (8);
	ft_strlcpy(opts->south_texture_path, line + i_bckp, i - i_bckp + 1);
	if ((fd = open(opts->south_texture_path, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", opts->south_texture_path);
		f_print_err(10);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 10 : errcode;
}

static int	f_pars_west_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				i_bckp;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	i_bckp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!(i - i_bckp))
		return (9);
	if (!(opts->west_texture_path = malloc(i - i_bckp + 1)))
		return (8);
	ft_strlcpy(opts->west_texture_path, line + i_bckp, i - i_bckp + 1);
	if ((fd = open(opts->west_texture_path, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", opts->west_texture_path);
		f_print_err(10);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 10 : errcode;
}

static int	f_pars_east_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				i_bckp;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	i_bckp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!(i - i_bckp))
		return (9);
	if (!(opts->east_texture_path = malloc(i - i_bckp + 1)))
		return (8);
	ft_strlcpy(opts->east_texture_path, line + i_bckp, i - i_bckp + 1);
	if ((fd = open(opts->east_texture_path, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", opts->east_texture_path);
		f_print_err(10);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 10 : errcode;
}

int			f_pars_wall_textures(char *line, int i, t_sdf *opts)
{
	if (line[i] == 'N')
	{
		return (opts->north_texture_path) ? \
			12 : f_pars_north_texture(line, i, opts);
	}
	else if (line[i] == 'S')
	{
		return (opts->south_texture_path) ? \
			13 : f_pars_south_texture(line, i, opts);
	}
	else if (line[i] == 'W')
	{
		return (opts->west_texture_path) ? \
			14 : f_pars_west_texture(line, i, opts);
	}
	else
	{
		return (opts->east_texture_path) ? \
			15 : f_pars_east_texture(line, i, opts);
	}
}
