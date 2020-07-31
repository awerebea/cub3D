/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:36:22 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/30 18:45:41 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

void	f_error_mlx(int errcode)
{
	if (errcode == 400)
		ft_printf("Error\ncode #400: mlx_init() fails to set up the connection \
to the X server.");
	else if (errcode == 401)
		ft_printf("Error\ncode #401: mlx_new_window() fails to create a new \
window.");
}
