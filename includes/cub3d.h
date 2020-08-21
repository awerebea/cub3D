/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/21 20:12:05 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define MIN_X_WIN_SIZE 100
# define MIN_Y_WIN_SIZE 100

# define MINIMAP_MAX_WDTH_FACTOR 0.3
# define MINIMAP_MAX_HGHT_FACTOR 0.5
# define MINIMAP_MAX_SQUARE_SIDE 20
# define VRAD 1

# define SP_SCALE_X 0.8
# define SP_SCALE_Y 0.8
# define SP_VERT_OFFSET 380

# define FOV_ANGLE 66
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 3

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

int				f_check_args(int argc, char **argv, t_sdf *opts);
void			f_skip_spaces(char *line, int *i);
int				f_cub3d_atoi(char *line, int *i);
int				f_get_a_from_int(int argb);
int				f_get_r_from_int(int argb);
int				f_get_g_from_int(int argb);
int				f_get_b_from_int(int argb);
int				f_get_int_from_argb(int a, int r, int g, int b);
int				f_close_n_exit(t_mlx *mlx);
int				f_exit(int errcode, t_sdf *opts);
void			f_print_err(int errcode, t_sdf *opts);
void			f_print_err_2(int errcode, t_sdf *opts);
int				f_pars_desc_file(char *map_file, t_sdf *opts);
int				f_pars_map(char *line, t_sdf *opts);
int				f_map_array_preparing(t_sdf *opts);
int				f_pars_sprite_texture(char *line, int i, t_sdf *opts);
int				f_pars_wall_textures(char *line, int i, t_sdf *opts);
void			f_game(t_sdf *opts);
int				f_game_init(t_mlx *mlx);
int				f_key_press(int key, t_mlx *mlx);
int				f_key_process(t_mlx *mlx);
int				f_key_release(int key, t_mlx *mlx);
void			f_raycasting(t_mlx *mlx);
int				f_sprites_handling(t_mlx *mlx);
void			f_sprites_init(t_mlx *mlx);
int				f_draw_all(t_mlx *mlx);
void			f_draw_sprite(t_mlx *mlx, t_sp *sp);
void			f_screenshot(t_mlx *mlx);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				f_pars_floor_color(char *line, int i, t_sdf *opts);
int				f_pars_ceiling_color(char *line, int i, t_sdf *opts);
void			f_draw_background(t_mlx *mlx);

#endif
