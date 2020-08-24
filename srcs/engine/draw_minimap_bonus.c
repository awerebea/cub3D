/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/24 16:27:23 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>

static void		f_draw_sprite_point(t_mlx *mlx, int x, int y)
{
	if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '2' && \
		mlx->map.sq_x > mlx->map.sq_side / 3 - 1 && \
		mlx->map.sq_x < mlx->map.sq_side - mlx->map.sq_side / 3 - 1 && \
		mlx->map.sq_y > mlx->map.sq_side / 3 - 1 && \
		mlx->map.sq_y < mlx->map.sq_side - mlx->map.sq_side / 3 - 1)
		my_mlx_pixel_put(&mlx->img, x, y, 0xFFFF00);
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

static int		f_view_sector(t_mlx *mlx, int x, int y)
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
	return (f_check_angle_range(mlx, delta_x, delta_y, angle));
}

static void		f_fill_minimap(t_mlx *mlx)
{
	int			x;
	int			y;

	x = mlx->map.x * mlx->map.sq_side + mlx->map.sq_x + mlx->map.edge_shift;
	y = mlx->map.y * mlx->map.sq_side + mlx->map.sq_y + mlx->map.edge_shift;
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
	else if (f_view_sector(mlx, x, y))
		my_mlx_pixel_put(&mlx->img, x, y, 0x0000FFFF);
	else if (ft_strchr("02NSWE", mlx->opts->map_array[mlx->map.y][mlx->map.x]))
		my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
	if (x > mlx->map.edge_shift + mlx->player.pos_x - mlx->map.sq_side / 6 && \
		x < mlx->map.edge_shift + mlx->player.pos_x + mlx->map.sq_side / 6 && \
		y > mlx->map.edge_shift + mlx->player.pos_y - mlx->map.sq_side / 6 && \
		y < mlx->map.edge_shift + mlx->player.pos_y + mlx->map.sq_side / 6)
		my_mlx_pixel_put(&mlx->img, x, y, 0xFF0000);
	f_draw_sprite_point(mlx, x, y);
}

void			f_draw_minimap(t_mlx *mlx)
{
	mlx->map.x = 0;
	mlx->map.y = 0;
	mlx->map.sq_x = 0;
	mlx->map.sq_y = 0;
	f_player_pos_init(mlx);
	while (mlx->map.y < mlx->map.map_height)
	{
		mlx->map.x = 0;
		while (mlx->map.x < mlx->map.map_width)
		{
			mlx->map.sq_y = 0;
			while (mlx->map.sq_y < mlx->map.sq_side)
			{
				mlx->map.sq_x = 0;
				while (mlx->map.sq_x < mlx->map.sq_side)
				{
					f_fill_minimap(mlx);
					mlx->map.sq_x++;
				}
				mlx->map.sq_y++;
			}
			mlx->map.x++;
		}
		mlx->map.y++;
	}
}
