/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:36:22 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/11 15:52:13 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

void	f_error_mlx(int errcode, t_sdf *opts)
{
	if (errcode == 400)
		ft_printf("Error\ncode #400: mlx_init() fails to set up the connection \
to the X server.");
	else if (errcode == 401)
		ft_printf("Error\ncode #401: mlx_new_window() fails to create a new \
window.");
	else if (errcode == 402)
		ft_printf("Error\ncode #402: mlx_new_image() fails to create a new \
image.");
	else if (errcode == 403)
		ft_printf("Error\ncode #403: mlx_get_data_addr() fails to get the data \
address of the current image.");
	else if (errcode == 410)
		ft_printf("Error\ncode #410: mlx_xpm_file_to_image() failed while \
reading %s texture.", opts->err_string);
}
