/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:25:29 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/24 14:50:45 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

static void	f_error_arguments(int errcode, t_sdf *opts)
{
	if (errcode == 100)
		ft_printf("Error\ncode #100: wrong number of arguments.\n\
DESCRIPTION: There can be only one or two arguments. The first argument MUST \
be a '.cub' map-file.\nThe second argument CAN be '--save', \
in this case the 'cub3D' just takes screenshot of spawn scene and quits.\n");
	else if (errcode == 101)
		ft_printf("Error\ncode #101: '%s' - invalid map file or it's \
path (open/close failed).\n", opts->err_string);
	else if (errcode == 102)
		ft_printf("Error\ncode #102: '%s' - invalid map file name or path.\n\
DESCRIPTION: the first argument is always the path to the map file, and it \
must have a name with at least one character and an extension '.cub'.\n", \
opts->err_string);
	else if (errcode == 103)
		ft_printf("Error\ncode #103: '%s' - wrong second argument.\n\
DESCRIPTION: it can be only '--save', in this case the 'cub3D' just takes \
screenshot of spawn scene and quits.\n", opts->err_string);
	else if (errcode == 104)
		ft_printf("Error\ncode #104: parsing the map file with \
'get_next_line' function failed.\n");
}

static void	f_error_systemlibs(int errcode, t_sdf *opts)
{
	(void)opts;
	if (errcode == 200)
		ft_printf("Error\ncode #200: memory allocation failed \
('malloc' function returned 'NULL').\n");
}

static void	f_error_opts_1(int errcode, t_sdf *opts)
{
	if (errcode == 300)
		ft_printf("Error\ncode #300: while parsing the map file, the string \
with invalid identifier was found.\n\
DESCRIPTION: the firsts information in each non-empty string must be \
identifier: 'R', 'NO', 'SO', 'WE', 'EA', 'S', 'F' or 'C' \
(splitted from other data by at least one 'space-symbol').\n");
	else if (errcode == 301)
		ft_printf("Error\ncode #301: string with '%s' identifier occurs more \
than once in the file.\nDESCRIPTION: each options string must be occured only \
once.\n", opts->err_string);
	else if (errcode == 302)
		ft_printf("Error\ncode #302: invalid string while map parsing \
detected:\n'%s'\n", opts->err_string);
	else if (errcode == 303)
		ft_printf("Error\ncode #303: empty string after the map detected.\n\
The map must be at the end of file (remove everything after the map).\n");
	else if (errcode == 310)
		ft_printf("Error\ncode #310: invalid resolution string format.\n\
DESCRIPTION: it must start by 'R' identifier and have only positive integer \
values of X and Y resolution, separated from each other by space-symbol(s).\n\
Examples of valid string:\n'R 1920 1080'\n'R    1024    768'\n");
	else if (errcode == 311)
		ft_printf("Error\ncode #311: '%dx%d'- invalid resolution, it must be \
in a range from '160x120' (QQVGA) to '7680x4320' (8K).\n", \
opts->x_render_size, opts->y_render_size);
}

static void	f_error_opts_2(int errcode, t_sdf *opts)
{
	if (errcode == 320)
		ft_printf("Error\ncode #320: '%s' - invalid texture file or it's \
path (open/close failed).\nCheck that the path to the texture does not start \
with a space symbol and there are no space symbols in the string after \
the texture name.\n", opts->err_string);
	else if (errcode == 330)
		ft_printf("Error\ncode #330: invalid format of string with '%s' \
identifier.\nExamples of valid string:\n'%s 128, 0, 255'\n'%s   25,196,64'\n", \
opts->err_string, opts->err_string, opts->err_string);
	else if (errcode == 331)
		ft_printf("Error\ncode #331: invalid RGB color code in string with \
'%s' identifier.\nR,G,B colors must be in range [0,255]: 0, 255, 255\n", \
opts->err_string);
	else if (errcode == 340)
		ft_printf("Error\ncode #340: not all parameters were found before \
starting the map.\nDESCRIPTION: all strings with identifiers: 'R', 'NO', 'SO', \
'WE', 'EA', 'S', 'F' or 'C' must be placed before map.\n");
}

void		f_print_err(int errcode, t_sdf *opts)
{
	if (errcode < 200)
		f_error_arguments(errcode, opts);
	else if (errcode < 300)
		f_error_systemlibs(errcode, opts);
	else if (errcode < 320)
		f_error_opts_1(errcode, opts);
	else if (errcode < 400)
		f_error_opts_2(errcode, opts);
}
