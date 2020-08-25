/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_part.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:11:21 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/25 23:27:46 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PART_H

# define BONUS_PART_H

typedef	struct	s_sdf
{
	int			x_win_size;
	int			y_win_size;
	char		*no_tex;
	char		*so_tex;
	char		*we_tex;
	char		*ea_tex;
	char		*sp_tex;
	char		*fl_tex;
	char		*ce_tex;
	int			gnl_ret;
	int			screenshot;
	int			pars_map_started;
	int			max_mapline_len;
	int			prior_spaces_mapline;
	int			errcode;
	char		*err_str;
	char		**map_array;
	char		*map_line;
	int			map_row_index;
	int			spawn_point_x;
	int			spawn_point_y;
	char		spawn_orientation;
}				t_sdf;

typedef struct	s_minimap
{
	int			x;
	int			y;
	int			sq_x;
	int			sq_y;
	int			map_width;
	int			map_height;
	int			sq_side;
	int			edge_shift;
}				t_minimap;

typedef struct	s_player
{
	int			pos_x;
	int			pos_y;
	float		view_angle;
	float		fov;
}				t_player;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			x_win_size;
	int			y_win_size;
	t_sdf		*opts;
	t_img		img;
	t_img		no_tex;
	t_img		so_tex;
	t_img		we_tex;
	t_img		ea_tex;
	t_img		sp_tex;
	t_img		fl_tex;
	t_img		ce_tex;
	t_minimap	map;
	t_player	player;
	t_game		game;
	t_sp		*sp_list;
	t_keys		key_flags;
	int			errcode;
}				t_mlx;

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

int				f_pars_floor_texture(char *line, int i, t_sdf *opts);
int				f_pars_ceiling_texture(char *line, int i, t_sdf *opts);
void			f_draw_textured_background(t_mlx *mlx);
void			f_minimap_init(t_mlx *mlx);
void			f_player_pos_init(t_mlx *mlx);
void			f_draw_minimap(t_mlx *mlx);
int				f_add_shade(int color, float shade);

#endif
