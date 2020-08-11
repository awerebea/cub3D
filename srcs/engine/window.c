/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/11 16:18:53 by awerebea         ###   ########.fr       */
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

static int	f_get_data_addr_for_textures(t_mlx *mlx)
{
	if (!(mlx->north_tex.addr = mlx_get_data_addr(mlx->north_tex.img_ptr, \
			&mlx->north_tex.bits_per_pix, &mlx->north_tex.line_len, \
			&mlx->north_tex.endian)))
		return (403);
	if (!(mlx->south_tex.addr = mlx_get_data_addr(mlx->south_tex.img_ptr, \
			&mlx->south_tex.bits_per_pix, &mlx->south_tex.line_len, \
			&mlx->south_tex.endian)))
		return (403);
	if (!(mlx->west_tex.addr = mlx_get_data_addr(mlx->west_tex.img_ptr, \
			&mlx->west_tex.bits_per_pix, &mlx->west_tex.line_len, \
			&mlx->west_tex.endian)))
		return (403);
	if (!(mlx->east_tex.addr = mlx_get_data_addr(mlx->east_tex.img_ptr, \
			&mlx->east_tex.bits_per_pix, &mlx->east_tex.line_len, \
			&mlx->east_tex.endian)))
		return (403);
	if (!(mlx->sprite_tex.addr = mlx_get_data_addr(mlx->sprite_tex.img_ptr, \
			&mlx->sprite_tex.bits_per_pix, &mlx->sprite_tex.line_len, \
			&mlx->sprite_tex.endian)))
		return (403);
	return (0);
}

static int	f_textures_init_from_xmp(t_mlx *mlx)
{
	if (!(mlx->north_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->north_texture_path, &mlx->north_tex.width, \
		&mlx->north_tex.height)))
		return (mlx->opts->err_string = ft_strdup("NO")) ? 410 : 200;
	if (!(mlx->south_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->south_texture_path, &mlx->south_tex.width, \
		&mlx->south_tex.height)))
		return (mlx->opts->err_string = ft_strdup("SO")) ? 410 : 200;
	if (!(mlx->west_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->west_texture_path, &mlx->west_tex.width, \
		&mlx->west_tex.height)))
		return (mlx->opts->err_string = ft_strdup("WE")) ? 410 : 200;
	if (!(mlx->east_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->east_texture_path, &mlx->east_tex.width, \
		&mlx->east_tex.height)))
		return (mlx->opts->err_string = ft_strdup("EA")) ? 410 : 200;
	if (!(mlx->sprite_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->sprite_texture_path, &mlx->sprite_tex.width, \
		&mlx->sprite_tex.height)))
		return (mlx->opts->err_string = ft_strdup("S")) ? 410 : 200;
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

int			f_window(t_sdf *opts)
{
	int		errcode;
	t_mlx	mlx;

	if ((errcode = f_window_n_images_init(&mlx, opts)))
		return (errcode);
	f_game(&mlx);
	/* mlx_string_put(mlx.mlx_ptr, mlx.win_ptr, mlx.x_win_size - \           */
	/*         mlx.map.edge_shift * 5, mlx.map.edge_shift, 0xFFFFFF, "FPS"); */
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
