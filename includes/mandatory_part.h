/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_part.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:11:21 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/25 23:12:34 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_PART_H

# define MANDATORY_PART_H

typedef	struct	s_sdf
{
	int			x_win_size;
	int			y_win_size;
	char		*no_tex;
	char		*so_tex;
	char		*we_tex;
	char		*ea_tex;
	char		*sp_tex;
	int			floor_color;
	int			ceiling_color;
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
	t_game		game;
	t_sp		*sp_list;
	t_keys		key_flags;
	int			errcode;
}				t_mlx;

int				f_pars_floor_color(char *line, int i, t_sdf *opts);
int				f_pars_ceiling_color(char *line, int i, t_sdf *opts);
void			f_draw_background(t_mlx *mlx);

#endif
