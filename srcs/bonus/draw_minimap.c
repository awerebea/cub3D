/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 10:52:00 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		f_map_start_n_end_init(t_mlx *mlx)
{
	mlx->map.map_start_x = mlx->player.pos_x - mlx->map.map_radius;
	mlx->map.map_end_x = mlx->player.pos_x + mlx->map.map_radius;
	mlx->map.map_start_y = mlx->player.pos_y - mlx->map.map_radius;
	mlx->map.map_end_y = mlx->player.pos_y + mlx->map.map_radius;
}

void			f_draw_minimap(t_mlx *mlx)
{
	f_player_pos_init(mlx);
	f_map_start_n_end_init(mlx);
	mlx->player.pos_x -= mlx->map.map_start_x;
	mlx->player.pos_y -= mlx->map.map_start_y;
	mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
	mlx->map.y = mlx->map.map_start_y / mlx->map.sq_side;
	f_draw_first_row(mlx);
	f_draw_middle_row(mlx);
	f_draw_last_row(mlx);
}
