/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_percent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:55:50 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/15 22:13:49 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				f_print_percent(t_opts *opts)
{
	int		count;
	int		spaces;

	count = 0;
	spaces = opts->width - 1;
	count += (opts->flags & 16) ? f_putchar_count('%', 1) : 0;
	while (spaces-- > 0)
		count += ((opts->flags & 17) == 1) ? \
			f_putchar_count('0', 1) : f_putchar_count(' ', 1);
	count += (!(opts->flags & 16)) ? f_putchar_count('%', 1) : 0;
	return (count);
}
