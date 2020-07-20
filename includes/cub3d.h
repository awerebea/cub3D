/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:12:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/20 00:32:54 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef	struct	s_sdf
{
	int			screenshot;
	int			x_render_size;
	int			y_render_size;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	char		*sprite_texture_path;
	int			floor_colour;
	int			ceiling_colour;
	int			spawn_point;
	int			line_count;
	int			max_length;
}				t_sdf;

int				f_check_args(int argc, char **argv, t_sdf *opts);
int				f_exit(int errcode);
int				f_pars_desc_file(char *map_file, t_sdf *opts);
int				f_pars_line(char *line, t_sdf *opts);
void			f_print_error_1_4(int errcode);

#endif
