/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array_preparing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:24:07 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/25 14:45:06 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"

static int	f_del_prior_spaces(t_sdf *opts)
{
	int		i;
	char	*tmp_ptr;

	i = 0;
	while (opts->map_array[i])
	{
		if (opts->prior_spaces_mapline)
		{
			if (!(tmp_ptr = ft_strdup(opts->map_array[i] + \
							opts->prior_spaces_mapline)))
				return (200);
			free(opts->map_array[i]);
			opts->map_array[i++] = tmp_ptr;
		}
	}
	return (0);
}

static int	f_add_trail_spaces(t_sdf *opts, int max_len)
{
	int		i;
	char	*tmp_ptr;
	int		line_len;

	i = 0;
	while (opts->map_array[i])
	{
		if ((line_len = ft_strlen(opts->map_array[i])) < max_len)
		{
			if (!(tmp_ptr = malloc(max_len + 1)))
				return (200);
			ft_strncpy(tmp_ptr, opts->map_array[i], line_len);
			ft_memset(tmp_ptr + line_len, ' ', max_len - line_len);
			tmp_ptr[max_len] = '\0';
			free(opts->map_array[i]);
			opts->map_array[i] = tmp_ptr;
		}
		i++;
	}
	return (0);
}

static int	f_del_superfluous_trail_spaces(t_sdf *opts, int max_len)
{
	int		i;
	char	*tmp_ptr;
	int		line_len;

	i = 0;
	while (opts->map_array[i])
	{
		if ((line_len = ft_strlen(opts->map_array[i])) > max_len)
		{
			if (!(tmp_ptr = malloc(max_len + 1)))
				return (200);
			ft_strlcpy(tmp_ptr, opts->map_array[i], max_len + 1);
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
	int		max_len;
	int		line_len;

	i = 0;
	max_len = 0;
	while (opts->map_array[i])
	{
		line_len = ft_strlen(opts->map_array[i]);
		while (line_len > 0 && opts->map_array[i][line_len - 1] == ' ')
			line_len--;
		max_len = (max_len < line_len) ? line_len : max_len;
		i++;
	}
	if ((opts->errcode = f_del_superfluous_trail_spaces(opts, max_len)))
		return (opts->errcode);
	return ((opts->errcode = f_add_trail_spaces(opts, max_len)) ? \
			opts->errcode : 0);
}

int			f_map_array_preparing(t_sdf *opts)
{
	if (!(opts->map_array = ft_split(opts->map_line, '\n')))
		return (200);
	if ((opts->errcode = f_del_prior_spaces(opts)))
		return (opts->errcode);
	if ((opts->errcode = f_del_trail_spaces(opts)))
		return (opts->errcode);
	return (opts->errcode);
}
