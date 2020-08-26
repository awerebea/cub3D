/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_common_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:11:21 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 10:45:00 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_COMMON_STRUCTS_H

# define CUB3D_COMMON_STRUCTS_H

typedef struct	s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pix;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_game
{
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		move_speed;
	float		rot_speed;
	float		*wall_dist_arr;
	float		old_dir_x;
	float		old_dir_y;
	float		old_plane_x;
	float		old_plane_y;
}				t_game;

typedef struct	s_sp
{
	int			id;
	float		x;
	float		y;
	float		dist;
	struct s_sp	*prev;
	struct s_sp	*next;
}				t_sp;

typedef struct	s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

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

#endif
