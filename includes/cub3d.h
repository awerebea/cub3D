/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/21 14:42:42 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MIN_X_RENDER_SIZE 128
# define MIN_Y_RENDER_SIZE 128
# define MAX_X_RENDER_SIZE 7680
# define MAX_Y_RENDER_SIZE 4320

typedef	struct	s_sdf
{
	int			x_render_size;
	int			y_render_size;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	char		*sprite_texture_path;
	int			floor_colour;
	int			ceiling_colour;
	int			screenshot;
	int			spawn_point;
	int			line_count;
	int			max_length;
	int			errcode;
	char		*err_string;
	char		*map_file;
	char		*screenshot_arg;
}				t_sdf;

int				f_check_args(int argc, char **argv, t_sdf *opts);
int				f_cub3d_atoi(char *line, int *i);
int				f_pars_desc_file(char *map_file, t_sdf *opts);
int				f_pars_wall_textures(char *line, int i, t_sdf *opts);
void			f_print_err(int errcode, t_sdf *opts);
void			f_skip_spaces(char *line, int *i);

#endif
