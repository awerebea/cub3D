/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array_preparing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:24:07 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/27 17:17:48 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	f_del_prior_spaces(t_sdf *opts)
{
	int		i;
	char	*tmp_ptr;

	i = 0;
	if (opts->prior_spaces_mapline)
	{
		while (opts->map_array[i])
		{
			if (!(tmp_ptr = ft_strdup(opts->map_array[i] + \
							opts->prior_spaces_mapline)))
				return (200);
			free(opts->map_array[i]);
			opts->map_array[i] = tmp_ptr;
			i++;
		}
		opts->spawn_point_x -= opts->prior_spaces_mapline;
	}
	return (0);
}

static int	f_add_trail_spaces(t_sdf *opts)
{
	int		i;
	char	*tmp_ptr;
	int		line_len;

	i = 0;
	while (opts->map_array[i])
	{
		if ((line_len = ft_strlen(opts->map_array[i])) < opts->max_mapline_len)
		{
			if (!(tmp_ptr = malloc(opts->max_mapline_len + 1)))
				return (200);
			ft_strncpy(tmp_ptr, opts->map_array[i], line_len);
			ft_memset(tmp_ptr + line_len, ' ', \
					opts->max_mapline_len - line_len);
			tmp_ptr[opts->max_mapline_len] = '\0';
			free(opts->map_array[i]);
			opts->map_array[i] = tmp_ptr;
		}
		i++;
	}
	return (0);
}

static int	f_del_superfluous_trail_spaces(t_sdf *opts)
{
	int		i;
	char	*tmp_ptr;
	int		line_len;

	i = 0;
	while (opts->map_array[i])
	{
		if ((line_len = ft_strlen(opts->map_array[i])) > opts->max_mapline_len)
		{
			if (!(tmp_ptr = malloc(opts->max_mapline_len + 1)))
				return (200);
			ft_strlcpy(tmp_ptr, opts->map_array[i], opts->max_mapline_len + 1);
			free(opts->map_array[i]);
			opts->map_array[i] = tmp_ptr;
		}
		i++;
	}
	return (0);
}

static int	f_del_trail_spaces(t_sdf *opts)
{
	int		i;
	int		line_len;

	i = 0;
	while (opts->map_array[i])
	{
		line_len = ft_strlen(opts->map_array[i]);
		while (line_len > 0 && opts->map_array[i][line_len - 1] == ' ')
			line_len--;
		opts->max_mapline_len = (opts->max_mapline_len < line_len) ? \
			line_len : opts->max_mapline_len;
		i++;
	}
	if ((opts->errcode = f_del_superfluous_trail_spaces(opts)))
		return (opts->errcode);
	return ((opts->errcode = f_add_trail_spaces(opts)) ? \
			opts->errcode : 0);
}

int			f_map_array_preparing(t_sdf *opts)
{
	if (!(opts->map_array = ft_split(opts->map_line, '\n')))
		return (200);
	free(opts->map_line);
	opts->map_line = NULL;
	if ((opts->errcode = f_del_prior_spaces(opts)))
		return (opts->errcode);
	if ((opts->errcode = f_del_trail_spaces(opts)))
		return (opts->errcode);
	return (opts->errcode);
}
