/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_n_background.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/06 17:09:32 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	f_fill_minimap(t_mlx *mlx)
{
	int			x;
	int			y;

	x = mlx->map.x * mlx->map.square_side + mlx->map.sq_x + mlx->map.edge_shift;
	y = mlx->map.y * mlx->map.square_side + mlx->map.sq_y + mlx->map.edge_shift;
	if (mlx->map.sq_x == mlx->map.square_side - 1 || \
			mlx->map.sq_y == mlx->map.square_side - 1 || \
			(mlx->map.x == 0 && mlx->map.sq_x == 0) || \
			(mlx->map.y == 0 && mlx->map.sq_y == 0))
		my_mlx_pixel_put(&mlx->img, x, y, 0x006B6B6B);
	else if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '1')
		my_mlx_pixel_put(&mlx->img, x, y, 0x001C596E);
	else
		my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
}

void		f_draw_minimap(t_mlx *mlx)
{
	while (mlx->map.y < mlx->map.map_height)
	{
		mlx->map.x = 0;
		while (mlx->map.x < mlx->map.map_width)
		{
			mlx->map.sq_y = 0;
			while (mlx->map.sq_y < mlx->map.square_side)
			{
				mlx->map.sq_x = 0;
				while (mlx->map.sq_x < mlx->map.square_side)
				{
					f_fill_minimap(mlx);
					mlx->map.sq_x++;
				}
				mlx->map.sq_y++;
			}
			mlx->map.x++;
		}
		mlx->map.y++;
	}
}

void	f_draw_player_minimap(t_mlx *mlx)
{
	int		x;
	int		y;

	x = mlx->player.pos_x - mlx->map.square_side / 6;
	while (x < mlx->player.pos_x + mlx->map.square_side / 6)
	{
		y = mlx->player.pos_y - mlx->map.square_side / 6;
		while (y < mlx->player.pos_y + mlx->map.square_side / 6)
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}
