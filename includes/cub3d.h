/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/09 15:39:37 by awerebea         ###   ########.fr       */
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

# define MINIMAP_MAX_WDTH_FACTOR 0.3
# define MINIMAP_MAX_HGHT_FACTOR 0.5
# define SQUARE_SIDE 64
# define VRAD 1

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define FOV_ANGLE 66

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
	int			scale;
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
	t_minimap	map;
	t_player	player;
}				t_mlx;

typedef struct	s_game
{
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		time_curr;
	float		time_prev;
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
	float		frame_time;
	char		*fps_text;
	float		move_speed;
	float		rotate_speed;
	t_mlx		*mlx;
}				t_game;

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
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			f_game(t_mlx *mlx);
void			f_draw_background(t_mlx *mlx);
void			f_draw_minimap(t_mlx *mlx);
void			f_draw_player_minimap(t_mlx *mlx);
void			f_raycasting(t_mlx *mlx);

#endif
