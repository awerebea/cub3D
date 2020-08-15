/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:10:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/15 17:08:38 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	f_sprites_swap_with_next(t_sp *sp)
{
	float	tmp_data;

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

static void	f_sprites_list_sort_by_dist_desc(t_mlx *mlx)
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

static void	f_sprites_dist_calculating(t_mlx *mlx)
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

int			f_sprites_handling(t_mlx *mlx)
{
	t_sp	*sp;

	if (!mlx->sp_list)
		return (0);
	f_sprites_dist_calculating(mlx);
	f_sprites_list_sort_by_dist_desc(mlx);
	sp = mlx->sp_list;
	while (sp)
	{
		f_draw_sprite(mlx, sp);
		sp = sp->next;
	}
	return (0);
}
