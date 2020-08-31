/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 10:17:44 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		f_draw_minimap_frame(t_mlx *mlx)
{
	int			x;
	int			y;

	x = mlx->map.edge_shift;
	y = mlx->map.edge_shift;
	while (x < mlx->map.edge_shift + mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR)
		my_mlx_pixel_put(&mlx->img, x++, y, 0xFFFFFF);
	x = mlx->map.edge_shift;
	y = mlx->map.edge_shift + mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR;
	while (x < mlx->map.edge_shift + mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR)
		my_mlx_pixel_put(&mlx->img, x++, y, 0xFFFFFF);
	x = mlx->map.edge_shift;
	y = mlx->map.edge_shift;
	while (y < mlx->map.edge_shift + mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR)
		my_mlx_pixel_put(&mlx->img, x, y++, 0xFFFFFF);
	x = mlx->map.edge_shift + mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR;
	y = mlx->map.edge_shift;
	while (y < mlx->map.edge_shift + mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR)
		my_mlx_pixel_put(&mlx->img, x, y++, 0xFFFFFF);
}

static void		f_map_start_n_end_init(t_mlx *mlx)
{
	mlx->map.map_start_x = mlx->player.pos_x - mlx->x_win_size * \
			MINIMAP_MAX_WDTH_FACTOR / 2;
	mlx->map.map_end_x = mlx->player.pos_x + mlx->x_win_size * \
			MINIMAP_MAX_WDTH_FACTOR / 2;
	mlx->map.map_start_y = mlx->player.pos_y - mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / 2;
	mlx->map.map_end_y = mlx->player.pos_y + mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / 2;
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
	f_draw_minimap_frame(mlx);
}
