/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:08:19 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 19:39:44 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static void	f_move(t_mlx *mlx, int dir)
{
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
		[(int)(mlx->game.player_x + dir * (mlx->game.dir_x * \
		mlx->game.move_speed))]))
		mlx->game.player_x += dir * (mlx->game.dir_x * mlx->game.move_speed);
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
		+ dir * (mlx->game.dir_y * mlx->game.move_speed))]\
		[(int)mlx->game.player_x]))
		mlx->game.player_y += dir * (mlx->game.dir_y * mlx->game.move_speed);
}

static void	f_strafe(t_mlx *mlx, int dir)
{
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
	[(int)(mlx->game.player_x + dir * (mlx->game.plane_x * \
		mlx->game.move_speed))]))
		mlx->game.player_x += dir * (mlx->game.plane_x * mlx->game.move_speed);
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y + \
		dir * (mlx->game.plane_y * mlx->game.move_speed))]\
		[(int)mlx->game.player_x]))
		mlx->game.player_y += dir * (mlx->game.plane_y * mlx->game.move_speed);
}

static void	f_rotate(t_mlx *mlx, int dir)
{
	mlx->game.old_dir_x = mlx->game.dir_x;
	mlx->game.dir_x = mlx->game.dir_x * cos(dir * mlx->game.rot_speed) - \
						mlx->game.dir_y * sin(dir * mlx->game.rot_speed);
	mlx->game.dir_y = mlx->game.old_dir_x * sin(dir * mlx->game.rot_speed) + \
						mlx->game.dir_y * cos(dir * mlx->game.rot_speed);
	mlx->game.old_plane_x = mlx->game.plane_x;
	mlx->game.plane_x = mlx->game.plane_x * cos(dir * mlx->game.rot_speed) - \
						mlx->game.plane_y * sin(dir * mlx->game.rot_speed);
	mlx->game.plane_y = mlx->game.old_plane_x * sin(dir * mlx->game.rot_speed) \
						+ mlx->game.plane_y * cos(dir * mlx->game.rot_speed);
}

int			f_key_process(t_mlx *mlx)
{
	mlx_do_sync(mlx->mlx_ptr);
	if (mlx->keys.w && !mlx->keys.s)
		f_move(mlx, 1);
	if (mlx->keys.s && !mlx->keys.w)
		f_move(mlx, -1);
	if (mlx->keys.a && !mlx->keys.d)
		f_strafe(mlx, -1);
	if (mlx->keys.d && !mlx->keys.a)
		f_strafe(mlx, 1);
	if (mlx->keys.left && !mlx->keys.right)
		f_rotate(mlx, -1);
	if (mlx->keys.right && !mlx->keys.left)
		f_rotate(mlx, 1);
	return (f_draw_all(mlx));
}
