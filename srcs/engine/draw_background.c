/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:08:08 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 14:55:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#ifdef BONUS

static void	f_floor_vars_calculation(t_mlx *mlx, t_fc_vars *fc_vars, int y)
{
	fc_vars->ray_dir_x_0 = mlx->game.dir_x - mlx->game.plane_x;
	fc_vars->ray_dir_y_0 = mlx->game.dir_y - mlx->game.plane_y;
	fc_vars->ray_dir_x_1 = mlx->game.dir_x + mlx->game.plane_x;
	fc_vars->ray_dir_y_1 = mlx->game.dir_y + mlx->game.plane_y;
	fc_vars->p = y - fc_vars->y_horizon - 1;
	fc_vars->floor_row_distance = (mlx->keys.shift_l) ? \
									0.5 * mlx->y_win_size / fc_vars->p : \
									0.5 * mlx->y_win_size / fc_vars->p;
	fc_vars->floor_step_x = fc_vars->floor_row_distance * \
				(fc_vars->ray_dir_x_1 - fc_vars->ray_dir_x_0) / mlx->x_win_size;
	fc_vars->floor_step_y = fc_vars->floor_row_distance * \
				(fc_vars->ray_dir_y_1 - fc_vars->ray_dir_y_0) / mlx->x_win_size;
	fc_vars->floor_x = mlx->game.player_x + fc_vars->floor_row_distance * \
						fc_vars->ray_dir_x_0;
	fc_vars->floor_y = mlx->game.player_y + fc_vars->floor_row_distance * \
						fc_vars->ray_dir_y_0;
}

static void	f_ceiling_vars_calculation(t_mlx *mlx, t_fc_vars *fc_vars, int y)
{
	fc_vars->ray_dir_x_0 = mlx->game.dir_x - mlx->game.plane_x;
	fc_vars->ray_dir_y_0 = mlx->game.dir_y - mlx->game.plane_y;
	fc_vars->ray_dir_x_1 = mlx->game.dir_x + mlx->game.plane_x;
	fc_vars->ray_dir_y_1 = mlx->game.dir_y + mlx->game.plane_y;
	fc_vars->p = fc_vars->y_horizon - 1 - y;
	fc_vars->ceil_row_distance = (mlx->keys.shift_l) ? \
									0.5 * mlx->y_win_size / fc_vars->p : \
									0.5 * mlx->y_win_size / fc_vars->p;
	fc_vars->ceil_step_x = fc_vars->ceil_row_distance * \
				(fc_vars->ray_dir_x_1 - fc_vars->ray_dir_x_0) / mlx->x_win_size;
	fc_vars->ceil_step_y = fc_vars->ceil_row_distance * \
				(fc_vars->ray_dir_y_1 - fc_vars->ray_dir_y_0) / mlx->x_win_size;
	fc_vars->ceil_x = mlx->game.player_x + fc_vars->ceil_row_distance * \
						fc_vars->ray_dir_x_0;
	fc_vars->ceil_y = mlx->game.player_y + fc_vars->ceil_row_distance * \
						fc_vars->ray_dir_y_0;
}

static void	f_draw_line_floor(t_mlx *mlx, t_fc_vars *fc_vars, int y, \
																	float shade)
{
	int			x;
	int			color;

	x = 0;
	while (x < mlx->x_win_size)
	{
		fc_vars->cell_x = (int)(fc_vars->floor_x);
		fc_vars->cell_y = (int)(fc_vars->floor_y);
		fc_vars->tex_x = (int)(mlx->fl_tex.width * (fc_vars->floor_x - \
						fc_vars->cell_x)) & (mlx->fl_tex.width - 1);
		fc_vars->tex_y = (int)(mlx->fl_tex.height * (fc_vars->floor_y - \
						fc_vars->cell_y)) & (mlx->fl_tex.height - 1);
		fc_vars->floor_x += fc_vars->floor_step_x;
		fc_vars->floor_y += fc_vars->floor_step_y;
		color = *(int*)(mlx->fl_tex.addr + ((fc_vars->tex_x + (fc_vars->tex_y \
				* mlx->fl_tex.width)) * (mlx->fl_tex.bits_per_pix / 8)));
		my_mlx_pixel_put(&mlx->img, x, y, f_add_shade(color, shade));
		x++;
	}
	x = 0;
}

static void	f_draw_line_ceiling(t_mlx *mlx, t_fc_vars *fc_vars, int y, \
																	float shade)
{
	int			x;
	int			color;

	x = 0;
	while (x < mlx->x_win_size)
	{
		fc_vars->cell_x = (int)(fc_vars->ceil_x);
		fc_vars->cell_y = (int)(fc_vars->ceil_y);
		fc_vars->tex_x = (int)(mlx->ce_tex.width * (fc_vars->ceil_x - \
						fc_vars->cell_x)) & (mlx->ce_tex.width - 1);
		fc_vars->tex_y = (int)(mlx->ce_tex.height * (fc_vars->ceil_y - \
						fc_vars->cell_y)) & (mlx->ce_tex.height - 1);
		fc_vars->ceil_x += fc_vars->ceil_step_x;
		fc_vars->ceil_y += fc_vars->ceil_step_y;
		color = *(int*)(mlx->ce_tex.addr + ((fc_vars->tex_x + (fc_vars->tex_y \
				* mlx->ce_tex.width)) * (mlx->ce_tex.bits_per_pix / 8)));
		my_mlx_pixel_put(&mlx->img, x, y, f_add_shade(color, shade));
		x++;
	}
	x = 0;
}

void		f_draw_textured_background(t_mlx *mlx)
{
	int			y;
	float		shade;
	float		relative_dist;
	t_fc_vars	fc_vars;

	fc_vars.y_horizon = (mlx->keys.shift_l) ? \
					mlx->y_win_size / 3 + 1 : mlx->y_win_size / 2 + 1;
	y = fc_vars.y_horizon;
	while (y < mlx->y_win_size)
	{
		relative_dist = (float)(mlx->y_win_size - y) / mlx->y_win_size;
		f_floor_vars_calculation(mlx, &fc_vars, y);
		shade = 1.0 / (1.0 + 0.75 * relative_dist + 6.0 * \
				pow(relative_dist, 2));
		f_draw_line_floor(mlx, &fc_vars, y, 1.0);
		y++;
	}
	y = 0;
	while (y < fc_vars.y_horizon)
	{
		relative_dist = (float)(mlx->y_win_size - y) / mlx->y_win_size;
		f_ceiling_vars_calculation(mlx, &fc_vars, y);
		shade = 1.0 / (1.0 + 0.75 * relative_dist + 6.0 * \
				pow(relative_dist, 2));
		f_draw_line_ceiling(mlx, &fc_vars, y, 1.0);
		y++;
	}
}

#else

void		f_draw_background(t_mlx *mlx)
{
	int			x;
	int			y;

	x = 0;
	while (x < mlx->x_win_size)
	{
		y = 0;
		while (y < (mlx->y_win_size / 2))
		{
			my_mlx_pixel_put(&mlx->img, x, y, mlx->opts->ceiling_color);
			y++;
		}
		while (y < mlx->y_win_size)
		{
			my_mlx_pixel_put(&mlx->img, x, y, mlx->opts->floor_color);
			y++;
		}
		x++;
	}
}

#endif
