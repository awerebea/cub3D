/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:25:29 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/17 18:27:53 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "libft.h"
#include <string.h>
#include <errno.h>

static void	f_errors_1(int errcode, t_sdf *opts)
{
	if (errcode == 100)
		ft_putstr_fd("Error\ncode #100: wrong number of arguments.\n\
DESCRIPTION: There can be only one or two arguments. The first argument MUST \
be a '.cub' map-file.\nThe second argument CAN be '--save', \
in this case the 'cub3D' just takes screenshot of spawn scene and quits.\n", 2);
	else if (errcode == 101)
	{
		ft_putstr_fd("Error\ncode #101: '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' - invalid map file or it's path (open/close \
failed).\n", 2);
	}
	else if (errcode == 102)
	{
		ft_putstr_fd("Error\ncode #102: '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' - invalid map file name or path.\n\
DESCRIPTION: the first argument is always the path to the map file, and it \
must have a name with at least one character and an extension '.cub'.\n", 2);
	}
}

static void	f_errors_2(int errcode, t_sdf *opts)
{
	if (errcode == 103)
	{
		ft_putstr_fd("Error\ncode #103: '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' - wrong second argument.\n\
DESCRIPTION: it can be only '--save', in this case the 'cub3D' just takes \
screenshot of spawn scene and quits.\n", 2);
	}
	else if (errcode == 104)
		ft_putstr_fd("Error\ncode #104: parsing the map file with \
'get_next_line' function failed.\n", 2);
	else if (errcode == 200)
		ft_putstr_fd("Error\ncode #200: memory allocation failed \
('malloc' function returned 'NULL').\n", 2);
	else if (errcode == 300)
		ft_putstr_fd("Error\ncode #300: while parsing the map file, the string \
with invalid identifier was found.\nDESCRIPTION: the firsts information in \
each non-empty string must be identifier: 'R', 'NO', 'SO', 'WE', 'EA', 'S', \
'F' or 'C' (splitted from other data by at least one 'space-symbol').\n", 2);
}

static void	f_errors_3(int errcode, t_sdf *opts)
{
	if (errcode == 301)
	{
		ft_putstr_fd("Error\ncode #301: string with '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' identifier occurs more than once in the file.\
\nDESCRIPTION: each options string must be occured only once.\n", 2);
	}
	else if (errcode == 302)
	{
		ft_putstr_fd("Error\ncode #302: invalid string while map parsing \
detected:\n'", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (errcode == 303)
		ft_putstr_fd("Error\ncode #303: empty string after the map detected.\n\
The map must be at the end of file (remove everything after the map).\n", 2);
	else if (errcode == 310)
		ft_putstr_fd("Error\ncode #310: invalid resolution string format.\n\
DESCRIPTION: it must start by 'R' identifier and have only positive integer \
values of X and Y resolution, separated from each other by space-symbol(s).\n\
Examples of valid string:\n'R 1920 1080'\n'R    1024    768'\n", 2);
}

static void	f_errors_4(int errcode, t_sdf *opts)
{
	if (errcode == 311)
	{
		ft_putstr_fd("Error\ncode #311: '", 2);
		ft_putnbr_fd(opts->x_win_size, 2);
		ft_putchar_fd('x', 2);
		ft_putnbr_fd(opts->y_win_size, 2);
		ft_putstr_fd("'- invalid resolution, it must be at least '", 2);
		ft_putnbr_fd(MIN_X_WIN_SIZE, 2);
		ft_putchar_fd('x', 2);
		ft_putnbr_fd(MIN_Y_WIN_SIZE, 2);
		ft_putstr_fd("'.\n", 2);
	}
	else if (errcode == 320)
	{
		ft_putstr_fd("Error\ncode #320: '", 2);
		ft_putstr_fd(opts->err_str, 2);
		ft_putstr_fd("' - invalid texture file path (open/close failed).\
\nCheck that the path to the texture does not start with a space symbol and \
there are no space symbols in the string after the texture name.\n", 2);
	}
}

void		f_print_err(int errcode, t_sdf *opts)
{
	if (errcode < 0)
		ft_putstr_fd(strerror(errno), 2);
	if (errcode < 103)
		f_errors_1(errcode, opts);
	else if (errcode < 301)
		f_errors_2(errcode, opts);
	else if (errcode < 311)
		f_errors_3(errcode, opts);
	else if (errcode < 330)
		f_errors_4(errcode, opts);
	else
		f_print_err_2(errcode, opts);
}
