/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:36:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/09/01 00:26:36 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>

static void	f_check_wall_hit_n_wall_dist_calculation(t_mlx *mlx, \
														t_wall_vars *w_vars)
{
	w_vars->hit = 0;
	while (!w_vars->hit)
	{
		if (w_vars->side_dist_x < w_vars->side_dist_y)
		{
			w_vars->side_dist_x += w_vars->delta_dist_x;
			w_vars->map_x += w_vars->step_x;
			w_vars->wall_side = (w_vars->ray_dir_x < 0) ? 2 : 3;
		}
		else
		{
			w_vars->side_dist_y += w_vars->delta_dist_y;
			w_vars->map_y += w_vars->step_y;
			w_vars->wall_side = (w_vars->ray_dir_y < 0) ? 0 : 1;
		}
		if (!ft_strchr("02NSWE", \
					mlx->opts->map_array[w_vars->map_y][w_vars->map_x]))
			w_vars->hit = 1;
	}
	if (w_vars->wall_side > 1)
		w_vars->wall_dist = (w_vars->map_x - mlx->game.player_x + \
				(1 - w_vars->step_x) / 2) / w_vars->ray_dir_x;
	else
		w_vars->wall_dist = (w_vars->map_y - mlx->game.player_y + \
				(1 - w_vars->step_y) / 2) / w_vars->ray_dir_y;
}

static void	f_step_n_side_dist_calculation(t_mlx *mlx, t_wall_vars *w_vars)
{
	if (w_vars->ray_dir_x < 0)
	{
		w_vars->step_x = -1;
		w_vars->side_dist_x = (mlx->game.player_x - w_vars->map_x) * \
			w_vars->delta_dist_x;
	}
	else
	{
		w_vars->step_x = 1;
		w_vars->side_dist_x = (1.0 + w_vars->map_x - mlx->game.player_x) * \
			w_vars->delta_dist_x;
	}
	if (w_vars->ray_dir_y < 0)
	{
		w_vars->step_y = -1;
		w_vars->side_dist_y = (mlx->game.player_y - w_vars->map_y) * \
			w_vars->delta_dist_y;
	}
	else
	{
		w_vars->step_y = 1;
		w_vars->side_dist_y = (1.0 + w_vars->map_y - mlx->game.player_y) * \
			w_vars->delta_dist_y;
	}
}

static void	f_delta_dist_calculation(t_wall_vars *w_vars)
{
	if (!w_vars->ray_dir_y)
		w_vars->delta_dist_x = 0;
	else
		w_vars->delta_dist_x = (!w_vars->ray_dir_x) ? 1 : \
									fabs(1 / w_vars->ray_dir_x);
	if (!w_vars->ray_dir_x)
		w_vars->delta_dist_y = 0;
	else
		w_vars->delta_dist_y = (!w_vars->ray_dir_y) ? 1 : \
									fabs(1 / w_vars->ray_dir_y);
}

void		f_raycasting(t_mlx *mlx)
{
	int			x;
	t_wall_vars w_vars;

	w_vars.tex_mirror = 0;
	x = 0;
	while (x < mlx->x_win_size)
	{
		w_vars.camera_x = 2 * x / (float)mlx->x_win_size - 1;
		w_vars.ray_dir_x = mlx->game.dir_x + mlx->game.plane_x * \
								w_vars.camera_x;
		w_vars.ray_dir_y = mlx->game.dir_y + mlx->game.plane_y * \
								w_vars.camera_x;
		w_vars.map_x = (int)mlx->game.player_x;
		w_vars.map_y = (int)mlx->game.player_y;
		f_delta_dist_calculation(&w_vars);
		f_step_n_side_dist_calculation(mlx, &w_vars);
		f_check_wall_hit_n_wall_dist_calculation(mlx, &w_vars);
		mlx->game.wall_dist_arr[x] = w_vars.wall_dist;
		f_draw_vert_line(mlx, &w_vars, x++);
	}
	f_sprites_handling(mlx);
}
