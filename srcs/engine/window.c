/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/02 15:22:20 by awerebea         ###   ########.fr       */
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
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->x_win_size, \
		mlx->y_win_size, "cub3D")))
		return (401);
	return (0);
}

static int	f_image_init(t_mlx *mlx, t_img *img)
{
	if (!(img->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(img->addr = mlx_get_data_addr(img->img_ptr, \
			&img->bits_per_pix, &img->line_len, &img->endian)))
		return (403);
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
	t_img	img;

	if ((errcode = f_window_init(&mlx, opts)))
		return (errcode);
	if ((errcode = f_image_init(&mlx, &img)))
		return (errcode);
	f_draw_background(&mlx, &img);
	f_draw_minimap(&mlx, &img);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img_ptr, 0, 0);
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, f_close_n_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
