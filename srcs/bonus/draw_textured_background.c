/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_background.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 21:02:57 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/16 01:53:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_tex_background.h"
#include <math.h>

void		draw_textured_background(t_mlx *mlx)
{
	int			x;
	int			y;
	int			color;
	float		shade;
	t_fc_vars	fc_vars;

	y = mlx->y_win_size / 2 + 1;
	while (y < mlx->y_win_size)
	{
		fc_vars.ray_dir_x_0 = mlx->game.dir_x - mlx->game.plane_x;
		fc_vars.ray_dir_y_0 = mlx->game.dir_y - mlx->game.plane_y;
		fc_vars.ray_dir_x_1 = mlx->game.dir_x + mlx->game.plane_x;
		fc_vars.ray_dir_y_1 = mlx->game.dir_y + mlx->game.plane_y;
		fc_vars.p = y - mlx->y_win_size / 2;
		fc_vars.row_distance = 0.5 * mlx->y_win_size / fc_vars.p;
		fc_vars.floor_step_x = fc_vars.row_distance * (fc_vars.ray_dir_x_1 - \
								fc_vars.ray_dir_x_0) / mlx->x_win_size;
		fc_vars.floor_step_y = fc_vars.row_distance * (fc_vars.ray_dir_y_1 - \
								fc_vars.ray_dir_y_0) / mlx->x_win_size;
		fc_vars.floor_x = mlx->game.player_x + fc_vars.row_distance * \
							fc_vars.ray_dir_x_0;
		fc_vars.floor_y = mlx->game.player_y + fc_vars.row_distance * \
							fc_vars.ray_dir_y_0;
		shade = 1 / (1 + 0.005 * ((mlx->y_win_size - y) / 20) + 0.006 * \
		pow(((mlx->y_win_size - y) / 20), 2));
		x = 0;
		while (x < mlx->x_win_size)
		{
			fc_vars.cell_x = (int)(fc_vars.floor_x);
			fc_vars.cell_y = (int)(fc_vars.floor_y);
			fc_vars.tex_x = (int)(mlx->fl_tex.width * (fc_vars.floor_x - \
							fc_vars.cell_x)) & \
								(mlx->fl_tex.width - 1);
			fc_vars.tex_y = (int)(mlx->fl_tex.height * (fc_vars.floor_y - \
							fc_vars.cell_y)) & \
								(mlx->fl_tex.height - 1);
			fc_vars.floor_x += fc_vars.floor_step_x;
			fc_vars.floor_y += fc_vars.floor_step_y;
			color = *(int*)(mlx->fl_tex.addr + ((fc_vars.tex_x + \
					(fc_vars.tex_y * mlx->fl_tex.width)) * \
					(mlx->fl_tex.bits_per_pix / 8)));
			my_mlx_pixel_put(&mlx->img, x, y, f_add_shade(color, shade));
			color = *(int*)(mlx->ce_tex.addr + ((fc_vars.tex_x + \
					(fc_vars.tex_y * mlx->ce_tex.width)) * \
					(mlx->ce_tex.bits_per_pix / 8)));
			my_mlx_pixel_put(&mlx->img, x, mlx->y_win_size - y - 1, \
					f_add_shade(color, shade));
			x++;
		}
		y++;
	}
}
