/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/18 21:24:41 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <string.h>
#include <errno.h>

void	f_opts_init(t_sdf *opts)
{
	opts->screenshot = 0;
}

int		main(int argc, char **argv)
{
	int		errcode;
	t_sdf	opts;

	f_opts_init(&opts);
	if ((errcode = f_check_args(argc, argv, &opts)))
		return (f_exit(errcode));
	ft_putstr_fd("All is OK!\n", 1);
	ft_putnbr_fd(opts.screenshot, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
