/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/12 15:23:49 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "ft_printf.h"

static int	f_get_data_addr_for_textures(t_mlx *mlx)
{
	if (!(mlx->no_tex.addr = mlx_get_data_addr(mlx->no_tex.img_ptr, \
		&mlx->no_tex.bits_per_pix, &mlx->no_tex.line_len, &mlx->no_tex.endian)))
		return (403);
	if (!(mlx->so_tex.addr = mlx_get_data_addr(mlx->so_tex.img_ptr, \
		&mlx->so_tex.bits_per_pix, &mlx->so_tex.line_len, &mlx->so_tex.endian)))
		return (403);
	if (!(mlx->we_tex.addr = mlx_get_data_addr(mlx->we_tex.img_ptr, \
		&mlx->we_tex.bits_per_pix, &mlx->we_tex.line_len, &mlx->we_tex.endian)))
		return (403);
	if (!(mlx->ea_tex.addr = mlx_get_data_addr(mlx->ea_tex.img_ptr, \
		&mlx->ea_tex.bits_per_pix, &mlx->ea_tex.line_len, &mlx->ea_tex.endian)))
		return (403);
	if (!(mlx->sp_tex.addr = mlx_get_data_addr(mlx->sp_tex.img_ptr, \
		&mlx->sp_tex.bits_per_pix, &mlx->sp_tex.line_len, &mlx->sp_tex.endian)))
		return (403);
	return (0);
}

static int	f_textures_init_from_xmp(t_mlx *mlx)
{
	if (!(mlx->no_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->no_tex, &mlx->no_tex.width, &mlx->no_tex.height)))
		return (mlx->opts->err_str = ft_strdup("NO")) ? 410 : 200;
	if (!(mlx->so_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->so_tex, &mlx->so_tex.width, &mlx->so_tex.height)))
		return (mlx->opts->err_str = ft_strdup("SO")) ? 410 : 200;
	if (!(mlx->we_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->we_tex, &mlx->we_tex.width, &mlx->we_tex.height)))
		return (mlx->opts->err_str = ft_strdup("WE")) ? 410 : 200;
	if (!(mlx->ea_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->ea_tex, &mlx->ea_tex.width, &mlx->ea_tex.height)))
		return (mlx->opts->err_str = ft_strdup("EA")) ? 410 : 200;
	if (!(mlx->sp_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->sp_tex, &mlx->sp_tex.width, &mlx->sp_tex.height)))
		return (mlx->opts->err_str = ft_strdup("S")) ? 410 : 200;
	return (f_get_data_addr_for_textures(mlx));
}

static int	f_window_n_images_init(t_mlx *mlx, t_sdf *opts)
{
	mlx->opts = opts;
	mlx->win_ptr = NULL;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (400);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->x_win_size, &mlx->y_win_size);
	if (mlx->x_win_size > opts->x_win_size)
		mlx->x_win_size = opts->x_win_size;
	if (mlx->y_win_size > opts->y_win_size)
		mlx->y_win_size = opts->y_win_size;
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->x_win_size, \
		mlx->y_win_size, "cub3D")))
		return (401);
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian)))
		return (403);
	return (f_textures_init_from_xmp(mlx));
}

void		f_window(t_sdf *opts)
{
	t_mlx	mlx;

	mlx.errcode = 0;
	if ((mlx.errcode = f_window_n_images_init(&mlx, opts)))
		f_close_n_exit(&mlx);
	f_game(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
