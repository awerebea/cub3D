/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shade_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:00:56 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/26 13:11:25 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			f_add_shade(int color, float shade)
{
	return ((int)(f_get_r_from_int(color) * shade) << 16 | \
			(int)(f_get_g_from_int(color) * shade) << 8 | \
			(int)(f_get_b_from_int(color) * shade));
}
