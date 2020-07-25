/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array_preparing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:24:07 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/25 12:58:58 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"

int		f_map_array_preparing(t_sdf *opts)
{
	int		i;
	int		j;
	int		line_len;
	int		max_len;
	char	*tmp_ptr;

	if (!(opts->map_array = ft_split(opts->map_line, '\n')))
		return (200);
	ft_printf("Splitted line:\n");
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
	i = 0;
	max_len = 0;
	while (opts->map_array[i])
	{
		j = 0;
		line_len = ft_strlen(opts->map_array[i]);
		while (opts->map_array[i][line_len--] == ' ')
			j++;
		max_len = (max_len < (line_len - j)) ? line_len - j : max_len;
		i++;
	}
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
	i = 0;
	while (opts->map_array[i])
	{
		if ((line_len = ft_strlen(opts->map_array[i])) < max_len)
		{
			while (line_len++ < max_len)
			{
				if (!(tmp_ptr = ft_strjoin(opts->map_array[i], " ")))
					return (200);
				free(opts->map_array[i]);
				opts->map_array[i] = tmp_ptr;
			}
		}
		i++;
	}
	i = 0;
	while (opts->map_array[i])
	{
		ft_printf("|");
		ft_printf(opts->map_array[i++]);
		ft_printf("|\n");
	}
	return (0);
}
