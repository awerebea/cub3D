/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:40:04 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/20 17:13:07 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

int				f_pars_no_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				i_bckp;
	int				fd;

	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	i_bckp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!(i - i_bckp))
		return (9);
	if (!(opts->north_texture_path = malloc(i - i_bckp + 1)))
		return (8);
	ft_strlcpy(opts->north_texture_path, line + i_bckp, i - i_bckp + 1);
	(fd = open(opts->north_texture_path, O_RDONLY)) < 0 ? \
						ft_printf("%s\n", opts->north_texture_path) : 0;
	fd < 0 ? f_print_err(9) : 0;
	if (fd < 0)
		return (fd);
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 10 : errcode;
}
