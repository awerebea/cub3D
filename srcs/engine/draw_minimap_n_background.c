/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_n_background.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:40:00 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/06 15:08:36 by awerebea         ###   ########.fr       */
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

static void	f_minimap_init(t_mlx *mlx)
{
	mlx->map.edge_shift = mlx->x_win_size / 100;

	mlx->map.map_width = mlx->opts->max_mapline_len;
	mlx->map.map_height = mlx->opts->map_row_index + 1;
	mlx->map.map_size = mlx->x_win_size / MINIMAP_SIZE_DIVISOR;
	if ((mlx->map.map_size / mlx->map.map_width) < \
			(mlx->y_win_size / mlx->map.map_height))
		mlx->map.square_side = mlx->map.map_size / mlx->map.map_width;
	else
		mlx->map.square_side = (mlx->y_win_size - mlx->x_win_size / 50) / \
						mlx->map.map_height;
	mlx->map.x = 0;
	mlx->map.y = 0;
	mlx->map.sq_x = 0;
	mlx->map.sq_y = 0;
}

static void	f_fill_minimap(t_mlx *mlx, t_img *img)
{
	int			x;
	int			y;

	x = mlx->map.x * mlx->map.square_side + mlx->map.sq_x + mlx->map.edge_shift;
	y = mlx->map.y * mlx->map.square_side + mlx->map.sq_y + mlx->map.edge_shift;
	if (mlx->map.sq_x == mlx->map.square_side - 1 || \
			mlx->map.sq_y == mlx->map.square_side - 1 || \
			(mlx->map.x == 0 && mlx->map.sq_x == 0) || \
			(mlx->map.y == 0 && mlx->map.sq_y == 0))
		my_mlx_pixel_put(img, x, y, 0x006B6B6B);
	else if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == '1')
		my_mlx_pixel_put(img, x, y, 0x001C596E);
	else
		my_mlx_pixel_put(img, x, y, 0x00000000);
}

void		f_draw_minimap(t_mlx *mlx, t_img *img)
{
	f_minimap_init(mlx);
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
					f_fill_minimap(mlx, img);
					mlx->map.sq_x++;
				}
				mlx->map.sq_y++;
			}
			mlx->map.x++;
		}
		mlx->map.y++;
	}
}
