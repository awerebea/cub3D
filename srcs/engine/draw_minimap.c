/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/10 16:44:26 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

static float	f_angle_calculation(float delta_x, float delta_y)
{
	float	angle;

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
	return (angle);
}

int				f_view_sector(t_mlx *mlx, int x, int y)
{
	float	delta_x;
	float	delta_y;
	float	angle;

	delta_x = x - mlx->map.edge_shift - mlx->player.pos_x;
	delta_y = y - mlx->map.edge_shift - mlx->player.pos_y;
	angle = f_angle_calculation(delta_x, delta_y);
	if ((mlx->player.view_angle - mlx->player.fov / 2 < 0) && (((angle >= \
		mlx->player.view_angle - mlx->player.fov / 2 + M_PI * 2) || \
		(angle <= mlx->player.view_angle + mlx->player.fov / 2)) && \
		(sqrt(pow(delta_x, 2) + pow(delta_y, 2)) <= mlx->map.square_side * VRAD)))
		return (1);
	if ((mlx->player.view_angle + mlx->player.fov / 2 >= M_PI * 2) && \
		((angle >= mlx->player.view_angle - mlx->player.fov / 2) && (angle \
		<= mlx->player.view_angle + mlx->player.fov / 2 - M_PI * 2) && \
		(sqrt(pow(delta_x, 2) + pow(delta_y, 2)) <= mlx->map.square_side * VRAD)))
		return (1);
	if ((angle >= mlx->player.view_angle - mlx->player.fov / 2) && (angle <= \
		mlx->player.view_angle + mlx->player.fov / 2) && \
		(sqrt(pow(delta_x, 2) + pow(delta_y, 2)) <= mlx->map.square_side * VRAD))
		return (1);
	return (0);
}

static void		f_fill_minimap(t_mlx *mlx)
{
	int			x;
	int			y;

	x = mlx->map.x * mlx->map.square_side + mlx->map.sq_x + mlx->map.edge_shift;
	y = mlx->map.y * mlx->map.square_side + mlx->map.sq_y + mlx->map.edge_shift;
	if ((mlx->map.sq_x == mlx->map.square_side - 1 || \
			mlx->map.sq_y == mlx->map.square_side - 1 || \
			(mlx->map.x == 0 && mlx->map.sq_x == 0) || \
			(mlx->map.x > 0 && mlx->map.sq_x == 0 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x - 1] == ' ') || \
			(mlx->map.y == 0 && mlx->map.sq_y == 0) || \
			(mlx->map.y > 0 && mlx->map.sq_y == 0 && \
			mlx->opts->map_array[mlx->map.y - 1][mlx->map.x] == ' ')) && \
			(mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' '))
		my_mlx_pixel_put(&mlx->img, x, y, 0x006B6B6B);
	else if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '1')
		my_mlx_pixel_put(&mlx->img, x, y, 0x001C596E);
	else if (f_view_sector(mlx, x, y))
		my_mlx_pixel_put(&mlx->img, x, y, 0x0000FFFF);
	else if (ft_strchr("02NSWE", mlx->opts->map_array[mlx->map.y][mlx->map.x]))
		my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
}

void			f_draw_minimap(t_mlx *mlx)
{
	mlx->map.x = 0;
	mlx->map.y = 0;
	mlx->map.sq_x = 0;
	mlx->map.sq_y = 0;
	while (mlx->map.y < mlx->map.map_height)
	{
		mlx->map.x = 0;
		while (mlx->map.x < mlx->map.map_width)
		{
			mlx->map.sq_y = 0;
			while (mlx->map.sq_y < mlx->map.square_side)
			{
				mlx->map.sq_x = 0;
				while (mlx->map.sq_x < mlx->map.square_side)
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

void			f_draw_player_minimap(t_mlx *mlx)
{
	int		x;
	int		y;

	f_player_pos_init(mlx);
	x = mlx->map.edge_shift + mlx->player.pos_x - mlx->map.square_side / 6;
	while (x < mlx->map.edge_shift + mlx->player.pos_x + \
			mlx->map.square_side / 6)
	{
		y = mlx->map.edge_shift + mlx->player.pos_y - mlx->map.square_side / 6;
		while (y < mlx->map.edge_shift + mlx->player.pos_y + \
				mlx->map.square_side / 6)
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}
