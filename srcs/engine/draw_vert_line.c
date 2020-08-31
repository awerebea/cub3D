/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:22:42 by awerebea          #+#    #+#             */
/*   Updated: 2020/09/01 00:54:21 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <math.h>

static int	f_get_pix_color_n_tex_y_calculation(t_mlx *mlx, t_wall_vars *w_vars)
{
	t_img	*tex_img;

	tex_img = NULL;
	if (w_vars->wall_side == 0)
		tex_img = &mlx->no_tex;
	else if (w_vars->wall_side == 1)
		tex_img = &mlx->so_tex;
	else if (w_vars->wall_side == 2)
		tex_img = &mlx->we_tex;
	else if (w_vars->wall_side == 3)
		tex_img = &mlx->ea_tex;
	w_vars->tex_y = (int)w_vars->tex_pos & (tex_img->height - 1);
	return (*(int*)(tex_img->addr + ((w_vars->tex_x + (w_vars->tex_y * \
							tex_img->width)) * (tex_img->bits_per_pix / 8))));
}

#ifdef BONUS

static void	f_tex_vars_calculation(t_mlx *mlx, t_wall_vars *w_vars)
{
	t_img	*tex_img;

	tex_img = NULL;
	w_vars->wall_x = (w_vars->wall_side > 1) ? mlx->game.player_y + \
		w_vars->wall_dist * w_vars->ray_dir_y : mlx->game.player_x + \
		w_vars->wall_dist * w_vars->ray_dir_x;
	w_vars->wall_x -= (int)(w_vars->wall_x);
	if (w_vars->wall_side == 0)
		tex_img = &mlx->no_tex;
	else if (w_vars->wall_side == 1)
		tex_img = &mlx->so_tex;
	else if (w_vars->wall_side == 2)
		tex_img = &mlx->we_tex;
	else if (w_vars->wall_side == 3)
		tex_img = &mlx->ea_tex;
	w_vars->tex_mirror = (w_vars->wall_side == 1 || w_vars->wall_side == 2) ? \
							1 : 0;
	w_vars->tex_x = (!w_vars->tex_mirror) ? (int)(w_vars->wall_x * \
		(float)(tex_img->width)) : (int)((float)(tex_img->width) - \
		w_vars->wall_x * (float)(tex_img->width) - 1);
	w_vars->tex_step = 1.0 * tex_img->height / w_vars->line_height;
	w_vars->tex_pos = (w_vars->line_start - mlx->y_win_size * \
		mlx->game.vert_pos_factor + w_vars->line_height / 2) * w_vars->tex_step;
}

void		f_draw_vert_line(t_mlx *mlx, t_wall_vars *w_vars, int x)
{
	int			color;
	float		shade;
	int			y;

	w_vars->line_height = (int)((mlx->y_win_size / w_vars->wall_dist) * 1.25);
	w_vars->line_start = mlx->y_win_size * mlx->game.vert_pos_factor - \
							w_vars->line_height / 2;
	if (w_vars->line_start < 0)
		w_vars->line_start = 0;
	w_vars->line_end = mlx->y_win_size * mlx->game.vert_pos_factor + \
							w_vars->line_height / 2;
	if (w_vars->line_end >= mlx->y_win_size)
		w_vars->line_end = mlx->y_win_size - 1;
	shade = 1 / (1 + 0.005 * w_vars->wall_dist + 0.006 * \
			pow(w_vars->wall_dist, 2));
	y = w_vars->line_start;
	f_tex_vars_calculation(mlx, w_vars);
	while (y <= w_vars->line_end)
	{
		color = f_get_pix_color_n_tex_y_calculation(mlx, w_vars);
		w_vars->tex_pos += w_vars->tex_step;
		my_mlx_pixel_put(&mlx->img, x, y++, f_add_shade(color, shade));
	}
}

#else

static void	f_tex_vars_calculation(t_mlx *mlx, t_wall_vars *w_vars)
{
	t_img	*tex_img;

	tex_img = NULL;
	w_vars->wall_x = (w_vars->wall_side > 1) ? mlx->game.player_y + \
		w_vars->wall_dist * w_vars->ray_dir_y : mlx->game.player_x + \
		w_vars->wall_dist * w_vars->ray_dir_x;
	w_vars->wall_x -= (int)(w_vars->wall_x);
	if (w_vars->wall_side == 0)
		tex_img = &mlx->no_tex;
	else if (w_vars->wall_side == 1)
		tex_img = &mlx->so_tex;
	else if (w_vars->wall_side == 2)
		tex_img = &mlx->we_tex;
	else if (w_vars->wall_side == 3)
		tex_img = &mlx->ea_tex;
	w_vars->tex_mirror = (w_vars->wall_side == 1 || w_vars->wall_side == 2) ? \
							1 : 0;
	w_vars->tex_x = (!w_vars->tex_mirror) ? (int)(w_vars->wall_x * \
		(float)(tex_img->width)) : (int)((float)(tex_img->width) - \
		w_vars->wall_x * (float)(tex_img->width) - 1);
	w_vars->tex_step = 1.0 * tex_img->height / w_vars->line_height;
	w_vars->tex_pos = (w_vars->line_start - mlx->y_win_size / 2 + \
							w_vars->line_height / 2) * w_vars->tex_step;
}

void		f_draw_vert_line(t_mlx *mlx, t_wall_vars *w_vars, int x)
{
	int			color;
	int			y;

	w_vars->line_height = (int)((mlx->y_win_size / w_vars->wall_dist) * 1.25);
	w_vars->line_start = mlx->y_win_size / 2 - w_vars->line_height / 2;
	if (w_vars->line_start < 0)
		w_vars->line_start = 0;
	w_vars->line_end = mlx->y_win_size / 2 + w_vars->line_height / 2;
	if (w_vars->line_end >= mlx->y_win_size)
		w_vars->line_end = mlx->y_win_size - 1;
	y = w_vars->line_start;
	f_tex_vars_calculation(mlx, w_vars);
	while (y <= w_vars->line_end)
	{
		color = f_get_pix_color_n_tex_y_calculation(mlx, w_vars);
		w_vars->tex_pos += w_vars->tex_step;
		my_mlx_pixel_put(&mlx->img, x, y++, color);
	}
}

#endif
