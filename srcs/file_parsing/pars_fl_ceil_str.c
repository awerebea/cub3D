/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fl_ceil_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:05:01 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 13:45:28 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

#ifdef BONUS

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

#else

static int	f_check_color_string(char *line, int i, int *rgb)
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
		return (330);
	return (0);
}

int			f_pars_floor_color(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				rgb[3];

	errcode = 0;
	if (opts->floor_color != -1)
		return (opts->err_str = ft_strdup("F")) ? 301 : 200;
	i++;
	if ((errcode = f_check_color_string(line, i, rgb)))
		return (opts->err_str = ft_strdup("F")) ? errcode : 200;
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (opts->err_str = ft_strdup("F")) ? 331 : 200;
	opts->floor_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (0);
}

int			f_pars_ceiling_color(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				rgb[3];

	errcode = 0;
	if (opts->ceiling_color != -1)
		return (opts->err_str = ft_strdup("C")) ? 301 : 200;
	i++;
	if ((errcode = f_check_color_string(line, i, rgb)))
		return (opts->err_str = ft_strdup("C")) ? errcode : 200;
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (opts->err_str = ft_strdup("C")) ? 331 : 200;
	opts->ceiling_color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (0);
}

#endif
