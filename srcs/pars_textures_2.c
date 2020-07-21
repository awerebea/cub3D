/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:05:01 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/21 15:14:22 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

int			f_pars_sprite_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				i_bckp;
	int				fd;

	if (opts->sprite_texture_path)
		return (opts->err_string = ft_strdup("S")) ? 301 : 200;
	errcode = 0;
	i += 3;
	f_skip_spaces(line, &i);
	i_bckp = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!(opts->sprite_texture_path = malloc(i - i_bckp + 1)))
		return (200);
	ft_strlcpy(opts->sprite_texture_path, line + i_bckp, i - i_bckp + 1);
	if ((fd = open(opts->sprite_texture_path, O_RDONLY)) < 0)
	{
		if (!(opts->err_string = ft_strdup(opts->sprite_texture_path)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	/* errcode = f_texture_check(opts, fd); */
	return (close(fd) < 0) ? 320 : errcode;
}
