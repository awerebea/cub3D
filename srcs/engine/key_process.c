/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:08:19 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/13 15:30:58 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include <math.h>

static void	f_move_forward(t_mlx *mlx)
{
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
	[(int)(mlx->game.player_x + mlx->game.dir_x * mlx->game.move_speed)]))
		mlx->game.player_x += mlx->game.dir_x * mlx->game.move_speed;
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
	+ mlx->game.dir_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
		mlx->game.player_y += mlx->game.dir_y * mlx->game.move_speed;
}

static void	f_move_back(t_mlx *mlx)
{
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
	[(int)(mlx->game.player_x - mlx->game.dir_x * mlx->game.move_speed)]))
		mlx->game.player_x -= mlx->game.dir_x * mlx->game.move_speed;
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
	- mlx->game.dir_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
		mlx->game.player_y -= mlx->game.dir_y * mlx->game.move_speed;
}

static void	f_strafe_left(t_mlx *mlx)
{
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
	[(int)(mlx->game.player_x - mlx->game.plane_x * mlx->game.move_speed)]))
		mlx->game.player_x -= mlx->game.plane_x * mlx->game.move_speed;
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
	- mlx->game.plane_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
		mlx->game.player_y -= mlx->game.plane_y * mlx->game.move_speed;
}

static void	f_rotate_left(t_mlx *mlx)
{
	mlx->game.old_dir_x = mlx->game.dir_x;
	mlx->game.dir_x = mlx->game.dir_x * cos(-mlx->game.rot_speed) - \
						mlx->game.dir_y * sin(-mlx->game.rot_speed);
	mlx->game.dir_y = mlx->game.old_dir_x * sin(-mlx->game.rot_speed) + \
						mlx->game.dir_y * cos(-mlx->game.rot_speed);
	mlx->game.old_plane_x = mlx->game.plane_x;
	mlx->game.plane_x = mlx->game.plane_x * cos(-mlx->game.rot_speed) - \
						mlx->game.plane_y * sin(-mlx->game.rot_speed);
	mlx->game.plane_y = mlx->game.old_plane_x * sin(-mlx->game.rot_speed) \
						+ mlx->game.plane_y * cos(-mlx->game.rot_speed);
}

static void	f_strafe_right(t_mlx *mlx)
{
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
	[(int)(mlx->game.player_x + mlx->game.plane_x * mlx->game.move_speed)]))
		mlx->game.player_x += mlx->game.plane_x * mlx->game.move_speed;
	if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
	+ mlx->game.plane_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
		mlx->game.player_y += mlx->game.plane_y * mlx->game.move_speed;
}

static void	f_rotate_right(t_mlx *mlx)
{
	mlx->game.old_dir_x = mlx->game.dir_x;
	mlx->game.dir_x = mlx->game.dir_x * cos(mlx->game.rot_speed) - \
						mlx->game.dir_y * sin(mlx->game.rot_speed);
	mlx->game.dir_y = mlx->game.old_dir_x * sin(mlx->game.rot_speed) + \
						mlx->game.dir_y * cos(mlx->game.rot_speed);
	mlx->game.old_plane_x = mlx->game.plane_x;
	mlx->game.plane_x = mlx->game.plane_x * cos(mlx->game.rot_speed) - \
						mlx->game.plane_y * sin(mlx->game.rot_speed);
	mlx->game.plane_y = mlx->game.old_plane_x * sin(mlx->game.rot_speed) \
						+ mlx->game.plane_y * cos(mlx->game.rot_speed);
}

int			f_key_process(t_mlx *mlx)
{
	if (mlx->key_flags.esc)
		f_close_n_exit(mlx);
	if (mlx->key_flags.w)
		f_move_forward(mlx);
	if (mlx->key_flags.w)
		f_move_back(mlx);
	if (mlx->key_flags.a)
		f_strafe_left(mlx);
	if (mlx->key_flags.a)
		f_strafe_right(mlx);
	if (mlx->key_flags.left)
		f_rotate_left(mlx);
	if (mlx->key_flags.left)
		f_rotate_right(mlx);
	return (f_draw_all(mlx));
}