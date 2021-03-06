/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:10:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/16 00:04:45 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	f_swap_sprites_data(t_sp *a, t_sp *b)
{
	float	tmp_data;

	tmp_data = (float)b->id;
	b->id = a->id;
	a->id = (int)tmp_data;
	tmp_data = b->x;
	b->x = a->x;
	a->x = tmp_data;
	tmp_data = b->y;
	b->y = a->y;
	a->y = tmp_data;
	tmp_data = b->dist;
	b->dist = a->dist;
	a->dist = tmp_data;
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
				f_swap_sprites_data(sp, sp->next);
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
