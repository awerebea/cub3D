/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/28 22:44:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>

int		f_draw_minimap_contour_assist_1(t_mlx *mlx, int x, int y)
{
	int		pixel_to_put;

	pixel_to_put = 0;
	if ((mlx->map.x < mlx->map.map_width - 1 && mlx->map.sq_x == \
			mlx->map.sq_side - 1 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ' && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x + 1] == ' '))
		pixel_to_put = 1;
	else if ((mlx->map.y < mlx->map.map_height - 1 && mlx->map.sq_y == \
			mlx->map.sq_side - 1 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ' && \
			mlx->opts->map_array[mlx->map.y + 1][mlx->map.x] == ' '))
		pixel_to_put = 1;
	else if (((mlx->map.x == mlx->map.map_width - 1 && mlx->map.sq_x == \
		mlx->map.sq_side - 1) || (mlx->map.y == mlx->map.map_height - 1 && \
		mlx->map.sq_y == mlx->map.sq_side - 1)) && \
		mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ')
		pixel_to_put = 1;
	if (pixel_to_put)
		my_mlx_pixel_put(&mlx->img, x, y, 0xFFFFFF);
	return (pixel_to_put);
}

int		f_draw_minimap_contour_assist_2(t_mlx *mlx, int x, int y)
{
	int		pixel_to_put;

	pixel_to_put = 0;
	if ((x == mlx->map.edge_shift || y == mlx->map.edge_shift) && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ')
		pixel_to_put = 1;
	else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side && \
			mlx->map.sq_x == mlx->map.map_end_x % mlx->map.sq_side - 1 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ')
		pixel_to_put = 1;
	else if (mlx->map.y == mlx->map.map_end_y / mlx->map.sq_side && \
			mlx->map.sq_y == mlx->map.map_end_y % mlx->map.sq_side - 1 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ')
		pixel_to_put = 1;
	else if (((mlx->map.x > 0 && mlx->map.sq_x == 0 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x - 1] == ' ') || \
			(mlx->map.y > 0 && mlx->map.sq_y == 0 && \
			mlx->opts->map_array[mlx->map.y - 1][mlx->map.x] == ' ')) && \
			(mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' '))
		pixel_to_put = 1;
	if (pixel_to_put)
		my_mlx_pixel_put(&mlx->img, x, y, 0xFFFFFF);
	return (pixel_to_put);
}

int		f_draw_minimap_contour(t_mlx *mlx, int x, int y)
{
	if (f_draw_minimap_contour_assist_1(mlx, x, y))
		return (0);
	else
		f_draw_minimap_contour_assist_2(mlx, x, y);
	return (0);
}

static void		f_draw_sprite_point(t_mlx *mlx, int x, int y)
{
	if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '2' && \
		mlx->map.sq_x > mlx->map.sq_side / 3 - 1 && \
		mlx->map.sq_x < mlx->map.sq_side - mlx->map.sq_side / 3 - 1 && \
		mlx->map.sq_y > mlx->map.sq_side / 3 - 1 && \
		mlx->map.sq_y < mlx->map.sq_side - mlx->map.sq_side / 3 - 1)
		my_mlx_pixel_put(&mlx->img, x, y, 0xFFFF00);
}

static void		f_draw_player_point(t_mlx *mlx, int x, int y)
{
	if (x > mlx->map.edge_shift + mlx->player.pos_x - mlx->map.sq_side / 6 && \
		x < mlx->map.edge_shift + mlx->player.pos_x + mlx->map.sq_side / 6 && \
		y > mlx->map.edge_shift + mlx->player.pos_y - mlx->map.sq_side / 6 && \
		y < mlx->map.edge_shift + mlx->player.pos_y + mlx->map.sq_side / 6)
		my_mlx_pixel_put(&mlx->img, x, y, 0xFF0000);
}

static int		f_check_angle_range(t_mlx *mlx, float delta_x, float delta_y, \
										float angle)
{
	if (mlx->player.view_angle - mlx->player.fov / 2 < 0)
	{
		if (!((angle >= mlx->player.view_angle + mlx->player.fov / 2) \
			&& (angle <= mlx->player.view_angle - mlx->player.fov / 2 + \
			M_PI * 2)) && (sqrt(pow(delta_x, 2) + pow(delta_y, 2)) <= \
			mlx->map.sq_side * VRAD))
			return (1);
	}
	if (mlx->player.view_angle + mlx->player.fov / 2 > M_PI * 2)
	{
		if (!((angle >= mlx->player.view_angle + mlx->player.fov / 2 - \
			M_PI * 2) && (angle <= mlx->player.view_angle - \
			mlx->player.fov / 2)) && (sqrt(pow(delta_x, 2) + pow(delta_y, 2)) \
			<= mlx->map.sq_side * VRAD))
			return (1);
	}
	if ((angle >= mlx->player.view_angle - mlx->player.fov / 2) && \
		(angle <= mlx->player.view_angle + mlx->player.fov / 2) && \
		(sqrt(pow(delta_x, 2) + pow(delta_y, 2)) <= mlx->map.sq_side * \
		VRAD))
		return (1);
	return (0);
}

static void		f_view_sector(t_mlx *mlx, int x, int y)
{
	float	delta_x;
	float	delta_y;
	float	angle;

	delta_x = x - mlx->map.edge_shift - mlx->player.pos_x;
	delta_y = y - mlx->map.edge_shift - mlx->player.pos_y;
	if (delta_x < 0 && delta_y < 0)
		angle = M_PI + atan(delta_y / delta_x);
	else if (delta_x > 0 && delta_y < 0)
		angle = 2 * M_PI - atan(-delta_y / delta_x);
	else if (delta_x < 0 && delta_y >= 0)
		angle = M_PI - atan(delta_y / -delta_x);
	else if (delta_x > 0 && delta_y >= 0)
		angle = atan(delta_y / delta_x);
	else if (delta_x == 0 && delta_y < 0)
		angle = M_PI * 3 / 2;
	else
		angle = M_PI / 2;
	if (f_check_angle_range(mlx, delta_x, delta_y, angle))
		my_mlx_pixel_put(&mlx->img, x, y, 0x0000FFFF);
}

void				f_map_start_n_end_x_init_assist(t_mlx *mlx)
{
	int			offset;

	offset = 0;
	mlx->map.map_start_x = mlx->player.pos_x - mlx->x_win_size * \
			MINIMAP_MAX_WDTH_FACTOR / 2;
	mlx->map.map_end_x = mlx->player.pos_x + mlx->x_win_size * \
			MINIMAP_MAX_WDTH_FACTOR / 2;
	if (mlx->map.map_start_x < 0)
	{
		offset -= mlx->map.map_start_x;
		mlx->map.map_start_x = 0;
		mlx->map.map_end_x += offset;
		if (mlx->map.map_end_x > mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR)
			mlx->map.map_end_x = mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR;
	}
	else if (mlx->map.map_end_x > mlx->map.map_width * mlx->map.sq_side)
	{
		offset = mlx->map.map_width * mlx->map.sq_side - mlx->map.map_end_x;
		mlx->map.map_end_x = mlx->map.map_width * mlx->map.sq_side;
		mlx->map.map_start_x += offset;
		if (mlx->map.map_start_x < 0)
			mlx->map.map_start_x = 0;
	}
}

void				f_map_start_n_end_x_init(t_mlx *mlx)
{
	int			offset;

	offset = 0;
	if (mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR / mlx->map.sq_side < \
			mlx->map.map_width)
		f_map_start_n_end_x_init_assist(mlx);
	else
	{
		mlx->map.map_start_x = 0;
		mlx->map.map_end_x = mlx->map.map_width * mlx->map.sq_side;
	}
}

void				f_map_start_n_end_y_init_assist(t_mlx *mlx)
{
	int			offset;

	offset = 0;
	mlx->map.map_start_y = mlx->player.pos_y - mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / 2;
	mlx->map.map_end_y = mlx->player.pos_y + mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / 2;
	if (mlx->map.map_start_y < 0)
	{
		offset -= mlx->map.map_start_y;
		mlx->map.map_start_y = 0;
		mlx->map.map_end_y += offset;
		if (mlx->map.map_end_y > mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR)
			mlx->map.map_end_y = mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR;
	}
	else if (mlx->map.map_end_y > mlx->map.map_height * mlx->map.sq_side)
	{
		offset = mlx->map.map_height * mlx->map.sq_side - \
					mlx->map.map_end_y;
		mlx->map.map_end_y = mlx->map.map_height * mlx->map.sq_side;
		mlx->map.map_start_y += offset;
		if (mlx->map.map_start_y < 0)
			mlx->map.map_start_y = 0;
	}
}

void				f_map_start_n_end_y_init(t_mlx *mlx)
{
	if (mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR / mlx->map.sq_side < \
			mlx->map.map_height)
		f_map_start_n_end_y_init_assist(mlx);
	else
	{
		mlx->map.map_start_y = 0;
		mlx->map.map_end_y = mlx->map.map_height * mlx->map.sq_side;
	}
}

static void		f_fill_minimap(t_mlx *mlx)
{
	int			x;
	int			y;

	x = mlx->map.x * mlx->map.sq_side + mlx->map.sq_x + mlx->map.edge_shift - \
		mlx->map.map_start_x;
	y = mlx->map.y * mlx->map.sq_side + mlx->map.sq_y + mlx->map.edge_shift - \
		mlx->map.map_start_y;
	if ((mlx->map.sq_x == mlx->map.sq_side - 1 || mlx->map.sq_y == \
		mlx->map.sq_side - 1 || (mlx->map.x == 0 && mlx->map.sq_x == 0) || \
		(mlx->map.x > 0 && mlx->map.sq_x == 0 && \
		mlx->opts->map_array[mlx->map.y][mlx->map.x - 1] == ' ') || \
		(mlx->map.y == 0 && mlx->map.sq_y == 0) || (mlx->map.y > 0 && \
		mlx->map.sq_y == 0 && mlx->opts->map_array[mlx->map.y - 1][mlx->map.x] \
		== ' ')) && (mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' '))
		my_mlx_pixel_put(&mlx->img, x, y, 0x006B6B6B);
	else if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '1')
		my_mlx_pixel_put(&mlx->img, x, y, 0x001C596E);
	else if (ft_strchr("02NSWE", mlx->opts->map_array[mlx->map.y][mlx->map.x]))
		my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
	f_view_sector(mlx, x, y);
	f_draw_player_point(mlx, x, y);
	f_draw_sprite_point(mlx, x, y);
	f_draw_minimap_contour (mlx, x, y);
}

void			f_draw_first_square(t_mlx *mlx)
{
	mlx->map.sq_x = mlx->map.map_start_x % mlx->map.sq_side;
	while (mlx->map.sq_x < mlx->map.sq_side)
	{
		f_fill_minimap(mlx);
		mlx->map.sq_x++;
	}
}

void			f_draw_middle_square(t_mlx *mlx)
{
	mlx->map.sq_x = 0;
	while (mlx->map.sq_x < mlx->map.sq_side)
	{
		f_fill_minimap(mlx);
		mlx->map.sq_x++;
	}
}

void			f_draw_last_square(t_mlx *mlx)
{
	mlx->map.sq_x = 0;
	while (mlx->map.sq_x < mlx->map.map_end_x % mlx->map.sq_side)
	{
		f_fill_minimap(mlx);
		mlx->map.sq_x++;
	}
}

void			f_draw_first_row(t_mlx *mlx)
{
	while (mlx->map.x <= mlx->map.map_end_x / mlx->map.sq_side)
	{
		mlx->map.sq_y = mlx->map.map_start_y % mlx->map.sq_side;
		while (mlx->map.sq_y < mlx->map.sq_side)
		{
			if (mlx->map.x == mlx->map.map_start_x / mlx->map.sq_side)
				f_draw_first_square(mlx);
			else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side)
				f_draw_last_square(mlx);
			else
				f_draw_middle_square(mlx);
			mlx->map.sq_y++;
		}
		mlx->map.x++;
	}
	mlx->map.y++;
}

void			f_draw_middle_row(t_mlx *mlx)
{
	while (mlx->map.y < mlx->map.map_end_y / mlx->map.sq_side)
	{
		mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
		while (mlx->map.x <= mlx->map.map_end_x / mlx->map.sq_side)
		{
			mlx->map.sq_y = 0;
			while (mlx->map.sq_y < mlx->map.sq_side)
			{
				if (mlx->map.x == mlx->map.map_start_x / mlx->map.sq_side)
					f_draw_first_square(mlx);
				else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side)
					f_draw_last_square(mlx);
				else
					f_draw_middle_square(mlx);
				mlx->map.sq_y++;
			}
			mlx->map.x++;
		}
		mlx->map.y++;
	}
	mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
}

void			f_draw_last_row(t_mlx *mlx)
{
	while (mlx->map.x <= mlx->map.map_end_x / mlx->map.sq_side)
	{
		mlx->map.sq_y = 0;
		while (mlx->map.sq_y < mlx->map.map_end_y % mlx->map.sq_side)
		{
			if (mlx->map.x == mlx->map.map_start_x / mlx->map.sq_side)
				f_draw_first_square(mlx);
			else if (mlx->map.x == mlx->map.map_end_x / mlx->map.sq_side)
				f_draw_last_square(mlx);
			else
				f_draw_middle_square(mlx);
			mlx->map.sq_y++;
		}
		mlx->map.x++;
	}
}

void			f_draw_minimap(t_mlx *mlx)
{
	f_player_pos_init(mlx);
	f_map_start_n_end_x_init(mlx);
	f_map_start_n_end_y_init(mlx);
	mlx->player.pos_x -= mlx->map.map_start_x;
	mlx->player.pos_y -= mlx->map.map_start_y;
	mlx->map.x = mlx->map.map_start_x / mlx->map.sq_side;
	mlx->map.y = mlx->map.map_start_y / mlx->map.sq_side;
	f_draw_first_row(mlx);
	f_draw_middle_row(mlx);
	f_draw_last_row(mlx);
}
