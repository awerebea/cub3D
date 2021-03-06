/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:02:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 10:54:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	f_player_pos_init(t_mlx *mlx)
{
	mlx->player.fov = FOV_ANGLE * M_PI / 180;
	mlx->player.pos_x = (int)(mlx->game.player_x * mlx->map.sq_side);
	mlx->player.pos_y = (int)(mlx->game.player_y * mlx->map.sq_side);
	if (!mlx->game.dir_x)
		mlx->player.view_angle = (mlx->game.dir_y > 0) ? \
									M_PI / 2 : M_PI * 3 / 2;
	else if (!mlx->game.dir_y)
		mlx->player.view_angle = (mlx->game.dir_x > 0) ? 0 : M_PI;
	else if (mlx->game.dir_x > 0)
		mlx->player.view_angle = (mlx->game.dir_y > 0) ? \
							atan(mlx->game.dir_y / mlx->game.dir_x) : \
							atan(mlx->game.dir_y / mlx->game.dir_x) + M_PI * 2;
	else if (mlx->game.dir_x < 0)
		mlx->player.view_angle = atan(mlx->game.dir_y / mlx->game.dir_x) + M_PI;
}

void	f_minimap_init(t_mlx *mlx)
{
	mlx->map.edge_shift = mlx->x_win_size / 150;
	mlx->map.map_width = mlx->opts->max_mapline_len;
	mlx->map.map_height = mlx->opts->map_row_index + 1;
	mlx->map.sq_side = MINIMAP_SQUARE_SIDE;
	if (mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR < \
			mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR)
		mlx->map.map_radius = mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR / 2;
	else
		mlx->map.map_radius = mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR / 2;
}
