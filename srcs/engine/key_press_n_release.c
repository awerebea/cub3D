/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_n_release.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:49:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/27 13:13:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_keys.h"

#ifdef BONUS

int		f_key_press(int key, t_mlx *mlx)
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
	return (0);
}

int		f_key_release(int key, t_mlx *mlx)
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

#else

int		f_key_press(int key, t_mlx *mlx)
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

int		f_key_release(int key, t_mlx *mlx)
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
