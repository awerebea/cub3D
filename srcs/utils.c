/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:36:56 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/06 15:57:23 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void			f_skip_spaces(char *line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
}

int				f_cub3d_atoi(char *line, int *i)
{
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	f_skip_spaces(line, i);
	if (line[*i] == '-')
		sign = -1;
	if (line[*i] == '-' || line[*i] == '+')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		if ((result * 10) < result)
			return (sign < 0 ? 0 : -1);
		result = result * 10 + line[*i] - '0';
		(*i)++;
	}
	return ((int)result * (int)sign);
}

void		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char		*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}
