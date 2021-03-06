/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:00:56 by awerebea          #+#    #+#             */
/*   Updated: 2020/09/01 01:05:14 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef BONUS

int			f_add_shade(int color, float shade)
{
	return ((int)(f_get_r_from_int(color) * shade) << 16 | \
			(int)(f_get_g_from_int(color) * shade) << 8 | \
			(int)(f_get_b_from_int(color) * shade));
}

int			f_draw_all(t_mlx *mlx)
{
	mlx->game.time_prev = mlx->game.time;
	mlx->game.time = clock();
	mlx->game.time_frame = (mlx->game.time - mlx->game.time_prev) / 1000000;
	mlx->game.move_speed = mlx->game.time_frame * MOVE_SPEED;
	mlx->game.rot_speed = mlx->game.time_frame * ROTATE_SPEED * M_PI / 180;
	if (mlx->keys.shift_l)
		mlx->game.vert_pos_factor = 0.25;
	else if (mlx->game.jump_in_progress)
	{
		mlx->game.time_jump_curr = (mlx->game.time - \
									mlx->game.time_jump_start) / 1000000;
		if (mlx->game.time_jump_curr > JUMP_TIME)
			mlx->game.jump_in_progress = 0;
		if (mlx->game.time_jump_curr > JUMP_TIME / 2.0)
			mlx->game.time_jump_curr = JUMP_TIME - mlx->game.time_jump_curr;
		mlx->game.vert_pos_factor = 0.5 + 0.4 * (1 - ((JUMP_TIME / 2.0 - \
								mlx->game.time_jump_curr) / (JUMP_TIME / 2.0)));
	}
	else
		mlx->game.vert_pos_factor = 0.5;
	f_draw_textured_background(mlx);
	f_raycasting(mlx);
	f_draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

#else

int			f_draw_all(t_mlx *mlx)
{
	f_draw_background(mlx);
	f_raycasting(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

#endif

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
