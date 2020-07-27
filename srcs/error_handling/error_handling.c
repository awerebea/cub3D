/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:25:29 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/25 16:16:57 by awerebea         ###   ########.fr       */
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
	else if (errcode == 200)
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
opts->x_win_size, opts->y_win_size);
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
	else if (errcode == 341)
		ft_printf("Error\ncode #341: map line #%d: '%s' is invalid.\n\
DESCRIPTION: The map must be composed of only 4 possible characters: \
0 for an empty space, 1 for a wall, 2 for an item and N,S,E or W for the \
player's start position and spawning orientation. Also it CAN be the space \
symbol (' '), BUT ONLY for free space outside of the walls area.\nAnd finally: \
the map must be closed/surrounded by walls.\n", opts->map_row_index + 1, \
opts->err_string);
}

static void	f_error_opts_3(int errcode, t_sdf *opts)
{
	(void)opts;
	if (errcode == 342)
		ft_printf("Error\ncode #342: the spawn point is found on the map more \
than once.\n");
	else if (errcode == 343)
		ft_printf("Error\ncode #343: the spawn point was not found on the \
map.\n");
	else if (errcode == 344)
		ft_printf("Error\ncode #344: the map was not found in the scene \
description file.\n");
	else if (errcode == 345)
		ft_printf("Error\ncode #345: invalid first map line: '%s'.\n\
DESCRIPTION: in the first line of the map there can be no characters other \
than 1 and a space (' ') (the map must be closed/surrounded by walls).\n", \
opts->err_string);
	else if (errcode == 346)
		ft_printf("Error\ncode #346: map column #%s is invalid.\nDESCRIPTION: \
the map must be closed/surrounded by walls.\n", \
opts->err_string);
}

void		f_print_err(int errcode, t_sdf *opts)
{
	if (errcode < 300)
		f_error_arguments(errcode, opts);
	else if (errcode < 320)
		f_error_opts_1(errcode, opts);
	else if (errcode < 342)
		f_error_opts_2(errcode, opts);
	else if (errcode < 400)
		f_error_opts_3(errcode, opts);
}
