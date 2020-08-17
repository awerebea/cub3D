/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 22:12:13 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/18 00:04:37 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

/* static void	f_bitmap_header_generate(mlx) */
/* {                                         */

/* }                                         */

/* static void	f_bitmap_image_generate(mlx)  */
/* {                                         */

/* }                                         */

unsigned char* createBitmapFileHeader (int height, int stride)
{
	int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

	static unsigned char fileHeader[] = {
		0,0,	 /// signature
		0,0,0,0, /// image file size in bytes
		0,0,0,0, /// reserved
		0,0,0,0, /// start of pixel array
	};

	fileHeader[ 0] = (unsigned char)('B');
	fileHeader[ 1] = (unsigned char)('M');
	fileHeader[ 2] = (unsigned char)(fileSize	   );
	fileHeader[ 3] = (unsigned char)(fileSize >>  8);
	fileHeader[ 4] = (unsigned char)(fileSize >> 16);
	fileHeader[ 5] = (unsigned char)(fileSize >> 24);
	fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

	return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
	static unsigned char infoHeader[] = {
		0,0,0,0, /// header size
		0,0,0,0, /// image width
		0,0,0,0, /// image height
		0,0,	 /// number of color planes
		0,0,	 /// bits per pixel
		0,0,0,0, /// compression
		0,0,0,0, /// image size
		0,0,0,0, /// horizontal resolution
		0,0,0,0, /// vertical resolution
		0,0,0,0, /// colors in color table
		0,0,0,0, /// important color count
	};

	infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
	infoHeader[ 4] = (unsigned char)(width		);
	infoHeader[ 5] = (unsigned char)(width >>  8);
	infoHeader[ 6] = (unsigned char)(width >> 16);
	infoHeader[ 7] = (unsigned char)(width >> 24);
	infoHeader[ 8] = (unsigned char)(height		 );
	infoHeader[ 9] = (unsigned char)(height >>	8);
	infoHeader[10] = (unsigned char)(height >> 16);
	infoHeader[11] = (unsigned char)(height >> 24);
	infoHeader[12] = (unsigned char)(1);
	infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

	return infoHeader;
}

void generateBitmapImage (void* image, int height, int width, char* imageFileName)
{
	int widthInBytes = width * BYTES_PER_PIXEL;

	unsigned char padding[3] = {0, 0, 0};
	int paddingSize = (4 - (widthInBytes) % 4) % 4;

	int stride = (widthInBytes) + paddingSize;

	FILE* imageFile = fopen(imageFileName, "wb");

	unsigned char* fileHeader = createBitmapFileHeader(height, stride);
	fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

	unsigned char* infoHeader = createBitmapInfoHeader(height, width);
	fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

	int i;
	for (i = 0; i < height; i++) {
		fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
		fwrite(padding, 1, paddingSize, imageFile);
	}

	fclose(imageFile);
}

static int	f_screenshot_preparing(t_mlx *mlx, t_sdf *opts)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		return (400);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->x_win_size, &mlx->y_win_size);
	if (mlx->x_win_size > opts->x_win_size)
		mlx->x_win_size = opts->x_win_size;
	if (mlx->y_win_size > opts->y_win_size)
		mlx->y_win_size = opts->y_win_size;
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian)))
		return (403);
	return (f_textures_init_from_xmp(mlx));
}

void		f_screenshot(t_mlx *mlx, t_sdf *opts)
{
	/* unsigned char	info_header[44]; */
	/* unsigned char	file_header[10]; */

	/* ft_bzero(info_header, 14);     */
	/* ft_bzero(info_header, 14);     */

	mlx->opts = opts;
	mlx->sp_list = NULL;
	mlx->img.img_ptr = NULL;
	if ((mlx->errcode = f_screenshot_preparing(mlx, opts)))
		f_close_n_exit(mlx);
	draw_textured_background(mlx);
	f_raycasting(mlx);
	f_draw_minimap(mlx);

	generateBitmapImage(mlx->img.img_ptr, mlx->y_win_size, mlx->x_win_size, "screenshot.bmp");

	f_close_n_exit(mlx);
}
