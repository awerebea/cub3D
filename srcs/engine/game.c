/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 13:59:12 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

#ifdef BONUS

static int	f_mlx_n_window_n_images_init(t_mlx *mlx, t_sdf *opts)
{
	mlx->opts = opts;
	mlx->win_ptr = NULL;
	mlx->sp_list = NULL;
	mlx->img.img_ptr = NULL;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (400);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->x_win_size, &mlx->y_win_size);
	if (mlx->x_win_size > opts->x_win_size)
		mlx->x_win_size = opts->x_win_size;
	if (mlx->y_win_size > opts->y_win_size)
		mlx->y_win_size = opts->y_win_size;
	if (!opts->screenshot)
	{
		if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size, "cub3D_bonus")))
			return (401);
	}
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian)))
		return (403);
	return (f_textures_init_from_xmp(mlx));
}

void		f_game(t_sdf *opts)
{
	t_mlx	mlx;

	mlx.errcode = 0;
	if ((mlx.errcode = f_mlx_n_window_n_images_init(&mlx, opts)))
		f_close_n_exit(&mlx);
	if (f_game_init(&mlx))
		f_close_n_exit(&mlx);
	f_sprites_init(&mlx);
	f_minimap_init(&mlx);
	if (opts->screenshot)
		f_screenshot(&mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 17, f_close_n_exit, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, f_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L << 1, f_key_release, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, f_key_process, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

#else

static int	f_mlx_n_window_n_images_init(t_mlx *mlx, t_sdf *opts)
{
	mlx->opts = opts;
	mlx->win_ptr = NULL;
	mlx->sp_list = NULL;
	mlx->img.img_ptr = NULL;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (400);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->x_win_size, &mlx->y_win_size);
	if (mlx->x_win_size > opts->x_win_size)
		mlx->x_win_size = opts->x_win_size;
	if (mlx->y_win_size > opts->y_win_size)
		mlx->y_win_size = opts->y_win_size;
	if (!opts->screenshot)
	{
		if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size, "cub3D")))
			return (401);
	}
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian)))
		return (403);
	return (f_textures_init_from_xmp(mlx));
}

void		f_game(t_sdf *opts)
{
	t_mlx	mlx;

	mlx.errcode = 0;
	if ((mlx.errcode = f_mlx_n_window_n_images_init(&mlx, opts)))
		f_close_n_exit(&mlx);
	if (f_game_init(&mlx))
		f_close_n_exit(&mlx);
	f_sprites_init(&mlx);
	if (opts->screenshot)
		f_screenshot(&mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 17, f_close_n_exit, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, f_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L << 1, f_key_release, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, f_key_process, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

#endif
