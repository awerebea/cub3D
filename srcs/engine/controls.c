/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:08:19 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/11 00:44:12 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"

static void	f_keys_w_s(int key, t_mlx *mlx)
{
	if (key == KEY_W)
	{
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
		[(int)(mlx->game.player_x + mlx->game.dir_x * mlx->game.move_speed)]))
			mlx->game.player_x += mlx->game.dir_x * mlx->game.move_speed;
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
		+ mlx->game.dir_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
			mlx->game.player_y += mlx->game.dir_y * mlx->game.move_speed;
	}
	if (key == KEY_S)
	{
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
		[(int)(mlx->game.player_x - mlx->game.dir_x * mlx->game.move_speed)]))
			mlx->game.player_x -= mlx->game.dir_x * mlx->game.move_speed;
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
		- mlx->game.dir_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
			mlx->game.player_y -= mlx->game.dir_y * mlx->game.move_speed;
	}
}

static void	f_keys_a_left(int key, t_mlx *mlx)
{
	if (key == KEY_A)
	{
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
		[(int)(mlx->game.player_x - mlx->game.plane_x * mlx->game.move_speed)]))
			mlx->game.player_x -= mlx->game.plane_x * mlx->game.move_speed;
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
		- mlx->game.plane_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
			mlx->game.player_y -= mlx->game.plane_y * mlx->game.move_speed;
	}
	if (key == KEY_LEFT)
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
}

static void	f_keys_d_right(int key, t_mlx *mlx)
{
	if (key == KEY_D)
	{
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)mlx->game.player_y]\
		[(int)(mlx->game.player_x + mlx->game.plane_x * mlx->game.move_speed)]))
			mlx->game.player_x += mlx->game.plane_x * mlx->game.move_speed;
		if (ft_strchr("0NSWE", mlx->opts->map_array[(int)(mlx->game.player_y \
		+ mlx->game.plane_y * mlx->game.move_speed)][(int)mlx->game.player_x]))
			mlx->game.player_y += mlx->game.plane_y * mlx->game.move_speed;
	}
	if (key == KEY_RIGHT)
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
}

int			f_controls_handling(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx, 1);
	else if (key == KEY_W || key == KEY_S)
		f_keys_w_s(key, mlx);
	else if (key == KEY_A || key == KEY_LEFT)
		f_keys_a_left(key, mlx);
	else if (key == KEY_D || key == KEY_RIGHT)
		f_keys_d_right(key, mlx);
	else
		ft_printf("%d\n", key);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_win_size, \
			mlx->y_win_size)))
		return (402);
	if (!(mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
			&mlx->img.bits_per_pix, &mlx->img.line_len, &mlx->img.endian)))
		return (403);
	f_draw_background(mlx);
	f_raycasting(mlx);
	f_draw_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}
