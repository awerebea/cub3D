/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:22:42 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/12 12:54:38 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	f_tex_x_n_step_calculation(t_mlx *mlx, t_img tex_img, int mirror)
{
	if (!mirror)
		mlx->game.tex_x = (int)(mlx->game.wall_x * (float)(tex_img.width));
	else
		mlx->game.tex_x = (int)((float)(tex_img.width) - mlx->game.wall_x \
								* (float)(tex_img.width) - 1);
	mlx->game.tex_step = 1.0 * tex_img.height / mlx->game.line_height;
}

static void	f_tex_vars_calculating(t_mlx *mlx)
{
	mlx->game.wall_x = (mlx->game.wall_side > 1) ? mlx->game.player_y + \
		mlx->game.wall_dist * mlx->game.ray_dir_y : mlx->game.player_x + \
		mlx->game.wall_dist * mlx->game.ray_dir_x;
	mlx->game.wall_x -= (int)(mlx->game.wall_x);
	if (mlx->game.wall_side == 0)
		f_tex_x_n_step_calculation(mlx, mlx->north_tex, 0);
	else if (mlx->game.wall_side == 1)
		f_tex_x_n_step_calculation(mlx, mlx->south_tex, 1);
	else if (mlx->game.wall_side == 2)
		f_tex_x_n_step_calculation(mlx, mlx->west_tex, 1);
	else if (mlx->game.wall_side == 3)
		f_tex_x_n_step_calculation(mlx, mlx->east_tex, 0);
	mlx->game.tex_pos = (mlx->game.line_start - mlx->y_win_size / 2 + \
							mlx->game.line_height / 2) * mlx->game.tex_step;
}

static int	f_get_pix_color_n_tex_y_calculation(t_mlx *mlx, t_img tex_img)
{
	mlx->game.tex_y = (int)mlx->game.tex_pos & (tex_img.height - 1);
	if (tex_img.width < 1 || tex_img.height < 1)
		return (-1);
	if (mlx->game.tex_x < 0)
		mlx->game.tex_x *= -1; //what for???
	if (mlx->game.tex_y < 0)
		mlx->game.tex_y *= -1; //what for???
	if (mlx->game.tex_x > tex_img.width || mlx->game.tex_y > tex_img.height)
		return (-1);
	return (*(int*)(tex_img.addr + ((mlx->game.tex_x + (mlx->game.tex_y * \
							tex_img.width)) * (tex_img.bits_per_pix / 8))));
}

static void	f_line_params_calculation(t_mlx *mlx)
{
	mlx->game.line_height = (int)(mlx->y_win_size / mlx->game.wall_dist);
	mlx->game.line_start = mlx->y_win_size / 2 - mlx->game.line_height / 2;
	if (mlx->game.line_start < 0)
		mlx->game.line_start = 0;
	mlx->game.line_end = mlx->y_win_size / 2 + mlx->game.line_height / 2;
	if (mlx->game.line_end >= mlx->y_win_size)
		mlx->game.line_end = mlx->y_win_size - 1;
}

void		f_draw_vert_line(t_mlx *mlx, int x)
{
	int			color;
	float		shade;
	int			y;

	f_line_params_calculation(mlx);
	shade = 1 / (1 + 0.005 * mlx->game.wall_dist + 0.006 * \
			pow(mlx->game.wall_dist, 2));
	y = mlx->game.line_start;
	f_tex_vars_calculating(mlx);
	while (y <= mlx->game.line_end)
	{
		if (mlx->game.wall_side == 0)
			color = f_get_pix_color_n_tex_y_calculation(mlx, mlx->north_tex);
		else if (mlx->game.wall_side == 1)
			color = f_get_pix_color_n_tex_y_calculation(mlx, mlx->south_tex);
		else if (mlx->game.wall_side == 2)
			color = f_get_pix_color_n_tex_y_calculation(mlx, mlx->west_tex);
		else if (mlx->game.wall_side == 3)
			color = f_get_pix_color_n_tex_y_calculation(mlx, mlx->east_tex);
		mlx->game.tex_pos += mlx->game.tex_step;
		my_mlx_pixel_put(&mlx->img, x, y++, f_add_shade(color, shade));
	}
}
