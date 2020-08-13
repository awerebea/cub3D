/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_list_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 02:04:25 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/13 21:16:15 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static t_sp	*f_sprite_new(t_mlx *mlx, int y, int x, int id)
{
	t_sp	*sp;

	if (!(sp = (t_sp*)malloc(sizeof(t_sp))))
	{
		mlx->errcode = 200;
		f_close_n_exit(mlx);
	}
	sp->id = id;
	sp->x = (float)x + 0.5;
	sp->y = (float)y + 0.5;
	sp->dist = 0.0;
	sp->prev = NULL;
	sp->next = NULL;
	return (sp);
}

static void	f_sprite_add_front(t_mlx *mlx, t_sp *sp)
{
	t_sp	*new_sp;

	if (mlx->sp_list && sp)
	{
		new_sp = sp;
		new_sp->next = mlx->sp_list;
		new_sp->next->prev = new_sp;
		mlx->sp_list = new_sp;
	}
}

void		f_sprites_init(t_mlx *mlx)
{
	int		i;
	int		j;
	int		k;
	t_sp	*sp;

	k = 0;
	i = 1;
	while (i < mlx->opts->map_row_index)
	{
		j = 1;
		while (mlx->opts->map_array[i][j])
		{
			if (mlx->opts->map_array[i][j] == '2')
			{
				sp = f_sprite_new(mlx, i, j, ++k);
				if (mlx->sp_list)
					f_sprite_add_front(mlx, sp);
				else
					mlx->sp_list = sp;
			}
			j++;
		}
		i++;
	}
	mlx->game.sp_count = k;
}
