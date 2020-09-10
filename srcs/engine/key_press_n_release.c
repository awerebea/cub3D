/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_n_release.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:49:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/09/10 10:55:59 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_keys.h"
#include <time.h>

#ifdef BONUS

static	void	f_jump_init(t_mlx *mlx)
{
	if (!mlx->game.jump_in_progress)
	{
		mlx->game.jump_in_progress = 1;
		mlx->game.time_jump_start = clock();
	}
}

int				f_key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx);
	else if (key == KEY_W)
		mlx->keys.w = 1;
	else if (key == KEY_A)
		mlx->keys.a = 1;
	else if (key == KEY_S)
		mlx->keys.s = 1;
	else if (key == KEY_D)
		mlx->keys.d = 1;
	else if (key == KEY_M)
		mlx->keys.m *= -1;
	else if (key == KEY_LEFT)
		mlx->keys.left = 1;
	else if (key == KEY_RIGHT)
		mlx->keys.right = 1;
	else if (key == KEY_SHIFT_L && !mlx->game.jump_in_progress)
		mlx->keys.shift_l = 1;
	else if (key == KEY_SPACE && !mlx->keys.shift_l)
		f_jump_init(mlx);
	else if (key == KEY_MINUS)
		mlx->map.sq_side -= (mlx->map.sq_side > 5) ? 2 : 0;
	else if (key == KEY_PLUS)
		mlx->map.sq_side += (mlx->map.sq_side < 23) ? 2 : 0;
	return (0);
}

int				f_key_release(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->keys.w = 0;
	else if (key == KEY_A)
		mlx->keys.a = 0;
	else if (key == KEY_S)
		mlx->keys.s = 0;
	else if (key == KEY_D)
		mlx->keys.d = 0;
	else if (key == KEY_LEFT)
		mlx->keys.left = 0;
	else if (key == KEY_RIGHT)
		mlx->keys.right = 0;
	else if (key == KEY_SHIFT_L)
		mlx->keys.shift_l = 0;
	return (0);
}

#else

int				f_key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx);
	else if (key == KEY_W)
		mlx->keys.w = 1;
	else if (key == KEY_A)
		mlx->keys.a = 1;
	else if (key == KEY_S)
		mlx->keys.s = 1;
	else if (key == KEY_D)
		mlx->keys.d = 1;
	else if (key == KEY_LEFT)
		mlx->keys.left = 1;
	else if (key == KEY_RIGHT)
		mlx->keys.right = 1;
	return (0);
}

int				f_key_release(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->keys.w = 0;
	else if (key == KEY_A)
		mlx->keys.a = 0;
	else if (key == KEY_S)
		mlx->keys.s = 0;
	else if (key == KEY_D)
		mlx->keys.d = 0;
	else if (key == KEY_LEFT)
		mlx->keys.left = 0;
	else if (key == KEY_RIGHT)
		mlx->keys.right = 0;
	return (0);
}

#endif
