/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:10:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/13 19:48:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void		f_sprites_swap_with_next(t_sp *sp)
{
	t_sp	*tmp_n;
	t_sp	*tmp_n_n;
	t_sp	*tmp_p;

	tmp_n = sp->next;
	tmp_n_n = sp->next->next;
	tmp_p = sp->prev;
	sp->next = sp;
	sp = tmp_n;
	tmp_n = sp->prev;
	sp->next = tmp_n;
	sp->prev = tmp_p;
	sp->next->prev = sp;
	sp->next->next = tmp_n_n;
}

void		f_sprites_list_sort_by_dist_desc(t_mlx *mlx)
{
	t_sp	*sp;

	sp = mlx->sp_list;
	/* while (sp) */
	/* { */
		/* while (sp->next) */
		/* { */
			/* if (sp->dist < sp->next->dist) */
				/* f_sprites_swap_with_next(sp); */
		/* } */
		/* sp = sp->next; */
	/* } */
	if (sp->next)
		f_sprites_swap_with_next(sp);
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
	f_sprites_dist_calculating(mlx);
	f_sprites_list_sort_by_dist_desc(mlx);
}
