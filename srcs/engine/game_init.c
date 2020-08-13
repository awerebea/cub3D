/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:22:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/13 21:12:00 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include <math.h>

static void	f_key_flags_init(t_mlx *mlx)
{
	mlx->key_flags.w = 0;
	mlx->key_flags.a = 0;
	mlx->key_flags.s = 0;
	mlx->key_flags.d = 0;
	mlx->key_flags.left = 0;
	mlx->key_flags.right = 0;
}

static void	f_dir_n_plane_calculation(t_mlx *mlx)
{
	mlx->game.dir_x = 0;
	mlx->game.dir_y = 0;
	mlx->game.plane_x = 0;
	mlx->game.plane_y = 0;
	if (mlx->opts->spawn_orientation == 'N')
	{
		mlx->game.dir_y = -1;
		mlx->game.plane_x = tan(M_PI * FOV_ANGLE / 360);
	}
	else if (mlx->opts->spawn_orientation == 'S')
	{
		mlx->game.dir_y = 1;
		mlx->game.plane_x = -tan(M_PI * FOV_ANGLE / 360);
	}
	else if (mlx->opts->spawn_orientation == 'W')
	{
		mlx->game.dir_x = -1;
		mlx->game.plane_y = -tan(M_PI * FOV_ANGLE / 360);
	}
	else if (mlx->opts->spawn_orientation == 'E')
	{
		mlx->game.dir_x = 1;
		mlx->game.plane_y = tan(M_PI * FOV_ANGLE / 360);
	}
}

int			f_game_init(t_mlx *mlx)
{
	mlx->game.player_x = (float)mlx->opts->spawn_point_x + 0.5;
	mlx->game.player_y = (float)mlx->opts->spawn_point_y + 0.5;
	f_dir_n_plane_calculation(mlx);
	mlx->game.delta_dist_x = 0;
	mlx->game.delta_dist_y = 0;
	mlx->game.move_speed = MOVE_SPEED;
	mlx->game.rot_speed = ROTATE_SPEED * M_PI / 180;
	mlx->game.sp_count = 0;
	if (!(mlx->game.wall_dist_arr = (float*)malloc(sizeof(float) * \
					mlx->x_win_size)))
		return (mlx->errcode = 200);
	f_key_flags_init(mlx);
	return (0);
}
