/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/12 20:47:03 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define MIN_X_WIN_SIZE 160
# define MIN_Y_WIN_SIZE 120
# define MAX_X_WIN_SIZE 7680
# define MAX_Y_WIN_SIZE 4320

# define MINIMAP_MAX_WDTH_FACTOR 0.3
# define MINIMAP_MAX_HGHT_FACTOR 0.5
# define VRAD 1

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A  0
# define KEY_S  1
# define KEY_D  2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define FOV_ANGLE 66
# define MOVE_SPEED 0.2
# define ROTATE_SPEED 5
# define SHADE_FACTOR 1.1

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
	int			spawn_point_x;
	int			spawn_point_y;
	char		spawn_orientation;
	int			max_mapline_len;
	int			prior_spaces_mapline;
	int			errcode;
	char		*err_str;
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
	int			width;
	int			height;
}				t_img;

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

typedef struct	s_game
{
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		old_dir_x;
	float		old_dir_y;
	float		plane_x;
	float		plane_y;
	float		old_plane_x;
	float		old_plane_y;
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
	float		*wall_dist_arr;
	int			wall_side;
	int			line_height;
	int			line_start;
	int			line_end;
	float		move_speed;
	float		rot_speed;
	float		wall_x;
	int			tex_x;
	int			tex_y;
	float		tex_pos;
	float		tex_step;
}				t_game;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			x_win_size;
	int			y_win_size;
	int			errcode;
	t_sdf		*opts;
	t_img		img;
	t_img		no_tex;
	t_img		so_tex;
	t_img		we_tex;
	t_img		ea_tex;
	t_img		sp_tex;
	t_minimap	map;
	t_player	player;
	t_game		game;
}				t_mlx;

int				f_check_args(int argc, char **argv, t_sdf *opts);
int				f_cub3d_atoi(char *line, int *i);
int				f_get_int_from_argb(int a, int r, int g, int b);
int				f_get_a_from_int(int argb);
int				f_get_r_from_int(int argb);
int				f_get_g_from_int(int argb);
int				f_get_b_from_int(int argb);
int				f_add_shade(int color, float shade);
int				f_exit(int errcode, t_sdf *opts);
int				f_close_n_exit(t_mlx *mlx);
int				f_map_array_preparing(t_sdf *opts);
int				f_pars_ceiling_color(char *line, int i, t_sdf *opts);
int				f_pars_desc_file(char *map_file, t_sdf *opts);
int				f_pars_floor_color(char *line, int i, t_sdf *opts);
int				f_pars_map(char *line, t_sdf *opts);
int				f_pars_sprite_texture(char *line, int i, t_sdf *opts);
int				f_pars_wall_textures(char *line, int i, t_sdf *opts);
void			f_window(t_sdf *opts);
void			f_print_err(int errcode, t_sdf *opts);
void			f_error_mlx(int errcode, t_sdf *opts);
void			f_skip_spaces(char *line, int *i);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			f_game(t_mlx *mlx);
void			f_draw_background(t_mlx *mlx);
void			f_draw_minimap(t_mlx *mlx);
void			f_player_pos_init(t_mlx *mlx);
void			f_draw_player_minimap(t_mlx *mlx);
void			f_raycasting(t_mlx *mlx);
int				f_check_textures_for_valid(t_mlx *mlx);
void			f_draw_vert_line(t_mlx *mlx, int x);
int				f_controls_handling(int key, t_mlx *mlx);

#endif
