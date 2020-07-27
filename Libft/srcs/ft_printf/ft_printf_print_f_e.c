/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_f_e.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:13:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/16 15:31:51 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static long double	round_float_and_conv_to_sci(long double val, t_opts *opts)
{
	int			i;
	long double	tmp;

	if (opts->spec == 'e' || opts->spec == 'E')
	{
		tmp = (val < 0) ? -val : val;
		while (tmp >= 10)
		{
			tmp /= 10;
			opts->e_pow++;
		}
		while (val && tmp < 1)
		{
			tmp *= 10;
			opts->e_pow--;
		}
		val = (val < 0) ? -tmp : tmp;
	}
	i = 0;
	tmp = 0.5;
	opts->prec = (!(opts->flags & 32)) ? 6 : opts->prec;
	while (i++ < opts->prec)
		tmp /= 10;
	return (val < 0) ? (val - tmp) : (val + tmp);
}

static int			f_print_fract(t_opts *opts, long double val)
{
	int			count;

	count = 0;
	if (opts->prec || (opts->flags & 2))
		count += f_putchar_count('.', 1);
	if (opts->prec)
	{
		val = (val < 0) ? -(val - (ssize_t)val) : val - (ssize_t)val;
		while (count <= opts->prec)
		{
			val *= 10;
			count += f_putchar_count((int)val + '0', 1);
			val -= (int)val;
		}
	}
	count += (opts->spec == 'e' || opts->spec == 'E') ? \
			f_print_e_pow(opts) : 0;
	return (count);
}

static int			f_flag_minus_zero(t_opts *opts, char *s, long double val, \
		int len)
{
	int			count;
	int			spaces;

	count = 0;
	count += f_print_sign(opts, val);
	spaces = (opts->prec) ? opts->width - count - len - opts->prec - 1 : \
			opts->width - len - count;
	spaces -= ((opts->flags & 2) && (opts->prec == 0)) ? 1 : 0;
	spaces -= (opts->spec == 'e' || opts->spec == 'E') ? 4 : 0;
	if (opts->flags & 16)
	{
		count += f_putstr_count(s, 1);
		count += f_print_fract(opts, val);
		while (spaces-- > 0)
			count += f_putchar_count(' ', 1);
	}
	else if (opts->flags & 1)
	{
		while (spaces-- > 0)
			count += f_putchar_count('0', 1);
		count += f_putstr_count(s, 1);
		count += f_print_fract(opts, val);
	}
	return (count);
}

static int			f_other_cases(t_opts *opts, char *s, long double val, \
		int len)
{
	int			count;
	int			spaces;

	count = 0;
	spaces = (opts->prec) ? opts->width - len - opts->prec - 1 : \
			opts->width - len;
	spaces -= ((opts->flags & 12) || val < 0) ? 1 : 0;
	spaces -= ((opts->flags & 2) && (opts->prec == 0)) ? 1 : 0;
	spaces -= (opts->spec == 'e' || opts->spec == 'E') ? 4 : 0;
	while (spaces-- > 0)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts, val);
	count += f_putstr_count(s, 1);
	count += f_print_fract(opts, val);
	return (count);
}

int					f_print_float_scientific(va_list ap, t_opts *opts)
{
	int			count;
	int			len_int_part;
	long double	val;
	char		*s;

	count = 0;
	val = (opts->subspec & 4) ? va_arg(ap, long double) : va_arg(ap, double);
	val = round_float_and_conv_to_sci(val, opts);
	s = (val < 0 && !(ssize_t)val) ? \
		ft_printf_strdup("-0") : f_llitoa_base((ssize_t)val, 10);
	if (!s)
		return (-1);
	len_int_part = (int)ft_printf_strlen(s);
	len_int_part -= (val < 0) ? 1 : 0;
	s += (val < 0) ? 1 : 0;
	if ((opts->flags & 16) || (opts->flags & 1))
		count = f_flag_minus_zero(opts, s, val, len_int_part);
	else
		count = f_other_cases(opts, s, val, len_int_part);
	(val < 0) ? free(--s) : free(s);
	return (count);
}
