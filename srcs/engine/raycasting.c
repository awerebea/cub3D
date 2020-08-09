/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:36:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 17:37:43 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "libft.h"
#include "ft_printf.h"

void		f_fps_n_move_n_rotate_speed_calculation(t_game *game)
{
	game->time_prev = game->time_curr;
	game->time_curr = clock();
	game->frame_time = (game->time_curr - game->time_prev) / 1000.0;
	/* ft_printf("%f\n", 1.0 / game->frame_time);               */
	/* game->fps_text = ft_itoa((int)(1.0 / game->frame_time)); */
	/* ft_printf("%s\n", game->fps_text);                       */
	game->move_speed = game->frame_time * 0.5;
	game->rotate_speed = game->frame_time * 0.2;
	ft_printf("move speed: %f\nrotate speed:%f\n", game->move_speed, game->rotate_speed);
}

void		f_draw_vert_line(t_game *game, int x)
{
	int			color;
	int			y;

	y = game->line_start;
	while (y <= game->line_end)
	{
		if (game->wall_side == 0)
			color = 0x224A7B;
		else if (game->wall_side == 1)
			color = 0xFF6524;
		else if (game->wall_side == 2)
			color = 0xA7F192;
		else
			color = 0x888945;
		my_mlx_pixel_put(&game->mlx->img, x, y, color);
		y++;
	}
}

void		f_vert_line_calculation(t_game *game)
{
	game->line_height = (int)(game->mlx->y_win_size / game->wall_dist);
	game->line_start = game->mlx->y_win_size / 2 - game->line_height / 2;
	if (game->line_start < 0)
		game->line_start = 0;
	game->line_end = game->mlx->y_win_size / 2 + game->line_height / 2;
	if (game->line_end >= game->mlx->y_win_size)
		game->line_end = game->mlx->y_win_size - 1;
}

void		f_check_wall_hit_n_wall_dist_calculation(t_game *game)
{
	game->hit = 0;
	while (!game->hit)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			game->map_x += game->step_x;
			game->wall_side = (game->ray_dir_x < 0) ? 2 : 3;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			game->map_y += game->step_y;
			game->wall_side = (game->ray_dir_y < 0) ? 0 : 1;
		}
		if (game->mlx->opts->map_array[game->map_y][game->map_x] != '0')
			game->hit = 1;
	}
	if (game->wall_side > 1)
		game->wall_dist = (game->map_x - game->player_x + (1 - game->step_x) \
				/ 2) / game->ray_dir_x;
	else
		game->wall_dist = (game->map_y - game->player_y + (1 - game->step_y) \
				/ 2) / game->ray_dir_y;
}

static void	f_step_n_side_dist_calculation(t_game *game)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (game->player_x - game->map_x) * game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (1.0 + game->map_x - game->player_x) * \
			game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (game->player_y - game->map_y) * game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (1.0 + game->map_y - game->player_y) * \
			game->delta_dist_y;
	}
}

void		f_raycasting(t_game *game)
{
	int			x;

	x = 0;
	while (x < game->mlx->x_win_size)
	{
		game->camera_x = 2 * x / (float)game->mlx->x_win_size - 1;
		game->ray_dir_x = game->dir_x + game->plane_x * game->camera_x;
		game->ray_dir_y = game->dir_y + game->plane_y * game->camera_x;
		if (!game->ray_dir_y)
			game->delta_dist_x = 0;
		else
			game->delta_dist_x = (!game->ray_dir_x) ? 1 : fabs(1 / game->ray_dir_x);
		if (!game->ray_dir_x)
			game->delta_dist_y = 0;
		else
			game->delta_dist_y = (!game->ray_dir_y) ? 1 : fabs(1 / game->ray_dir_y);
		game->map_x = (int)game->player_x;
		game->map_y = (int)game->player_y;
		f_step_n_side_dist_calculation(game);
		f_check_wall_hit_n_wall_dist_calculation(game);
		f_vert_line_calculation(game);
		f_draw_vert_line(game, x);
		x++;
	}
	f_fps_n_move_n_rotate_speed_calculation(game);
}
