/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_squares.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 10:08:09 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void		f_fill_minimap(t_mlx *mlx)
{
	int			x;
	int			y;

	if (mlx->map.x >= 0 && mlx->map.y >= 0  && mlx->map.x < mlx->map.map_width \
			&& mlx->map.y < mlx->map.map_height)
	{
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
		else if (f_check_view_sector(mlx, x, y))
			my_mlx_pixel_put(&mlx->img, x, y, 0x0000FFFF);
		else if (ft_strchr("02NSWE", mlx->opts->map_array[mlx->map.y][mlx->map.x]))
			my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
		f_draw_player_point(mlx, x, y);
		f_draw_sprite_point(mlx, x, y);
		/* f_draw_minimap_contour(mlx, x, y); */
	}
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
