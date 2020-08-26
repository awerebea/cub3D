/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 11:21:18 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int				main(int argc, char **argv)
{
	int		errcode;
	t_sdf	opts;

	if ((errcode = f_opts_init(&opts)))
		return (errcode);
	if ((errcode = f_check_args(argc, argv, &opts)))
		return (f_exit(errcode, &opts));
	if ((errcode = f_pars_desc_file(argv[1], &opts)))
		return (f_exit(errcode, &opts));
	f_game(&opts);
	return (0);
}
