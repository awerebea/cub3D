/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_rows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 10:00:34 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			f_draw_first_row(t_mlx *mlx)
{
	while (mlx->map.x <= mlx->map.map_end_x / mlx->map.sq_side)
	{
		mlx->map.sq_y = mlx->map.map_start_y % mlx->map.sq_side;
		while (mlx->map.sq_y < mlx->map.sq_side)
		{
			if (mlx->map.x == mlx->map.map_start_x / mlx->map.sq_side)
				f_draw_first_square(mlx);
			else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side)
				f_draw_last_square(mlx);
			else
				f_draw_middle_square(mlx);
			mlx->map.sq_y++;
		}
		mlx->map.x++;
	}
	mlx->map.y++;
}

void			f_draw_middle_row(t_mlx *mlx)
{
	while (mlx->map.y < mlx->map.map_end_y / mlx->map.sq_side)
	{
		mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
		while (mlx->map.x <= mlx->map.map_end_x / mlx->map.sq_side)
		{
			mlx->map.sq_y = 0;
			while (mlx->map.sq_y < mlx->map.sq_side)
			{
				if (mlx->map.x == mlx->map.map_start_x / mlx->map.sq_side)
					f_draw_first_square(mlx);
				else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side)
					f_draw_last_square(mlx);
				else
					f_draw_middle_square(mlx);
				mlx->map.sq_y++;
			}
			mlx->map.x++;
		}
		mlx->map.y++;
	}
	mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
}

void			f_draw_last_row(t_mlx *mlx)
{
	while (mlx->map.x <= mlx->map.map_end_x / mlx->map.sq_side)
	{
		mlx->map.sq_y = 0;
		while (mlx->map.sq_y < mlx->map.map_end_y % mlx->map.sq_side)
		{
			if (mlx->map.x == mlx->map.map_start_x / mlx->map.sq_side)
				f_draw_first_square(mlx);
			else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side)
				f_draw_last_square(mlx);
			else
				f_draw_middle_square(mlx);
			mlx->map.sq_y++;
		}
		mlx->map.x++;
	}
}
