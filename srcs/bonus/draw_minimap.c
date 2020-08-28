/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/28 23:42:59 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		f_map_start_n_end_x_init_assist(t_mlx *mlx)
{
	int			offset;

	offset = 0;
	mlx->map.map_start_x = mlx->player.pos_x - mlx->x_win_size * \
			MINIMAP_MAX_WDTH_FACTOR / 2;
	mlx->map.map_end_x = mlx->player.pos_x + mlx->x_win_size * \
			MINIMAP_MAX_WDTH_FACTOR / 2;
	if (mlx->map.map_start_x < 0)
	{
		offset -= mlx->map.map_start_x;
		mlx->map.map_start_x = 0;
		mlx->map.map_end_x += offset;
		if (mlx->map.map_end_x > mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR)
			mlx->map.map_end_x = mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR;
	}
	else if (mlx->map.map_end_x > mlx->map.map_width * mlx->map.sq_side)
	{
		offset = mlx->map.map_width * mlx->map.sq_side - mlx->map.map_end_x;
		mlx->map.map_end_x = mlx->map.map_width * mlx->map.sq_side;
		mlx->map.map_start_x += offset;
		if (mlx->map.map_start_x < 0)
			mlx->map.map_start_x = 0;
	}
}

static void		f_map_start_n_end_x_init(t_mlx *mlx)
{
	if (mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR / mlx->map.sq_side < \
			mlx->map.map_width)
		f_map_start_n_end_x_init_assist(mlx);
	else
	{
		mlx->map.map_start_x = 0;
		mlx->map.map_end_x = mlx->map.map_width * mlx->map.sq_side;
	}
}

static void		f_map_start_n_end_y_init_assist(t_mlx *mlx)
{
	int			offset;

	offset = 0;
	mlx->map.map_start_y = mlx->player.pos_y - mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / 2;
	mlx->map.map_end_y = mlx->player.pos_y + mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / 2;
	if (mlx->map.map_start_y < 0)
	{
		offset -= mlx->map.map_start_y;
		mlx->map.map_start_y = 0;
		mlx->map.map_end_y += offset;
		if (mlx->map.map_end_y > mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR)
			mlx->map.map_end_y = mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR;
	}
	else if (mlx->map.map_end_y > mlx->map.map_height * mlx->map.sq_side)
	{
		offset = mlx->map.map_height * mlx->map.sq_side - \
					mlx->map.map_end_y;
		mlx->map.map_end_y = mlx->map.map_height * mlx->map.sq_side;
		mlx->map.map_start_y += offset;
		if (mlx->map.map_start_y < 0)
			mlx->map.map_start_y = 0;
	}
}

static void		f_map_start_n_end_y_init(t_mlx *mlx)
{
	if (mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR / mlx->map.sq_side < \
			mlx->map.map_height)
		f_map_start_n_end_y_init_assist(mlx);
	else
	{
		mlx->map.map_start_y = 0;
		mlx->map.map_end_y = mlx->map.map_height * mlx->map.sq_side;
	}
}

void			f_draw_minimap(t_mlx *mlx)
{
	f_player_pos_init(mlx);
	f_map_start_n_end_x_init(mlx);
	f_map_start_n_end_y_init(mlx);
	mlx->player.pos_x -= mlx->map.map_start_x;
	mlx->player.pos_y -= mlx->map.map_start_y;
	mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
	mlx->map.y = mlx->map.map_start_y / mlx->map.sq_side;
	f_draw_first_row(mlx);
	f_draw_middle_row(mlx);
	f_draw_last_row(mlx);
}
