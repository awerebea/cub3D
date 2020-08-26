/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 22:12:13 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 13:25:29 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>

static char	*f_get_filename(t_mlx *mlx)
{
	int		fd;
	char	*filename;
	char	*name_index;
	char	*tmp;
	int		i;

	i = 2;
	filename = ft_strdup("screenshot.bmp");
	while ((fd = open(filename, O_RDONLY)) > 0)
	{
		free(filename);
		if (close(fd) < 0)
			mlx->errcode = 500;
		if (mlx->errcode)
			return (NULL);
		if (!(name_index = ft_itoa(i++)) || \
			!(tmp = ft_strjoin("screenshot_", name_index)) || \
			!(filename = ft_strjoin(tmp, ".bmp")))
			mlx->errcode = 200;
		free((name_index) ? name_index : NULL);
		free((tmp) ? tmp : NULL);
		if (!filename)
			return (NULL);
	}
	return (filename);
}

static int	f_bmp_image_write(t_mlx *mlx, char *bitmap_file_header, \
															char *dib_header)
{
	int		fd;
	char	*filename;

	if (!(filename = f_get_filename(mlx)))
		return (mlx->errcode);
	if ((fd = open(filename, O_RDWR | O_CREAT, 664)) < 0)
		return (fd);
	write(fd, bitmap_file_header, 14);
	write(fd, dib_header, 40);
	write(fd, mlx->img.addr, mlx->x_win_size * mlx->y_win_size * \
			mlx->img.bits_per_pix / 8);
	free(filename);
	return (close(fd) < 0) ? 320 : 0;
}

static void	f_bmp_headers_generate(t_mlx *mlx, char *bitmap_file_header, \
															char *dib_header)
{
	int		file_size;

	file_size = 14 + 40 + mlx->x_win_size * mlx->y_win_size * \
			mlx->img.bits_per_pix / 8;
	bitmap_file_header[0] = 'B';
	bitmap_file_header[1] = 'M';
	bitmap_file_header[2] = (char)(file_size);
	bitmap_file_header[3] = (char)(file_size >> 8);
	bitmap_file_header[4] = (char)(file_size >> 16);
	bitmap_file_header[5] = (char)(file_size >> 24);
	bitmap_file_header[10] = (char)(14 + 40);
	dib_header[0] = (char)(40);
	dib_header[4] = (char)(mlx->x_win_size);
	dib_header[5] = (char)(mlx->x_win_size >> 8);
	dib_header[6] = (char)(mlx->x_win_size >> 16);
	dib_header[7] = (char)(mlx->x_win_size >> 24);
	dib_header[8] = (char)(-mlx->y_win_size);
	dib_header[9] = (char)(-mlx->y_win_size >> 8);
	dib_header[10] = (char)(-mlx->y_win_size >> 16);
	dib_header[11] = (char)(-mlx->y_win_size >> 24);
	dib_header[12] = (char)(1);
	dib_header[14] = (char)(mlx->img.bits_per_pix);
}

#ifdef BONUS

void		f_screenshot(t_mlx *mlx)
{
	char	bitmap_file_header[14];
	char	dib_header[40];

	ft_bzero(bitmap_file_header, 14);
	ft_bzero(dib_header, 40);
	f_draw_textured_background(mlx);
	f_raycasting(mlx);
	f_draw_minimap(mlx);
	f_bmp_headers_generate(mlx, bitmap_file_header, dib_header);
	mlx->errcode = f_bmp_image_write(mlx, bitmap_file_header, dib_header);
	f_close_n_exit(mlx);
}

#else

void		f_screenshot(t_mlx *mlx)
{
	char	bitmap_file_header[14];
	char	dib_header[40];

	ft_bzero(bitmap_file_header, 14);
	ft_bzero(dib_header, 40);
	f_draw_background(mlx);
	f_raycasting(mlx);
	f_bmp_headers_generate(mlx, bitmap_file_header, dib_header);
	mlx->errcode = f_bmp_image_write(mlx, bitmap_file_header, dib_header);
	f_close_n_exit(mlx);
}

#endif
