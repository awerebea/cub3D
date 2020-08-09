/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:22:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 17:46:08 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "ft_printf.h"
#include <math.h>

static void	f_minimap_init(t_mlx *mlx)
{
	mlx->map.square_side = SQUARE_SIDE;
	mlx->map.edge_shift = mlx->x_win_size / 100;
	mlx->map.map_width = mlx->opts->max_mapline_len;
	mlx->map.map_height = mlx->opts->map_row_index + 1;
	if ((mlx->map.scale = mlx->x_win_size * MINIMAP_MAX_WDTH_FACTOR / \
						mlx->map.map_width) > mlx->y_win_size * \
			MINIMAP_MAX_HGHT_FACTOR / mlx->map.map_height)
		mlx->map.scale = (mlx->y_win_size * MINIMAP_MAX_HGHT_FACTOR) / \
						mlx->map.map_height;
	mlx->map.x = 0;
	mlx->map.y = 0;
	mlx->map.sq_x = 0;
	mlx->map.sq_y = 0;
}

static void	f_player_init(t_mlx *mlx)
{
	mlx->player.fov = FOV_ANGLE * M_PI / 180;
	mlx->player.pos_x = mlx->opts->spawn_point_x * mlx->map.square_side + \
						mlx->map.square_side / 2;
	mlx->player.pos_y = mlx->opts->spawn_point_y * mlx->map.square_side + \
						mlx->map.square_side / 2;
	if (mlx->opts->spawn_orientation == 'N')
		mlx->player.view_angle = M_PI * 3 / 2;
	else if (mlx->opts->spawn_orientation == 'S')
		mlx->player.view_angle = M_PI / 2;
	else if (mlx->opts->spawn_orientation == 'W')
		mlx->player.view_angle = M_PI;
	else if (mlx->opts->spawn_orientation == 'E')
		mlx->player.view_angle = 0.0;
}

void	f_dir_n_plane_calculation(t_game *game)
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
	game->time_curr = clock();
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

int			f_controls_handling(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		f_close_n_exit(mlx, 1);
	/* if (key == KEY_W)                                                                             */
	/* {                                                                                             */
	/*     if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed; */
	/* }                                                                                             */
	else
		ft_printf("%d\n", key);
	return (0);
}

/* void		f_draw_map_view_sector(t_mlx *mlx)                             */
/* {                                                                    */
/*     int		i;                                                          */
/*     int		x;                                                          */
/*     int		y;                                                          */
/*     float	ray_angle;                                                 */

/*     i = 0;                                                           */
/*     x = mlx->player.pos_x;                                           */
/*     while (i < mlx->x_win_size)                                      */
/*     {                                                                */
/*         ray_angle = mlx->player.view_angle - mlx->player.fov / 2 + \ */
/*                     mlx->player.fov * i / mlx->x_win_size;           */
/*     }                                                                */
/* }                                                                    */

void		f_game(t_mlx *mlx)
{
	t_game		game;

	f_game_init(mlx, &game);
	f_minimap_init(mlx);
	f_player_init(mlx);
	f_raycasting(&game);
	f_draw_minimap(mlx);
	f_draw_player_minimap(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	mlx_key_hook(mlx->win_ptr, f_controls_handling, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, f_close_n_exit, mlx);
	/* f_draw_map_view_sector(mlx); */
}
