/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_contour_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/28 22:57:09 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		f_draw_minimap_contour_assist_1(t_mlx *mlx, int x, int y)
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

static int		f_draw_minimap_contour_assist_2(t_mlx *mlx, int x, int y)
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

int				f_draw_minimap_contour(t_mlx *mlx, int x, int y)
{
	if (f_draw_minimap_contour_assist_1(mlx, x, y))
		return (0);
	else
		f_draw_minimap_contour_assist_2(mlx, x, y);
	return (0);
}
