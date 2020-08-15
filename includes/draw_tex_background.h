/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_background.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 01:48:15 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/16 01:52:28 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_TEX_BACKGROUND_H

# define DRAW_TEX_BACKGROUND_H

typedef struct	s_fc_vars
{
	int		p;
	int		cell_x;
	int		cell_y;
	int		tex_x;
	int		tex_y;
	float	ray_dir_x_0;
	float	ray_dir_y_0;
	float	ray_dir_x_1;
	float	ray_dir_y_1;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
}				t_fc_vars;

#endif
