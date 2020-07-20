/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:12:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/20 15:09:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int				f_check_args(int argc, char **argv, t_sdf *opts)
{
	if (argc < 2 || argc > 3)
		return (1);
	if (ft_strlen(argv[1]) < 5 \
			|| (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5)))
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		return (2);
	}
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 6)))
			return (3);
		else
			opts->screenshot = 1;
	}
	return (0);
}
