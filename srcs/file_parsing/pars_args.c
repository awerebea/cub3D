/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 21:12:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/12 15:23:49 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int			f_check_args(int argc, char **argv, t_sdf *opts)
{
	int	len;

	if (argc < 2 || argc > 3)
		return (100);
	if ((len = ft_strlen(argv[1])) < 5 \
			|| ft_strncmp(argv[1] + len - 4, ".cub", 5) \
			|| !ft_strncmp(argv[1] + len - 5, "/.cub", 6))
		return (opts->err_str = ft_strdup(argv[1])) ? 102 : 200;
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 6)))
		{
			return (opts->err_str = ft_strdup(argv[2])) ? 103 : 200;
		}
		else
			opts->screenshot = 1;
	}
	return (0);
}
