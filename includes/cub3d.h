/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/02 12:30:37 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MIN_X_WIN_SIZE 160
# define MIN_Y_WIN_SIZE 120
# define MAX_X_WIN_SIZE 7680
# define MAX_Y_WIN_SIZE 4320

# define MINIMAP_SIZE mlx->x_win_size / 1
/* # define BLOCK_SIZE mlx->map.square_side */

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define BITS_PER_PIXEL 32
# define FOV 66

typedef	struct	s_sdf
{
	int			x_win_size;
	int			y_win_size;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	char		*sprite_texture_path;
	int			floor_color;
	int			ceiling_color;
	int			gnl_ret;
	int			screenshot;
	int			pars_map_started;
	int			spawn_point_x;
	int			spawn_point_y;
	char		spawn_orientation;
	int			max_mapline_len;
	int			prior_spaces_mapline;
	int			errcode;
	char		*err_string;
	int			map_row_index;
	char		**map_array;
	char		*map_line;
}				t_sdf;

typedef struct	s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pix;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_minimap
{
	int			x;
	int			y;
	int			sq_x;
	int			sq_y;
	int			map_width;
	int			map_height;
	int			square_side;
}				t_minimap;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			x_win_size;
	int			y_win_size;
	t_sdf		*opts;
	t_img		img;
	t_minimap	map;
}				t_mlx;

int				f_check_args(int argc, char **argv, t_sdf *opts);
int				f_cub3d_atoi(char *line, int *i);
int				f_exit(int errcode, t_sdf *opts);
int				f_map_array_preparing(t_sdf *opts);
int				f_pars_ceiling_color(char *line, int i, t_sdf *opts);
int				f_pars_desc_file(char *map_file, t_sdf *opts);
int				f_pars_floor_color(char *line, int i, t_sdf *opts);
int				f_pars_map(char *line, t_sdf *opts);
int				f_pars_sprite_texture(char *line, int i, t_sdf *opts);
int				f_pars_wall_textures(char *line, int i, t_sdf *opts);
int				f_window(t_sdf *opts);
void			f_print_err(int errcode, t_sdf *opts);
void			f_error_mlx(int errcode);
void			f_skip_spaces(char *line, int *i);
void			f_draw_background(t_mlx *mlx);
void			f_draw_minimap(t_mlx *mlx);

#endif
