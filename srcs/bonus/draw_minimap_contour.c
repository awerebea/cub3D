/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_contour.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 12:02:02 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			f_draw_minimap_contour(t_mlx *mlx, int x, int y)
{
	if (mlx->map.x < mlx->map.map_width - 1 && mlx->map.sq_x == \
			mlx->map.sq_side - 1 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ' && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x + 1] == ' ')
		my_mlx_pixel_put(&mlx->img, x, y, 0xD7D7D7);
	else if (mlx->map.y < mlx->map.map_height - 1 && mlx->map.sq_y == \
			mlx->map.sq_side - 1 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ' && \
			mlx->opts->map_array[mlx->map.y + 1][mlx->map.x] == ' ')
		my_mlx_pixel_put(&mlx->img, x, y, 0xD7D7D7);
	else if (((mlx->map.x == mlx->map.map_width - 1 && mlx->map.sq_x == \
			mlx->map.sq_side - 1) || (mlx->map.y == mlx->map.map_height - 1 && \
			mlx->map.sq_y == mlx->map.sq_side - 1)) && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' ')
		my_mlx_pixel_put(&mlx->img, x, y, 0xD7D7D7);
	else if (((((mlx->map.x > 0 && mlx->map.sq_x == 0 && \
			mlx->opts->map_array[mlx->map.y][mlx->map.x - 1] == ' ') || \
			(mlx->map.y > 0 && mlx->map.sq_y == 0 && \
			mlx->opts->map_array[mlx->map.y - 1][mlx->map.x] == ' '))) || \
			((mlx->map.x == 0 && mlx->map.sq_x == 0) || (mlx->map.y == 0 && \
			mlx->map.sq_y == 0))) && \
			(mlx->opts->map_array[mlx->map.y][mlx->map.x] != ' '))
		my_mlx_pixel_put(&mlx->img, x, y, 0xD7D7D7);
}
