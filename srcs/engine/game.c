/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:22:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/06 15:18:00 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* #include "mlx.h" */
#include <math.h>

void		f_player_init(t_mlx *mlx)
{
	mlx->player.pos_x = mlx->map.edge_shift + mlx->opts->spawn_point_x * mlx->map.square_side + \
				mlx->map.square_side / 2;
	mlx->player.pos_y = mlx->map.edge_shift + mlx->opts->spawn_point_y * mlx->map.square_side + \
				mlx->map.square_side / 2;
	if (mlx->opts->spawn_orientation == 'N')
		mlx->player.view_angle = M_PI * 3 / 2;
	else if (mlx->opts->spawn_orientation == 'S')
		mlx->player.view_angle = M_PI / 2;
	else if (mlx->opts->spawn_orientation == 'W')
		mlx->player.view_angle = M_PI;
	else if (mlx->opts->spawn_orientation == 'E')
		mlx->player.view_angle = 0.0;
}

void		f_game(t_mlx *mlx)
{
	int			x;
	int			y;

	f_player_init(mlx);
	x = mlx->player.pos_x - mlx->map.square_side / 6;
	while (x < mlx->player.pos_x + mlx->map.square_side / 6)
	{
		y = mlx->player.pos_y - mlx->map.square_side / 6;
		while (y < mlx->player.pos_y + mlx->map.square_side / 6)
		{
			my_mlx_pixel_put(mlx->img, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}
