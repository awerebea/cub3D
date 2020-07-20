/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:25:29 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/20 11:33:37 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <string.h>
#include <errno.h>

void			f_print_error_1_6(int errcode)
{
	if (errcode == 1)
		ft_putstr_fd("Error\ncode #1: wrong number of arguments.\n\
DESCRIPTION: There can be only one or two arguments. The first argument MUST \
be a '.cub' file wih map.\nThe second argument CAN be '--save', \
in this case the 'cub3D' just takes screenshot of spawn scene and quits.\n", 2);
	else if (errcode == 2)
		ft_putstr_fd("Error\ncode #2: wrong name of map file.\n\
DESCRIPTION: the first argument is always the name of the map file, and it \
must have a name with at least one character and an extension '.cub'.\n", 2);
	else if (errcode == 3)
		ft_putstr_fd("Error\ncode #3: wrong second argument.\n\
DESCRIPTION: it can be only '--save', in this case the 'cub3D' just takes \
screenshot of spawn scene and quits.\n", 2);
	else if (errcode == 4)
		ft_putstr_fd("Error\ncode #4: parsing the map file with get_next_line \
function failed.\n", 2);
	else if (errcode == 5)
		ft_putstr_fd("Error\ncode #5: while parsing the map file, the string \
with invalid identifier was found.\nThe firsts information in each non-empty \
string must be identifier: 'R', 'NO', 'SO', 'WE', 'EA', 'S', 'F' or 'C' \
(splitted from other data by at least one 'space-symbol').\n", 2);
	else if (errcode == 6)
		ft_putstr_fd("Error\ncode #6: invalid resolution string format, \
it must be for example: 'R 1920 1080'.\n", 2);
}

void			f_print_error_7_8(int errcode)
{
	if (errcode == 7)
		ft_putstr_fd("Error\ncode #7: invalid resolution, it must be \
in a range from '160x120' (QQVGA) to '7680x4320' (8K).\n", 2);
}
