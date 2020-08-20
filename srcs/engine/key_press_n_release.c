/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_n_release.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 14:49:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/20 17:09:23 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		f_key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx);
	else if (key == KEY_W)
		mlx->key_flags.w = 1;
	else if (key == KEY_A)
		mlx->key_flags.a = 1;
	else if (key == KEY_S)
		mlx->key_flags.s = 1;
	else if (key == KEY_D)
		mlx->key_flags.d = 1;
	else if (key == KEY_LEFT)
		mlx->key_flags.left = 1;
	else if (key == KEY_RIGHT)
		mlx->key_flags.right = 1;
	return (0);
}

int		f_key_release(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->key_flags.w = 0;
	if (key == KEY_A)
		mlx->key_flags.a = 0;
	if (key == KEY_S)
		mlx->key_flags.s = 0;
	if (key == KEY_D)
		mlx->key_flags.d = 0;
	if (key == KEY_LEFT)
		mlx->key_flags.left = 0;
	if (key == KEY_RIGHT)
		mlx->key_flags.right = 0;
	return (0);
}
