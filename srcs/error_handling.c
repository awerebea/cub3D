/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:25:29 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/20 16:33:56 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <string.h>
#include <errno.h>

static void	f_errors_range_1(int errcode)
{
	if (errcode == 1)
		ft_putstr_fd("Error\ncode #1: wrong number of arguments.\n\
DESCRIPTION: There can be only one or two arguments. The first argument MUST \
be a '.cub' file wih map.\nThe second argument CAN be '--save', \
in this case the 'cub3D' just takes screenshot of spawn scene and quits.\n", 2);
	else if (errcode == 2)
		ft_putstr_fd("Error\ncode #2: invalid map file name or path.\n\
DESCRIPTION: the first argument is always the path to the map file, and it \
must have a name with at least one character and an extension '.cub'.\n", 2);
	else if (errcode == 3)
		ft_putstr_fd("Error\ncode #3: wrong second argument.\n\
DESCRIPTION: it can be only '--save', in this case the 'cub3D' just takes \
screenshot of spawn scene and quits.\n", 2);
	else if (errcode == 4)
		ft_putstr_fd("Error\ncode #4: parsing the map file with \
'get_next_line' function failed.\n", 2);
	else if (errcode == 5)
		ft_putstr_fd("Error\ncode #5: while parsing the map file, the string \
with invalid identifier was found.\n\
DESCRIPTION: the firsts information in each non-empty string must be \
identifier: 'R', 'NO', 'SO', 'WE', 'EA', 'S', 'F' or 'C' \
(splitted from other data by at least one 'space-symbol').\n", 2);
}

static void	f_errors_range_2(int errcode)
{
	if (errcode == 6)
		ft_putstr_fd("Error\ncode #6: invalid resolution string format.\n\
DESCRIPTION: there must be 'R' identifier and positive integer values of \
X and Y resolution, separated from each other by space-symbol(s).\n\
Example of valid string: 'R 1920 1080'.\n", 2);
	else if (errcode == 7)
		ft_putstr_fd("Error\ncode #7: invalid resolution, it must be \
in a range from '160x120' (QQVGA) to '7680x4320' (8K).\n", 2);
	else if (errcode == 8)
		ft_putstr_fd("Error\ncode #8: memory allocation failed \
('malloc' function returned 'NULL').\n", 2);
	else if (errcode == 9)
		ft_putstr_fd("Error\ncode #9: invalid north wall texture file name or \
path.\n", 2);
}

void		f_print_err(int errcode)
{
	if (errcode <= 5)
		f_errors_range_1(errcode);
	else if (errcode <= 9)
		f_errors_range_2(errcode);
}
