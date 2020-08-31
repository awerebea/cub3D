/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 16:29:32 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/31 23:08:38 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#ifdef BONUS

static void	f_draw_sprite_vert_line(t_mlx *mlx, t_sp_vars *sp_vars, int x, \
																	float shade)
{
	int		y;
	int		d;
	int		color;

	y = sp_vars->start_y;
	while (y < sp_vars->end_y)
	{
		d = (y - sp_vars->vert_offset) * 256 - mlx->y_win_size * \
			(2 * mlx->game.vert_pos_factor) * 128 + sp_vars->height * 128;
		if (d < 0)
			d *= -1;
		sp_vars->tex_y = d * mlx->sp_tex.height / sp_vars->height / 256;
		color = *(int*)(mlx->sp_tex.addr + ((sp_vars->tex_x + \
				(sp_vars->tex_y * mlx->sp_tex.width)) * \
				(mlx->sp_tex.bits_per_pix / 8)));
		if (color & 0x00FFFFFF)
			my_mlx_pixel_put(&mlx->img, x, y, f_add_shade(color, shade));
		y++;
	}
}

void		f_draw_sprite(t_mlx *mlx, t_sp *sp)
{
	int			x;
	float		shade;
	t_sp_vars	sp_vars;

	shade = 1 / (1 + 0.005 * sp->dist + 0.006 * pow(sp->dist, 2));
	f_sprite_vars_calc_start(mlx, sp, &sp_vars);
	f_sprite_vars_calc_finish(mlx, &sp_vars);
	x = sp_vars.start_x;
	while (x < sp_vars.end_x)
	{
		sp_vars.tex_x = (int)(256 * (x - (-sp_vars.width / 2 + \
							sp_vars.scr_x)) * mlx->sp_tex.width / \
							sp_vars.width) / 256;
		if (sp_vars.transform_y > 0 && x > 0 && x < mlx->x_win_size && \
				sp_vars.transform_y < mlx->game.wall_dist_arr[x])
			f_draw_sprite_vert_line(mlx, &sp_vars, x, shade);
		x++;
	}
}

#else

static void	f_draw_sprite_vert_line(t_mlx *mlx, t_sp_vars *sp_vars, int x)
{
	int		y;
	int		d;
	int		color;

	y = sp_vars->start_y;
	while (y < sp_vars->end_y)
	{
		d = (y - sp_vars->vert_offset) * 256 - \
			mlx->y_win_size * 128 + sp_vars->height * 128;
		sp_vars->tex_y = ((d * mlx->sp_tex.height) / sp_vars->height) \
							/ 256;
		color = *(int*)(mlx->sp_tex.addr + ((sp_vars->tex_x + \
				(sp_vars->tex_y * mlx->sp_tex.width)) * \
				(mlx->sp_tex.bits_per_pix / 8)));
		if (color & 0x00FFFFFF)
			my_mlx_pixel_put(&mlx->img, x, y, color);
		y++;
	}
}

void		f_draw_sprite(t_mlx *mlx, t_sp *sp)
{
	int			x;
	t_sp_vars	sp_vars;

	f_sprite_vars_calc_start(mlx, sp, &sp_vars);
	f_sprite_vars_calc_finish(mlx, &sp_vars);
	x = sp_vars.start_x;
	while (x < sp_vars.end_x)
	{
		sp_vars.tex_x = (int)(256 * (x - (-sp_vars.width / 2 + \
							sp_vars.scr_x)) * mlx->sp_tex.width / \
							sp_vars.width) / 256;
		if (sp_vars.transform_y > 0 && x > 0 && x < mlx->x_win_size && \
				sp_vars.transform_y < mlx->game.wall_dist_arr[x])
			f_draw_sprite_vert_line(mlx, &sp_vars, x);
		x++;
	}
}

#endif
