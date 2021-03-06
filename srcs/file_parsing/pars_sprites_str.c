/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sprites_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:05:01 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 11:49:21 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int			f_pars_sprite_texture(char *line, int i, t_sdf *opts)
{
	int				errcode;
	int				fd;

	if (opts->sp_tex)
		return (opts->err_str = ft_strdup("S")) ? 301 : 200;
	errcode = 0;
	i += 2;
	f_skip_spaces(line, &i);
	if (!(opts->sp_tex = ft_strdup(line + i)))
		return (200);
	if ((fd = open(opts->sp_tex, O_RDONLY)) < 0)
	{
		if (!(opts->err_str = ft_strdup(opts->sp_tex)))
			return (200);
		f_print_err(320, opts);
		return (fd);
	}
	return (close(fd) < 0) ? 320 : errcode;
}
