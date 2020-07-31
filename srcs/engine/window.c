/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/31 11:35:40 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int			f_close_n_exit(t_mlx *mlx)
{
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx->mlx_ptr);
	exit(f_exit(0, mlx->opts));
}

static int	f_window_init(t_mlx *mlx, t_sdf *opts)
{
	mlx->win_ptr = NULL;
	mlx->opts = opts;
	mlx->x_win_size = 0;
	mlx->y_win_size = 0;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (400);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->x_win_size, &mlx->y_win_size);
	if (mlx->x_win_size > opts->x_win_size)
		mlx->x_win_size = opts->x_win_size;
	if (mlx->y_win_size > opts->y_win_size)
		mlx->y_win_size = opts->y_win_size;
	return (0);
}

int			f_draw_floor_n_ceiling(t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	while (x <= mlx->x_win_size)
	{
		y = 0;
		while (y <= (mlx->y_win_size / 2))
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, \
					mlx->opts->ceiling_color);
			y++;
		}
		while (y <= mlx->y_win_size)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, \
					mlx->opts->floor_color);
			y++;
		}
		x++;
	}
	return (0);
}

int			deal_key(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx);
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
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
