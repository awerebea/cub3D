/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:36:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/12 21:10:12 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "libft.h"

static void	f_check_wall_hit_n_wall_dist_calculation(t_mlx *mlx)
{
	mlx->game.hit = 0;
	while (!mlx->game.hit)
	{
		if (mlx->game.side_dist_x < mlx->game.side_dist_y)
		{
			mlx->game.side_dist_x += mlx->game.delta_dist_x;
			mlx->game.map_x += mlx->game.step_x;
			mlx->game.wall_side = (mlx->game.ray_dir_x < 0) ? 2 : 3;
		}
		else
		{
			mlx->game.side_dist_y += mlx->game.delta_dist_y;
			mlx->game.map_y += mlx->game.step_y;
			mlx->game.wall_side = (mlx->game.ray_dir_y < 0) ? 0 : 1;
		}
		if (!ft_strchr("02NSWE", \
					mlx->opts->map_array[mlx->game.map_y][mlx->game.map_x]))
			mlx->game.hit = 1;
	}
	if (mlx->game.wall_side > 1)
		mlx->game.wall_dist = (mlx->game.map_x - mlx->game.player_x + \
				(1 - mlx->game.step_x) / 2) / mlx->game.ray_dir_x;
	else
		mlx->game.wall_dist = (mlx->game.map_y - mlx->game.player_y + \
				(1 - mlx->game.step_y) / 2) / mlx->game.ray_dir_y;
}

static void	f_step_n_side_dist_calculation(t_mlx *mlx)
{
	if (mlx->game.ray_dir_x < 0)
	{
		mlx->game.step_x = -1;
		mlx->game.side_dist_x = (mlx->game.player_x - mlx->game.map_x) * \
			mlx->game.delta_dist_x;
	}
	else
	{
		mlx->game.step_x = 1;
		mlx->game.side_dist_x = (1.0 + mlx->game.map_x - mlx->game.player_x) * \
			mlx->game.delta_dist_x;
	}
	if (mlx->game.ray_dir_y < 0)
	{
		mlx->game.step_y = -1;
		mlx->game.side_dist_y = (mlx->game.player_y - mlx->game.map_y) * \
			mlx->game.delta_dist_y;
	}
	else
	{
		mlx->game.step_y = 1;
		mlx->game.side_dist_y = (1.0 + mlx->game.map_y - mlx->game.player_y) * \
			mlx->game.delta_dist_y;
	}
}

static void	f_delta_dist_calculation(t_mlx *mlx)
{
	if (!mlx->game.ray_dir_y)
		mlx->game.delta_dist_x = 0;
	else
		mlx->game.delta_dist_x = (!mlx->game.ray_dir_x) ? 1 : \
									fabs(1 / mlx->game.ray_dir_x);
	if (!mlx->game.ray_dir_x)
		mlx->game.delta_dist_y = 0;
	else
		mlx->game.delta_dist_y = (!mlx->game.ray_dir_y) ? 1 : \
									fabs(1 / mlx->game.ray_dir_y);
}

void		f_raycasting(t_mlx *mlx)
{
	int			x;

	x = 0;
	while (x < mlx->x_win_size)
	{
		mlx->game.camera_x = 2 * x / (float)mlx->x_win_size - 1;
		mlx->game.ray_dir_x = mlx->game.dir_x + mlx->game.plane_x * \
								mlx->game.camera_x;
		mlx->game.ray_dir_y = mlx->game.dir_y + mlx->game.plane_y * \
								mlx->game.camera_x;
		mlx->game.map_x = (int)mlx->game.player_x;
		mlx->game.map_y = (int)mlx->game.player_y;
		f_delta_dist_calculation(mlx);
		f_step_n_side_dist_calculation(mlx);
		f_check_wall_hit_n_wall_dist_calculation(mlx);
		mlx->game.wall_dist_arr[x] = mlx->game.wall_dist;
		f_draw_vert_line(mlx, x++);
	}
}
