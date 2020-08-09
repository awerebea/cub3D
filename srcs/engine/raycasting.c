/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:36:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 18:54:58 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "libft.h"
#include "ft_printf.h"

void		f_fps_n_move_n_rotate_speed_calculation(t_mlx *mlx)
{
	mlx->game.time_prev = mlx->game.time_curr;
	mlx->game.time_curr = clock();
	mlx->game.frame_time = (mlx->game.time_curr - mlx->game.time_prev) / 1000.0;
	mlx->game.move_speed = mlx->game.frame_time * 0.5;
	mlx->game.rotate_speed = mlx->game.frame_time * 0.2;
	
	ft_printf("move speed: %f\nrotate speed:%f\n", mlx->game.move_speed, \
			mlx->game.rotate_speed);
}

void		f_draw_vert_line(t_mlx *mlx, int x)
{
	int			color;
	int			y;

	y = mlx->game.line_start;
	while (y <= mlx->game.line_end)
	{
		if (mlx->game.wall_side == 0)
			color = 0x224A7B;
		else if (mlx->game.wall_side == 1)
			color = 0xFF6524;
		else if (mlx->game.wall_side == 2)
			color = 0xA7F192;
		else
			color = 0x888945;
		my_mlx_pixel_put(&mlx->img, x, y, color);
		y++;
	}
}

void		f_vert_line_calculation(t_mlx *mlx)
{
	mlx->game.line_height = (int)(mlx->y_win_size / mlx->game.wall_dist);
	mlx->game.line_start = mlx->y_win_size / 2 - mlx->game.line_height / 2;
	if (mlx->game.line_start < 0)
		mlx->game.line_start = 0;
	mlx->game.line_end = mlx->y_win_size / 2 + mlx->game.line_height / 2;
	if (mlx->game.line_end >= mlx->y_win_size)
		mlx->game.line_end = mlx->y_win_size - 1;
}

void		f_check_wall_hit_n_wall_dist_calculation(t_mlx *mlx)
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
		if (mlx->opts->map_array[mlx->game.map_y][mlx->game.map_x] != '0')
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

void		f_deltas_calculation(t_mlx *mlx)
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
		f_deltas_calculation(mlx);
		f_step_n_side_dist_calculation(mlx);
		f_check_wall_hit_n_wall_dist_calculation(mlx);
		f_vert_line_calculation(mlx);
		f_draw_vert_line(mlx, x);
		x++;
	}
	f_fps_n_move_n_rotate_speed_calculation(mlx);
}
