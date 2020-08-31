/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_squares.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 11:38:12 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>

int				f_check_pix_visibility(t_mlx *mlx, int x, int y)
{
	int			pix_radius;

	pix_radius = sqrt(pow(x - mlx->map.edge_shift - mlx->player.pos_x, 2) + \
					pow(y - mlx->map.edge_shift - mlx->player.pos_y, 2));
	if (pix_radius == mlx->map.map_radius - 1)
	{
		my_mlx_pixel_put(&mlx->img, x, y, 0xFFFFFF);
		return (0);
	}
	else if (pix_radius < mlx->map.map_radius)
	{
		my_mlx_pixel_put(&mlx->img, x, y, 0x000000);
		return (1);
	}
	return (0);
}

static void		f_draw_inner_map_pix(t_mlx *mlx, int x, int y)
{
	if ((mlx->map.sq_x == mlx->map.sq_side - 1 || mlx->map.sq_y == \
		mlx->map.sq_side - 1 || (mlx->map.x == 0 && mlx->map.sq_x == 0) || \
		(mlx->map.x > 0 && mlx->map.sq_x == 0 && \
		mlx->opts->map_array[mlx->map.y][mlx->map.x - 1] == ' ') || \
		(mlx->map.y == 0 && mlx->map.sq_y == 0) || (mlx->map.y > 0 && \
		mlx->map.sq_y == 0 && mlx->opts->map_array[mlx->map.y - 1][mlx->map.x] \
		== ' ')) && (mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' '))
		my_mlx_pixel_put(&mlx->img, x, y, 0x6B6B6B);
	else if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '1')
		my_mlx_pixel_put(&mlx->img, x, y, 0x1C596E);
	else if (f_check_view_sector(mlx, x, y))
		my_mlx_pixel_put(&mlx->img, x, y, 0x00FFFF);
	else if (ft_strchr("02NSWE", mlx->opts->map_array[mlx->map.y][mlx->map.x]))
		my_mlx_pixel_put(&mlx->img, x, y, 0x000000);
	f_draw_player_point(mlx, x, y);
	f_draw_sprite_point(mlx, x, y);
	f_draw_minimap_contour(mlx, x, y);
}

static void		f_fill_minimap(t_mlx *mlx)
{
	int			x;
	int			y;
	int			pix_visible;

	x = mlx->map.x * mlx->map.sq_side + mlx->map.sq_x + mlx->map.edge_shift - \
		mlx->map.map_start_x;
	y = mlx->map.y * mlx->map.sq_side + mlx->map.sq_y + mlx->map.edge_shift - \
	mlx->map.map_start_y;
	pix_visible = f_check_pix_visibility(mlx, x, y);
	if (mlx->map.x >= 0 && mlx->map.y >= 0  && mlx->map.x < mlx->map.map_width \
			&& mlx->map.y < mlx->map.map_height && pix_visible)
		f_draw_inner_map_pix(mlx, x, y);
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
