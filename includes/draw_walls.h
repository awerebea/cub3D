/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:29:27 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/16 01:33:16 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_WALLS_H

# define DRAW_WALLS_H

typedef struct	s_wall_vars
{
	int			map_x;
	int			map_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	int			step_x;
	int			step_y;
	float		camera_x;
	float		ray_dir_x;
	float		ray_dir_y;
	int			hit;
	float		wall_dist;
	int			wall_side;
	int			line_height;
	int			line_start;
	int			line_end;
	float		wall_x;
	int			tex_x;
	int			tex_y;
	float		tex_pos;
	float		tex_step;
}				t_wall_vars;

void			f_draw_vert_line(t_mlx *mlx, t_wall_vars *w_vars, int x);

#endif
