/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:36:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/11 22:54:13 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "libft.h"
#include "ft_printf.h"

int			f_get_texture_pix_color(t_img tex_img, int tex_x, int tex_y)
{
	if (tex_img.width < 1 || tex_img.height < 1)
		return (-1);
	tex_x = abs(tex_x);
	tex_y = abs(tex_y);
	if (tex_x > tex_img.width || tex_y > tex_img.height || tex_x < 0 \
			|| tex_y < 0)
		return (-1);
	return (*(int*)(tex_img.addr + ((tex_x + (tex_y * tex_img.width)) * \
					(tex_img.bits_per_pix / 8))));
}

void		f_texture_vars_calculating(t_mlx *mlx)
{
	mlx->game.wall_x = (mlx->game.wall_side > 1) ? mlx->game.player_y + \
		mlx->game.wall_dist * mlx->game.ray_dir_y : mlx->game.player_x + \
		mlx->game.wall_dist * mlx->game.ray_dir_x;
	mlx->game.wall_x -= floor(mlx->game.wall_x);
	if (mlx->game.wall_side == 0)
	{
		mlx->game.texture_x = (mlx->game.dir_y < 0) ? \
						mlx->north_tex.width - mlx->game.texture_x - 1 : \
						(int)(mlx->game.wall_x * (float)(mlx->north_tex.width));
		mlx->game.texture_step = 1.0 * mlx->north_tex.height / \
									mlx->game.line_height;
	}
	else if (mlx->game.wall_side == 1)
	{
		mlx->game.texture_x = (mlx->game.dir_y < 0) ? \
						mlx->south_tex.width - mlx->game.texture_x - 1 : \
						(int)(mlx->game.wall_x * (float)(mlx->south_tex.width));
		mlx->game.texture_step = 1.0 * mlx->south_tex.height / \
									mlx->game.line_height;
	}
	else if (mlx->game.wall_side == 2)
	{
		mlx->game.texture_x = (mlx->game.dir_x > 0) ? \
						mlx->west_tex.width - mlx->game.texture_x - 1 : \
						(int)(mlx->game.wall_x * (float)(mlx->west_tex.width));
		mlx->game.texture_step = 1.0 * mlx->west_tex.height / \
									mlx->game.line_height;
	}
	else if (mlx->game.wall_side == 2)
	{
		mlx->game.texture_x = (mlx->game.dir_x > 0) ? \
						mlx->east_tex.width - mlx->game.texture_x - 1 : \
						(int)(mlx->game.wall_x * (float)(mlx->east_tex.width));
		mlx->game.texture_step = 1.0 * mlx->east_tex.height / \
									mlx->game.line_height;
	}
	mlx->game.texture_pos = (mlx->game.line_start - mlx->y_win_size / 2 + \
							mlx->game.line_height /2) * mlx->game.texture_step;
}

static void	f_draw_vert_line(t_mlx *mlx, int x)
{
	int			color;
	float		shade;
	int			y;

	mlx->game.line_height = (int)(mlx->y_win_size / mlx->game.wall_dist);
	mlx->game.line_start = mlx->y_win_size / 2 - mlx->game.line_height / 2;
	if (mlx->game.line_start < 0)
		mlx->game.line_start = 0;
	mlx->game.line_end = mlx->y_win_size / 2 + mlx->game.line_height / 2;
	if (mlx->game.line_end >= mlx->y_win_size)
		mlx->game.line_end = mlx->y_win_size - 1;
	shade = pow(((float)mlx->game.line_end / (float)mlx->y_win_size), 1.2);
	y = mlx->game.line_start;
	f_texture_vars_calculating(mlx);
	while (y <= mlx->game.line_end)
	{
		if (mlx->game.wall_side == 0)
		{
			mlx->game.texture_y = (int)mlx->game.texture_pos & \
									(mlx->north_tex.height - 1);
			color = f_get_texture_pix_color(mlx->north_tex, \
					mlx->game.texture_x, mlx->game.texture_y);
		}
		else if (mlx->game.wall_side == 1)
		{
			mlx->game.texture_y = (int)mlx->game.texture_pos & \
									(mlx->south_tex.height - 1);
			color = f_get_texture_pix_color(mlx->south_tex, \
					mlx->game.texture_x, mlx->game.texture_y);
		}
		else if (mlx->game.wall_side == 2)
		{
			mlx->game.texture_y = (int)mlx->game.texture_pos & \
									(mlx->west_tex.height - 1);
			color = f_get_texture_pix_color(mlx->west_tex, \
					mlx->game.texture_x, mlx->game.texture_y);
		}
		else
		{
			mlx->game.texture_y = (int)mlx->game.texture_pos & \
									(mlx->east_tex.height - 1);
			color = f_get_texture_pix_color(mlx->east_tex, \
					mlx->game.texture_x, mlx->game.texture_y);
		}
		mlx->game.texture_pos += mlx->game.texture_step;
		my_mlx_pixel_put(&mlx->img, x, y++, f_add_shade(color, shade));
	}
}

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
		f_draw_vert_line(mlx, x++);
	}
}
