/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:47:17 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/18 17:42:59 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <string.h>
#include <errno.h>

void	f_sdf_init(t_sdf *sdf)
{
	sdf->screenshot = 0;
}

void	f_print_error_1_10(int errcode)
{
	if (errcode == 1)
		ft_putstr_fd("Error 1: no map file specified\n", 1);
	else if (errcode == 2)
		ft_putstr_fd("Error 2: map file must have name (at least 1 symbol) and \
extension '.cub'\n", 1);
	else if (errcode == 3)
		ft_putstr_fd("Error 3: wrong extension of map file, \
it must be '.cub'\n", 1);
	else if (errcode == 4)
		ft_putstr_fd("Error 4: wrong second argument, \
it can be only '--save' (if You want take screenshot of scene and quit)\n", 1);
	else if (errcode == 5)
		ft_putstr_fd("Error 5: wrong number of arguments, \
it can be minimum one (.cub file) and maximum two (if You want take screenshot \
of scene and quit)\n", 1);
}

int		f_exit(int errcode)
{
	if (errcode > 0 && errcode <= 10)
		f_print_error_1_10(errcode);
	else
		ft_putstr_fd(strerror(errno), 1);
	return (0);
}

int		f_check_args(int argc, char **argv, t_sdf *sdf)
{
	if (argc < 2)
		return (1);
	if (ft_strlen(argv[1]) < 5)
		return (2);
	if ((ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5)))
		return (3);
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 6)))
			return (4);
		else
			sdf->screenshot = 1;
	}
	if (argc > 3)
		return (5);
	return (0);
}

int		main(int argc, char **argv)
{
	int		errcode;
	t_sdf	sdf;

	f_sdf_init(&sdf);
	if ((errcode = f_check_args(argc, argv, &sdf)))
		return (f_exit(errcode));
	ft_putstr_fd("All is OK!\n", 1);
	ft_putnbr_fd(sdf.screenshot, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
