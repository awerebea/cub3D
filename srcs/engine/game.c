/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:22:58 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 15:09:31 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
	f_minimap_init(mlx);
	f_player_init(mlx);
	f_raycasting(mlx);
	f_draw_minimap(mlx);
	f_draw_player_minimap(mlx);
	/* f_draw_map_view_sector(mlx); */
}
