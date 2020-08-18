/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 22:12:13 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/18 15:31:03 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>

static char	*f_bmp_file_header_generate(t_mlx *mlx)
{
	char	*file_header;
	int		file_size;

	if (!(file_header = malloc(sizeof(char) * 14)))
		return (NULL);
	ft_bzero(file_header, 14);
	file_size = 14 + 40 + mlx->x_win_size * mlx->y_win_size * \
			mlx->img.bits_per_pix / 8;
	file_header[0] = 'B';
	file_header[1] = 'M';
	file_header[2] = (char)(file_size);
	file_header[3] = (char)(file_size >> 8);
	file_header[4] = (char)(file_size >> 16);
	file_header[5] = (char)(file_size >> 24);
	file_header[10] = (char)(14 + 40);
	return (file_header);
}

static char	*f_bmp_info_header_generate(t_mlx *mlx)
{
	char	*info_header;

	if (!(info_header = malloc(sizeof(char) * 40)))
		return (NULL);
	ft_bzero(info_header, 40);
	info_header[0] = (char)(40);
	info_header[4] = (char)(mlx->x_win_size);
	info_header[5] = (char)(mlx->x_win_size >> 8);
	info_header[6] = (char)(mlx->x_win_size >> 16);
	info_header[7] = (char)(mlx->x_win_size >> 24);
	info_header[8] = (char)(-mlx->y_win_size);
	info_header[9] = (char)(-mlx->y_win_size >> 8);
	info_header[10] = (char)(-mlx->y_win_size >> 16);
	info_header[11] = (char)(-mlx->y_win_size >> 24);
	info_header[12] = (char)(1);
	info_header[14] = (char)(mlx->img.bits_per_pix);
	return (info_header);
}

static int	f_bmp_image_write(char *file_header, char *info_header, t_mlx *mlx)
{
	int		fd;

	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT, 664)) < 0)
		return (fd);
	write(fd, file_header, 14);
	write(fd, info_header, 40);
	write(fd, mlx->img.addr, mlx->x_win_size * mlx->y_win_size * \
			mlx->img.bits_per_pix / 8);
	free(file_header);
	free(info_header);
	return (close(fd) < 0) ? 320 : 0;
}

void		f_screenshot(t_mlx *mlx)
{
	char	*file_header;
	char	*info_header;

	draw_textured_background(mlx);
	f_raycasting(mlx);
	f_draw_minimap(mlx);
	if (!(file_header = f_bmp_file_header_generate(mlx)) || \
		!(info_header = f_bmp_info_header_generate(mlx)))
	{
		mlx->errcode = 200;
		if (file_header)
			free(file_header);
		if (info_header)
			free(info_header);
		f_close_n_exit(mlx);
	}
	mlx->errcode = f_bmp_image_write(file_header, info_header, mlx);
	f_close_n_exit(mlx);
}
