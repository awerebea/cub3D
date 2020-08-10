/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 10:39:53 by awerebea          #+#    #+#             */
/*   Updated: 2020/08/10 12:44:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	f_get_int_from_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	f_get_a_from_int(int argb)
{
	return ((argb & 0xFF000000) >> 24);
}

int	f_get_r_from_int(int argb)
{
	return ((argb & 0x00FF0000) >> 16);
}

int	f_get_g_from_int(int argb)
{
	return ((argb & 0x0000FF00) >> 8);
}

int	f_get_b_from_int(int argb)
{
	return (argb & 0x000000FF);
}
