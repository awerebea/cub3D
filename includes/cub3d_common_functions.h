/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_common_functions.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:11:21 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 16:41:45 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_COMMON_FUNCTIONS_H

# define CUB3D_COMMON_FUNCTIONS_H

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
int				f_opts_init(t_sdf *opts);
int				f_check_opts_completeness(t_sdf *opts);
int				f_pars_desc_file(char *map_file, t_sdf *opts);
int				f_pars_resolution(char *line, int i, t_sdf *opts);
int				f_pars_line(char *line, t_sdf *opts);
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
int				f_textures_init_from_xmp(t_mlx *mlx);
int				f_sprites_handling(t_mlx *mlx);
void			f_sprites_init(t_mlx *mlx);
int				f_draw_all(t_mlx *mlx);
void			f_draw_sprite(t_mlx *mlx, t_sp *sp);
void			f_sprite_vars_calc_start(t_mlx *mlx, t_sp *sp, \
														t_sp_vars *sp_vars);
void			f_sprite_vars_calc_finish(t_mlx *mlx, t_sp_vars *sp_vars);
void			f_draw_vert_line(t_mlx *mlx, t_wall_vars *w_vars, int x);
void			f_screenshot(t_mlx *mlx);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
