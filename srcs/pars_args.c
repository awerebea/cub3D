/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:12:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/24 13:18:39 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	f_check_screenshot_arg(char **argv, t_sdf *opts)
{
	int	len;

	len = ft_strlen(argv[2]);
	if ((ft_strncmp(argv[2], "--save", 6)))
	{
		if (!(opts->err_string = malloc(len + 1)))
			return (200);
		ft_strlcpy(opts->err_string, argv[2], len + 1);
		return (103);
	}
	else
		opts->screenshot = 1;
	return (0);
}

int			f_check_args(int argc, char **argv, t_sdf *opts)
{
	int	len;
	int	errcode;

	if (argc < 2 || argc > 3)
		return (100);
	if ((len = ft_strlen(argv[1])) < 5 \
			|| (ft_strncmp(argv[1] + len - 4, ".cub", 5)))
	{
		if (!(opts->err_string = malloc(len + 1)))
			return (200);
		ft_strlcpy(opts->err_string, argv[1], len + 1);
		return (102);
	}
	if (argc == 3)
	{
		if ((errcode = f_check_screenshot_arg(argv, opts)))
			return (errcode);
	}
	return (0);
}
