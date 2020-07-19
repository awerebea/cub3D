/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_desc_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:22:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/20 00:33:14 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>


void			f_skip_spaces(char *line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
}

int				f_cub3d_atoi(char *line, int *i)
{
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	f_skip_spaces(line, i);
	if (line[*i] == '-')
		sign = -1;
	if (line[*i] == '-' || line[*i] == '+')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		if ((result * 10) < result)
			return (sign < 0 ? 0 : -1);
		result = result * 10 + line[*i] - '0';
		(*i)++;
	}
	return ((int)result * (int)sign);
}

int				f_pars_resolution(char *line, int i, t_sdf *opts)
{
	i++;
	opts->x_render_size = f_cub3d_atoi(line, &i);
	i++;
	opts->y_render_size = f_cub3d_atoi(line, &i);

	/* ft_putstr_fd("Resolution\n", 1);      */
	/* ft_putnbr_fd(opts->x_render_size, 1); */
	/* ft_putstr_fd("\n", 1);                */
	/* ft_putnbr_fd(opts->y_render_size, 1); */
	/* ft_putstr_fd("\n", 1);                */
	return (0);
}

int				f_pars_line(char *line, t_sdf *opts)
{
	int		i;

	i = 0;
	f_skip_spaces(line, &i);
	if (line[i] == 'R' && ft_isspace(line[i + 1]))
		return (f_pars_resolution(line, i, opts));
	else if (!(ft_strncmp(line + i, "NO", 2)) && ft_isspace(line[i + 2]))
	{
		/* ft_putstr_fd("NO\n", 1); */
		return (0);
	}
	return (!(line[i])) ? 0 : 5;
}

int				f_pars_desc_file(char *map_file, t_sdf *opts)
{
	char	*line;
	int		fd;
	int		gnl_ret;
	int		errcode;

	if ((fd = open(map_file, O_RDONLY)) < 0)
		return (fd);
	gnl_ret = 1;
	errcode = 0;
	while (gnl_ret > 0 && !errcode)
	{
		if ((gnl_ret = get_next_line(fd, &line)) < 0)
			return (4);
		errcode = f_pars_line(line, opts);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (errcode);
}
