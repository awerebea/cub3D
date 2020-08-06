/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:08:08 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/06 17:09:02 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		f_draw_background(t_mlx *mlx)
{
	int			x;
	int			y;

	x = 0;
	while (x < mlx->x_win_size)
	{
		y = 0;
		while (y < (mlx->y_win_size / 2))
		{
			my_mlx_pixel_put(&mlx->img, x, y, mlx->opts->ceiling_color);
			y++;
		}
		while (y < mlx->y_win_size)
		{
			my_mlx_pixel_put(&mlx->img, x, y, mlx->opts->floor_color);
			y++;
		}
		x++;
	}
}
