/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_n_background.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/02 23:03:33 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char		*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}

void		f_draw_background(t_mlx *mlx, t_img *img)
{
	int			x;
	int			y;

	x = 0;
	while (x < mlx->x_win_size)
	{
		y = 0;
		while (y < (mlx->y_win_size / 2))
		{
			my_mlx_pixel_put(img, x, y, mlx->opts->ceiling_color);
			y++;
		}
		while (y < mlx->y_win_size)
		{
			my_mlx_pixel_put(img, x, y, mlx->opts->floor_color);
			y++;
		}
		x++;
	}
}

static void	f_minimap_init(t_mlx *mlx, t_minimap *map)
{
	map->map_width = mlx->opts->max_mapline_len;
	map->map_height = mlx->opts->map_row_index + 1;
	map->map_size = mlx->x_win_size / MINIMAP_SIZE_DIVISOR;
	if ((map->map_size / map->map_width) < \
			(mlx->y_win_size / map->map_height))
		map->square_side = map->map_size / map->map_width;
	else
		map->square_side = (mlx->y_win_size - mlx->x_win_size / 50) / \
						map->map_height;
	map->x = 0;
	map->y = 0;
	map->sq_x = 0;
	map->sq_y = 0;
}

static void	f_fill_minimap(t_mlx *mlx, t_img *img, t_minimap *map)
{
	int			x;
	int			y;

	x = map->x * map->square_side + map->sq_x + mlx->x_win_size / 100;
	y = map->y * map->square_side + map->sq_y + mlx->x_win_size / 100;
	if (map->sq_x == map->square_side - 1 || \
			map->sq_y == map->square_side - 1 || \
			(map->x == 0 && map->sq_x == 0) || \
			(map->y == 0 && map->sq_y == 0))
		my_mlx_pixel_put(img, x, y, 0x006B6B6B);
	else if (mlx->opts->map_array[map->y][map->x] == '1')
		my_mlx_pixel_put(img, x, y, 0x001C596E);
	else
		my_mlx_pixel_put(img, x, y, 0x00000000);
}

void		f_draw_minimap(t_mlx *mlx, t_img *img)
{
	t_minimap	map;

	f_minimap_init(mlx, &map);
	while (map.y < map.map_height)
	{
		map.x = 0;
		while (map.x < map.map_width)
		{
			map.sq_y = 0;
			while (map.sq_y < map.square_side)
			{
				map.sq_x = 0;
				while (map.sq_x < map.square_side)
				{
					f_fill_minimap(mlx, img, &map);
					map.sq_x++;
				}
				map.sq_y++;
			}
			map.x++;
		}
		map.y++;
	}
}
