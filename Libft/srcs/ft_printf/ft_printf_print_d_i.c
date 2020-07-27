/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_d_i.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:29:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/16 14:53:14 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		f_flag_minus_zero(t_opts *opts, char *s, ssize_t val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_sign(opts, val);
		while (opts->prec > len)
		{
			count += f_putchar_count('0', 1);
			opts->prec--;
		}
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : f_putstr_count(s, 1);
		while (count < opts->width)
			count += f_putchar_count(' ', 1);
	}
	else if ((opts->flags & 1) && !(opts->flags & 32))
	{
		count += f_print_sign(opts, val);
		while (count < opts->width - len)
			count += f_putchar_count('0', 1);
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : f_putstr_count(s, 1);
	}
	return (count);
}

static int		f_val_zero(t_opts *opts, ssize_t val, int len)
{
	int		count;
	int		spaces;

	count = 0;
	if (opts->flags & 12)
		opts->width--;
	if (opts->prec)
		spaces = opts->width - opts->prec;
	else if (!(opts->flags & 32))
		spaces = opts->width - len;
	else
		spaces = opts->width;
	while (count < spaces)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts, val);
	while (opts->prec-- >= len)
		count += f_putchar_count('0', 1);
	count += (!(opts->flags & 32)) ? f_putchar_count('0', 1) : 0;
	return (count);
}

static int		f_other_cases(t_opts *opts, char *s, ssize_t val, int len)
{
	int		count;

	count = 0;
	opts->prec = (len > opts->prec) ? len : opts->prec;
	if (opts->flags & 12 || val < 0)
		opts->width--;
	while (count < opts->width - opts->prec)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts, val);
	while (opts->prec-- > len)
		count += f_putchar_count('0', 1);
	count += f_putstr_count(s, 1);
	return (count);
}

int				f_print_int(va_list ap, t_opts *opts)
{
	int		count;
	ssize_t	val;
	char	*s;
	int		len;

	if (opts->subspec & 12)
		val = (opts->subspec & 4) ? va_arg(ap, long long) : va_arg(ap, long);
	else if (opts->subspec & 3)
		val = (opts->subspec & 1) ? \
			(signed char)va_arg(ap, int) : (short int)va_arg(ap, int);
	else
		val = va_arg(ap, int);
	s = f_llitoa_base(val, 10);
	len = (int)ft_printf_strlen(s);
	len -= (val < 0) ? 1 : 0;
	s += (val < 0) ? 1 : 0;
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = f_flag_minus_zero(opts, s, val, len);
	else if (!val)
		count = f_val_zero(opts, 0, len);
	else
		count = f_other_cases(opts, s, val, len);
	(val < 0) ? free(--s) : free(s);
	return (count);
}
