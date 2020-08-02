/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/02 12:36:41 by awerebea         ###   ########.fr       */
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
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian);
	return (0);
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
	f_draw_background(&mlx);
	/* f_draw_minimap(&mlx); */
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, f_close_n_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
