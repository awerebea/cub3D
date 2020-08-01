/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/01 13:15:08 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int			f_close_n_exit(t_mlx *mlx, int window)
{
	if (window == 1)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx->mlx_ptr);
	exit(f_exit(0, mlx->opts));
}

static int	f_window_init(t_mlx *mlx, t_sdf *opts)
{
	mlx->win_ptr = NULL;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (400);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->x_win_size, &mlx->y_win_size);
	if (mlx->x_win_size > opts->x_win_size)
		mlx->x_win_size = opts->x_win_size;
	if (mlx->y_win_size > opts->y_win_size)
		mlx->y_win_size = opts->y_win_size;
	mlx->opts = opts;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size);
	mlx->img.addr = (int *)mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian);
	return (0);
}

void		f_draw_floor_n_ceiling(t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	while (x <= mlx->x_win_size)
	{
		y = 0;
		while (y <= (mlx->y_win_size / 2))
		{
			mlx->img.addr[y * mlx->x_win_size + x] = mlx->opts->ceiling_color;
			y++;
		}
		while (y <= mlx->y_win_size)
		{
			mlx->img.addr[y * mlx->x_win_size + x] = mlx->opts->floor_color;
			y++;
		}
		x++;
	}
}

void		f_minimap_init(t_mlx *mlx)
{
	mlx->map.map_width = mlx->opts->max_mapline_len;
	mlx->map.map_height = mlx->opts->map_row_index + 1;
	mlx->map.square_side = ((mlx->map.square_side = (MINIMAP_SIZE / \
		mlx->map.map_width)) < (mlx->y_win_size / mlx->map.map_height)) ? \
		mlx->map.square_side : (mlx->y_win_size / mlx->map.map_height);
	mlx->map.x = 0;
	mlx->map.y = 0;
	mlx->map.sq_x = 0;
	mlx->map.sq_y = 0;
}

void		f_fill_minimap(t_mlx *mlx)
{
	if (mlx->map.sq_x == mlx->map.square_side - 1|| \
		mlx->map.sq_y == mlx->map.square_side - 1 || \
		(mlx->map.x == 0 && mlx->map.sq_x == 0) || \
		(mlx->map.y == 0 && mlx->map.sq_y == 0))
	{
		mlx->img.addr[(mlx->map.y * mlx->map.square_side + \
		mlx->map.sq_y) * mlx->x_win_size + mlx->map.x * \
		mlx->map.square_side + mlx->map.sq_x] = 0xFFFFFFFF;
	}
	else if (mlx->opts->map_array[mlx->map.y][mlx->map.x] == \
			'1')
	{
		mlx->img.addr[(mlx->map.y * mlx->map.square_side + \
		mlx->map.sq_y) * mlx->x_win_size + mlx->map.x * \
		mlx->map.square_side + mlx->map.sq_x] = 0xFF1C596E;
	}
	else
		mlx->img.addr[(mlx->map.y * mlx->map.square_side + \
		mlx->map.sq_y) * mlx->x_win_size + mlx->map.x * \
		mlx->map.square_side + mlx->map.sq_x] = 0xFF000000;

}

void		f_draw_minimap(t_mlx *mlx)
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

int			deal_key(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx, 1);
	else
		ft_putnbr_fd(key, 1);
	return (0);
}

int			f_window(t_sdf *opts)
{
	int		errcode;
	t_mlx	mlx;

	if ((errcode = f_window_init(&mlx, opts)))
		return (errcode);
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.x_win_size, \
		mlx.y_win_size, "cub3D")))
		return (401);
	f_draw_floor_n_ceiling(&mlx);
	f_draw_minimap(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, f_close_n_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
