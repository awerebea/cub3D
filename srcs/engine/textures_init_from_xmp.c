/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init_from_xmp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 14:01:49 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

#ifdef BONUS

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
	if (!(mlx->fl_tex.addr = mlx_get_data_addr(mlx->fl_tex.img_ptr, \
		&mlx->fl_tex.bits_per_pix, &mlx->fl_tex.line_len, &mlx->fl_tex.endian)))
		return (403);
	if (!(mlx->ce_tex.addr = mlx_get_data_addr(mlx->ce_tex.img_ptr, \
		&mlx->ce_tex.bits_per_pix, &mlx->ce_tex.line_len, &mlx->ce_tex.endian)))
		return (403);
	return (0);
}

int			f_textures_init_from_xmp(t_mlx *mlx)
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
	if (!(mlx->fl_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->fl_tex, &mlx->fl_tex.width, &mlx->fl_tex.height)))
		return (mlx->opts->err_str = ft_strdup("F")) ? 410 : 200;
	if (!(mlx->ce_tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		mlx->opts->ce_tex, &mlx->ce_tex.width, &mlx->ce_tex.height)))
		return (mlx->opts->err_str = ft_strdup("C")) ? 410 : 200;
	return (f_get_data_addr_for_textures(mlx));
}

#else

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

int			f_textures_init_from_xmp(t_mlx *mlx)
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

#endif
