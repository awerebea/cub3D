/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_options_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:05:01 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/24 14:53:45 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

static int	f_check_color_string(char *line, int i, t_sdf *opts, int *rgb)
{
	int				errcode;
	int				number;
	int				comma;

	errcode = 0;
	number = 0;
	comma = 0;
	f_skip_spaces(line, &i);
	while (line[i] && !errcode)
	{
		if (ft_isdigit(line[i]) && number < 3)
		{
			number++;
			rgb[number - 1] = f_cub3d_atoi(line, &i);
			f_skip_spaces(line, &i);
			if (line[i])
				(line[i++] == ',' && comma < 2) ? comma++ : errcode++;
			f_skip_spaces(line, &i);
		}
		else
			errcode++;
	}
	if (errcode || !(number == 3 && comma == 2))
		return (opts->err_string = ft_strdup("F")) ? 330 : 200;
	return (0);
}

int			f_pars_floor_color(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				rgb[3];

	errcode = 0;
	if (opts->floor_color != -1)
		return (opts->err_string = ft_strdup("F")) ? 301 : 200;
	i++;
	if ((errcode = f_check_color_string(line, i, opts, rgb)))
		return (errcode);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (opts->err_string = ft_strdup("F")) ? 331 : 200;
	opts->floor_color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (0);
}

int			f_pars_ceiling_color(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				rgb[3];

	errcode = 0;
	if (opts->ceiling_color != -1)
		return (opts->err_string = ft_strdup("C")) ? 301 : 200;
	i++;
	if ((errcode = f_check_color_string(line, i, opts, rgb)))
		return (errcode);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (opts->err_string = ft_strdup("C")) ? 331 : 200;
	opts->ceiling_color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (0);
}

int			f_pars_sprite_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	if (opts->sprite_texture_path)
		return (opts->err_string = ft_strdup("S")) ? 301 : 200;
	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	if (!(opts->sprite_texture_path = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->sprite_texture_path, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(opts->sprite_texture_path)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 320 : errcode;
}
