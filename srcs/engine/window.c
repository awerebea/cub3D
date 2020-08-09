/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 19:20:43 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "ft_printf.h"

int			f_close_n_exit(t_mlx *mlx, int window)
{
	if (window == 1)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx->mlx_ptr);
	exit(f_exit(0, mlx->opts));
}

static int	f_window_n_image_init(t_mlx *mlx, t_sdf *opts)
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
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->x_win_size, \
		mlx->y_win_size, "cub3D")))
		return (401);
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian)))
		return (403);
	return (0);
}

int			f_window(t_sdf *opts)
{
	int		errcode;
	t_mlx	mlx;

	if ((errcode = f_window_n_image_init(&mlx, opts)))
		return (errcode);
	f_game(&mlx);
	/* mlx_string_put(mlx.mlx_ptr, mlx.win_ptr, mlx.x_win_size - \           */
	/*         mlx.map.edge_shift * 5, mlx.map.edge_shift, 0xFFFFFF, "FPS"); */
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
