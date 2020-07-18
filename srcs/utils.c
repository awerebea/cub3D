/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:12:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/18 21:26:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <string.h>
#include <errno.h>

static void		f_print_error_1_3(int errcode)
{
	if (errcode == 1)
		ft_putstr_fd("ERROR 1: wrong number of arguments.\n\
DESCRIPTION: There can be only one or two arguments. The first argument MUST \
be a '.cub' file wih map.\nThe second argument CAN be '--save', \
in this case the 'cub3D' just takes screenshot of spawn scene and quits.\n", 2);
	else if (errcode == 2)
		ft_putstr_fd("ERROR 2: wrong name of map file.\n\
DESCRIPTION: the first argument is always the name of the map file, and it \
must have a name with at least one character and an extension '.cub'.\n", 2);
	else if (errcode == 3)
		ft_putstr_fd("ERROR 3: wrong second argument.\n\
DESCRIPTION: it can be only '--save', in this case the 'cub3D' just takes \
screenshot of spawn scene and quits.\n", 2);
}

int				f_exit(int errcode)
{
	if (errcode > 0 && errcode <= 10)
		f_print_error_1_3(errcode);
	else
		ft_putstr_fd(strerror(errno), 1);
	return (errcode);
}

int				f_check_args(int argc, char **argv, t_sdf *opts)
{
	if (argc < 2 || argc > 3)
		return (1);
	if (ft_strlen(argv[1]) < 5 \
			|| (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5)))
		return (2);
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 6)))
			return (3);
		else
			opts->screenshot = 1;
	}
	if (argc > 3)
		return (5);
	return (0);
}
