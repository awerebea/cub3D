/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_p_u_x_o.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:43:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/16 00:48:01 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		f_print_prefix(t_opts *opts, size_t val)
{
	if (opts->spec == 'p' || ((opts->spec == 'x') && (opts->flags & 2) && val))
		return (f_putstr_count("0x", 1));
	if ((opts->spec == 'X') && (opts->flags & 2) && val)
		return (f_putstr_count("0X", 1));
	if (opts->spec == 'o' && (opts->flags & 2))
	{
		opts->prec -= (opts->prec) ? 1 : 0;
		return (f_putchar_count('0', 1));
	}
	return (0);
}

static int		f_flag_minus_or_zero(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_prefix(opts, val);
		while (opts->prec > len)
			opts->prec -= (count += f_putchar_count('0', 1)) ? 1 : 0;
		count += (!val && ((((opts->flags & 32) && !opts->prec)) || \
		((opts->spec == 'o' && ((opts->flags & 3) == 2) && !opts->prec)))) ? \
				0 : f_putstr_count(s, 1);
		while (count < opts->width)
			count += f_putchar_count(' ', 1);
	}
	else if ((opts->flags & 1) && !(opts->flags & 32))
	{
		count += f_print_prefix(opts, val);
		while (count < opts->width - len)
			count += f_putchar_count('0', 1);
		count += (!val && ((((opts->flags & 32) && !opts->prec)) || \
				((opts->spec == 'o' && ((opts->flags & 3) == 2))))) ? \
					0 : f_putstr_count(s, 1);
	}
	return (count);
}

static int		f_val_zero(t_opts *opts, int len)
{
	int		count;
	int		spaces;

	count = 0;
	if (opts->spec != 'p' && (opts->flags & 12))
		opts->width--;
	if (opts->spec == 'p')
		opts->width -= 2;
	if (opts->prec)
		spaces = opts->width - opts->prec;
	else if (!(opts->flags & 32))
		spaces = opts->width - len;
	else
		spaces = opts->width;
	spaces -= (opts->spec == 'o' && ((opts->flags & 34) == 34) && \
			!opts->prec) ? 1 : 0;
	while (count < spaces)
		count += f_putchar_count(' ', 1);
	count += f_print_prefix(opts, 0);
	while (opts->prec-- >= len)
		count += f_putchar_count('0', 1);
	count += (!(opts->flags & 32) && (!(opts->spec == 'o' && \
					(opts->flags & 34)))) ? f_putchar_count('0', 1) : 0;
	return (count);
}

static int		f_other_cases(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	opts->prec = (len > opts->prec) ? len : opts->prec;
	if ((opts->spec != 'p' && (opts->flags & 12 || val < 0)) || \
			(opts->spec == 'o' && (opts->flags & 2) && opts->prec == len))
		opts->width--;
	if (opts->spec == 'p' || \
			((opts->spec == 'x' || opts->spec == 'X') && (opts->flags & 2)))
		opts->width -= 2;
	while (count < opts->width - opts->prec)
		count += f_putchar_count(' ', 1);
	count += f_print_prefix(opts, val);
	while (opts->prec-- > len)
		count += f_putchar_count('0', 1);
	count += f_putstr_count(s, 1);
	return (count);
}

int				f_print_ptr_uns_hex_oct(va_list ap, t_opts *opts)
{
	int				count;
	size_t			val;
	char			*s;
	int				len;

	count = 0;
	val = f_check_u_o_x_subspec(ap, opts);
	if (opts->spec == 'u')
		s = f_ullitoa_base(val, 10);
	else if (opts->spec == 'o')
		s = f_ullitoa_base(val, 8);
	else if (opts->spec == 'p' || opts->spec == 'x' || opts->spec == 'X')
		s = f_ullitoa_base(val, 16);
	s = (opts->spec == 'X') ? f_strupper(s) : s;
	if (!s)
		return (-1);
	len = (int)ft_printf_strlen(s);
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = f_flag_minus_or_zero(opts, s, val, len);
	else if (!val)
		count = f_val_zero(opts, len);
	else
		count = f_other_cases(opts, s, val, len);
	free(s);
	return (count);
}
