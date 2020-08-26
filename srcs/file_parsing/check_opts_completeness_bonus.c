/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opts_completeness_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:38:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 12:04:43 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		f_check_opts_completeness(t_sdf *opts)
{
	if (opts->x_win_size == -1 || opts->y_win_size == -1 || !opts->no_tex \
		|| !opts->so_tex || !opts->we_tex || !opts->ea_tex \
		|| !opts->sp_tex || !opts->fl_tex || !opts->ce_tex)
		return (1);
	opts->pars_map_started = 1;
	return (0);
}
