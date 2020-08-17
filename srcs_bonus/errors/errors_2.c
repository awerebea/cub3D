/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:36:22 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/17 18:27:59 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"

static void	f_errors_5(int errcode, t_sdf *opts)
{
	if (errcode == 330)
	{
		ft_putstr_fd("Error\ncode #330: invalid format of string with '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' identifier.\nExamples of valid string:\n'", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd(" 128, 0, 255'\n'", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("   25,196,64'\n", 2);
	}
	else if (errcode == 331)
	{
		ft_putstr_fd("Error\ncode #331: invalid RGB color code in string with \
'", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' identifier.\nR,G,B colors must be in range [0,255]: 0, \
255, 255\n", 2);
	}
	else if (errcode == 340)
		ft_putstr_fd("Error\ncode #340: not all parameters were found before \
starting the map.\nDESCRIPTION: all strings with identifiers: 'R', 'NO', 'SO', \
'WE', 'EA', 'S', 'F' or 'C' must be placed before map.\n", 2);
}

static void	f_errors_6(int errcode, t_sdf *opts)
{
	if (errcode == 341)
	{
		ft_putstr_fd("Error\ncode #341: map line #", 2);
		ft_putnbr_fd(opts->map_row_index + 1, 2);
		ft_putstr_fd(": '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' is invalid.\nDESCRIPTION: The map must be composed of \
only 4 possible characters: 0 for an empty space, 1 for a wall, 2 for an item \
and N,S,E or W for the player's start position and spawning orientation. Also \
it CAN be the space symbol (' '), BUT ONLY for free space outside of the walls \
area.\nAnd finally: the map must be closed/surrounded by walls.\n", 2);
	}
	else if (errcode == 342)
		ft_putstr_fd("Error\ncode #342: the spawn point is found on the map \
more than once.\n", 2);
	else if (errcode == 343)
		ft_putstr_fd("Error\ncode #343: the spawn point was not found on the \
map.\n", 2);
	else if (errcode == 344)
		ft_putstr_fd("Error\ncode #344: the map was not found in the scene \
description file.\n", 2);
}

static void	f_errors_7(int errcode, t_sdf *opts)
{
	if (errcode == 345)
	{
		ft_putstr_fd("Error\ncode #345: invalid first map line: '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("'.\nDESCRIPTION: in the first line of the map there can \
be no characters other than 1 and a space (' ') (the map must be \
closed/surrounded by walls).\n", 2);
	}
	else if (errcode == 346)
	{
		ft_putstr_fd("Error\ncode #346: map column #", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd(" is invalid.\nDESCRIPTION: the map must be \
closed/surrounded by walls.\n", 2);
	}
}

static void	f_errors_8(int errcode, t_sdf *opts)
{
	if (errcode == 400)
		ft_putstr_fd("Error\ncode #400: mlx_init() fails to set up the \
connection to the X server.\n", 2);
	else if (errcode == 401)
		ft_putstr_fd("Error\ncode #401: mlx_new_window() fails to create a new \
window.\n", 2);
	else if (errcode == 402)
		ft_putstr_fd("Error\ncode #402: mlx_new_image() fails to create a new \
image.\n", 2);
	else if (errcode == 403)
		ft_putstr_fd("Error\ncode #403: mlx_get_data_addr() fails to get the \
data address of the current image.\n", 2);
	else if (errcode == 410)
	{
		ft_putstr_fd("Error\ncode #410: mlx_xpm_file_to_image() failed while \
reading ", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd(" texture.\n", 2);
	}
}

void		f_print_err_2(int errcode, t_sdf *opts)
{
	if (errcode < 341)
		f_errors_5(errcode, opts);
	else if (errcode < 345)
		f_errors_6(errcode, opts);
	else if (errcode < 400)
		f_errors_7(errcode, opts);
	else
		f_errors_8(errcode, opts);
}
