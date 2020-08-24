/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:00:56 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/24 16:10:22 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

int			f_close_n_exit(t_mlx *mlx)
{
	t_sp		*sp_tmp;

	if (mlx->game.wall_dist_arr)
		free(mlx->game.wall_dist_arr);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->sp_list)
	{
		while (mlx->sp_list)
		{
			sp_tmp = mlx->sp_list->next;
			free(mlx->sp_list);
			mlx->sp_list = sp_tmp;
		}
	}
	free(mlx->mlx_ptr);
	exit(f_exit(mlx->errcode, mlx->opts));
}

void		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char		*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}
