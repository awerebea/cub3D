/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:36:56 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 11:23:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
