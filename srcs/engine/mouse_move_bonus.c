/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 15:00:36 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/27 17:04:48 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

#ifdef LINUX

int		f_mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->game.delta_x = ((x - mlx->game.mouse_x) * mlx->game.sens / 1000.0);
	if (mlx->game.mouse_x)
	{
		mlx->game.old_dir_x = mlx->game.dir_x;
		mlx->game.dir_x = mlx->game.dir_x * cos(mlx->game.delta_x) - \
							mlx->game.dir_y * sin(mlx->game.delta_x);
		mlx->game.dir_y = mlx->game.old_dir_x * sin(mlx->game.delta_x) + \
							mlx->game.dir_y * cos(mlx->game.delta_x);
		mlx->game.old_plane_x = mlx->game.plane_x;
		mlx->game.plane_x = mlx->game.plane_x * cos(mlx->game.delta_x) - \
							mlx->game.plane_y * sin(mlx->game.delta_x);
		mlx->game.plane_y = mlx->game.old_plane_x * sin(mlx->game.delta_x) + \
							mlx->game.plane_y * cos(mlx->game.delta_x);
	}
	mlx->game.mouse_x = x;
	(mlx->keys.m > 0) ? mlx_mouse_hide(mlx->mlx_ptr, mlx->win_ptr) : \
				mlx_mouse_show(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->keys.m > 0 && (x < mlx->x_win_size * 0.2 || x > mlx->x_win_size \
			* 0.8 || y < mlx->y_win_size * 0.2 || y > mlx->y_win_size * 0.8))
	{
		mlx->game.mouse_x = 0;
		mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, mlx->x_win_size / 2, \
				mlx->y_win_size / 2);
	}
	return (0);
}

#else

int		f_mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->game.delta_x = ((x - mlx->game.mouse_x) * mlx->game.sens / 1000.0);
	if (mlx->game.mouse_x && y)
	{
		mlx->game.old_dir_x = mlx->game.dir_x;
		mlx->game.dir_x = mlx->game.dir_x * cos(mlx->game.delta_x) - \
							mlx->game.dir_y * sin(mlx->game.delta_x);
		mlx->game.dir_y = mlx->game.old_dir_x * sin(mlx->game.delta_x) + \
							mlx->game.dir_y * cos(mlx->game.delta_x);
		mlx->game.old_plane_x = mlx->game.plane_x;
		mlx->game.plane_x = mlx->game.plane_x * cos(mlx->game.delta_x) - \
							mlx->game.plane_y * sin(mlx->game.delta_x);
		mlx->game.plane_y = mlx->game.old_plane_x * sin(mlx->game.delta_x) + \
							mlx->game.plane_y * cos(mlx->game.delta_x);
	}
	mlx->game.mouse_x = x;
	(mlx->keys.m > 0) ? mlx_mouse_hide(mlx->mlx_ptr, mlx->win_ptr) : \
				mlx_mouse_show(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->keys.m > 0 && (x < mlx->x_win_size * 0.2 || x > mlx->x_win_size \
			* 0.8))
	{
		mlx->game.mouse_x = 0;
		mlx_mouse_move(mlx->win_ptr, mlx->x_win_size / 2, mlx->y_win_size / 2);
	}
	return (0);
}

#endif
