/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:22:42 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/16 02:01:10 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_walls.h"
#include <math.h>

static void	f_tex_x_n_step_calculation(t_wall_vars *w_vars, t_img tex_img, \
																	int mirror)
{
	if (!mirror)
		w_vars->tex_x = (unsigned int)(w_vars->wall_x * \
							(float)(tex_img.width));
	else
		w_vars->tex_x = (unsigned int)((float)(tex_img.width) - \
							w_vars->wall_x * (float)(tex_img.width) - 1);
	w_vars->tex_step = 1.0 * tex_img.height / w_vars->line_height;
}

static void	f_tex_vars_calculating(t_mlx *mlx, t_wall_vars *w_vars)
{
	w_vars->wall_x = (w_vars->wall_side > 1) ? mlx->game.player_y + \
		w_vars->wall_dist * w_vars->ray_dir_y : mlx->game.player_x + \
		w_vars->wall_dist * w_vars->ray_dir_x;
	w_vars->wall_x -= (int)(w_vars->wall_x);
	if (w_vars->wall_side == 0)
		f_tex_x_n_step_calculation(w_vars, mlx->no_tex, 0);
	else if (w_vars->wall_side == 1)
		f_tex_x_n_step_calculation(w_vars, mlx->so_tex, 1);
	else if (w_vars->wall_side == 2)
		f_tex_x_n_step_calculation(w_vars, mlx->we_tex, 1);
	else if (w_vars->wall_side == 3)
		f_tex_x_n_step_calculation(w_vars, mlx->ea_tex, 0);
	w_vars->tex_pos = (w_vars->line_start - mlx->y_win_size / 2 + \
							w_vars->line_height / 2) * w_vars->tex_step;
}

static int	f_get_pix_color_n_tex_y_calculation(t_wall_vars *w_vars, \
																t_img tex_img)
{
	w_vars->tex_y = (int)w_vars->tex_pos & (tex_img.height - 1);
	if (w_vars->tex_x < 0)
		w_vars->tex_x *= -1; //what for???
	if (w_vars->tex_y < 0)
		w_vars->tex_y *= -1; //what for???
	if (w_vars->tex_x > tex_img.width || w_vars->tex_y > tex_img.height)
		return (-1); //what for???
	return (*(int*)(tex_img.addr + ((w_vars->tex_x + (w_vars->tex_y * \
							tex_img.width)) * (tex_img.bits_per_pix / 8))));
}

static void	f_line_params_calculation(t_mlx *mlx, t_wall_vars *w_vars)
{
	w_vars->line_height = (int)((mlx->y_win_size / w_vars->wall_dist) * 1.25);
	w_vars->line_start = mlx->y_win_size / 2 - w_vars->line_height / 2;
	if (w_vars->line_start < 0)
		w_vars->line_start = 0;
	w_vars->line_end = mlx->y_win_size / 2 + w_vars->line_height / 2;
	if (w_vars->line_end >= mlx->y_win_size)
		w_vars->line_end = mlx->y_win_size - 1;
}

void		f_draw_vert_line(t_mlx *mlx, t_wall_vars *w_vars, int x)
{
	int			color;
	float		shade;
	int			y;

	f_line_params_calculation(mlx, w_vars);
	shade = 1 / (1 + 0.005 * w_vars->wall_dist + 0.006 * \
			pow(w_vars->wall_dist, 2));
	y = w_vars->line_start;
	f_tex_vars_calculating(mlx, w_vars);
	while (y <= w_vars->line_end)
	{
		if (w_vars->wall_side == 0)
			color = f_get_pix_color_n_tex_y_calculation(w_vars, mlx->no_tex);
		else if (w_vars->wall_side == 1)
			color = f_get_pix_color_n_tex_y_calculation(w_vars, mlx->so_tex);
		else if (w_vars->wall_side == 2)
			color = f_get_pix_color_n_tex_y_calculation(w_vars, mlx->we_tex);
		else if (w_vars->wall_side == 3)
			color = f_get_pix_color_n_tex_y_calculation(w_vars, mlx->ea_tex);
		w_vars->tex_pos += w_vars->tex_step;
		my_mlx_pixel_put(&mlx->img, x, y++, f_add_shade(color, shade));
	}
}
