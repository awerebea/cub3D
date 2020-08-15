/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 16:29:32 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/15 19:14:51 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	f_sprite_vars_calc_start(t_mlx *mlx, t_sp *sp)
{
	mlx->game.sp_dist_x = sp->x - mlx->game.player_x;
	mlx->game.sp_dist_y = sp->y - mlx->game.player_y;
	mlx->game.inv_factor = 1.0 / (mlx->game.plane_x * mlx->game.dir_y - \
			mlx->game.plane_y * mlx->game.dir_x);
	mlx->game.transform_x = mlx->game.inv_factor * (mlx->game.dir_y * \
			mlx->game.sp_dist_x - mlx->game.dir_x * mlx->game.sp_dist_y);
	mlx->game.transform_y = mlx->game.inv_factor * (-mlx->game.plane_y * \
			mlx->game.sp_dist_x + mlx->game.plane_x * mlx->game.sp_dist_y);
	mlx->game.sp_scr_x = (int)((mlx->x_win_size / 2) * (1 + \
			mlx->game.transform_x / mlx->game.transform_y));
	mlx->game.sp_vert_offset = (int)(SP_VERT_OFFSET / mlx->game.transform_y);
}

static void	f_sprite_vars_calc_finish(t_mlx *mlx)
{
	if ((mlx->game.sp_height = (int)((mlx->y_win_size / \
					mlx->game.transform_y) * SP_SCALE_Y)) < 0)
		mlx->game.sp_height *= -1;
	if ((mlx->game.sp_start_y = -mlx->game.sp_height / 2 + mlx->y_win_size \
		/ 2 + mlx->game.sp_vert_offset) < 0)
		mlx->game.sp_start_y = 0;
	if ((mlx->game.sp_end_y = mlx->game.sp_height / 2 + mlx->y_win_size / \
		2 + mlx->game.sp_vert_offset) >= mlx->y_win_size)
		mlx->game.sp_end_y = mlx->y_win_size - 1;
	if ((mlx->game.sp_width = (int)((mlx->y_win_size / \
					mlx->game.transform_y) * SP_SCALE_X)) < 0)
		mlx->game.sp_width *= -1;
	if ((mlx->game.sp_start_x = -mlx->game.sp_width / 2 + mlx->game.sp_scr_x) \
			< 0)
		mlx->game.sp_start_x = 0;
	if ((mlx->game.sp_end_x = mlx->game.sp_width / 2 + \
				mlx->game.sp_scr_x) < 0)
		mlx->game.sp_end_x = mlx->x_win_size - 1;
}

static void	f_draw_sprite_vert_line(t_mlx *mlx, int x, float shade)
{
	int		y;
	int		d;
	int		color;

	y = mlx->game.sp_start_y;
	while (y < mlx->game.sp_end_y)
	{
		d = (y - mlx->game.sp_vert_offset) * 256 - \
			mlx->y_win_size * 128 + mlx->game.sp_height * 128;
		mlx->game.tex_y = ((d * mlx->sp_tex.height) / mlx->game.sp_height) \
							/ 256;
		color = *(int*)(mlx->sp_tex.addr + ((mlx->game.tex_x + \
				(mlx->game.tex_y * mlx->sp_tex.width)) * \
				(mlx->sp_tex.bits_per_pix / 8)));
		if (color & 0x00FFFFFF)
			my_mlx_pixel_put(&mlx->img, x, y, f_add_shade(color, shade));
		y++;
	}
}

void		f_draw_sprite(t_mlx *mlx, t_sp *sp)
{
	int		x;
	float	shade;

	shade = 1 / (1 + 0.005 * sp->dist + 0.006 * pow(sp->dist, 2));
	f_sprite_vars_calc_start(mlx, sp);
	f_sprite_vars_calc_finish(mlx);
	x = mlx->game.sp_start_x;
	while (x < mlx->game.sp_end_x)
	{
		mlx->game.tex_x = (int)(256 * (x - (-mlx->game.sp_width / 2 + \
							mlx->game.sp_scr_x)) * mlx->sp_tex.width / \
							mlx->game.sp_width) / 256;
		if (mlx->game.transform_y > 0 && x > 0 && x < mlx->x_win_size && \
				mlx->game.transform_y < mlx->game.wall_dist_arr[x])
			f_draw_sprite_vert_line(mlx, x, shade);
		x++;
	}
}
