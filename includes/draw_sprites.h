/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 23:57:50 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/16 01:05:48 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_SPRITES_H

# define DRAW_SPRITES_H

typedef struct	s_sp_vars
{
	float		dist_x;
	float		dist_y;
	float		inv_factor;
	float		transform_x;
	float		transform_y;
	int			scr_x;
	int			vert_offset;
	int			width;
	int			height;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			tex_x;
	int			tex_y;
}				t_sp_vars;

#endif
