/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:36:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 12:58:33 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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
	game->line_start = -game->line_height / 2 + game->mlx->y_win_size / 2;
	if (game->line_start < 0)
		game->line_start = 0;
	game->line_end = game->line_height / 2 + game->mlx->y_win_size / 2;
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
		game->wall_dist = (float)(game->map_x - game->player_x + (1 - game->step_x) \
				/ 2) / game->ray_dir_x;
	else
		game->wall_dist = (float)(game->map_y - game->player_y + (1 - game->step_y) \
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

static void	f_dir_n_plane_calculation(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0;
	if (game->mlx->opts->spawn_orientation == 'N')
	{
		game->dir_y = -1;
		game->plane_x = tan(M_PI * FOV_ANGLE / 360);
	}
	else if (game->mlx->opts->spawn_orientation == 'S')
	{
		game->dir_y = 1;
		game->plane_x = -tan(M_PI * FOV_ANGLE / 360);
	}
	else if (game->mlx->opts->spawn_orientation == 'W')
	{
		game->dir_x = -1;
		game->plane_y = -tan(M_PI * FOV_ANGLE / 360);
	}
	else if (game->mlx->opts->spawn_orientation == 'E')
	{
		game->dir_x = 1;
		game->plane_y = tan(M_PI * FOV_ANGLE / 360);
	}
}

void		f_game_init(t_mlx *mlx, t_game *game)
{
	game->player_x = (float)mlx->opts->spawn_point_x + 0.5;
	game->player_y = (float)mlx->opts->spawn_point_y + 0.5;
	game->mlx = mlx;
	f_dir_n_plane_calculation(game);
	game->time_curr = 0;
	game->time_prev = 0;
	/* game->hit = 0;         */
	/* game->wall_dist = 0;   */
	/* game->wall_side = 0;   */
	/* game->step_x = 0;      */
	/* game->step_y = 0;      */
	/* game->camera_x = 0;    */
	/* game->ray_dir_x = 0;   */
	/* game->ray_dir_y = 0;   */
	/* game->side_dist_x = 0; */
	/* game->side_dist_y = 0; */
	game->delta_dist_x = 0;
	game->delta_dist_y = 0;
}

void		f_raycasting(t_mlx *mlx)
{
	int			x;
	t_game		game;

	f_game_init(mlx, &game);
	x = 0;
	while (x < mlx->x_win_size)
	{
		game.camera_x = 2 * x / (float)mlx->x_win_size - 1;
		game.ray_dir_x = game.dir_x + game.plane_x * game.camera_x;
		game.ray_dir_y = game.dir_y + game.plane_y * game.camera_x;
		if (!game.ray_dir_y)
			game.delta_dist_x = 0;
		else
			game.delta_dist_x = (!game.ray_dir_x) ? 1 : fabs(1 / game.ray_dir_x);
		if (!game.ray_dir_x)
			game.delta_dist_y = 0;
		else
			game.delta_dist_y = (!game.ray_dir_y) ? 1 : fabs(1 / game.ray_dir_y);
		game.map_x = (int)game.player_x;
		game.map_y = (int)game.player_y;
		f_step_n_side_dist_calculation(&game);
		f_check_wall_hit_n_wall_dist_calculation(&game);
		f_vert_line_calculation(&game);
		f_draw_vert_line(&game, x);
		x++;
	}
}
