/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:10:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/15 12:42:29 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void		f_sprites_swap_with_next(t_sp *sp)
{
	float	tmp_data;;

	tmp_data = (float)sp->next->id;
	sp->next->id = sp->id;
	sp->id = (int)tmp_data;
	tmp_data = sp->next->x;
	sp->next->x = sp->x;
	sp->x = tmp_data;
	tmp_data = sp->next->y;
	sp->next->y = sp->y;
	sp->y = tmp_data;
	tmp_data = sp->next->dist;
	sp->next->dist = sp->dist;
	sp->dist = tmp_data;
}

void		f_sprites_list_sort_by_dist_desc(t_mlx *mlx)
{
	t_sp	*sp;
	int		swap_flag;

	sp = mlx->sp_list;
	swap_flag = 1;
	while (swap_flag)
	{
		swap_flag = 0;
		while (sp->next)
		{
			if (sp->dist < sp->next->dist)
			{
				f_sprites_swap_with_next(sp);
				swap_flag = 1;
			}
			sp = sp->next;
		}
		sp = mlx->sp_list;
	}
}

void		f_sprites_dist_calculating(t_mlx *mlx)
{
	t_sp	*sp;

	sp = mlx->sp_list;
	while (sp)
	{
		sp->dist = sqrt(pow(mlx->game.player_x - sp->x, 2) + \
						pow(mlx->game.player_y - sp->y, 2));
		sp = sp->next;
	}
}

void		f_sprites_handling(t_mlx *mlx)
{
	t_sp	*sp;
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	int		d;
	int		color;

	f_sprites_init(mlx);
	f_sprites_dist_calculating(mlx);
	f_sprites_list_sort_by_dist_desc(mlx);
	sp = mlx->sp_list;
	while (sp)
	{
		mlx->game.sp_dist_x = sp->x - mlx->game.player_x;
		mlx->game.sp_dist_y = sp->y - mlx->game.player_y;
		mlx->game.inv_factor = 1.0 / (mlx->game.plane_x * mlx->game.dir_y - \
				mlx->game.plane_y *  mlx->game.dir_x);
		mlx->game.transform_x = mlx->game.inv_factor * (mlx->game.dir_y * \
				sp->x - mlx->game.dir_x * sp->y);
		mlx->game.transform_y = mlx->game.inv_factor * (-mlx->game.plane_y * \
				sp->x + mlx->game.plane_x * sp->y);
		mlx->game.sp_scr_x = (int)((mlx->x_win_size / 2) * (1 + \
				mlx->game.transform_x / mlx->game.transform_y));
		if ((mlx->game.sp_height = (int)(mlx->y_win_size / \
						mlx->game.transform_y)) < 0)
			mlx->game.sp_height *= -1;
		if ((mlx->game.sp_start_y = -mlx->game.sp_height / 2 + \
					mlx->y_win_size / 2) < 0)
			mlx->game.sp_start_y = 0;
		if ((mlx->game.sp_end_y = mlx->game.sp_height / 2 + \
					mlx->y_win_size / 2) < 0)
			mlx->game.sp_end_y = mlx->y_win_size - 1;
		if ((mlx->game.sp_width = (int)(mlx->y_win_size / \
						mlx->game.transform_y)) < 0)
			mlx->game.sp_width *= -1;
		if ((mlx->game.sp_start_x = -mlx->game.sp_width / 2 + \
					mlx->game.sp_scr_x) < 0)
			mlx->game.sp_start_x = 0;
		if ((mlx->game.sp_end_x = mlx->game.sp_width / 2 + \
					mlx->game.sp_scr_x) < 0)
			mlx->game.sp_end_x = mlx->x_win_size - 1;
		x = mlx->game.sp_start_x;
		while (x < mlx->game.sp_end_x)
		{
			tex_x = (int)(256 * (x - (-mlx->game.sp_width / 2 + \
				mlx->game.sp_scr_x)) * mlx->sp_tex.width / mlx->game.sp_width);
			if (mlx->game.transform_y > 0 && x > 0 && x < mlx->x_win_size && \
					mlx->game.transform_y < mlx->game.wall_dist_arr[x])
			{
				y = mlx->game.sp_start_y;
				while (y < mlx->game.sp_end_y)
				{
					d = y * 256 - mlx->y_win_size * 128 + mlx->game.sp_height \
						* 128;
					tex_y = ((d * mlx->sp_tex.height) / mlx->game.sp_height) \
							/ 256;
					color = *(int*)(mlx->sp_tex.addr + ((tex_x + (tex_y * \
						mlx->sp_tex.width)) * (mlx->sp_tex.bits_per_pix / 8)));
					/* color = 0x00155155; */
					if (color & 0x00FFFFFF)
						my_mlx_pixel_put(&mlx->img, x, y, color);
					y++;
				}
			}
			x++;
		}
		sp = sp->next;
	}
}
