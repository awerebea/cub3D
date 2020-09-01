/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_vars_calc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 16:29:32 by awerebea          #+#    #+#             */
/*   Updated: 2020/09/01 09:21:21 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#ifdef BONUS

void	f_sprite_vars_calc_start(t_mlx *mlx, t_sp *sp, t_sp_vars *sp_vars)
{
	sp_vars->dist_x = sp->x - mlx->game.player_x;
	sp_vars->dist_y = sp->y - mlx->game.player_y;
	sp_vars->inv_factor = 1.0 / (mlx->game.plane_x * mlx->game.dir_y - \
			mlx->game.plane_y * mlx->game.dir_x);
	sp_vars->transform_x = sp_vars->inv_factor * (mlx->game.dir_y * \
			sp_vars->dist_x - mlx->game.dir_x * sp_vars->dist_y);
	sp_vars->transform_y = sp_vars->inv_factor * (-mlx->game.plane_y * \
			sp_vars->dist_x + mlx->game.plane_x * sp_vars->dist_y);
	sp_vars->scr_x = (int)((mlx->x_win_size / 2) * (1 + \
			sp_vars->transform_x / sp_vars->transform_y));
	sp_vars->vert_offset = (int)((mlx->y_win_size - mlx->y_win_size / 2 * \
				sqrt(SPRITE_SCALE)) / sp_vars->transform_y);
}

void	f_sprite_vars_calc_finish(t_mlx *mlx, t_sp_vars *sp_vars)
{
	if ((sp_vars->height = (int)((mlx->y_win_size / \
					sp_vars->transform_y) * SPRITE_SCALE)) < 0)
		sp_vars->height *= -1;
	if ((sp_vars->start_y = -sp_vars->height / 2 + mlx->y_win_size * \
						mlx->game.vert_pos_factor + sp_vars->vert_offset) < 0)
		sp_vars->start_y = 0;
	if ((sp_vars->end_y = sp_vars->height / 2 + mlx->y_win_size * \
						mlx->game.vert_pos_factor + sp_vars->vert_offset) >= \
						mlx->y_win_size)
		sp_vars->end_y = mlx->y_win_size - 1;
	if ((sp_vars->width = (int)((mlx->y_win_size / \
					sp_vars->transform_y) * SPRITE_SCALE)) < 0)
		sp_vars->width *= -1;
	if ((sp_vars->start_x = -sp_vars->width / 2 + sp_vars->scr_x) \
			< 0)
		sp_vars->start_x = 0;
	if ((sp_vars->end_x = sp_vars->width / 2 + \
				sp_vars->scr_x) >= mlx->x_win_size)
		sp_vars->end_x = mlx->x_win_size - 1;
}

#else

void	f_sprite_vars_calc_start(t_mlx *mlx, t_sp *sp, t_sp_vars *sp_vars)
{
	sp_vars->dist_x = sp->x - mlx->game.player_x;
	sp_vars->dist_y = sp->y - mlx->game.player_y;
	sp_vars->inv_factor = 1.0 / (mlx->game.plane_x * mlx->game.dir_y - \
			mlx->game.plane_y * mlx->game.dir_x);
	sp_vars->transform_x = sp_vars->inv_factor * (mlx->game.dir_y * \
			sp_vars->dist_x - mlx->game.dir_x * sp_vars->dist_y);
	sp_vars->transform_y = sp_vars->inv_factor * (-mlx->game.plane_y * \
			sp_vars->dist_x + mlx->game.plane_x * sp_vars->dist_y);
	sp_vars->scr_x = (int)((mlx->x_win_size / 2) * (1 + \
			sp_vars->transform_x / sp_vars->transform_y));
	sp_vars->vert_offset = (int)((mlx->y_win_size - mlx->y_win_size / 2 * \
				sqrt(SPRITE_SCALE)) / sp_vars->transform_y);
}

void	f_sprite_vars_calc_finish(t_mlx *mlx, t_sp_vars *sp_vars)
{
	if ((sp_vars->height = (int)((mlx->y_win_size / \
					sp_vars->transform_y) * SPRITE_SCALE)) < 0)
		sp_vars->height *= -1;
	if ((sp_vars->start_y = -sp_vars->height / 2 + mlx->y_win_size \
		/ 2 + sp_vars->vert_offset) < 0)
		sp_vars->start_y = 0;
	if ((sp_vars->end_y = sp_vars->height / 2 + mlx->y_win_size / \
		2 + sp_vars->vert_offset) >= mlx->y_win_size)
		sp_vars->end_y = mlx->y_win_size - 1;
	if ((sp_vars->width = (int)((mlx->y_win_size / \
					sp_vars->transform_y) * SPRITE_SCALE)) < 0)
		sp_vars->width *= -1;
	if ((sp_vars->start_x = -sp_vars->width / 2 + sp_vars->scr_x) \
			< 0)
		sp_vars->start_x = 0;
	if ((sp_vars->end_x = sp_vars->width / 2 + \
				sp_vars->scr_x) >= mlx->x_win_size)
		sp_vars->end_x = mlx->x_win_size - 1;
}

#endif
