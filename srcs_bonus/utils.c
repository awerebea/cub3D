/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:36:56 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/17 19:24:15 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"

int		f_exit(int errcode, t_sdf *opts)
{
	int		i;

	i = 0;
	f_print_err(errcode, opts);
	free((opts->no_tex) ? opts->no_tex : NULL);
	free((opts->so_tex) ? opts->so_tex : NULL);
	free((opts->we_tex) ? opts->we_tex : NULL);
	free((opts->ea_tex) ? opts->ea_tex : NULL);
	free((opts->sp_tex) ? opts->sp_tex : NULL);
	free((opts->fl_tex) ? opts->fl_tex : NULL);
	free((opts->ce_tex) ? opts->ce_tex : NULL);
	free((opts->err_str) ? opts->err_str : NULL);
	free((opts->map_line) ? opts->map_line : NULL);
	if (opts->map_array)
	{
		while (opts->map_array[i])
		{
			free(opts->map_array[i]);
			opts->map_array[i++] = NULL;
		}
		free(opts->map_array);
		opts->map_array = NULL;
	}
	return (errcode);
}

void	f_skip_spaces(char *line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
}

int		f_cub3d_atoi(char *line, int *i)
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
